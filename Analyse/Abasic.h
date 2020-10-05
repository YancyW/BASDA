#pragma once
#ifndef ANALYSE_BASIC_H
#define ANALYSE_BASIC_H
#include <string> 
#include <iostream>

#include "TH1.h"
#include "TMath.h"
#include "TLine.h"
#include "TLatex.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TTree.h"

#include "Class/DrawClass.h"
//#include "AnalyseClass/AnalyseClass.h"
//#include "AnalyseClass/File.h"
#include "AnalyseClass/Cut.h"
#include "Function/Ffile.h"
#include "Make_Table.h"
	

template<typename TCut1, typename TCut2>
bool GetCut(TCut1 data, TCut2 limit_down, TCut2 limit_up){
	if(data<limit_down || data>limit_up){
		return(false);
	}
	else{
		return(true);
	}
}


template<typename TCut1, typename TCut2>
bool GetCut(TCut1 data, TCut2 limit_down, TCut2 limit_up, float &pass, float weight=1){
	if(data<limit_down || data>limit_up){
		return(false);
	}
	else{
		pass+=weight;
		return(true);
	}
}


bool Apply_Cut(CDraw &para, float weight, int cut_level, float &pass_num);
bool Apply_Cut(CDraw &para, std::vector<TH1F*> &hvariable, std::vector<TH1F*> &hvariable_tot,float weight, int level,float &pass_num);
void Fill_Tree(CDraw &para, float event_rate, TTree* data0, TTree* data1, TTree* data2);
void Fill_Tree(CDraw &para, float event_rate, TTree* data0, TTree* data1);
void Fill_Tree(CDraw &para, float event_rate, TTree* data0);
#endif
