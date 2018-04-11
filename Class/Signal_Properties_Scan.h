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


class CSignal_Property_Scan{
	private:
	public:
		Int_t              property_num;
		std::vector<std::string> properties;

		void Read_Signal_Properties_Scan(CPath &path);
};

#endif