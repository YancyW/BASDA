#pragma once
#ifndef MAKE_TABLE_H
#define MAKE_TABLE_H
#include <string>
#include <vector>
#include "yaml-cpp/yaml.h"

#include "boost/filesystem.hpp"

#include "Latex/LTable.h" 
#include "Latex/LItem.h" 
#include "Class/DrawClass.h"
#include "AnalyseClass/File_List.h" 
#include "AnalyseClass/Sort_List.h" 


void  Print_Complete_Channel(CDraw &para, float lumi, std::ostream& out, AFile_List &fileList, ASort_List& data);
void  Print_Complete_Sort   (CDraw &para, std::ostream& out, ASort_List& data);

float Make_Table(CDraw &para, float lumi,  std::vector<std::string> yaml_file,std::string out_file);
void  Make_Table_Pre(CDraw &para);
#endif
