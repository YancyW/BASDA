#include "Fvector.h"
bool Vec_Exist(std::vector<std::string>V1, std::string input){
	if(V1.size()==0){return(false);}

	std::vector<std::string>::iterator ret;
	ret = std::find(V1.begin(), V1.end(), input);
	if(ret == V1.end()){
		return(false);
	}
	else{
		return(true);
	}
}

std::ostream & operator<< (std::ostream & ostr, std::vector<bool> flo){
	printf("\n"); 
	for(unsigned int i=0;i<flo.size()-1;i++){
        ostr<<flo[i]<<", ";
	}
    ostr<<flo[flo.size()-1]<<std::endl;
	return ostr;
}

std::ostream & operator<< (std::ostream & ostr, std::vector<double> flo){
	printf("\n"); 
	for(unsigned int i=0;i<flo.size()-1;i++){
        ostr<<flo[i]<<", ";
	}
    ostr<<flo[flo.size()-1]<<std::endl;
	return ostr;
}


std::ostream & operator<< (std::ostream & ostr, std::vector<int> flo){
	printf("\n"); 
	for(unsigned int i=0;i<flo.size()-1;i++){
        ostr<<flo[i]<<", ";
	}
    ostr<<flo[flo.size()-1]<<std::endl;
	return ostr;
}


std::ostream & operator<< (std::ostream & ostr, std::vector<float> flo){
	printf("\n"); 
	for(unsigned int i=0;i<flo.size()-1;i++){
        ostr<<flo[i]<<", ";
	}
    ostr<<flo[flo.size()-1]<<std::endl;
	return ostr;
}

std::ostream & operator<< (std::ostream & ostr, std::vector<std::string> str){
	printf("\n"); 
	for(unsigned int i=0;i<str.size();i++){
        ostr<<str[i]<<"\n";
	}
	return ostr;
}

