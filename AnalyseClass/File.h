#pragma once
#ifndef AFILE_H
#define AFILE_H
#include <string> 
#include <vector> 
#include <iostream>
#include "Class/DrawClass.h"
#include "Function/Ffile.h"
#include "Analyse/Make_Table.h"
class AFile_Name{
	private:
		std::string                 _output_lable ;
	public:
		std::string                 name      ;
		std::string                 latex     ;

		std::vector<std::string>	basic_file;
		std::vector<float>          xection   ;

		std::string             	Unpol_file;
		std::string             	MVA_file  ;
		std::string                 CUT_file  ;
		std::string                 ana_data  ;
		std::string                 ana_Unpol ;

		AFile_Name(){
			Init();
		}

		void Init();

		void Clear(){
			name      = ""    ;
			latex     = ""    ;
			basic_file.clear();
			xection   .clear();
			MVA_file  = ""    ;
			CUT_file  = ""    ;
			ana_data  = ""    ;
		}

		int Num(){
			return(basic_file.size());
		}

		void Set_OutputLable(std::string file_type);

		std::string Output_RootFile();

		std::string Output_DataFile();

		void Print();
};

class AFile{
	public:
		std::vector<AFile_Name>  input       ;
		std::vector<AFile_Name>  output      ;
		AFile_Name               output_total;
		std::vector<std::string> folder      ;
		//folder order
        //The data_folder:"             
        //The plot_folder_name:"        
        //The plot_combine_folder_name:"
        //The event_Unpol_folder:"      
        //The event_MVA_folder:"        
        //The event_CUT_folder:"        
        //The plot_summary horizontaly:"        
        //The plot_in_sensitivity:"        
		std::string              significance  ;
		std::string              output_table  ;
		std::string              reweight_table;
		std::string              sensitivity   ;
		std::string              output_MVA    ;
		std::string              dataset_MVA   ;
		std::string              plot_CUT      ;

		int Input_Num(){
			return(input.size());
		}

		int Output_Num(){
			return(output.size());
		}

		void Clear();
		void Print();
		std::string  change_name(std::string arg_string);
		void get_file_name(CDraw &para);

};


std::ostream & operator<<(std::ostream & ostr, AFile_Name &file_name);
std::ostream & operator<<(std::ostream & ostr, AFile &file_name);

#endif



