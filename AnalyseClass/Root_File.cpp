#include "Root_File.h"
/*****************************************************************************************
* Contruction 
*****************************************************************************************/

ARoot_File::ARoot_File(std::string input_file, std::string head_name){
	root_file_vec.push_back(ARoot_File_Single(input_file,head_name));
	_file_num=1;
	_current_file_num=0;
}

ARoot_File::ARoot_File(std::vector<std::string> input_file, std::vector<std::string> head_name){
	_file_num = input_file.size();
	if(_file_num>4){
		//this property is prepared for two beam polarization combination, so the size is limited <=4
		ShowMessage(2,"Error: ARoot_File::ARoot_File, input file size larger than 4");
	}
	for(int i=0;i<_file_num;i++){
		root_file_vec.push_back(ARoot_File_Single(input_file[i],head_name[i]));
	}
}

ARoot_File::ARoot_File(std::vector<std::string> input_file, std::string head_name){
	_file_num = input_file.size();
	if(_file_num>4){
		//this property is prepared for two beam polarization combination, so the size is limited <=4
		ShowMessage(2,"Error: ARoot_File::ARoot_File, input file size larger than 4");
	}
	for(int i=0;i<_file_num;i++){
		root_file_vec.push_back(ARoot_File_Single(input_file[i],head_name));
	}
}

void ARoot_File::Delete(){
	for(int i=0;i<_file_num;i++){
		root_file_vec[i].Delete();
	}
}



/*****************************************************************************************
* Init 
*****************************************************************************************/


void ARoot_File::Init_Var(AVariable &input_var){
	_var =&input_var;
	for(int i=0;i<_file_num;i++){
		root_file_vec[i].Init_Var(_var);
	}
}

void ARoot_File::Init_Para(CDraw& para){
	_event = para.event;
	_scenario = para.scenario;
}

void ARoot_File::Init_Event(){
	CD_File(0);
	_event.Init(root_file_vec[0].Nevent());
}

/*****************************************************************************************
* Return private member value --- _event
 *****************************************************************************************/

AVariable* ARoot_File::Var_Ptr(){
	return(_var);
}

int ARoot_File::File_Num(){
	return(_file_num);
}

int ARoot_File::Current_File_Num(){
	return(_current_file_num);
}
long long int ARoot_File::Event(){
	return(_event.Event());
};

long long int ARoot_File::Total_Event(){
	return(_event.Total_Event());
}

Long64_t ARoot_File::Begin_Event(){
	return(_event.Begin_Event());
}

Long64_t ARoot_File::End_Event(){
	return(_event.End_Event());
}

long int ARoot_File::Nevent(int polnum){
	return(root_file_vec[polnum].Nevent());
}

CScenario ARoot_File::Scenario(){
	return(_scenario);
}

/*****************************************************************************************
 * Register Variable
 *****************************************************************************************/


void ARoot_File::CD_File(int filenum){
	if(filenum>_file_num){
		ShowMessage(2,"Error, in ARoot_File::CD_File, input argument > total file number",_file_num, filenum);
	}
	root_file_vec[filenum].file->cd();
}

void ARoot_File::Register_Var(){
	for(int i=0;i<_file_num;i++){
		root_file_vec[i].Register_Var();
	}
}



/*****************************************************************************************
* Get key value 
*****************************************************************************************/


void ARoot_File::Get_Entry(long int event){
	if(event > root_file_vec[_current_file_num].Nevent()){
		ShowMessage(2,"Error, in ARoot_File::Get_Entry, input argument > total file number",root_file_vec[_current_file_num].Nevent(), event);
	}
	root_file_vec[_current_file_num].Get_Entry(event);
}




bool ARoot_File::Get_Event(long int &num){
	if(num>=_event.Total_Event()){
		_current_file_num++;
		if(_current_file_num>=_file_num){
			return(false);
		}
		CD_File(_current_file_num);
		_event.Init(root_file_vec[_current_file_num].Nevent());
	}
	else{
		_event.Get_Event(num);
	}
	return(true);
};

