#pragma once
#ifndef GLOBAL_PARA_CUT_SCAN_H
#define GLOBAL_PARA_CUT_SCAN_H
#include "TStyle.h"
#include <string> 
#include <vector>
#include "yaml-cpp/yaml.h"

#include "Function/Fbasic.h"
#include "Lib/MessageFormat.h"
#include "Class/Judge.h"
#include "RWpara/RWbasic.h"
#include "Class/Path.h"
#include "AnalyseClass/Variable.h"

#include <product.hpp>
#include "helpers.hpp"
#include <iterator>
#include "catch.hpp"

#include <iomanip>
#include <map>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

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
#include "Lib/MessageFormat.h"
#include "Function/Ftuple.hpp" 
typedef std::vector< std::pair<std::string,std::vector<std::string> > > CCut_Scan_String;

class CCut_Scan_basic{
	private:
		std::string        _scan_name;
		AJudge             _Used;
	public:
		std::vector<float> scan;

		void Set();

		std::string Name();

		void Set_Name(std::string input_name);

		bool Check_Scan_Element_Number();

		std::vector<float> Cut_Value();

		std::string Cut_Value_Print();

		void Print();
};


class CCut_Scan{
	private:
		int              _scan_num;
		std::vector<std::vector<std::vector<float> > > _all_cut_scan;
		std::vector<int> _cut_num;
		std::vector<std::vector<std::vector<float> > > _cut_combine;
	public:

		std::vector<CCut_Scan_basic> scan;

		void Set_Scan_Num();

		void Set_Which_Cut(AVariable var);

		void Set_All_Cut();

		void Set_Cut_Combination();

		void Set(AVariable var);

		std::string Name(int i){
			return(scan[i].Name());
		}

		std::vector<float> Cut_Scan_Value(int i){
			return(scan[i].Cut_Value());
		}

		int Num(){
			return(_scan_num);
		}

		std::vector<int> Cut_Num(){
			return(_cut_num);
		}

		std::vector<std::vector<std::vector<float> > > All_Cut_Scan(){
			return(_all_cut_scan);
		}

		std::vector<std::vector<std::vector<float> > > Cut_Combine(){
			return(_cut_combine);
		}

		void Read_Cut_Scan(std::string path, AVariable var);

		void Print();
};
std::ostream & operator<< (std::ostream & ostr, CCut_Scan_basic str);
std::ostream & operator<< (std::ostream & ostr, CCut_Scan str);
#endif
