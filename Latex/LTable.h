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
void Print_Table_First_Column(std::ostream& out, TPrint1 content, bool Is_Fomular = false, int width=20){
	if( Is_Fomular ){
		out<< " $" << std::setw(width) << content << " $ & " ;
	}
	else{
		out<< std::setw(width+4) << content << " & " ;
	}
}

template<typename TPrint1>
void Print_Table_Last_Column (std::ostream& out, TPrint1 content, bool Is_Fomular = false , int width=20 ){
	if( Is_Fomular ){
		out<< " $" << std::setw(width) << content << "$ \\\\ " <<std::endl;
	}
	else{
		out<< std::setw(width+4) << content << "\\\\ " <<std::endl;
	}
}


void Print_Table_Begin(std::ostream& out, std::string size, int item_num);
void Print_Table_End(std::ostream& out, std::string size);
void Print_Line(std::ostream& out);

#endif
