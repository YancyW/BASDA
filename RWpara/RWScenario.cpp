#include "Class/Scenario.h"
#include "Function/Fbasic.h"
#include "RWpara/RWbasic.h"

void CScenario:: Read_Scenario(CPath &path, CFlow &flow){
	ShowMessage(3, "read Scenario");
	YAML::Node scenario_node = YAML::LoadFile(path.scenario_file);

	RW_element("elec_pol" ,scenario_node,this->elec_pol);
	RW_element("posi_pol" ,scenario_node,this->posi_pol);

    Cal_Pol();

	YAML::Node nodes = scenario_node["Scenario"];
	for(YAML::const_iterator it=nodes.begin(); it != nodes.end(); ++it){
		ShowMessage(3, "scenario name",it->first.as<std::string>());
		this->scenario.push_back(it->second.as<CScenario_Basic>());
	}

	bool get_scenario=false;
	for(unsigned int i=0;i<=scenario.size();i++){
		if(flow.working_scenario == this->scenario[i].name){
			this->default_scenario = this->scenario[i];
			get_scenario = true;
			break;
		}
	}
	if(!get_scenario){
		ShowMessage(2,"do NOT have correct running scenario");
		exit(0);
	}
}

void CScenario::Cal_Pol(){
	pol.clear();
	float elecl=(1 - elec_pol)/2;
	float elecr=(1 + elec_pol)/2;
	float posil=(1 - posi_pol)/2;
	float posir=(1 + posi_pol)/2;

	pol.push_back( elecl * posir);
	pol.push_back( elecr * posil);
	pol.push_back( elecl * posil);
	pol.push_back( elecr * posir);
}
