#pragma once
#ifndef FUNCTION_TABLE_H
#define FUNCTION_TABLE_H
#include <string>
#include <vector>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "Lib/MessageFormat.h"

template<typename TPrint1>
void Print_Table_First_Column(std::ostream& out, TPrint1 content, bool Is_Fomular = false){
	if( Is_Fomular ){
		out<< " $" << content << " $ & " ;
	}
	else{
		out<< content << " & " ;
	}
}

template<typename TPrint1>
void Print_Table_Last_Column (std::ostream& out, TPrint1 content, bool Is_Fomular = false ){
	if( Is_Fomular ){
		out<< " $" << content << "$ \\\\ " <<std::endl;
	}
	else{
		out<< content << "\\\\ " <<std::endl;
	}
}


void Print_Table_Begin(std::ostream& out, std::string size, int item_num);
void Print_Table_End(std::ostream& out, std::string size);
void Print_Line(std::ostream& out);

#endif
