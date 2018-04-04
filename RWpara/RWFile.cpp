#include "Class/File.h"
void CFile::  Read_File(CPath path){
	ShowMessage(3, "read file");
	YAML::Node file_node = YAML::LoadFile(path.input_file );
	ShowMessage(1);

	RW_element("FILE_NUM"           ,file_node,this->file_num          );
	RW_element("CHANNEL_NUM"        ,file_node,this->channel_num       );
	RW_element("Root_Head_Name"     ,file_node,this->root_head_name    );
	RW_element("Root_Head_MVA_Name" ,file_node,this->root_head_MVA_name);
	RW_element("CHANNEL_NUM"        ,file_node,this->channel_num       );

	for(int i=0;i<file_num;i++){
		RW_vector_element("FILE"         , i, file_node, this->file);
	}
	for(int i=0;i<channel_num;i++){
		RW_vector_element("FILE_DESCRIP" , i, file_node, this->file_descrip);
	}
};

