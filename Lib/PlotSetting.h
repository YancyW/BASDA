#pragma once
#ifndef PLOTSETTING_H
#define PLOTSETTING_H
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

#include "MessageFormat.h"

	void SetSgStyle();
	void txtN(Double_t x0, Double_t y0, TH1 *h, std::string sName="N=%.0f", Double_t sizeTxt=0.06);
	TH1F * newTH1F(std::string name="h1", Double_t binw=0.01, Double_t LowBin=0.0, Double_t HighBin=3.0, Bool_t MevTitle=1, Int_t iMode=-1);
	void LineX1(Double_t atX, Int_t iColor=kRed, Int_t iStyle=1, Double_t iWidth=1);
#endif
