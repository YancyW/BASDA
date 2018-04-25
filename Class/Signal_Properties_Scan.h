#pragma once
#ifndef GLOBAL_PARA_SIGNAL_PROPERTY_SCAN_H
#define GLOBAL_PARA_SIGNAL_PROPERTY_SCAN_H
#include "TStyle.h"
#include <string> 
#include <vector>
#include "yaml-cpp/yaml.h"

#include "Function/Fbasic.h"
#include "RWpara/RWbasic.h"
#include "Class/Path.h"
#include "Class/Plot.h"


class CSignal_Property_Scan{
	private:
	public:
		Int_t              property_num;
		std::vector<std::string> properties;
		std::vector<std::string> observables;

		void Read_Signal_Properties_Scan(CPath &path);
		Cplot_line         plot_sig;
		Cplot_line         plot_bkg;
};

#endif
