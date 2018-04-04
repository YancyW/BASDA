#include "Class/MVA.h"
void CMVA::  Read_MVA(CPath path){
	ShowMessage(3, "read MVA");
	YAML::Node MVA_node = YAML::LoadFile(path.MVA_file);
	ShowMessage(1);

	RW_element("MVA_type"          ,MVA_node,this->MVA_type          );
	RW_element("MVA_level"         ,MVA_node,this->MVA_level         );
	RW_element("MVA_weight"        ,MVA_node,this->MVA_weight        );
	RW_element("MVA_event_setting" ,MVA_node,this->MVA_event_setting );
	RW_element("MVA_method_setting",MVA_node,this->MVA_method_setting);

};

