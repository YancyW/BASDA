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
			if(_list[k].second[l].second.data[1].second!=0){
				tot_num++;
			}
		}
	}
	return(tot_num);
}

float ASort_List::Data_Sig(int k){
	float sig=0;
	for(int j=0;j<Sub_Sort_Num(0);j++){
		sig +=  _list[0].second[j].second.data[k].second;
	}
	return(sig);
}


float ASort_List::Data_Bkg(int k){
	float bkg=0;
	for(int i=1;i<Sort_Num();i++){
		for(int j=0;j<Sub_Sort_Num(i);j++){
			bkg +=  _list[i].second[j].second.data[k].second;
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

void ASort_List::Input_Element(std::vector<std::pair<std::string,int> > sort_name, std::string cut_name, float val){
	if(sort_name.size()!=0){
		Input_Element(sort_name[0].first,sort_name[1].first,cut_name,val);
	}
}

void ASort_List::Input_Element(std::string sort_name, std::string sub_sort_name,std::string cut_name, float val){
	bool get_cut     =false;

	Input_Sub_Sort(sort_name, sub_sort_name);

	for(unsigned int i=0;i<_list.size();i++){
		if(_list[i].first == sort_name){
			for(unsigned int j=0;j<_list[i].second.size();j++){
				if(_list[i].second[j].first == sub_sort_name){
					for(unsigned int k=0;k<_list[i].second[j].second.data.size();k++){
						if(_list[i].second[j].second.data[k].first == cut_name){
							get_cut = true;
							_list[i].second[j].second.data[k].second += val;
						}
					}
					if(!get_cut){
						_list[i].second[j].second.Input_Element(cut_name,val);
					}
				}
			}
		}
	}
}

void ASort_List::Input_Sub_Sort(std::string sort_name, std::string sub_sort_name){
	bool get_sub_sort=false;

	Input_Sort(sort_name);

	for(unsigned int i=0;i<_list.size();i++){
		if(_list[i].first == sort_name){
			for(unsigned int j=0;j<_list[i].second.size();j++){
				if(_list[i].second[j].first == sub_sort_name){
					get_sub_sort = true;
				}
			}
			if(!get_sub_sort){
				std::pair< std::string, AFile_Data > new_sub_sort;
				new_sub_sort.first = sub_sort_name;
				_list[i].second.push_back(new_sub_sort);
			}
		}
	}
}

void ASort_List::Input_Sort(std::string sort_name){
	bool get_sort    =false;

	for(unsigned int i=0;i<_list.size();i++){
		if(_list[i].first == sort_name){
			get_sort = true;
		}
	}
	if(!get_sort){
		std::pair<std::string,std::vector< std::pair< std::string, AFile_Data> > > new_sort;
		new_sort.first = sort_name;
		_list.push_back(new_sort);
	}
}

