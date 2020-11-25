#include "Class/File.h"

void CFile::Print(){
	ShowMessage(2,"The CFile is ");
	ShowMessage(3,"file_num"          ,file_num          );
	ShowMessage(3,"channel_num"       ,channel_num       );
	ShowMessage(3,"root_head_name"    ,root_head_name    );
	ShowMessage(3,"root_head_MVA_name",root_head_MVA_name);
	for(int i=0;i<file_num;i++){
		ShowMessage(4,"file is "           ,file[i]        );
		ShowMessage(4,"file descripion is ",file_descrip[i]);
	}
}


std::ostream & operator<< (std::ostream & ostr, CFile str){
	str.Print();
	return ostr;
}

