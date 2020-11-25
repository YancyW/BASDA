#pragma once
#ifndef CMVA_H
#define CMVA_H
#include "yaml-cpp/yaml.h"

#include "RWpara/RWbasic.h"
#include "Class/Path.h"
#include "Class/Flow.h"
#include "Lib/MessageFormat.h"

class CMVA_Basic{
	private:
	public:
		std::string             MVA_type             ;
		Int_t                   MVA_level            ;
	    float                   MVA_weight           ;
		std::string             MVA_event_setting    ;
		std::string             MVA_method_setting   ;
		std::string             MVA_factory_setting  ;

		void                    Print()              ;
};


class CMVA{
	private:
	public:
		std::vector<CMVA_Basic> mva;
		CMVA_Basic              default_mva;

		std::string MVA_Type             (){
			return(default_mva.MVA_type);
		}
		Int_t       MVA_Level            (){
			return(default_mva.MVA_level);
		}
	    float       MVA_Weight           (){
			return(default_mva.MVA_weight);
		}
		std::string MVA_Event_Setting    (){
			return(default_mva.MVA_event_setting);
		}
		std::string MVA_Method_Setting   (){
			return(default_mva.MVA_method_setting);
		}
		std::string MVA_Factory_Setting  (){
			return(default_mva.MVA_factory_setting);
		}

		void        Read_MVA(CPath &path, CFlow &flow);
		void        Print();
};


namespace YAML{
	template<>
		struct convert<CMVA_Basic>{
			static bool decode(const Node& node, CMVA_Basic& mva){ 
				for(YAML::const_iterator it=node.begin(); it != node.end(); ++it){
					if(it->first.as<std::string>()=="MVA_type"){
						RW_element(it->first.as<std::string>(), it, mva.MVA_type);
					}
					else if(it->first.as<std::string>()=="MVA_level"){
						RW_element(it->first.as<std::string>(), it, mva.MVA_level);
					}
					else if(it->first.as<std::string>()=="MVA_weight"){
						RW_element(it->first.as<std::string>(), it, mva.MVA_weight);
					}
					else if(it->first.as<std::string>()=="MVA_event_setting"){
						RW_element(it->first.as<std::string>(), it, mva.MVA_event_setting);
					}
					else if(it->first.as<std::string>()=="MVA_method_setting"){
						RW_element(it->first.as<std::string>(), it, mva.MVA_method_setting);
					}
					else{
						ShowMessage(2,"wrong input when load class CMVA_Basic",it->first.as<std::string>());
					}
				}
				ShowMessage(2,"finish reading CMVA_Basic");
				return true;
			}
		};
};


std::ostream & operator<< (std::ostream & ostr, CMVA_Basic str);
std::ostream & operator<< (std::ostream & ostr, CMVA str);
#endif
