#pragma once
#ifndef ANALYSE_CLASS
#define ANALYSE_CLASS
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

	public:
	std::string                  _name      ;
	TFile*                       _root_file ; 

		std::vector<Analyse_Figure>  figure ; 
		float                        in_weight ; 


		Analyse_Single_File()               ; 

		~Analyse_Single_File()              ; 

		void Init             (AVariable &var, TFile *plot_file, float extra_weight, bool record_switch, bool plot_switch,std::string figure_name, std::string file_name, std::vector<std::string> tree_name);

		void Clear()                        ;

		void Root_Init();
		void Root_Init_Var      (); 
		void Root_Endow_Weight  (); 
		void Root_Endow_Var     (AVariable &var); 
		void Root_Endow_Unused_Var(AVariable &var, ACut &cut); 
		void Root_Fill          (int rootnum); 
		void Root_Close_Tree    (int rootnum); 
		void Root_Close_File    (); 

		void Plot_Origin        ( AVariable &var) ;
		void Plot_Final         ( AVariable &var) ;

		void Add_Pass_NoCut     ( ) ;
		void Add_Pass_AllCut    ( ) ;

		bool Get_Cut            ( AVariable &var,ACut &cut                                                      ) ;
		bool Use_Cut            ( Avariable &var, float weight, Analyse_Figure &figure                          ) ;
		bool Loop_Cut           ( AVariable &var, std::vector<Analyse_Figure> & figure, float weight, ACut &cut ) ;

		void Record_Information ( std::ofstream &myfile, AVariable& var, ACut &cut, std::string sample_name     ) ;

};


class Analyse_Multi_File : public APlot{
	private:
		int									   _var_num         ;

		int									   _file_num        ;

		TFile*								   _root_file       ; 
		TList*                                 _list;

		bool                                   _record_switch   ;
		bool                                   _plot_switch     ;

		ACut                                   _cut             ;

		float                                  _extra_weight    ; 

		Analyse_Single_File*                   _which_sort      ;
		void                                   _Find_Which_Sort (CDraw &para, AFile &file_name, int filenum ) ;

		bool                                   _Has_Drawn       ;
	public:
		AVariable                              var              ;
		std::vector<Analyse_Single_File>       file             ;
		std::vector< std::pair<std::string,std::vector<Analyse_Single_File > > > sort;


		int Var_Num();


		Analyse_Multi_File(CDraw &para, AFile &file_name){
			Init(para,file_name);
		}

		~Analyse_Multi_File(){
			Clear();
		}


		void Init_Color();
		void Init                   ( CDraw &para, AFile &file_name                              ) ;
		void Clear                  ();
		void Root_Init              ( CDraw &para, AFile &file_name, int filenum);
		void Root_Init_Var          ( int filenum); 
		void Root_Endow_Var         ( int filenum);
		void Root_Endow_Weight      ( int filenum);
		void Root_Fill              ( int filenum                                                ) ;
		void Root_Close             ( int filenum                                                ) ;
		void Root_Close_Last        ( CDraw &para) ;

		void Plot_Origin            ( int filenum) ;
		void Plot_Final             ( int filenum) ;

		void Add_Pass_NoCut         ( int filenum) ;
		void Add_Pass_AllCut        ( int filenum) ;
		void Add_Tot_Pass           ( int filenum                                                ) ;

		bool Get_Cut                ( int filenum) ;

		void Record_Information     ( int filenum,std::ofstream &myfile, std::string sample_name ) ;
		void Record_Tot_Information ( std::ofstream &myfile, std::string sample_name             ) ;

		void Draw_Single            ( CDraw& para,AFile& file_name ,std::string hist_label                   ) ;
		void Draw_Sort              ( CDraw& para,AFile& file_name ,std::string hist_label                   ) ;

		void Fill_Figure            ( );

		void Draw_Figure            ( CDraw& para,AFile& file_name                               ) ;
};
#endif
