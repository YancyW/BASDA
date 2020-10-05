#include "LTable.h"

void Print_Table_Begin(std::ostream& out, std::string size, int item_num){
	out<< " \\begin{center}\n" ;
	out<< " \\begin{" << size << "}\n" ;
	out<< " \\begin{tabular}{|" ;

	for(int i=0;i<item_num;i++){
		if(i!=item_num-1){
			out<< "c| " ;
		}
		else{
			out<< "c|}" << std::endl;
		}
	}

	out<< " \\hline" <<std::endl ;
}

void Print_Table_End(std::ostream& out, std::string size){
	out<< " \\hline" <<std::endl ;
	out<< " \\end{tabular}" <<std::endl ;
	out<< " \\end{" << size << "}" <<std::endl ;
	out<< " \\end{center}" <<std::endl ;
	out<< " " <<std::endl ;
	out<< " " <<std::endl ;
}

void Print_Line(std::ostream& out){
		out<< " \\hline" <<std::endl ;
}



