#include "Class/Scenario.h"

void CScenario_Basic::Print(){
	ShowMessage(2 , "The CScenario_Basic is ");
	ShowMessage(3 , "name"                      , name      );
	ShowMessage(3 , "energy"                    , energy    );
	ShowMessage(3 , "lumi"                      , lumi      );

	for(unsigned int i=0;i<run_ratio.size();i++){
		ShowMessage(4 , "run_ratio"                 , run_ratio[i] );
	}
}


void CScenario::Print(){
	ShowMessage(2 , "The CScenariois ");
	ShowMessage(3 , "elec_pol"                   , elec_pol);
	ShowMessage(3 , "posi_pol"                   , posi_pol);

	for(unsigned int i=0;i<pol.size();i++){
		ShowMessage(4 , "pol"                 , pol[i] );
	}

	ShowMessage(3 , "The default_scenario is:", default_scenario);
}


std::ostream & operator<< (std::ostream & ostr, CScenario_Basic str){
	str.Print();
	return ostr;
}

std::ostream & operator<< (std::ostream & ostr, CScenario str){
	str.Print();
	return ostr;
}


