#pragma once
#ifndef ANALYSE_CLASS_SORT_LIST_H
#define ANALYSE_CLASS_SORT_LIST_H
#include <string>
#include <vector>

#include "Function/FCalc.h" 
#include "AnalyseClass/File_List.h" 

class ASort_List{
	public:
		std::vector< std::pair<std::string,std::vector< std::pair< std::string, AFile_Data> > > > _list;
		// first  vector      --- all sorts
		//     first          --- sort name
		//     second vector  --- sub sorts in this sort
		//            first   --- sub sort name 
		//            second  --- cut data of each subsort 

		int  Sort_Num(){
			return(_list.size());
		}

		std::string Sort_Name(int i){
			return(_list[i].first);
		}

		int  Sub_Sort_Num(int i){
			return(_list[i].second.size());
		}

		std::string Sub_Sort_Name(int i,int j){
			return(_list[i].second[j].first);
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
			return(_list[i].second[j].second.data[k].second);
		}

		float Data_Sig(int k);

		float Data_Bkg(int k);

		std::vector<float> Data_Final();

		float Significance();

		void Input_Element(std::vector<std::pair<std::string,int> > sort_name, std::string cut_name, float val);

		void Input_Element(std::string sort_name, std::string sub_sort_name,std::string cut_name, float val);

		void Input_Sub_Sort(std::string sort_name, std::string sub_sort_name);

		void Input_Sort(std::string sort_name);

};


#endif
