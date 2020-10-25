#pragma once
#ifndef FUNCTION_BASIC_H
#define FUNCTION_BASIC_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>

#include "Lib/MessageFormat.h" 
#include "Function/FString.h" 

template <class TType>
TType String_To_Num(const std::string& str){
	std::stringstream iss(str);
	TType num;
	iss >> num;
	return(num);
}

template <class TType>
std::string Num_To_String(TType i){
	std::string fnum;
	std::stringstream num;

	num << i;
	num >> fnum;
	return(fnum);
}

std::string Int_to_String(int i);
std::string Float_to_String(float i);
std::string Int_to_String_descrip(int i);

std::string NameHistogram(std::string signal_name, std::string class_name, std::string observable_name, int i);
std::string NameDescrip(std::string class_name, std::string observable_name, int i);

std::string GetUnit(std::string observe_name);

#define Get_VarName(x) #x


template <typename TTname>
std::string Get_ClassName(TTname x){

	std::string tname;
	tname = typeid(x).name();

	return(tname);
}


void CountNumber(Int_t variable, Int_t tot_num, Int_t slot,std::string  Message);


bool Is_Digits(const std::string &str);
#endif
