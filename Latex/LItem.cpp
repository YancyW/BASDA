#include "LItem.h"

void Print_Item_Begin(std::ostream& out){
	out<< " \\begin{itemize}\n" ;
}
void Print_Item_End(std::ostream& out){
	out<< " \n \\end{itemize}" <<std::endl ;
	out<< " " <<std::endl ;
	out<< " " <<std::endl ;
}


