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


class ARoot_File_Single{
	private:
		AVariable* _var; 
		float*     _in_weight;
		double*    _in_weight_d;
		long int*  _in_weight_i;
		float      _xsection;
		long int   _nevent;
	public:
		TFile* file;
		TTree* tree;

		ARoot_File_Single(std::string input_file, std::string head_name);
		ARoot_File_Single(std::string input_file, std::string head_name,float input_xsec);
		~ARoot_File_Single();

		void Delete();

		/*****************************************************************************************
		 * Init 
		 *****************************************************************************************/

		void Read(std::string input_file, std::string head_name);

		void Init_Xsection(float xsection);

		void Init_Var(AVariable &input_var); 

		void Init_Weight(Analyse_Single_File &input_weight); 

		/*****************************************************************************************
		 * Register variabble 
		 *****************************************************************************************/

		void SetBranchAddress(std::string var_name, float  *var);
		void SetBranchAddress(std::string var_name, double *var);
		void SetBranchAddress(std::string var_name, long int *var);
		void Register_Var(); 
		
		/*****************************************************************************************
		 * Get key value 
		 *****************************************************************************************/

		void Get_Entry(int event);

		float Get_Xsection();

		/*****************************************************************************************
		 * Return private value
		 *****************************************************************************************/

		long int Nevent();

};


class ARoot_File{
	private:
		int                                 _file_num;
		int                                 _current_file_num;
		std::vector<float>                  _in_weight; 
		CEvent                              _event;
		CScenario                           _scenario;
	public:
		std::vector<ARoot_File_Single>      root_file_vec;

		ARoot_File(std::string input_file, std::string head_name);
		//input file number is better for smaller than 4
		ARoot_File(std::vector<std::string> input_file, std::vector<std::string> head_name);
		ARoot_File(std::vector<std::string> input_file, std::string head_name);

		void Delete();

		/*****************************************************************************************
		 * Init 
		 *****************************************************************************************/

		void Init_Weight();

		void Init_Var(AVariable &input_var); 

		void Init_Weight(Analyse_Single_File &input_weight); 

		/*****************************************************************************************
		 * Return ARoot_File_Single's value
		 *****************************************************************************************/

		long int Nevent(int polnum);

		/*****************************************************************************************
		 * Register Variable
		 *****************************************************************************************/

		void Register_Var(); 

		/*****************************************************************************************
		 * Get key value 
		 *****************************************************************************************/

		void Get_Para(CDraw& para); 

		bool Get_Event(long int &num);
		
		void Get_Entry(long int event);
		
		float Get_Weight();

		
		
		/*****************************************************************************************
		 * Return private member value --- _file_num
		 *****************************************************************************************/

		void CD_File(int filenum);

		int File_Num();
		
		/*****************************************************************************************
		 * Return private member value --- _event
		 *****************************************************************************************/
		long long int Event();

		long long int Total_Event();

		Long64_t Begin_Event();

		Long64_t End_Event();
};
#endif
