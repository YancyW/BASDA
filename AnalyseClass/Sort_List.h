#pragma once
#ifndef ANALYSE_CLASS_SORT_LIST_H
#define ANALYSE_CLASS_SORT_LIST_H
#include <string>
#include <vector>

#include "Lib/MessageFormat.h"
#include "Function/FCalc.h" 
#include "AnalyseClass/File_List.h" 
#include "Class/BKG_Sort.h" 

typedef                                                 std::pair< std::string, AFile_Data>       ASub_Sort_Type;
typedef                                    std::vector< std::pair< std::string, AFile_Data> >     ASub_Sort_List_Type;
typedef              std::pair<std::string,std::vector< std::pair< std::string, AFile_Data> > >   ASort_Type;
typedef std::vector< std::pair<std::string,std::vector< std::pair< std::string, AFile_Data> > > > ASort_List_Type;
class ASort_List{
	public:
		bool _exist=false;

		ASort_List_Type _list;
		ASort_List_Type _default_list;
		// first  vector      --- all sorts
		//     first          --- sort name
		//     second vector  --- sub sorts in this sort
		//            first   --- sub sort name 
		//            second  --- cut data of each subsort 
		void Set_Data_Pos(std::string input_name, int i, int j){
			_list[i].second[j].second.Set_Data_Pos(input_name);
		}

		void Set_Data_Pos(std::string input_name){
			for(int k=0;k<Sort_Num();k++){
				for(int l=0;l<Sub_Sort_Num(k);l++){
					_list[k].second[l].second.Set_Data_Pos(input_name);
				}
			}
		}

		void Set_Sort(std::string input_name);

		int Data_Pos(int i, int j){
			return(_list[i].second[j].second.Data_Pos());
		}

		int  Sort_Num(){
			return(_list.size());
		}

		std::string Sort_Name(int i){
			return(_list[i].first);
		}

		std::string Default_Sort_Name(int i){
			return(_default_list[i].first);
		}

		int  Sub_Sort_Num(int i){
			return(_list[i].second.size());
		}

		std::string Sub_Sort_Name(int i,int j){
			return(_list[i].second[j].first);
		}

		std::string Default_Sub_Sort_Name(int i,int j){
			return(_default_list[i].second[j].first);
		}

		int Total_Sort_Num();

		int Total_Unzero_Sort_Num();

		AFile_Data Sub_Sort_Content(int i,int j){
			return(_list[i].second[j].second);
		}

		int Data_Num(int i=0, int j=0){
			return(_list[i].second[j].second.data.size());
		}

		int Last_Data_Num(int i=0, int j=0){
			return(_list[i].second[j].second.data.size()-1);
		}

		std::string Data_Name(int k, int i=0, int j=0){
			return(_list[i].second[j].second.data[k].first);
		}

		float Data_Content(int k,int i, int j){
			//return(_list[i].second[j].second.data[k].second);
			return(_list[i].second[j].second.Data_Content(k));
		}

		float Data_Content(std::string input_name,int i, int j){
			//return(_list[i].second[j].second.data[k].second);
			return(_list[i].second[j].second.Data_Content(input_name));
		}

		std::string Full_Sort_Name(int i=0, int j=0){
			std::string sort_name=_list[i].first;
			std::string sub_sort_name=_list[i].second[j].first;
			std::string final_name=sort_name+"_"+sub_sort_name;
			return(final_name);
		}

		float Data_Sig(int k);

		float Data_Bkg(int k);

		std::vector<float> Data_Final();

		float Significance();

		float Significance(int i);

		float Efficiency();

		float Efficiency(int i);

		float Relative_Improvement(int i);

		void Input_Element(CBKG_Sort bkg_sort);

		void Input_Element(std::vector<std::pair<std::string,int> > sort_name, std::string cut_name, float val);
		void Input_Element(std::vector<std::pair<std::string,float> > sort_name, std::string cut_name, float val);
		/*
		template<typename TSort_name>
		void Input_Element_Template(std::vector<std::pair<std::string,TSort_name> > sort_name, std::string cut_name, float val){
			if(sort_name.size()!=0){
				Input_Single_Element(_list, sort_name[0].first,sort_name[1].first,cut_name,val);
			}
		}
		*/

		void Input_Single_Element(ASort_List_Type &output_list, std::string sort_name, std::string sub_sort_name,std::string cut_name, float val);

		void Input_Sub_Sort(ASort_List_Type &output_list, std::string sort_name, std::string sub_sort_name);

		void Input_Sort(ASort_List_Type &output_list, std::string sort_name);

		void Add_Name(std::string pre_name, std::string post_name);

		void Add_Sort(std::string sort_name, std::string sub_sort_name, AFile_Data input_data);

		ASort_Type Get_Sort(std::string sort_name);

		ASub_Sort_Type Get_Sub_Sort(std::string sub_sort_name);

		AFile_Data Get_Row_Data(std::string row_name);


		void Print(int i=2, bool has_title=false);

};


#endif
