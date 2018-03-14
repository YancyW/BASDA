#include "File_List.h"

void AFile_Data::Input_Element(std::string cut_name, float val){
	data.push_back(std::make_pair(cut_name,val));
}

void AFile_List::Input_Element(AFile_Data file){
	std::string str = file.data[0].first;
	_list.push_back(std::make_pair(str,file));
}

float AFile_List::Data_Bkg(int k){
	float bkg=0;
	for(int i=1;i<File_Num();i++){
		bkg +=  _list[i].second.data[k].second;
	}
	return(bkg);
}

