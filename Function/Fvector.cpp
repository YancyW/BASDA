
#include "Fvector.h"
std::ostream & operator<< (std::ostream & ostr, std::vector<bool> flo){
	printf("\n"); 
	for(unsigned int i=0;i<flo.size();i++){
        ostr<<flo[i]<<", ";
	}
	return ostr;
}

std::ostream & operator<< (std::ostream & ostr, std::vector<double> flo){
	printf("\n"); 
	for(unsigned int i=0;i<flo.size();i++){
        ostr<<flo[i]<<", ";
	}
	return ostr;
}


std::ostream & operator<< (std::ostream & ostr, std::vector<int> flo){
	printf("\n"); 
	for(unsigned int i=0;i<flo.size();i++){
        ostr<<flo[i]<<", ";
	}
	return ostr;
}


std::ostream & operator<< (std::ostream & ostr, std::vector<float> flo){
	printf("\n"); 
	for(unsigned int i=0;i<flo.size();i++){
        ostr<<flo[i]<<", ";
	}
	return ostr;
}

/*std::ostream & operator<< (std::ostream & ostr, std::vector<std::string> str){
	printf("\n"); 
	for(unsigned int i=0;i<str.size();i++){
        ostr<<str[i]<<"\n";
	}
	return ostr;
}*/

