#include "Class/BKG_Sort.h"

void CBKG_Sort_basic::Print(){
	ShowMessage(2,"The CBKG_Sort_basic is ");
	ShowMessage(4,"_class name is ",_class_name);
	ShowMessage(3,"_sub_class_num is ",_sub_class_num);
	for(int i=0;i<_sub_class_num;i++){
		ShowMessage(4,"_sub_class_name is ",_sub_class_name[i]);
		ShowMessage(4,"_sub_class_legend is ",_sub_class_legend[i]);
		ShowMessage(4,"_default_sub_class_legend is ",_default_sub_class_legend[i]);
		ShowMessage(4,"_default_class_legend is ",_default_class_legend[i]);
	}
}


void CBKG_Sort::Print(){
	ShowMessage(2,"The CBKG_Sort is ");
	ShowMessage(3,"_sort num is ",_sort_num);
	for(int i=0;i<_sort_num;i++){
		sort[i].Print();
	}
}

std::ostream & operator<< (std::ostream & ostr, CBKG_Sort_basic str){
	str.Print();
	return ostr;
}

std::ostream & operator<< (std::ostream & ostr, CBKG_Sort str){
	str.Print();
	return ostr;
}

