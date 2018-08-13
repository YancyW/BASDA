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


class ARoot_File_Single{
	private:
		AVariable* _var; 
		float      _xsection;
		long int   _nevent;
		std::string _file_name;
		std::string _tree_name;
	public:
		TFile* file;
		TTree* tree;

		ARoot_File_Single(std::string input_file, std::string tree_name);
		ARoot_File_Single(std::string input_file, std::string tree_name,float input_xsec);
		~ARoot_File_Single();

		void Delete();

		/*****************************************************************************************
		 * Init 
		 *****************************************************************************************/

		void Read(std::string input_file, std::string tree_name);

		void Init_Xsection(float xsection);

		void Init_Var(AVariable* input_var); 

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

		/*****************************************************************************************
		 * Return private value
		 *****************************************************************************************/

		AVariable*  Var_Ptr();
		float       Xsection();
		long int    Nevent();
		std::string File_Name();
		std::string Tree_Name();

};


class ARoot_File{
	private:
		AVariable*                          _var; 
		int                                 _file_num;
		int                                 _current_file_num;
		CEvent                              _event;
		CScenario                           _scenario;
	public:
		std::vector<ARoot_File_Single>      root_file_vec;

		/*****************************************************************************************
		 * Contruction 
		 *****************************************************************************************/

		ARoot_File(std::string input_file, std::string tree_name);
		//input file number is better for smaller than 4
		ARoot_File(std::vector<std::string> input_file, std::vector<std::string> tree_name);
		ARoot_File(std::vector<std::string> input_file, std::string tree_name);

		void Delete();

		/*****************************************************************************************
		 * Init 
		 *****************************************************************************************/

		void Init_Var(AVariable &input_var); 

		void Init_Para(CDraw& para); 

		void Init_Event();
		
		/*****************************************************************************************
		 * Return private member value --- _event
		 *****************************************************************************************/
		AVariable* Var_Ptr();

		int File_Num();

		int Current_File_Num();

		long long int Event();

		long long int Total_Event();

		Long64_t Begin_Event();

		Long64_t End_Event();

		long int Nevent(int polnum);

		CScenario Scenario();

		/*****************************************************************************************
		 * Register Variable
		 *****************************************************************************************/

		void CD_File(int filenum);

		void Register_Var(); 

		/*****************************************************************************************
		 * Get key value 
		 *****************************************************************************************/

		void Get_Entry(long int event);
		
		bool Get_Event(long int &num);
		
		
		
		/*****************************************************************************************
		 * Return private member value --- _file_num
		 *****************************************************************************************/

};
#endif
