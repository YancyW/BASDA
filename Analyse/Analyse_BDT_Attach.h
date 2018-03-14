#pragma once
#ifndef ANALYSE_BDT_ATTACH_H
#define ANALYSE_BDT_ATTACH_H
#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TTreeFormula.h"

#include "TMVA/Reader.h"
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/MethodCuts.h"

#include "Class/DrawClass.h"
#include "Analyse/Abasic.h"
#include "AnalyseClass/File.h"

void Analyse_BDT_Attach_Pre(CDraw &para);
void Analyse_BDT_Attach(CDraw &para, AFile &file_name);
#endif
