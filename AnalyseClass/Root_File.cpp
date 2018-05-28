#include "Root_File.h"

ARoot_File::ARoot_File(std::string input_file, std::string head_name){
	Read(input_file, head_name);
}

void ARoot_File::Read(std::string input_file, std::string head_name){
	file  = new TFile(input_file.c_str());
	file  ->cd();
	tree  =(TTree*)file->Get(head_name.c_str());
	nevent= tree->GetEntries();
}

void ARoot_File::Delete(){
	ShowMessage(2,"file is deleting",file->GetName());
	file   ->cd();
	nevent =0;
	delete tree;
	delete file;
}

ARoot_File::~ARoot_File(){
}

void ARoot_File::SetBranchAddress(std::string var_name, float* var){
	tree->SetBranchAddress(var_name.c_str(), var);
}

void ARoot_File::SetBranchAddress(std::string var_name, double* var){
	tree->SetBranchAddress(var_name.c_str(), var);
}

void ARoot_File::SetBranchAddress(std::string var_name, long int* var){
	tree->SetBranchAddress(var_name.c_str(), var);
}

void ARoot_File::GetEntry(int event){
	tree->GetEntry(event);
}

void ARoot_File::Init_Var(AVariable &input_var){
	_var = &input_var;
}

void ARoot_File::Init_Weight(Analyse_Single_File& input_weight){
	_in_weight   = &(input_weight.in_weight);
	_in_weight_d = &(input_weight.in_weight_d);
	_in_weight_i = &(input_weight.in_weight_i);
}

void ARoot_File::Register_Var(){
		if(_var->weight_exist){
			if(_var->weight_type=="F"){
				SetBranchAddress("weight", _in_weight);
			}
			else if(_var->weight_type=="D"){
				SetBranchAddress("weight", _in_weight_d);
			}
			else if(_var->weight_type=="I"){
				SetBranchAddress("weight", _in_weight_i);
			}
		}
		else{
//			*in_weight = file_name.input[j].xection[0]/in_file[j].nevent;  
		}

		for(int k=0;k<_var->num;k++){
			if(_var->var[k].title_name=="weight"){
				continue;
			}
			if(_var->var[k].variable_type=="F"){
				SetBranchAddress(_var->var[k].title_name.c_str(), &(_var->var[k].variable));
			}
			else if(_var->var[k].variable_type=="I"){
				SetBranchAddress(_var->var[k].title_name.c_str(), &(_var->var[k].variable_i));
			}
			else if(_var->var[k].variable_type=="D"){
				SetBranchAddress(_var->var[k].title_name.c_str(), &(_var->var[k].variable_d));
			}
		}
}
