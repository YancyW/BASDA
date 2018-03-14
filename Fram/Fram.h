#pragma once
#ifndef FRAM_H
#define FRAM_H
#include "Class/DrawClass.h"
#include "Analyse/Analyse_Find_Cut.h"
#include "Analyse/Analyse_Pre_Cut.h"
#include "Analyse/Analyse_Direct_Cut.h"
#include "Analyse/Analyse_BDT_Train.h"
#include "Analyse/Analyse_BDT_Attach.h"
#include "Analyse/Analyse_Sensitivity.h"
#include "Analyse/Analyse_Mass_Scan.h"
#include "Analyse/Analyse_Summarize_Plot.h"
#include "Analyse/Analyse_Complete.h"
#include "Analyse/Make_Complete_Table.h"
#include "Lib/Record.h"
	
void Fram(CDraw &para);

#endif
