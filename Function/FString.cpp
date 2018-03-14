#include "FString.h"
bool Find_Str(std::string str1, std::string str2){
	
	std::size_t found_str= str1.find(str2);
	if (found_str!=std::string::npos){
		return(true);
	}
	return(false);
}


