#pragma once
#include <string> 
#include <iostream>
#include "TH1.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TChain.h"


#include "yaml-cpp/yaml.h"

#include "Class/DrawClass.h"
#include "Lib/PlotSetting.h"
#include "Lib/MessageFormat.h"

void StartProcess();
void LoadFile(CDraw &para);
void LoadLibrary(CDraw &para);
void SetPlot();
void EndProcess();
