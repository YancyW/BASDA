#pragma once
#ifndef GLOBAL_PARA_MASS_SCAN_H
#define GLOBAL_PARA_MASS_SCAN_H
#include "TStyle.h"
#include <string> 
#include <vector>
#include "yaml-cpp/yaml.h"

#include "Function/Fbasic.h"
#include "RWpara/RWbasic.h"
#include "Class/Path.h"


class CMass_Scan{
	private:
	public:
		Int_t              mass_num;
		std::vector<float> mass;

		void Read_Mass_Scan(CPath &path);
};

#endif
