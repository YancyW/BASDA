#pragma once
#ifndef GLOBAL_PARA_PATH 
#define GLOBAL_PARA_PATH
#include "TStyle.h"
#include <string> 
#include <vector>
#include "yaml-cpp/yaml.h"

#include "Lib/MessageFormat.h"
#include "Function/Fbasic.h"
#include "RWpara/RWbasic.h"
#include "Function/Ffile.h"


class CPath{
	private:
	public:
		std::string   process          ;
		std::string   output_folder    ;

		std::string   record_file      ;

		std::string   output_file      ;
		std::string   event_file       ;
		std::string   single_plot      ;
		std::string   combine_plot     ;
		std::string   horizontal_summary_plot;

		std::string   input_file       ;
		std::string   debug_file       ;
		std::string   analyse_file     ;
		std::string   flow_file        ;
		std::string   cut_file         ;
		std::string   plot_file        ;
		std::string   MVA_file         ;

		std::string   var_file         ;
		std::string   sensitivity_file ;
		std::string   mass_scan_file   ;
		std::string   bkg_sort_file    ;
		std::string   scenario_file    ;

		void          Read_Path(std::string steering_file)  ;
		void          Create_Folder()  ;
};

#endif
