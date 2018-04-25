#include "Fram/Fsection.h"
//------------------------------------------------------------------------------
//
void StartProcess(){
	ShowMessage();
	ShowMessage(1,"--------------------------------------------------------------------------------------------------------------------");
    ShowMessage(1,"-                                                    BASDA                                                         -");
    ShowMessage(1,"-                                     Beautiful_And_Simple_Drawing_Atificer                                        -");
    ShowMessage(1,"-                                                release 0.0.5                                                     -");
    ShowMessage(1,"-                                                  Yan Wang                                                        -");
    ShowMessage(1,"-                                        email:wangyan728@ihep.ac.cn                                               -");
    ShowMessage(1,"-                                           or:yan.wang@desy.de                                                    -");
	ShowMessage(1,"-                                                                                                                  -");
    ShowMessage(1,"-                                     A software package for analysis and plot.                                    -");
	ShowMessage(1,"-                                                                                                                  -");
    ShowMessage(1,"-                                Please cite if you use this package or part of my code.                           -");
	ShowMessage(1,"-                                                                                                                  -");
    ShowMessage(1,"-                           BASDA is provided without warranty under the terms of the GNU GPLv2.                   -");
	ShowMessage(1,"-                                                                                                                  -");
	ShowMessage(1,"--------------------------------------------------------------------------------------------------------------------");
	ShowMessage();
}



//------------------------------------------------------------------------------
//
void LoadFile(CDraw &para){
	ShowMessage(2, "load file");
	ShowMessage(3, "input path file   ",para.steering_file);
	ShowMessage();
//	CLoad para;
  	para.Read();

	ShowMessage(3, "The read files");

	ShowMessage(3, "The path                 is read ",para.Jpath     );

	ShowMessage(3, "The file                 is read ",para.Jfile     );

	ShowMessage(3, "The debug                is read ",para.Jdebug    );

	ShowMessage(3, "The flow                 is read ",para.Jflow     );

	ShowMessage(3, "The event                is read ",para.Jevent    );

	ShowMessage(3, "The var                  is read ",para.Jvar      );

	ShowMessage(3, "The sensitivity          is read ",para.Jsen      );

	ShowMessage(3, "The signal_property_scan is read ",para.JSP_scan  );

	ShowMessage(3, "The BKG sort             is read ",para.Jbkg_sort );

	ShowMessage(3, "The scenario             is read ",para.Jscenario );

	ShowMessage(3, "The plot                 is read ",para.Jplot     );

	ShowMessage(3, "The MVA                  is read ",para.JMVA      );

	ShowMessage(                                                      );
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
	ShowMessage(2,"set plot style ---- Loading BASDA Style" );
	ShowMessage();
//	gStyle->SetOptStat(0);
//	SetSgStyle();
	ShowMessage();

	TStyle *BASDAStyle = new TStyle("BASDAStyle","Style for rbkarl plots");
	BASDAStyle->SetPaperSize(12., 12.);

	// For the canvas:
	BASDAStyle->SetCanvasBorderMode(0);
	BASDAStyle->SetCanvasBorderSize(0);
	BASDAStyle->SetCanvasColor(kWhite);
	BASDAStyle->SetCanvasDefH(1000); //Height of canvas
	BASDAStyle->SetCanvasDefW(700); //Width of canvas
	BASDAStyle->SetCanvasDefX(0);   //Position on screen
	BASDAStyle->SetCanvasDefY(0);

	// For the Pad:
	BASDAStyle->SetPadBorderMode(0);
	BASDAStyle->SetPadBorderSize(0);
	BASDAStyle->SetPadColor(kWhite);
	BASDAStyle->SetPadGridX(true);
	BASDAStyle->SetPadGridY(true);
	BASDAStyle->SetGridColor(0);
	BASDAStyle->SetGridStyle(3);
	BASDAStyle->SetGridWidth(1);
	// Margins:
	BASDAStyle->SetPadTopMargin(0.07);
	BASDAStyle->SetPadBottomMargin(0.18);
	BASDAStyle->SetPadLeftMargin(0.18);
	BASDAStyle->SetPadRightMargin(0.05);
	  


	// For the frame:
	BASDAStyle->SetFrameBorderMode(0);
	BASDAStyle->SetFrameBorderSize(0);
	BASDAStyle->SetFrameFillColor(0);
	BASDAStyle->SetFrameFillStyle(0);
	BASDAStyle->SetFrameLineColor(1);
	BASDAStyle->SetFrameLineStyle(1);
	BASDAStyle->SetFrameLineWidth(0);

	// For the histo:
	BASDAStyle->SetHistLineColor(1);
	BASDAStyle->SetHistLineStyle(0);
	BASDAStyle->SetHistLineWidth(1);
	BASDAStyle->SetHistTopMargin(0.);



	// For the Legend
	//BASDAStyle->SetLegendFillColor(0);
	BASDAStyle->SetLegendBorderSize(1);
	//BASDAStyle->SetLegendFont(42);

	  
	// For the Global title:
	BASDAStyle->SetOptTitle(1);
	BASDAStyle->SetTitleFont(42);
	BASDAStyle->SetTitleColor(1);
	BASDAStyle->SetTitleBorderSize(0);
	BASDAStyle->SetTitleAlign(13);
	BASDAStyle->SetTitleTextColor(1);
	BASDAStyle->SetTitleFillColor(0);
	BASDAStyle->SetTitleFontSize(0.06);
	BASDAStyle->SetTitleX(0.005);
	BASDAStyle->SetTitleY(0.995);
	BASDAStyle->SetTitleW(0.995);
	BASDAStyle->SetTitleH(0.06);


	// For the axis titles:

	BASDAStyle->SetTitleColor(1, "XYZ");
	BASDAStyle->SetTitleFont(42, "XYZ");
	BASDAStyle->SetTitleSize(0.07, "XYZ");
	BASDAStyle->SetTitleXOffset(1.2);
	BASDAStyle->SetTitleYOffset(1.2);


	// For the axis labels:

	BASDAStyle->SetLabelColor(1, "XYZ");
	BASDAStyle->SetLabelFont(42, "XYZ");
	BASDAStyle->SetLabelOffset(0.0, "XY");
	BASDAStyle->SetLabelOffset(0.01, "Z");
	BASDAStyle->SetLabelSize(0.07, "XY");
	BASDAStyle->SetLabelSize(0.06, "Z");

	// For the axis:
	BASDAStyle->SetAxisColor(1, "XYZ");
	BASDAStyle->SetStripDecimals(kTRUE);
	BASDAStyle->SetTickLength(0.03, "XYZ");
	BASDAStyle->SetNdivisions(505, "XYZ");
	BASDAStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
	BASDAStyle->SetPadTickY(1);

	// Change for log plots:
	BASDAStyle->SetOptLogx(0);
	BASDAStyle->SetOptLogy(0);
	BASDAStyle->SetOptLogz(0);

	// For the statistics box:
	BASDAStyle->SetOptFile(0);
	BASDAStyle->SetOptStat(0); // To display name entries mean and RMS:   SetOptStat("nemr");
	BASDAStyle->SetStatColor(kWhite);
	BASDAStyle->SetStatFont(42);
	BASDAStyle->SetStatFontSize(0.025);
	BASDAStyle->SetStatTextColor(1);
	BASDAStyle->SetStatFormat("6.4g");
	BASDAStyle->SetStatBorderSize(1);
	BASDAStyle->SetStatH(0.1);
	BASDAStyle->SetStatW(0.15);

	BASDAStyle->SetEndErrorSize(2);
	//BASDAStyle->SetErrorMarker(20);
	BASDAStyle->SetErrorX(0.5);
	  
	BASDAStyle->SetMarkerStyle(7);

	//For the fit/function:
	BASDAStyle->SetOptFit(0);
	BASDAStyle->SetFitFormat("5.4g");
	BASDAStyle->SetFuncColor(4);
	BASDAStyle->SetFuncStyle(1);
	BASDAStyle->SetFuncWidth(1);

	//For the date:
	BASDAStyle->SetOptDate(0);
	// BASDAStyle->SetDateX(Float_t x = 0.01);
	// BASDAStyle->SetDateY(Float_t y = 0.01);

	//  BASDAStyle->SetPalette(1,0);

	BASDAStyle->cd();

	///////// pretty palette ///////////

	const Int_t NRGBs = 5;
	int NCont = 255;

	Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
	Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
	Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
	Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
	BASDAStyle->SetNumberContours(NCont);
	  
	/////////////////////////////////////

	gROOT->SetStyle("BASDAStyle");
}

//------------------------------------------------------------------------------
//
void EndProcess(){
	ShowMessage();
	ShowMessage(1,"end");
}
