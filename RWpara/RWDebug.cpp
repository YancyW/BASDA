#include "Class/debug.h"
void CDebug::  Read_Debug(CPath path){
	ShowMessage(3, "read debug");
	YAML::Node debug_node = YAML::LoadFile(path.debug_file );

	RW_element("Debug_mode"                 ,debug_node,this->mode );
	RW_element("Debug_mode_num"             ,debug_node,this->num_debug_mode  );
	RW_element("Debug_level"                ,debug_node,this->level);

	ShowMessage(1);

	for(int i=0;i<this->num_debug_mode;i++){
		RW_vector_element("Debug"       , i, debug_node,  this->debug);
	}
}


