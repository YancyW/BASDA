#pragma once
#ifndef ANALYSE_CLASS_SINGLE
#define ANALYSE_CLASS_SINGLE
#include <iostream>
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


#include "AnalyseClass/Variable.h"
#include "AnalyseClass/Cut.h"
#include "AnalyseClass/File.h"
#include "AnalyseClass/Plot.h"
#include "Analyse/Abasic.h"
#include "Function/Fbasic.h"
#include "Function/FString.h"
class Analyse_Figure{
	public:
		TH1F*       hvariable_origin;
		TH1F*       hvariable_before;
		TH1F*       hvariable_after ;
		TH1F*       hvariable_final ;

		float       pass            ;
		long int    event           ;

		~Analyse_Figure(){
			Clear();
		}

		void Init(Avariable &info, std::string name);

		void Init();

		void Clear();

		TH1F* Hist_Origin();
		TH1F* Hist_Before();
		TH1F* Hist_After();
		TH1F* Hist_Final();
		TH1F* Hist(std::string label);

		void Plot(float &variable, TH1F* &hvariable,float weight);
		void Plot_Origin(float &variable, float weight);
		void Plot_Before(float &variable, float weight);
		void Plot_After(float &variable, float weight);
		void Plot_Final(float &variable, float weight);
		void Set_Pass(float weight);
		void Add_Pass(float weight);
};



class Analyse_Single_File{
	private:
		float               	     _lumi      ;
		int							 _var_num   ; 
		std::vector<float>           _rootvar   ; 


		int							 _tree_num  ; 
		std::vector<TTree*>          _tree      ; 

		float                        _out_weight; 
		float                        _extra_weight ; 

		int							 _figure_num; 

		bool                         _record_switch;
		bool                         _plot_switch  ;
		std::ofstream*               _data_file;

	public:
		std::string                  _name      ;
		TFile*                       _root_file ; 

		std::vector<Analyse_Figure>  figure ; 
		float                        in_weight   ; 
		double                       in_weight_d ; 
		long int                     in_weight_i ; 


		Analyse_Single_File();

		~Analyse_Single_File()              ; 

		void Init                  ( AVariable &var, TFile *plot_file, float extra_weight, bool record_switch, bool plot_switch,std::string figure_name, std::string file_name, std::vector<std::string> tree_name ) ;

		void Clear                 ( ) ;

		void Root_Init             ( ) ;
		void Root_Init_Var         ( ) ;
		void File_Init             ( std::ofstream& file_name                                                                                                                                                   ) ;
		void Root_Endow_Weight     ( ) ;
		void Root_Endow_Var        ( AVariable &var                                                                                                                                                          ) ;
		void Root_Endow_Unused_Var ( AVariable &var, ACut &cut                                                                                                                                               ) ;
		void Root_Fill             ( int rootnum                                                                                                                                                             ) ;
		void Root_Close_Tree       ( int rootnum                                                                                                                                                             ) ;
		void Root_Close_File       ( ) ;
		void File_Close            ( ) ;

		void Plot_Origin           ( AVariable &var                                                                                                                                                          ) ;
		void Plot_Final            ( AVariable &var                                                                                                                                                          ) ;

		void Add_Pass_NoCut        ( ) ;
		void Add_Pass_AllCut       ( ) ;

		bool Get_Cut               ( AVariable &var, ACut &cut                                                                                                                                               ) ;
		bool Use_Cut               ( Avariable &var, float weight, Analyse_Figure &figure                                                                                                                    ) ;
		bool Loop_Cut              ( AVariable &var, std::vector<Analyse_Figure> & figure, float weight, ACut &cut                                                                                           ) ;

		//void Record_Information  ( std::ofstream &myfile, AVariable& var, ACut &cut, std::string sample_name                                                                                             ) ;
	    void Record_Information    ( AVariable& var, ACut &cut, std::string sample_name                                                                                                                      ) ;

};


#endif
