#include "Class/Cut_Scan.h"
using TCut_Scan_Product=std::tuple<std::vector<float>, std::vector<float> >;
using ResTCut_Scan_Product = std::vector<TCut_Scan_Product>;

void CCut_Scan_basic::Print(){
	ShowMessage(2,"The CCut_Scan_basic is ");
	ShowMessage(4,"_scan name is ",Name());
	for(unsigned int i=0;i<scan.size();i++){
		ShowMessage(4,"_cut_scan is ", Cut_Value_Print());
	}
}


void CCut_Scan::Set_Which_Cut(AVariable var){
	for(int i=0;i<_scan_num;i++){
		int var_num=var.Find_Var(Name(i));
		_cut_num.push_back(var_num);
	}
}

void CCut_Scan::Set_All_Cut(){
	for(int i=0; i<_scan_num;i++){
		std::vector<std::vector<float> > new_cut;
		float cut_min = scan[i].scan[0];
		float cut_max = scan[i].scan[1];
		float cut_inc = scan[i].scan[2];
		for(float j=cut_min; j<cut_max; j=j+cut_inc){
			std::vector<float> new_cut_basic;
			new_cut_basic.push_back(j);
			new_cut_basic.push_back(j+cut_inc);
			new_cut.push_back(new_cut_basic);
		}
		_all_cut_scan.push_back(new_cut);
	}
}


void CCut_Scan::Set_Cut_Combination(){
	if(_all_cut_scan.size()==1){
		_cut_combine = _all_cut_scan;
	}
	else if(_all_cut_scan.size()<1){
		ShowMessage(2,"no all_cut_scan");
		exit(0);
	}
	else{
		_cut_combine = _all_cut_scan[0];
		for(int i=0;i<_scan_num;i++){
			TCut_Scan_Product product_result;
			auto p=product(all_cut_combine,all_cut_scan[i+1]);
			ResTCut_Scan_Product v(std::begin(p), std::end(p));
			for(int j=0; j<v.size();j++){
				std::vector<std::vector<float> > vector_v=to_vector(v[j]); 
			}
		}
	}
}

void CCut_Scan::Print(){
	ShowMessage(2,"The CCut_Scan is ");
	ShowMessage(3,"_scan num is ",Num());
	for(int i=0;i<Num();i++){
		scan[i].Print();
	}
}

std::ostream & operator<< (std::ostream & ostr, CCut_Scan_basic str){
	str.Print();
	return ostr;
}

std::ostream & operator<< (std::ostream & ostr, CCut_Scan str){
	str.Print();
	return ostr;
}


