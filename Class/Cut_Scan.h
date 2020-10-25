#pragma once
#ifndef GLOBAL_PARA_CUT_SCAN_H
#define GLOBAL_PARA_CUT_SCAN_H
#include "TStyle.h"
#include <string> 
#include <vector>
#include "yaml-cpp/yaml.h"

#include "Function/Fbasic.h"
#include "Class/Judge.h"
#include "RWpara/RWbasic.h"
#include "Lib/MessageFormat.h"
#include "Class/Path.h"
#include "AnalyseClass/Variable.h"


typedef std::vector< std::pair<std::string,std::vector<std::string> > > CCut_Scan_String;

class CCut_Scan_basic{
	private:
		std::string        _scan_name;
		AJudge             _Used;
	public:
		std::vector<float> scan;

		void Set(){
			_Used.Set();
		}

		std::string Name(){
			if(_Used.Exist()){
				return(_scan_name);
			}
			else{
				ShowMessage(2,"In CCut_Scan_basic, Name: This Scan didn't set first.");
				return("None");
			}
		}

		void Set_Name(std::string input_name){
			_scan_name = input_name;
		}

		bool Check_Scan_Element_Number(){
			if(_Used.Exist() && scan.size()==3){
				return(true);
			}
			else{
				return(false);
			}
		}

		std::vector<float> Cut_Value(){
			if(Check_Scan_Element_Number()){
				return(scan);
			}
			else{
				ShowMessage(2,"In CCut_Scan_basic, Cut Value: This Scan didn't set first.");
			}
			std::vector<float> empty;
			return(empty);
		}

		std::string Cut_Value_Print(){
			if(Check_Scan_Element_Number()){
				std::string pvalue="["+Float_to_String(scan[0])+","+Float_to_String(scan[1])+","+Float_to_String(scan[2])+"]";
				return(pvalue);
			}
			else{
				ShowMessage(2,"In CCut_Scan_basic, Cut_Value_Print: This Scan didn't set first.");
				return("None");
			}
		}
		void Print();
};


class CCut_Scan{
	private:
		int              _scan_num;
		std::vector<std::vector<std::vector<float> > > _all_cut_scan;
		std::vector<int> _cut_num;
		std::vector<std::vector<float> >  _cut_combine;
	public:

		std::vector<CCut_Scan_basic> scan;

		void Set_Scan_Num(){
			_scan_num = scan.size();
		}

		void Set_All_Cut_Combination();

		void Set_Which_Cut(AVariable var);

		void Set(){
			Set_Scan_Num();
			for(int i=0;i<_scan_num;i++){
				scan[i].Set();
			}
			Set_All_Cut();
			Set_Cut_Combination();
		}


		std::string Name(int i){
			return(scan[i].Name());
		}


		std::vector<float> Cut_Scan_Value(int i){
			return(scan[i].Cut_Value());
		}

		int Num(){
			return(_scan_num);
		}

		std::vector<int> Cut_Num(){
			return(_cut_num);
		}

		std::vector<std::vector<std::vector<float> > > All_Cut_Scan(){
			return(_all_cut_scan);
		}

		std::vector<std::vector<float> > Cut_Combine(){
			return(_cut_combine);
		}

		void Read_Cut_Scan(std::string path, AVariable var);

		void Print();
};
std::ostream & operator<< (std::ostream & ostr, CCut_Scan_basic str);
std::ostream & operator<< (std::ostream & ostr, CCut_Scan str);
#endif
