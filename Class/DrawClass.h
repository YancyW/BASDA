#pragma once
#ifndef CLASS_DRAW 
#define CLASS_DRAW 
#include "TStyle.h"
#include "TTree.h"
#include "TChain.h"
#include <string> 
#include <vector>
#include "yaml-cpp/yaml.h"

#include "Lib/MessageFormat.h"
#include "Function/Fbasic.h"

#include "Class/File.h"
#include "Class/Flow.h"
#include "Class/Path.h"
#include "Class/debug.h"
#include "Class/Event.h"
#include "Class/Sensitivity.h"
#include "Class/Signal_Properties_Scan.h"
#include "Class/BKG_Sort.h"
#include "Class/Scenario.h"
#include "Class/Plot.h"
#include "Class/Plot_Direct.h"
#include "Class/MVA.h"
#include "Class/Time.h"
#include "AnalyseClass/Variable.h"
#include "Class/Cut_Scan.h"


//-----------------------------------------------------

class CDraw{
	public:
		std::string                  steering_file       ;

		Bool_t                       Jpath               ;
		Bool_t                       Jfile               ;
		Bool_t                       Jdebug              ;
		Bool_t                       Jflow               ;
		Bool_t                       Jevent              ;
		Bool_t                       Jsen                ;
		Bool_t                       Jvar                ;
		Bool_t                       JSP_scan            ;
		Bool_t                       Jbkg_sort           ;
		Bool_t                       Jscenario           ;
		Bool_t                       Jplot               ;
		Bool_t                       Jplot_direct        ;
		Bool_t                       JMVA                ;
		Bool_t                       Jcut_scan           ;

		CPath                        path                ;
		CPath                        default_path        ;

		CFile                        file                ;
		CFile                        default_file        ;

		CDebug                       debug               ;

		CFlow                        flow                ;
		CFlow                        default_flow        ;

		CEvent                       event               ;
		CEvent                       default_event       ;

		CSensitivity                 sensitivity         ;
		CSensitivity                 default_sensitivity ;

		AVariable                    var                 ;
		AVariable                    default_var         ;

		CSignal_Property_Scan        signal_scan         ;
		CSignal_Property_Scan        default_signal_scan ;

		CBKG_Sort                    bkg_sort            ;
		CBKG_Sort                    default_bkg_sort    ;

		CScenario                    scenario            ;
		CScenario                    default_scenario    ;

		CPlot                        plot                ;
		CPlot                        default_plot        ;

		CPlot_Direct                 plot_direct         ;
		CPlot_Direct                 default_plot_direct ;

		CMVA                         MVA                 ;
		CMVA                         default_MVA         ;

		CCut_Scan                    cut_scan            ;
		CCut_Scan                    default_cut_scan    ;

		CTime                        time                ;

		CDraw(int argc, char*argv[]){
			if(argc==2){
				this->steering_file = argv[1];
			}
			else{
				this->steering_file = "control/path.dat";
			}
		}

		void               Read()       ;

		void Get_Event(long long int num){
			event.Get_Event(num);
		};

		long long int Event(){
			return(event.Event());
		};

		long long int Total_Event(){
			return(event.Total_Event());
		}
};
#endif
