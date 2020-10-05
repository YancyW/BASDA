#ifndef ANALYSIS_CLASS_PLOT_H
#define ANALYSIS_CLASS_PLOT_H
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
#include "TPDF.h"
#include "TPostScript.h"

#include "Lib/MessageFormat.h"
#include "Class/DrawClass.h"

class APlot{ 
	private:

		std::vector<TFile*>                    _sig_File        ;
		int                                    _sig_num         ;
		std::vector<TTree*>                    _sig_Tree        ;

		std::vector<TFile*>                    _bkg_File        ;
		int                                    _bkg_num         ;
		std::vector<TTree*>                    _bkg_Tree        ;

		TH1F*                                  _sig_histo_total ;
		TH1F*                                  _bkg_histo_total ;

		std::vector<TH1F*>                     _sig_histo       ;
		std::vector<TH1F*>                     _bkg_histo       ;

		bool                                   _Has_Input       ;

		float                                  _weight          ;
		float                                  _value           ;

	public:
		APlot(){
			Init();
		}

		~APlot(){
			Clear();
		}

		void Init();
		void Clear();

		TH1F* Sig_Histo_Total(){
			return(_sig_histo_total);
		}

		TH1F* Bkg_Histo_Total(){
			return(_bkg_histo_total);
		}

		std::vector<TH1F*> Sig_Histo(){
			return(_sig_histo);
		}

		std::vector<TH1F*> Bkg_Histo(){
			return(_bkg_histo);
		}

		bool Get_Input_File(CDraw &para, Avariable &info, std::vector<std::string> input_sig, std::vector<std::string> input_bkg);
		bool Get_Histogram (CDraw &para, Avariable &info, std::string output_folder);

		bool Set_Line_Style(CDraw& para, Avariable &info, TH1F * histo, int color_index, int linestyle_index, bool norm_switch);
		bool Set_Line_Style_Test(CDraw& para, Avariable &info, TH1F * histo, Cplot_line setting);
		std::vector<std::string> Set_Stack_Title(CDraw& para, std::string name);
		void Set_Stack_Style(CDraw& para, Avariable &info, THStack* ss, TVirtualPad* pad, std::string hist_label);
		void Print_Plot(CDraw &para, Avariable& info, std::string name);

		void DrawLogo();
};


#endif
