#pragma once
#ifndef ANALYSE_SUMMARIZE_SENSITIVITY_H
#define ANALYSE_SUMMARIZE_SENSITIVITY_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <string>
#include <vector>
#include <inttypes.h>
#include "yaml-cpp/yaml.h"
#include <cmath>


#include "Function/Fbasic.h" 
#include "Function/Ffile.h" 
#include "Lib/MessageFormat.h"
#include "Class/DrawClass.h"
#include "AnalyseClass/AnalyseClass.h"
#include "AnalyseClass/Plot.h"
#include "Abasic.h"
#include "Make_Table.h"
#include "AnalyseClass/File.h"


void Analyse_Summarize_Sensitivity_Pre(CDraw &para);

void Analyse_Summarize_Separate_Sensitivity_Pre(CDraw &para);

void Analyse_Summarize_Sensitivity(CDraw &para, std::vector<std::string> &sig_name);

void Analyse_Get_Exclusion_Limits(CDraw& para, std::string out_file_path);
#endif
