#pragma once
#ifndef ANALYSE_MVA_TRAIN_H
#define ANALYSE_MVA_TRAIN_H
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/DataLoader.h"
#include "TMVA/TMVAGui.h"

#include "Class/DrawClass.h"
#include "Analyse/Abasic.h"
#include "AnalyseClass/File.h"

using namespace TMVA;

void Analyse_MVA_Train_Pre(CDraw &para);
void Analyse_MVA_Train(CDraw &para, AFile &file_name);

#endif
