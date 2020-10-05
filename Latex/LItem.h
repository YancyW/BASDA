#pragma once
#ifndef FUNCTION_ITEM_H
#define FUNCTION_ITEM_H
#include <string>
#include <vector>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "Lib/MessageFormat.h"

template<typename TPrint1>
void Print_Item (std::ostream& out, TPrint1 content, int pos=-2){
	if(pos==1){
		out<< "\\item" << content;
	}
	else if(pos==-1){
		out<< content << std::endl;
	}
	else if(pos==0){
		out<< "\\item" << content << std::endl;
	}
	else if(pos==-2){
		out<< content;
	}
}

void Print_Item_Begin(std::ostream& out);
void Print_Item_End(std::ostream& out);

#endif
