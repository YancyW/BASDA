#pragma once
#ifndef MAKE_COMPLETE_EFFICIENCY_PLOT_H
#define MAKE_COMPLETE_EFFICIENCY_PLOT_H
#include <string>
#include <vector>
#include "yaml-cpp/yaml.h"

#include "boost/filesystem.hpp"

#include "Latex/LTable.h" 
#include "Latex/LItem.h" 
#include "Class/DrawClass.h"
#include "AnalyseClass/File_List.h" 
#include "AnalyseClass/Sort_List.h" 
#include "Analyse/Make_Efficiency_Plot.h" 


void  Make_Complete_Efficiency_Plot_Pre(CDraw &para);
#endif
