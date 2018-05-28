#ifndef ANALYSIS_CLASS_ROOT_FILE_H
#define ANALYSIS_CLASS_ROOT_FILE_H
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
#include "AnalyseClass/AnalyseClass_Single.h"


class ARoot_File{
	private:
		AVariable* _var; 
		float*     _in_weight;
		double*    _in_weight_d;
		long int*  _in_weight_i;
	public:
		TFile* file;
		TTree* tree;
		long int nevent;

		ARoot_File(std::string input_file, std::string head_name);
		~ARoot_File();
		void Delete();
		void Read(std::string input_file, std::string head_name);
		void SetBranchAddress(std::string var_name, float  *var);
		void SetBranchAddress(std::string var_name, double *var);
		void SetBranchAddress(std::string var_name, long int *var);

		void GetEntry(int event);

		void Init_Var(AVariable &input_var); 

		void Init_Weight(Analyse_Single_File &input_weight); 

		void Register_Var(); 
};


#endif
