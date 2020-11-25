#include "Class/Flow.h"

void CFlow::Print(){
	ShowMessage(2 , "The CFlow is ");
	ShowMessage(3 , "begin_object"     , begin_object        );
	ShowMessage(3 , "signal_property"  , signal_property     );
	ShowMessage(3 , "working_scenario" , working_scenario    );
	ShowMessage(3 , "MVA_method"       , MVA_method          );

	ShowMessage(3 , "cut"              , cut                 );
	ShowMessage(3 , "record_output"    , record_output       );
	ShowMessage(3 , "plot"             , plot                );
	ShowMessage(3 , "plot_object"      , plot_object         );
	ShowMessage(3 , "record_event"     , record_event        );
	ShowMessage(3 , "MVA_training"     , MVA_training        );
	ShowMessage(3 , "MVA_level"        , MVA_level           );
	ShowMessage(3 , "MVA_weight"       , MVA_weight          );
	ShowMessage(3 , "level"            , level               );
}

std::ostream & operator<< (std::ostream & ostr, CFlow str){
	str.Print();
	return ostr;
}

