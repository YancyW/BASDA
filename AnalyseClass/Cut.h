#pragma once
#ifndef GLOBAL_PARA_CUT_H
#define GLOBAL_PARA_CUT_H
#include "TStyle.h"
#include <string> 
#include <vector>
#include "yaml-cpp/yaml.h"

#include "Function/Fbasic.h"
#include "RWpara/RWbasic.h"
#include "Class/Path.h"
#include "Class/DrawClass.h"


class ACut{
	private:
	public:
		int cut_num;
		int pre_cut_num;
		std::vector<int> cut;
		std::vector<int> pre_cut;

		void Read_Cut(CPath &path);
};


#endif
