#include "Class/Cut_Scan.h"
using iter::product;
using TCut_Scan_Product=std::tuple<std::vector<float>, std::vector<float> >;
using ResTCut_Scan_Product = std::vector<TCut_Scan_Product>;
using TCut_Scan_Product_multi=std::tuple<std::vector<std::vector<float> >, std::vector<float> >;
using ResTCut_Scan_Product_multi = std::vector<TCut_Scan_Product_multi>;

void CCut_Scan_basic::Set(){
	_Used.Set();
}

std::string CCut_Scan_basic::Name(){
	if(_Used.Exist()){
		return(_scan_name);
	}
	else{
		ShowMessage(2,"In CCut_Scan_basic, Name: This Scan didn't set first.");
		return("None");
	}
}

void CCut_Scan_basic::Set_Name(std::string input_name){
	_scan_name = input_name;
}

bool CCut_Scan_basic::Check_Scan_Element_Number(){
	if(_Used.Exist() && scan.size()==3){
		return(true);
	}
	else{
		return(false);
	}
}

std::vector<float> CCut_Scan_basic::Cut_Value(){
	if(Check_Scan_Element_Number()){
		return(scan);
	}
	else{
		ShowMessage(2,"In CCut_Scan_basic, Cut Value: This Scan didn't set first.");
	}
	std::vector<float> empty;
	return(empty);
}

std::string CCut_Scan_basic::Cut_Value_Print(){
	if(Check_Scan_Element_Number()){
		std::string pvalue="["+Float_to_String(scan[0])+","+Float_to_String(scan[1])+","+Float_to_String(scan[2])+"]";
		return(pvalue);
	}
	else{
		ShowMessage(2,"In CCut_Scan_basic, Cut_Value_Print: This Scan didn't set first.");
		return("None");
	}
}

void CCut_Scan_basic::Print(){
	ShowMessage(2,"The CCut_Scan_basic is ");
	ShowMessage(4,"_scan name is ",Name());
	for(unsigned int i=0;i<scan.size();i++){
		ShowMessage(4,"_cut_scan is ", Cut_Value_Print());
	}
}

void CCut_Scan::Set_Scan_Num(){
	_scan_num = scan.size();
}


void CCut_Scan::Set_Which_Cut(AVariable var){
	for(int i=0;i<_scan_num;i++){
		int var_num=var.Find_Var(Name(i));
		_cut_num.push_back(var_num);
	}
}

void CCut_Scan::Set_All_Cut(){
	for(int i=0; i<_scan_num;i++){
		// first cut min
		// second cut max
		// third cut inc 
		// fourth  --- 
		// fifth   1  --- fix cut max = fourth para
		//         -1 --- fix cut min = fourth para
		//         0  --- fix cut min = first ; cut max = second
		std::vector<std::vector<float> > new_cut;
		float cut_min = scan[i].scan[0];
		float cut_max = scan[i].scan[1];
		float cut_inc = scan[i].scan[2];
		float cut_fix = scan[i].scan[3];                                                                                                                                                                                                   
		float cut_label = scan[i].scan[4];

		for(float j=cut_min; j<cut_max; j=j+cut_inc){
			std::vector<float> new_cut_first_level;

			if(cut_label>0){
				new_cut_first_level.push_back(j);
				new_cut_first_level.push_back(cut_fix);
			}
			else if(cut_label<0){
				new_cut_first_level.push_back(cut_fix);
				new_cut_first_level.push_back(j);
			}

			else if(cut_label==0){
				new_cut_first_level.push_back(j);
				new_cut_first_level.push_back(j+cut_inc);
			}
			new_cut.push_back(new_cut_first_level);
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
		std::vector<std::vector<float> > first = _all_cut_scan[0]; 
		std::vector<std::vector<float> > second= _all_cut_scan[1];
		auto p=product(first,second);
		ResTCut_Scan_Product v(std::begin(p), std::end(p));


		std::vector<std::vector<std::vector<float> > > cut_product12 ;
		for(unsigned int j=0; j<v.size();j++){
			std::vector<std::vector<float> > cut_product_to_vector = to_vector(v[j]); 
			cut_product12.push_back(cut_product_to_vector);
		}
		if(_scan_num==2){
			_cut_combine=cut_product12;
		}
		else{
			for(int i=2;i<_scan_num;i++){
				std::vector<std::vector<float> > second= _all_cut_scan[i];
				auto p=product(cut_product12,second);
				ResTCut_Scan_Product_multi v(std::begin(p), std::end(p));
				ShowMessage(2,"vsize",v.size());
				for(unsigned int j=0; j<v.size();j++){
					std::vector<std::vector<float> > product_first_element= std::get<0>(v[j]); 
					std::vector<float>               product_second_element = std::get<1>(v[j]); 
					product_first_element.push_back(product_second_element);
					ShowMessage(2,"i,j",i,j);
					_cut_combine.push_back(product_first_element);
				}
			}
		}
	}
}

void CCut_Scan::Set(AVariable var){
	Set_Scan_Num();
	for(int i=0;i<_scan_num;i++){
		scan[i].Set();
	}
	Set_Which_Cut(var);
	Set_All_Cut();
	Set_Cut_Combination();
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


