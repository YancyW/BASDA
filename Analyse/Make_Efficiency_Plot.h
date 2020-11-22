#pragma once
#ifndef MAKE_EFFICIENCY_PLOT_H
#define MAKE_EFFICIENCY_PLOT_H
#include <string>
#include <vector>
#include "yaml-cpp/yaml.h"

#include "boost/filesystem.hpp"

#include "Latex/LTable.h" 
#include "Latex/LItem.h" 
#include "Class/DrawClass.h"
#include "AnalyseClass/File_List.h" 
#include "AnalyseClass/Sort_List.h" 


#include "TCanvas.h"
#include "TDirectory.h"
#include "TF1.h"
#include "TFile.h"
#include "TFitter.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TH2F.h"
#include "TH3.h"
#include "THStack.h"
#include "TImage.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TLine.h"
#include "TMath.h"
#include "TMatrix.h"
#include "TMatrixT.h"
#include "TMinuit.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TStyle.h"
#include "TTree.h"

void Extract_Sort_Data(CDraw &para, AFile_List &fileList, ASort_List& data);
void Draw_Efficiency_Plot(CDraw &para, ASort_List& data,std::string out_file_name);
void Make_Efficiency_Plot(CDraw &para, std::vector<std::string> yaml_file,std::string out_file_name);
void Make_Efficiency_Plot_Pre(CDraw &para);
#endif
