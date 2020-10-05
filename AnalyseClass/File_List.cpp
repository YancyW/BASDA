#include "File_List.h"

void AFile_Data::Input_Element(std::string cut_name, float val){
	if(data.size()!=0){
		if(data.back().first=="None"){
			data.back().first=cut_name;
			data.back().second=val;
			return;
		}
	}
	data.push_back(std::make_pair(cut_name,val));
}

void AFile_Data::Print(int i,bool has_title){
	if(has_title){
		ShowMessage(i,"The File Data is","");
	}
	if(Data_Num()<1){return;}
	if(Data_Name(0)=="None"){return;}

	ShowMessage(i+1,"cut name","cut value");
	for(int l=0;l<Data_Num();l++){
		ShowMessage(i+1,Data_Name(l),Data_Content(l));
	}
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

void AFile_List::Print(int i,bool has_title){
	if(has_title){
		ShowMessage(i,"The File is","");
	}
	for(int k=0;k<File_Num();k++){
		ShowMessage(i+1,"file name",File_Name(k));
		File_Content(k).Print(i+1,has_title);
	}
}

