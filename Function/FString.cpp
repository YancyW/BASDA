#include "FString.h"
bool Find_Str(std::string str1, std::string str2){
	
	std::size_t found_str= str1.find(str2);
	if (found_str!=std::string::npos){
		return(true);
	}
	return(false);
}


std::vector<std::string> Find_Str_in_Filename(std::string str){
	unsigned first_open   = str.find_first_of("_{");
	unsigned first_close  = str.find("}^") ;
	unsigned second_open  = str.find("^{") ;
	unsigned second_close = str.find_last_of("}") ;

	std::string strNew0 = str.substr (0, first_open);
	std::string strNew1 = str.substr (first_open+2, first_close-first_open-2);
	std::string strNew2 = str.substr (second_open+2, second_close-second_open-2);
	std::vector<std::string> strNew;
	strNew.push_back(strNew0);
	strNew.push_back(strNew1);
	strNew.push_back(strNew2);
	return(strNew);
}
