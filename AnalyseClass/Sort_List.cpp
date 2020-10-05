#include "Sort_List.h"

int ASort_List::Total_Sort_Num(){
	int tot_num=0;
	for(unsigned int k=0;k<_list.size();k++){
		for(unsigned int l=0;l<_list[k].second.size();l++){
			tot_num++;
		}
	}
	return(tot_num);
}

int ASort_List::Total_Unzero_Sort_Num(){
	int tot_num=0;
	for(unsigned int k=0;k<_list.size();k++){
		for(unsigned int l=0;l<_list[k].second.size();l++){
			int pos=Data_Pos(k,l);
			if(_list[k].second[l].second.Data_Content(pos+1)!=0){
				tot_num++;
			}
		}
	}
	return(tot_num);
}

float ASort_List::Data_Sig(int k){
	float sig=0;
	for(int j=0;j<Sub_Sort_Num(0);j++){
		int pos=Data_Pos(0,j)-1;
		sig +=  _list[0].second[j].second.data[pos+k].second;
	}
	return(sig);
}


float ASort_List::Data_Bkg(int k){
	float bkg=0;
	for(int i=1;i<Sort_Num();i++){
		if(_list[i].first=="Significance"||_list[i].first=="Efficiency"||_list[i].first=="Improvement"||_list[i].first=="Total Background"){
			continue;
		}
		for(int j=0;j<Sub_Sort_Num(i);j++){
			int pos=Data_Pos(i,j)-1;
			bkg +=  _list[i].second[j].second.data[pos+k].second;
		}
	}
	return(bkg);
}

std::vector<float> ASort_List::Data_Final(){
	std::vector<float> final_data;
	int last_row=Data_Num()-1;

	for(int i=0;i<Sort_Num();i++){
		for(int j=0;j<Sub_Sort_Num(i);j++){
			final_data.push_back(_list[i].second[j].second.data[last_row].second);
		}
	}
	return(final_data);
}

float ASort_List::Significance(){
	int   last_num = Last_Data_Num();
	float sig      = Get_Significance(Data_Sig(last_num),Data_Bkg(last_num));

	return(sig);
}

float ASort_List::Significance(int i){
	float sig      = Get_Significance(Data_Sig(i),Data_Bkg(i));

	return(sig);
}

float ASort_List::Relative_Improvement(int i){
	if(i==1){
		return(0);
	}
	float sig_old  = Get_Significance(Data_Sig(i-1),Data_Bkg(i-1));
	float sig_new  = Get_Significance(Data_Sig(i),Data_Bkg(i));

	return(sig_new/sig_old);
}


float ASort_List::Efficiency(){
	int   last_num = Last_Data_Num();
	int   pos=Data_Pos(0,0);
	float sig      = Get_Efficiency(Data_Sig(last_num),Data_Sig(pos));
	return(sig);
}

float ASort_List::Efficiency(int i){
	int   pos=Data_Pos(0,0);
	float sig      = Get_Efficiency(Data_Sig(i),Data_Sig(pos));
	return(sig);
}

void ASort_List::Input_Element(CBKG_Sort input_sort){
	for(int i=0;i<input_sort.Num();i++){
		for(int j=0;j<input_sort.sort[i].Sub_Num();j++){
			std::string sort_name=input_sort.sort[i].Class();
			std::string sub_sort_name=input_sort.sort[i].Sub_Class()[j];
			Input_Single_Element(_list,sort_name,sub_sort_name,"None",0);

    		std::string default_sort_name=input_sort.sort[i].Default_Legend(0);
    		std::string default_sub_sort_name=input_sort.sort[i].Legend(j);
    		Input_Single_Element(_default_list,default_sort_name,default_sub_sort_name,"None",0);
		}
	}
}

void ASort_List::Input_Element(std::vector<std::pair<std::string,int> > sort_name, std::string cut_name, float val){
	if(sort_name.size()!=0){
		Input_Single_Element(_list, sort_name[0].first,sort_name[1].first,cut_name,val);
	}
}

void ASort_List::Input_Element(std::vector<std::pair<std::string,float> > sort_name, std::string cut_name, float val){
	if(sort_name.size()!=0){
		Input_Single_Element(_list, sort_name[0].first,sort_name[1].first,cut_name,val);
	}
}

void ASort_List::Input_Single_Element(ASort_List_Type  &out_list, std::string sort_name, std::string sub_sort_name,std::string cut_name, float val){
	bool get_cut     =false;

	Input_Sub_Sort(out_list, sort_name, sub_sort_name);

	
	for(unsigned int i=0;i<out_list.size();i++){
		if(out_list[i].first == sort_name){
			for(unsigned int j=0;j<out_list[i].second.size();j++){
				if(out_list[i].second[j].first == sub_sort_name){
					for(unsigned int k=0;k<out_list[i].second[j].second.data.size();k++){
						if(out_list[i].second[j].second.data[k].first == cut_name){
							get_cut = true;
							out_list[i].second[j].second.data[k].second += val;
						}
					}
					if(!get_cut){
						out_list[i].second[j].second.Input_Element(cut_name,val);
					}
				}
			}
		}
	}
}

void ASort_List::Input_Sub_Sort(ASort_List_Type  &out_list, std::string sort_name, std::string sub_sort_name){
	bool get_sub_sort=false;

	Input_Sort(out_list, sort_name);

	for(unsigned int i=0;i<out_list.size();i++){
		if(out_list[i].first == sort_name){
			for(unsigned int j=0;j<out_list[i].second.size();j++){
				if(out_list[i].second[j].first == sub_sort_name){
					get_sub_sort = true;
				}
			}
			if(!get_sub_sort){
				std::pair< std::string, AFile_Data > new_sub_sort;
				new_sub_sort.first = sub_sort_name;
				out_list[i].second.push_back(new_sub_sort);
			}
		}
	}
}

void ASort_List::Input_Sort(ASort_List_Type  &out_list, std::string sort_name){
	_exist = true;
	bool get_sort    =false;

	for(unsigned int i=0;i<out_list.size();i++){
		if(out_list[i].first == sort_name){
			get_sort = true;
		}
	}
	if(!get_sort){
		std::pair<std::string,std::vector< std::pair< std::string, AFile_Data> > > new_sort;
		new_sort.first = sort_name;
		out_list.push_back(new_sort);
	}
}

void ASort_List::Add_Sort(std::string sort_name, std::string sub_sort_name, AFile_Data input_data){
	ASort_Type sort_type; 
	sort_type.first=sort_name;
		ASub_Sort_Type sub_sort_type; 
		sub_sort_type.first=sub_sort_name;
		sub_sort_type.second=input_data;
	sort_type.second.push_back(sub_sort_type);

	_exist = true;
	_list.push_back(sort_type);
}


void ASort_List::Add_Name(std::string pre_name, std::string post_name){
	for(int k=0;k<Sort_Num();k++){
		if(_list[k].first=="Significance"||_list[k].first=="Efficiency"||_list[k].first=="Improvement"||_list[k].first=="Total Background"){
			continue;
		}
		for(int l=0;l<Sub_Sort_Num(k);l++){
			_list[k].second[l].first=pre_name+_list[k].first+"_"+_list[k].second[l].first+post_name;
		}
	}
}

ASort_Type ASort_List::Get_Sort(std::string sort_name){
	int pos=-1;
	for(unsigned int i=0;i<_list.size();i++){
		if(_list[i].first == sort_name){
			pos = i;
			break;
		}
	}
	if(pos==-1){
		ASort_Type tmp;
		return(tmp);
	}
	else{
		return(_list[pos]);
	}
}


//if having duplicated sub sort name in different sorts, then only return the first one!!!
ASub_Sort_Type ASort_List::Get_Sub_Sort(std::string sub_sort_name){
	int pos=-1;
	int sub_pos=-1;
	for(unsigned int i=0;i<_list.size();i++){
		for(unsigned int j=0;j<_list[i].second.size();j++){
			if(_list[i].second[j].first == sub_sort_name){
				pos = i;
				sub_pos = j;
				break;
			}
		}
		if(sub_pos!=-1){
			break;
		}
	}
	if(pos==-1){
		ASub_Sort_Type tmp;
		return(tmp);
	}
	else{
		return(_list[pos].second[sub_pos]);
	}
}



AFile_Data ASort_List::Get_Row_Data(std::string row_name){
	AFile_Data out_data;

	for(unsigned int i=0;i<_list.size();i++){
		for(unsigned int j=0;j<_list[i].second.size();j++){
			int pos=Data_Pos(i,j);
			for(int k=pos;k<_list[i].second[j].second.Data_Num();k++){
				if(_list[i].second[j].second.Data_Name(k)==row_name){
					out_data.Input_Element(Full_Sort_Name(i,j),_list[i].second[j].second.Data_Content(k));
				}
			}
		}
	}

	return(out_data);
}


void ASort_List::Print(int i, bool has_title){
	if(has_title){
		ShowMessage(i,"The sort is","");
	}
	for(int k=0;k<Sort_Num();k++){
		ShowMessage(i,"sort name",Sort_Name(k));
		for(int l=0;l<Sub_Sort_Num(k);l++){
			ShowMessage(i+1,"sub sort name",Sub_Sort_Name(k,l),k,l);
			Sub_Sort_Content(k,l).Print(i+1);
			
		}
	}
}

void ASort_List::Set_Sort(std::string input_name){
	Set_Data_Pos(input_name);
	int pos=Data_Pos(0,0);
	for(int k=pos;k<_list[0].second[0].second.Data_Num();k++){
		Input_Single_Element(_list, "Total Background", "BKG", Data_Name(k), Data_Bkg(k));
		Input_Single_Element(_list, "Efficiency", "E", Data_Name(k), Efficiency(k));
		Input_Single_Element(_list, "Improvement", "I", Data_Name(k), Relative_Improvement(k));
		Input_Single_Element(_list, "Significance", "S", Data_Name(k), Significance(k));
	}
}
