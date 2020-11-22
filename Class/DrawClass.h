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
#include "Class/Debug.h"
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

		CPath                        path                ;
		CPath                        default_path        ;
		Bool_t                       Jpath               ;

		CFile                        file                ;
		CFile                        default_file        ;
		Bool_t                       Jfile               ;

		CDebug                       debug               ;
		Bool_t                       Jdebug              ;

		CFlow                        flow                ;
		CFlow                        default_flow        ;
		Bool_t                       Jflow               ;

		CEvent                       event               ;
		CEvent                       default_event       ;
		Bool_t                       Jevent              ;

		CSensitivity                 sensitivity         ;
		CSensitivity                 default_sensitivity ;
		Bool_t                       Jsen                ;

		AVariable                    var                 ;
		AVariable                    default_var         ;
		Bool_t                       Jvar                ;

		CSignal_Property_Scan        signal_scan         ;
		CSignal_Property_Scan        default_signal_scan ;
		Bool_t                       JSP_scan            ;

		CBKG_Sort                    bkg_sort            ;
		CBKG_Sort                    default_bkg_sort    ;
		Bool_t                       Jbkg_sort           ;

		CScenario                    scenario            ;
		CScenario                    default_scenario    ;
		Bool_t                       Jscenario           ;

		CPlot                        plot                ;
		CPlot                        default_plot        ;
		Bool_t                       Jplot               ;

		CPlot_Direct                 plot_direct         ;
		CPlot_Direct                 default_plot_direct ;
		Bool_t                       Jplot_direct        ;

		CMVA                         MVA                 ;
		CMVA                         default_MVA         ;
		Bool_t                       JMVA                ;

		CCut_Scan                    cut_scan            ;
		CCut_Scan                    default_cut_scan    ;
		Bool_t                       Jcut_scan           ;


		CTime                        time                ;

		CDraw(int argc, char*argv[]){
			if(argc==2){
				this->steering_file = argv[1];
			}
			else{
				this->steering_file = "control/path.dat";
			}
			std::cout<<"input file " << this->steering_file << std::endl;
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

		void Print();
};


std::ostream & operator<< (std::ostream & ostr, CDraw str);
#endif
