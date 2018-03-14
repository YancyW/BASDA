#include "Class/Sensitivity.h"
#include "Function/Fbasic.h"

void CSensitivity:: Read_Sensitivity(CPath path){
	ShowMessage(3, "read Sensitivity");
	YAML::Node sen_node= YAML::LoadFile(path.sensitivity_file);

	RW_element("ExpCL"     ,sen_node,this->ExpCL);
	RW_element("sig_scale_switch" ,sen_node,this->sig_scale_switch);
	RW_element("sig_scale_factor" ,sen_node,this->sig_scale_factor);
	RW_element("sig_scale_pow"    ,sen_node,this->sig_scale_pow    );
}

