#pragma once
#ifndef GLOBAL_PARA_SENSITIVITY_H
#define GLOBAL_PARA_SENSITIVITY_H
#include "TStyle.h"
#include <string> 
#include <vector>
#include "yaml-cpp/yaml.h"

#include "RWpara/RWbasic.h"
#include "Class/Path.h"


class CSensitivity{
	private:
	public:
		double ExpCL;
		bool   sig_scale_switch;
		double sig_scale_factor;
		double sig_scale_pow;
		void   Read_Sensitivity(CPath path);
};

#endif
