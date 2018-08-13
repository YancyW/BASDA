#include "Class/Sensitivity.h"

void CSensitivity::Print(){
	ShowMessage(2,"The CSensitivity is ");
	ShowMessage(3,"ExpCL",ExpCL           );
	ShowMessage(3,"sig_scale_switch",sig_scale_switch);
	ShowMessage(3,"sig_scale_factor",sig_scale_factor);
	ShowMessage(3,"sig_scale_pow"   ,sig_scale_pow   );
}
