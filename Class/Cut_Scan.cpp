#include "Class/Cut_Scan.h"

void CCut_Scan_basic::Print(){
	ShowMessage(2,"The CCut_Scan_basic is ");
	ShowMessage(4,"_scan name is ",Name());
	for(unsigned int i=0;i<scan.size();i++){
		ShowMessage(4,"_cut_scan is ", Cut_Value_Print());
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


