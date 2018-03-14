#pragma once
#ifndef MAKE_COMPLETE_TABLE_H
#define MAKE_COMPLETE_TABLE_H
#include <string>
#include <vector>
#include "yaml-cpp/yaml.h"

#include "boost/filesystem.hpp"

#include "Latex/LTable.h" 
#include "Latex/LItem.h" 
#include "Class/DrawClass.h"
#include "AnalyseClass/File_List.h" 
#include "AnalyseClass/Sort_List.h" 
#include "Analyse/Make_Table.h" 


void  Print_Complete_Combine(CDraw &para, std::ostream& out, std::vector<std::vector<float> >& final_cut);

float Make_Complete_Table(CDraw &para, float lumi, std::vector<std::string> yaml_file,std::string out_file_name,bool IsRecord,std::vector<float>& final_cut);
void  Make_Complete_Table_Pre(CDraw &para);
#endif
