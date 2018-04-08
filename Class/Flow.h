#pragma once
#ifndef GLOBAL_PARA_FLOW 
#define GLOBAL_PARA_FLOW
#include "TStyle.h"
#include <string> 
#include <vector>
#include "yaml-cpp/yaml.h"

#include "Lib/MessageFormat.h"
#include "Function/Fbasic.h"
#include "RWpara/RWbasic.h"
#include "Function/Ffile.h"
#include "Class/Path.h"


class CFlow{
	private:
	public:
		Bool_t                  cut                  ;
		Bool_t                  plot                 ;
		std::string             plot_object          ;
		Bool_t                  record_output        ;
		Int_t                   level                ;
		std::string             signal_property      ;
		std::string             working_scenario     ;
		std::string             begin_object         ;
		Bool_t                  record_event         ;
		std::string             MVA_method           ;
		Bool_t                  MVA_training         ;
		Int_t                   MVA_level            ;
	    float                   MVA_weight           ;

		void                    Read_Flow(CPath path);
};

#endif
