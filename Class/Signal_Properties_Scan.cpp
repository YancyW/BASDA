#include "Class/Signal_Properties_Scan.h"

void CSignal_Property_Scan::Print(){
	ShowMessage(2,"The CSignal_Property_Scan is ");
	ShowMessage(3,"property_num is ",property_num);
	for(int i=0;i<property_num;i++){
		ShowMessage(4,"properties are ",properties[i]);
		ShowMessage(4,"observables are",observables[i]);
	}

////plot_sig.Print();
////plot_bkg.Print();;

	plot_stack.Print();;
	plot_legend.Print();;
}


std::ostream & operator<< (std::ostream & ostr, CSignal_Property_Scan str){
	str.Print();
	return ostr;
}


