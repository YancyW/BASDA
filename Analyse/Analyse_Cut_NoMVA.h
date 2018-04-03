#pragma once
#ifndef ANALYSE_CUT_NOMVA_H
#define ANALYSE_CUT_NOMVA_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <string>
#include <vector>
#include <inttypes.h>
#include "yaml-cpp/yaml.h"
#include <cmath>


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
#include <iomanip>
#include <map>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 


#include "Function/Fbasic.h" 
#include "Lib/MessageFormat.h"
#include "Class/DrawClass.h"
#include "Analyse/Abasic.h"
#include "Analyse/Analyse_Pre_Cut.h"
#include "Analyse/Analyse_Direct_Cut.h"
#include "AnalyseClass/File.h"
#include "AnalyseClass/Cut.h"

void Analyse_Cut_NoMVA_Pre(CDraw &para);
#endif
