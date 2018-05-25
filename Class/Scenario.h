#pragma once
#ifndef GLOBAL_PARA_SCENARIO_H
#define GLOBAL_PARA_SCENARIO_H
#include "TStyle.h"
#include <string> 
#include <vector>
#include "yaml-cpp/yaml.h"

#include "Function/Fbasic.h"
#include "RWpara/RWbasic.h"
#include "Class/Path.h"
#include "Class/Flow.h"

class CScenario_Basic{
	public:
	std::string             name;
	float                   energy;
	float                   lumi;
	std::vector<float>      run_ratio;

	CScenario_Basic(){
		name = "";
		energy = 0;
		lumi = 0;
	}
};


class CScenario{
	private:
	public:
		float                   elec_pol;
		float                   posi_pol;
		std::vector<float>      pol     ;

		std::vector<CScenario_Basic> scenario;
		CScenario_Basic         default_scenario;

		CScenario(){
			elec_pol = 0;
			posi_pol = 0;
		}

		~CScenario(){

		}

		void                    Cal_Pol();
		void Read_Scenario      (CPath &path, CFlow &flow);

		CScenario_Basic         Default_Scenario(){
			return(default_scenario);
		}

		std::string Scenario_Name(){
			return(default_scenario.name);
		}

		float Energy(){
			return(default_scenario.energy);
		}

		float Lumi(){
			return(default_scenario.lumi);
		}

		std::string Lumi_Tex(){
	        std::string lumi_tex= " \\int L dt ="+Float_to_String(default_scenario.lumi)+" fb^{-1} ";
			return(lumi_tex);
		}

		std::vector<float> Run_Ratio_Vec(){
			return(default_scenario.run_ratio);
		}

		float Run_Ratio(int i, int j){
			float ratio = 0.0;
			if(i==-1&&j==-1){
				ratio = default_scenario.run_ratio[2];
			}
			else if(i==-1&&j==1){
				ratio = default_scenario.run_ratio[0];
			}
			else if(i==1&&j==-1){
				ratio = default_scenario.run_ratio[1];
			}
			else if(i==1&&j==1){
				ratio = default_scenario.run_ratio[3];
			}
			else{
				ShowMessage(2,"Error: in CScenario::Run_Ratio, no correct pol");
			}

			return(ratio);
		}

		std::string Run_Ratio_Marker(int i, int j){
			std::string ratio = "";
			if(i==-1&&j==-1){
				ratio = "(-,-)";
			}
			else if(i==-1&&j==1){
				ratio = "(-,+)";
			}
			else if(i==1&&j==-1){
				ratio = "(+,-)";
			}
			else if(i==1&&j==1){
				ratio = "(+,+)";
			}
			else{
				ShowMessage(2,"Error: in CScenario::Run_Ratio_Marker, no correct pol");
			}

			return(ratio);
		}
};

namespace YAML{
	template<>
		struct convert<CScenario_Basic>{
			static bool decode(const Node& node, CScenario_Basic& sce){ 
				for(int i=0;i<4;i++){
					sce.run_ratio.push_back(-1.0);
				}
				for(YAML::const_iterator it=node.begin(); it != node.end(); ++it){
					if(it->first.as<std::string>()=="energy"){
						RW_element(it->first.as<std::string>(), it, sce.energy);
					}
					else if(it->first.as<std::string>()=="name"){
						RW_element(it->first.as<std::string>(), it, sce.name);
					}
					else if(it->first.as<std::string>()=="luminosity"){
						RW_element(it->first.as<std::string>(), it, sce.lumi);
					}
					else if(it->first.as<std::string>()=="(-,+)"){
						RW_element(it->first.as<std::string>(), it, sce.run_ratio[0]);
					}
					else if(it->first.as<std::string>()=="(+,-)"){
						RW_element(it->first.as<std::string>(), it, sce.run_ratio[1]);
					}
					else if(it->first.as<std::string>()=="(-,-)"){
						RW_element(it->first.as<std::string>(), it, sce.run_ratio[2]);
					}
					else if(it->first.as<std::string>()=="(+,+)"){
						RW_element(it->first.as<std::string>(), it, sce.run_ratio[3]);
					}
					else{
						ShowMessage(2,"wrong input when load class CScenario_Basic",it->first.as<std::string>());
					}
				}
				if(sce.run_ratio[2]<0.0&&sce.run_ratio[3]<0.0){
					sce.run_ratio.erase(sce.run_ratio.begin()+2,sce.run_ratio.end());
				}
				ShowMessage(2,"finish reading CScenario_Basic ");
				return true;
			}
		};
};
#endif
