#include "DrawClass.h"
void CDraw::Print(){
     path            . Print();
     file            . Print();
     debug           . Print();
     flow            . Print();
	 event           . Print();
	 sensitivity     . Print();
	 var             . Print();
	 signal_scan     . Print();
	 bkg_sort        . Print();
	 scenario        . Print();
	 plot            . Print();
	 MVA             . Print();
}


std::ostream & operator<< (std::ostream & ostr, CDraw str){
	str.Print();
	return ostr;
}

