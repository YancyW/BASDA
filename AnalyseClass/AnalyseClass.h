#pragma once
#ifndef ANALYSE_CLASS
#define ANALYSE_CLASS
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
#include "AnalyseClass/AnalyseClass_Single.h"
#include "AnalyseClass/Cut.h"
#include "AnalyseClass/File.h"
#include "AnalyseClass/Plot.h"
#include "Analyse/Abasic.h"
#include "Function/Fbasic.h"
#include "Function/FString.h"


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
		std::ofstream*                         _data_file;
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


		void Init_Color             (                                                            ) ;
		void Init                   ( CDraw &para, AFile &file_name                              ) ;
		void Clear                  (                                                            ) ;
		void Root_Init              ( CDraw &para, AFile &file_name, int filenum                 ) ;
		void Root_Init_Var          ( int filenum                                                ) ;
		void File_Init              ( std::ofstream& file_name, int filenum                      ) ;
		void Root_Endow_Var         ( int filenum                                                ) ;
		void Root_Endow_Weight      ( int filenum                                                ) ;
		void Root_Fill              ( int filenum                                                ) ;
		void Root_Close             ( int filenum                                                ) ;
		void Root_Close_Last        ( CDraw &para                                                ) ;
		void File_Close             ( int filenum                                                ) ;

		void Plot_Origin            ( int filenum                                                ) ;
		void Plot_Final             ( int filenum                                                ) ;

		void Add_Pass_NoCut         ( int filenum                                                ) ;
		void Add_Pass_AllCut        ( int filenum                                                ) ;
		void Add_Tot_Pass           ( int filenum                                                ) ;

		bool Get_Cut                ( int filenum                                                ) ;

		//void Record_Information   ( int filenum,std::ofstream &myfile, std::string sample_name ) ;
		void Record_Information     ( int filenum, std::string sample_name                       ) ;
		//void Record_Tot_Information ( std::ofstream &myfile, std::string sample_name             ) ;
		void Record_Tot_Information ( std::string sample_name             ) ;

		void Draw_Single            ( CDraw& para,AFile& file_name ,std::string hist_label       ) ;
		void Draw_Sort              ( CDraw& para,AFile& file_name ,std::string hist_label       ) ;

		void Fill_Figure            (                                                            ) ;

		void Draw_Figure            ( CDraw& para,AFile& file_name                               ) ;
};
#endif
