#pragma once
#ifndef AANALYSE_SENSITIVITY_H
#define AANALYSE_SENSITIVITY_H
#include <iostream>
#include <TFile.h>
#include <TH1D.h>
#include <TRandom3.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TColor.h>
#include <TLimit.h>
#include <TConfidenceLevel.h>
#include "TSysLimit/TSysLimitChannel.h"
#include "TSysLimit/TSysLimit.h"
#include "TSysLimit/TSysLimitResult.h"
#include "TSysLimit/TSysLimitScan.h"
#include "TTree.h"
#include "THStack.h"
#include "TImage.h"
#include "TLegend.h"

#include "Class/DrawClass.h"
#include "AnalyseClass/File.h"
#include "AnalyseClass/Plot.h"



void Analyse_Sensitivity_Pre(CDraw &para);
void Analyse_Sensitivity_Complete(CDraw &para);
//void Analyse_Sensitivity(CDraw &para, std::vector<std::string> input_sigfile_name, std::vector<std::string> input_bkgfile_name, std::string output_file_name, std::string output_folder);
void Analyse_Sensitivity(CDraw &para, APlot &plot, std::string output_file_name, std::string output_folder);
#endif
