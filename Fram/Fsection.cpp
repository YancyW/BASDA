#include "Fram/Fsection.h"
//------------------------------------------------------------------------------
//
void StartProcess(){
	ShowMessage();
	ShowMessage(1,"--------------------------------------------------------------------------------------------------------------------");
    ShowMessage(1,"-                                          AnalyseRoot release 0.0.1                                               -");
    ShowMessage(1,"-                                                  Yan Wang                                                        -");
    ShowMessage(1,"-                                        email:wangyan728@ihep.ac.cn                                               -");
    ShowMessage(1,"-                                           or:yan.wang@desy.de                                                    -");
	ShowMessage(1,"-                                                                                                                  -");
    ShowMessage(1,"-                                 A software package for analysis and plot at ilc.                                 -");
	ShowMessage(1,"-                                                                                                                  -");
    ShowMessage(1,"-                                Please cite if you use this package or part of my code.                           -");
	ShowMessage(1,"-                                                                                                                  -");
    ShowMessage(1,"-                     AnalyseRoot is provided without warranty under the terms of the GNU GPLv2.                   -");
    ShowMessage(1,"-                                                 It uses Root lib.                                                -");
	ShowMessage(1,"-                                                                                                                  -");
	ShowMessage(1,"--------------------------------------------------------------------------------------------------------------------");
	ShowMessage();
}



//------------------------------------------------------------------------------
//
void LoadFile(CDraw &para){
	ShowMessage(1, "load file");
	ShowMessage();
//	CLoad para;
  	para.Read();

	ShowMessage(2,"The Read files");

	ShowMessage(2, "The path  is read ",para.Jpath );

	ShowMessage(2, "The file  is read ",para.Jfile );

	ShowMessage(2, "The debug is read ",para.Jdebug);

	ShowMessage(2, "The flow  is read ",para.Jflow );

	ShowMessage(2, "The event is read ",para.Jevent);

	ShowMessage(2, "The var   is read ",para.Jvar  );

	ShowMessage();
}

//------------------------------------------------------------------------------

//
void LoadLibrary(CDraw &para){

	ShowMessage(1,"load libraray"); 
	ShowMessage();

	//init para
	LoadFile(para);

	SetPlot();

	if(!para.flow.record_output){
		fclose(stdout);
		freopen("/dev/tty","w",stdout);
	}
	gErrorIgnoreLevel = kWarning;
}


//------------------------------------------------------------------------------
//
void SetPlot(){
	ShowMessage();
	ShowMessage(1,"set plot style ---- Loading ywang Style" );
	ShowMessage();
//	gStyle->SetOptStat(0);
//	SetSgStyle();
	ShowMessage();

	TStyle *ywangStyle = new TStyle("ywangStyle","Style for rbkarl plots");
	ywangStyle->SetPaperSize(12., 12.);

	// For the canvas:
	ywangStyle->SetCanvasBorderMode(0);
	ywangStyle->SetCanvasBorderSize(0);
	ywangStyle->SetCanvasColor(kWhite);
	ywangStyle->SetCanvasDefH(1000); //Height of canvas
	ywangStyle->SetCanvasDefW(700); //Width of canvas
	ywangStyle->SetCanvasDefX(0);   //Position on screen
	ywangStyle->SetCanvasDefY(0);

	// For the Pad:
	ywangStyle->SetPadBorderMode(0);
	ywangStyle->SetPadBorderSize(0);
	ywangStyle->SetPadColor(kWhite);
	ywangStyle->SetPadGridX(true);
	ywangStyle->SetPadGridY(true);
	ywangStyle->SetGridColor(0);
	ywangStyle->SetGridStyle(3);
	ywangStyle->SetGridWidth(1);


	// For the frame:
	ywangStyle->SetFrameBorderMode(0);
	ywangStyle->SetFrameBorderSize(0);
	ywangStyle->SetFrameFillColor(0);
	ywangStyle->SetFrameFillStyle(0);
	ywangStyle->SetFrameLineColor(1);
	ywangStyle->SetFrameLineStyle(1);
	ywangStyle->SetFrameLineWidth(0);

	// For the histo:
	ywangStyle->SetHistLineColor(1);
	ywangStyle->SetHistLineStyle(0);
	ywangStyle->SetHistLineWidth(1);


	ywangStyle->SetEndErrorSize(2);
	//ywangStyle->SetErrorMarker(20);
	ywangStyle->SetErrorX(0.5);
	  
	ywangStyle->SetMarkerStyle(7);

	//For the fit/function:
	ywangStyle->SetOptFit(0);
	ywangStyle->SetFitFormat("5.4g");
	ywangStyle->SetFuncColor(4);
	ywangStyle->SetFuncStyle(1);
	ywangStyle->SetFuncWidth(1);

	//For the date:
	ywangStyle->SetOptDate(0);
	// ywangStyle->SetDateX(Float_t x = 0.01);
	// ywangStyle->SetDateY(Float_t y = 0.01);

	// For the statistics box:
	ywangStyle->SetOptFile(0);
	ywangStyle->SetOptStat(0); // To display name entries mean and RMS:   SetOptStat("nemr");
	ywangStyle->SetStatColor(kWhite);
	ywangStyle->SetStatFont(42);
	ywangStyle->SetStatFontSize(0.025);
	ywangStyle->SetStatTextColor(1);
	ywangStyle->SetStatFormat("6.4g");
	ywangStyle->SetStatBorderSize(1);
	ywangStyle->SetStatH(0.1);
	ywangStyle->SetStatW(0.15);

	//Fot fit box
	ywangStyle->SetFitFormat("8.4g");

	// For the Legend
	//ywangStyle->SetLegendFillColor(0);
	ywangStyle->SetLegendBorderSize(1);
	//ywangStyle->SetLegendFont(42);

	  
	  // Margins:
	ywangStyle->SetPadTopMargin(0.07);
	ywangStyle->SetPadBottomMargin(0.18);
	ywangStyle->SetPadLeftMargin(0.17);
	ywangStyle->SetPadRightMargin(0.05);
	  
	// For the Global title:
	ywangStyle->SetOptTitle(1);
	ywangStyle->SetTitleFont(42);
	ywangStyle->SetTitleColor(1);
	ywangStyle->SetTitleBorderSize(0);
	ywangStyle->SetTitleAlign(13);
	ywangStyle->SetTitleTextColor(1);
	ywangStyle->SetTitleFillColor(0);
	ywangStyle->SetTitleFontSize(0.06);
	ywangStyle->SetTitleX(0.005);
	ywangStyle->SetTitleY(0.995);
	ywangStyle->SetTitleW(0.995);
	ywangStyle->SetTitleH(0.06);


	// For the axis titles:

	ywangStyle->SetTitleColor(1, "XYZ");
	ywangStyle->SetTitleFont(42, "XYZ");
	ywangStyle->SetTitleSize(0.07, "XYZ");
	ywangStyle->SetTitleXOffset(1.2);
	ywangStyle->SetTitleYOffset(1.2);


	// For the axis labels:

	ywangStyle->SetLabelColor(1, "XYZ");
	ywangStyle->SetLabelFont(42, "XYZ");
	ywangStyle->SetLabelOffset(0.01, "XY");
	ywangStyle->SetLabelOffset(0.01, "Z");
	ywangStyle->SetLabelSize(0.07, "XY");
	ywangStyle->SetLabelSize(0.06, "Z");

	// For the axis:
	ywangStyle->SetAxisColor(1, "XYZ");
	ywangStyle->SetStripDecimals(kTRUE);
	ywangStyle->SetTickLength(0.03, "XYZ");
	ywangStyle->SetNdivisions(505, "XYZ");
	ywangStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
	ywangStyle->SetPadTickY(1);

	// Change for log plots:
	ywangStyle->SetOptLogx(0);
	ywangStyle->SetOptLogy(0);
	ywangStyle->SetOptLogz(0);



	ywangStyle->cd();
	//  ywangStyle->SetPalette(1,0);

	///////// pretty palette ///////////

	const Int_t NRGBs = 5;
	int NCont = 255;

	Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
	Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
	Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
	Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
	ywangStyle->SetNumberContours(NCont);
	  
	/////////////////////////////////////

	gROOT->ForceStyle();
}

//------------------------------------------------------------------------------
//
void EndProcess(){
	ShowMessage();
	ShowMessage(1,"end");
}
