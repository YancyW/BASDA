#pragma once
#ifndef GLOBAL_PARA_BKG_SORT_H
#define GLOBAL_PARA_BKG_SORT_H
#include "TStyle.h"
#include <string> 
#include <vector>
#include "yaml-cpp/yaml.h"

#include "Function/Fbasic.h"
#include "Class/Judge.h"
#include "RWpara/RWbasic.h"
#include "Class/Path.h"


typedef std::vector< std::pair<std::string,std::vector<std::string> > > CBKG_Sort_String;

class CBKG_Sort_basic{
	private:
		int _sub_class_num;
		AJudge _Used;

		std::string              _class_name;
		std::vector<std::string> _sub_class_name;
		std::vector<std::string> _default_sub_class_legend;
		std::vector<std::string> _default_class_legend;
		std::vector<std::string> _sub_class_legend;
	public:

		void Set_Num(){
			_sub_class_num = _sub_class_name.size();
		}

		void Set(){
			Set_Num();
			_Used.Set();
		}

		int Sub_Num(){
			if(_Used.Exist()){
				return(_sub_class_num);
			}
			else{
				ShowMessage(2,"In CBKG_Sort_basic, Sub_Num: This Sort didn't set first.");
				return(-1);
			}
		}

		void Set_Class(std::string name){
			_class_name = name;
		}

		void Set_Sub_Class(std::vector<std::string> &name){
			_sub_class_name = name;
		}

		void Set_Sub_Class(std::string name){
			_sub_class_name.push_back(name);
		}

		void Set_Legend(std::string leg){
			_sub_class_legend.push_back(leg);
		}

		void Set_Default_Sub_Legend(std::string leg){
			_default_sub_class_legend.push_back(leg);
		}

		void Set_Default_Legend(std::string leg){
			_default_class_legend.push_back(leg);
		}

		std::string Class(){
			if(!_Used.Exist()){
				ShowMessage(2,"In CBKG_Sort_basic, Legend: This Sort didn't set first.");
				return("");
			}
			return(_class_name);
		}

		std::vector<std::string> Sub_Class(){
			if(!_Used.Exist()){
				ShowMessage(2,"In CBKG_Sort_basic, Legend: This Sort didn't set first.");
				std::vector<std::string> tmp;
				return(tmp);
			}
			return(_sub_class_name);
		}

		std::string Sub_Class(int ith){
			if(!_Used.Exist()){
				ShowMessage(2,"In CBKG_Sort_basic, Legend: This Sort didn't set first.");
				return("");
			}
			if(ith < _sub_class_num){
				return(_sub_class_name[ith]);
			}
			ShowMessage(2,"Error: in CBKG_Sort_basic::Sub_Class, input num exceed max");
			return("Wrong");
		}

		std::string Name(int ith){
			if(!_Used.Exist()){
				ShowMessage(2,"In CBKG_Sort_basic, Legend: This Sort didn't set first.");
				return("");
			}
			if(ith < _sub_class_num){
				std::string name = _class_name + "_" + _sub_class_name[ith];
				return(name);
			}
			ShowMessage(2,"Error: in CBKG_Sort_basic::Sub_Class, input num exceed max");
			return("Wrong");
		}

		std::string Legend(int ith){
			if(!_Used.Exist()){
				ShowMessage(2,"In CBKG_Sort_basic, Legend: This Sort didn't set first.");
				return("");
			}
			if(ith < _sub_class_num){
				return(_sub_class_legend[ith]);
			}
			ShowMessage(2,"Error: in CBKG_Sort_basic::Sub_Class, input num exceed max");
			return("Wrong");
		}

		std::string Default_Sub_Legend(int ith){
			if(!_Used.Exist()){
				ShowMessage(2,"In CBKG_Sort_basic, Default_Legend: This Sort didn't set first.");
				return("");
			}
			if(ith < _sub_class_num){
				return(_default_sub_class_legend[ith]);
			}
			ShowMessage(2,"Error: in CBKG_Sort_basic::Sub_Class, input num exceed max");
			return("Wrong");
		}

		std::string Default_Legend(int ith){
			if(!_Used.Exist()){
				ShowMessage(2,"In CBKG_Sort_basic, Default_Legend: This Sort didn't set first.");
				return("");
			}
			if(ith < _sub_class_num){
				return(_default_class_legend[ith]);
			}
			ShowMessage(2,"Error: in CBKG_Sort_basic::Sub_Class, input num exceed max");
			return("Wrong");
		}

		std::pair<std::string, int> Find_Sub_Class(std::string str){
			std::pair<std::string, int> pos;

			bool exist_sub_class= false;
			for(int l=0;l<_sub_class_num;l++){
				if (Find_Str(str, _default_sub_class_legend[l])){
					pos.first  = _default_sub_class_legend[l];
					pos.second = l;
					exist_sub_class = true;
				}
			}
			if(!exist_sub_class){
				pos.first  = "Null";
				pos.second = -1; 
			}
			return(pos);
		}

};


class CBKG_Sort{
	private:
		int              _sort_num;
	public:

		std::vector<CBKG_Sort_basic> sort;

		int Num(){
			return(_sort_num);
		}

		int Total_Sort_Num(){
			int tot_num=0;
			for(int k=0;k<_sort_num;k++){
				for(int l=0;l<sort[k].Sub_Num();l++){
					tot_num++;
				}
			}
			return(tot_num);
		}

		std::vector<std::pair<std::string, int> > Find_Class(std::string str){

			std::vector<std::pair<std::string,int> > pos;

			bool exist_class= false;
			for(int k=0;k<_sort_num; k++){
				if (Find_Str(str, sort[k].Class())){
					pos.push_back(std::make_pair(sort[k].Class(), k)); 
					std::pair<std::string,int> sub_pair = sort[k].Find_Sub_Class(str); 
					if(sub_pair.first!="Null"){
						pos.push_back(sub_pair); 
						exist_class= true;
					}
				}
			}
			if(!exist_class){
				pos.clear();
			}
			return(pos);
		}

		void Read_BKG_Sort(CPath &path);
};

#endif
