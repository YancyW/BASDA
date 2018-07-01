#pragma once
#ifndef ANALYSIS_CLASS_FILE_LIST_H
#define ANALYSIS_CLASS_FILE_LIST_H
#include <string>
#include <vector>
#include "yaml-cpp/yaml.h"
#include <iostream>

class AFile_Data{
	public:
		std::vector< std::pair<std::string,float> > data;
		std::vector< std::pair<std::string,float> > event;
		float weight;

		AFile_Data(){
			weight=0;
		}

		void Input_Element(std::string cut_name, float val);

		////	const  AFile_Data operator = (AFile_Data P1){
		////		for(int i=0;i<P1.data.size();i++){
		////			data.push_back(std::make_pair(P1.data[i].first,P1.data[i].second));
		////		}
		////		weight=P1.weight;
		////		return(P1);
		////	}
		const  AFile_Data operator + (AFile_Data P1){
			AFile_Data Nnew;
			if(data.size()==P1.data.size()){
				for(unsigned int i=0;i<P1.data.size();i++){
					Nnew.data.push_back(std::make_pair(data[i].first,data[i].second+P1.data[i].second));
				}
				Nnew.weight=weight+P1.weight;
				return(Nnew);
			}
			else{
				return(P1);
			}
		}
};

class AFile_List{
	public:
		std::vector<std::pair<std::string,AFile_Data> >  _list;
		// first  vector  --- all files
		// pair first     --- file name 
		// pair second    --- cut data of each file 

		void Input_Element(AFile_Data file);

		int  File_Num(){
			return(_list.size());
		}

		int  Last_File_Num(){
			return(_list.size()-1);
		}

		std::string File_Name(int i){
			return(_list[i].first);
		}

		AFile_Data File_Content(int i){
			return(_list[i].second);
		}

		int Data_Num(int i=0){
			return(_list[i].second.data.size());
		}

		int Last_Data_Num(int i=0){
			return(_list[i].second.data.size()-1);
		}

		std::string Data_Name(int j,int i=0){
			return(_list[i].second.data[j].first);
		}

		float Data_Content(int j,int i){
			return(_list[i].second.data[j].second);
		}

		float Event_Content(int j,int i){
			return(_list[i].second.event[j].second);
		}

		float Data_Sig(int k){
			float sig =  _list[0].second.data[k].second;
			return(sig);
		}

		float Data_Bkg(int k);
};

typedef std::pair<std::string,AFile_Data> Pair_File;
class PolNum{
	private:
		std::vector<Pair_File > Pol;
		Pair_File tot_Num;
	public:
		PolNum(){
		}

		PolNum(Pair_File LR, Pair_File RL){
			Pol.clear();
			Pol.push_back(LR);
			Pol.push_back(RL);
		}

		PolNum(Pair_File LR, Pair_File RL, Pair_File LL, Pair_File RR){
			Pol.clear();
			Pol.push_back(LR);
			Pol.push_back(RL);
			Pol.push_back(LL);
			Pol.push_back(RR);
		}

		~PolNum(){
			Pol.clear();
		}

		void calTotNum(float elec_pol, float posi_pol){
			if(Pol.size()<2){
				return;
			}
			float elecm=(1 - elec_pol)/2;
			float elecp=(1 + elec_pol)/2;
			float posim=(1 - posi_pol)/2;
			float posip=(1 + posi_pol)/2;
			float anverage_xection      ;
			for(unsigned int i=0;i<Pol[0].second.data.size();i++){
				float anverage_xectionlr=( elecm * posip * Pol[0].second.data[i].second* Pol[0].second.weight);
				float anverage_xectionrl=( elecp * posim * Pol[1].second.data[i].second* Pol[0].second.weight);
				float anverage_xectionll=0;
				float anverage_xectionrr=0;
				if(Pol.size()>2){
					anverage_xectionll  =( elecm * posim * Pol[2].second.data[i].second* Pol[0].second.weight);
					anverage_xectionrr  =( elecp * posip * Pol[3].second.data[i].second* Pol[0].second.weight);
				}
				anverage_xection  =( anverage_xectionlr + anverage_xectionrl + anverage_xectionll + anverage_xectionrr );
				tot_Num.second.data.push_back(std::make_pair(Pol[0].second.data[i].first,anverage_xection));
				tot_Num.first=Pol[0].first;
			}
		}

		void setTotNum(){
			calTotNum(-0.8,0.3);
			return;
		}

		Pair_File getTotNum(){
			return(tot_Num);
		}

};


namespace YAML{
	template<>
		struct convert<AFile_Data>{
			static bool decode(const Node& node, AFile_Data& fnum){ 
				int i=0;
				for(YAML::const_iterator it=node.begin(); it != node.end(); ++it){
					switch(i){
						default:
    						if(it->second.IsSequence()){
    							std::vector<float> input_val = it->second.as<std::vector<float> >();
    						//fnum.data.push_back(std::make_pair(it->first.as<std::string>(),it->second.as<float>()));break;
    							if(input_val.size()==2){
    								fnum.data .push_back(std::make_pair(it->first.as<std::string>(),input_val[0]));
    								fnum.event.push_back(std::make_pair(it->first.as<std::string>(),input_val[1]));
    							}
    							else if(input_val.size()==1){
    								fnum.data .push_back(std::make_pair(it->first.as<std::string>(),input_val[0]));
    								fnum.event.push_back(std::make_pair(it->first.as<std::string>(),input_val[0]));
    							}
    						}
							else if(it->second.IsScalar()){
    							fnum.data .push_back(std::make_pair(it->first.as<std::string>(),it->second.as<float>()));
    							fnum.event.push_back(std::make_pair(it->first.as<std::string>(),it->second.as<float>()));
    						}
							break;
					}
					i++;
				}
				return true;
			}
		};
};

#endif
