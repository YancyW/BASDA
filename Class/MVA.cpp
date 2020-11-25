#include "Class/MVA.h"

void CMVA_Basic::Print(){
	ShowMessage(2 , "The CMVA_Basic is ");
	ShowMessage(2,"MVA_type",MVA_type            );
	ShowMessage(2,"MVA_level",MVA_level           );
	ShowMessage(2,"MVA_weight",MVA_weight          );
	ShowMessage(2,"MVA_event_setting",MVA_event_setting   );
	ShowMessage(2,"MVA_method_setting",MVA_method_setting  );
	ShowMessage(2,"MVA_factory_setting",MVA_factory_setting );
}
void CMVA::Print(){
	ShowMessage(2 , "The default CMVA is ");
	default_mva.Print();
}


std::ostream & operator<< (std::ostream & ostr, CMVA_Basic str){
	str.Print();
	return ostr;
}

std::ostream & operator<< (std::ostream & ostr, CMVA str){
	str.Print();
	return ostr;
}

