#include "Fvector.h"
bool Vec_Exist(WVecstring V1, std::string input){
	if(V1.size()==0){return(false);}

	WVecstring::iterator ret;
	ret = std::find(V1.begin(), V1.end(), input);
	if(ret == V1.end()){
		return(false);
	}
	else{
		return(true);
	}
}

bool Vec_Exist(WVecbool V1, bool input){
	if(V1.size()==0){return(false);}

	WVecbool::iterator ret;
	ret = std::find(V1.begin(), V1.end(), input);
	if(ret == V1.end()){
		return(false);
	}
	else{
		return(true);
	}
}
bool Vec_Exist(WVecfloat V1, float input){
	if(V1.size()==0){return(false);}

	WVecfloat::iterator ret;
	ret = std::find(V1.begin(), V1.end(), input);
	if(ret == V1.end()){
		return(false);
	}
	else{
		return(true);
	}
}
bool Vec_Exist(WVecdouble V1, double input){
	if(V1.size()==0){return(false);}

	WVecdouble::iterator ret;
	ret = std::find(V1.begin(), V1.end(), input);
	if(ret == V1.end()){
		return(false);
	}
	else{
		return(true);
	}
}
bool Vec_Exist(WVecint V1, int input){
	if(V1.size()==0){return(false);}

	WVecint::iterator ret;
	ret = std::find(V1.begin(), V1.end(), input);
	if(ret == V1.end()){
		return(false);
	}
	else{
		return(true);
	}
}
std::ostream & operator<< (std::ostream & ostr, const WVecbool &flo){
	printf("\n"); 
	ostr << "(";
    std::copy(flo.begin(), flo.end(), std::ostream_iterator<bool> (ostr,", "));
	ostr << ")";
	return ostr;
}

std::ostream & operator<< (std::ostream & ostr, const WVecdouble &flo){
	printf("\n"); 
	ostr << "(";
    std::copy(flo.begin(), flo.end(), std::ostream_iterator<double> (ostr,", "));
	ostr << ")";
	return ostr;
}


std::ostream & operator<< (std::ostream & ostr, const WVecint &flo){
	printf("\n"); 
	ostr << "(";
    std::copy(flo.begin(), flo.end(), std::ostream_iterator<int> (ostr,", "));
	ostr << ")";
	return ostr;
}


std::ostream & operator<< (std::ostream & ostr, const WVecfloat &flo){
	printf("\n"); 
	ostr << "(";
    std::copy(flo.begin(), flo.end(), std::ostream_iterator<float> (ostr,", "));
	ostr << ")";
	return ostr;
}

std::ostream & operator<< (std::ostream & ostr, const WVecstring &flo){
	printf("\n"); 
	ostr << "(";
    std::copy(flo.begin(), flo.end(), std::ostream_iterator<std::string> (ostr,", "));
	ostr << ")";
	return ostr;
}

std::ostream & operator<< (std::ostream & ostr, const WVecVecint  &flo){
	printf("\n"); 
	ostr << "(\n";
	for(std::vector<std::vector<int> >::const_iterator it=flo.begin();
		it!=flo.end();
		it++){
		ostr << " " << *it << "\n";
	}
	ostr << ")";
	return ostr;
}

std::ostream & operator<< (std::ostream & ostr, const WVecVecdouble &flo){
	printf("\n"); 
	ostr << "(\n";
	for(std::vector<std::vector<double> >::const_iterator it=flo.begin();
		it!=flo.end();
		it++){
		ostr << " " << *it << "\n";
	}
	ostr << ")";
	return ostr;
}

std::ostream & operator<< (std::ostream & ostr, const WVecVecfloat &flo){
	printf("\n"); 
	ostr << "(\n";
	for(std::vector<std::vector<float> >::const_iterator it=flo.begin();
		it!=flo.end();
		it++){
		ostr << " " << *it << "\n";
	}
	ostr << ")";
	return ostr;
}

std::ostream & operator<< (std::ostream & ostr, const WVecVecbool &flo){
	printf("\n"); 
	ostr << "(\n";
	for(std::vector<std::vector<bool> >::const_iterator it=flo.begin();
		it!=flo.end();
		it++){
		ostr << " " << *it << "\n";
	}
	ostr << ")";
	return ostr;
}

std::ostream & operator<< (std::ostream & ostr, const WVecVecstring &flo){
	printf("\n"); 
	ostr << "(\n";
	for(std::vector<std::vector<std::string> >::const_iterator it=flo.begin();
		it!=flo.end();
		it++){
		ostr << " " << *it << "\n";
	}
	ostr << ")";
	return ostr;
}
