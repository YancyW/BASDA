#pragma once
#ifndef FVECTOR_H
#define FVECTOR_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <typeinfo>

typedef std::vector<int> WVecint;
typedef std::vector<double> WVecdouble;
typedef std::vector<float> WVecfloat;
typedef std::vector<bool> WVecbool;
typedef std::vector<std::string> WVecstring;

typedef std::vector< std::vector<int> > WVecVecint;
typedef std::vector< std::vector<double> > WVecVecdouble;
typedef std::vector< std::vector<float> > WVecVecfloat;
typedef std::vector< std::vector<bool> > WVecVecbool;
typedef std::vector< std::vector<std::string> > WVecVecstring;

/*
   template <typename TVector_equal>
   std::vector<TVector_equal> operator = (std::vector<TVector_equal> V1){
   std::vector <TVector_equal> Vnew;

   Vnew.resize(V1.size());
   copy(V1.begin(),V1.end(),Vnew.begin());
   return(Vnew);
   }
   */

template <typename TVector_add>
std::vector<TVector_add> operator + (std::vector<TVector_add> V1, std::vector<TVector_add> V2){
	std::vector <TVector_add> Vnew;

	Vnew.resize(V1.size()+V2.size());
	copy(V1.begin(),V1.end(),Vnew.begin());
	copy(V2.begin(),V2.end(),Vnew.begin()+V1.size());

	//	stable_sort(Vnew.begin(),Vnew.end());
	//	reverse(Vnew.begin(),Vnew.end());
	return(Vnew);
}

template <typename TVector_add>
std::vector<TVector_add> operator +=(std::vector<TVector_add> V1, std::vector<TVector_add> V2){
	std::vector <TVector_add> Vnew;

	Vnew.resize(V1.size()+V2.size());
	copy(V1.begin(),V1.end(),Vnew.begin());
	copy(V2.begin(),V2.end(),Vnew.begin()+V1.size());

	//	stable_sort(Vnew.begin(),Vnew.end());
	//	reverse(Vnew.begin(),Vnew.end());
	return(Vnew);
}

template <typename TVector_minus>
std::vector<TVector_minus> operator - (std::vector<TVector_minus> V1, std::vector<TVector_minus> V2){
	std::vector <TVector_minus> Vnew,Vminus;
	if(V1.size()==0 || V2.size()==0){
		return(Vnew);
	}

	Vnew=V1;
	Vminus=V2;
	////std::cout<<"in Vector minus: define Vnew  "<<Vnew.size()<<std::endl;
	////std::cout<<"in Vector minus: define Vnew end "<<Vnew[Vnew.size()-1]<<std::endl;
	////std::cout<<"in Vector minus: define Vminus end "<<Vminus[Vminus.size()-1]<<std::endl;

	typename std::vector<TVector_minus>::iterator it1=Vnew.begin();
	typename std::vector<TVector_minus>::iterator it2=Vminus.begin();
	//	std::cout<<"in Vector minus: define iterator  "<<Vnew.size()<<std::endl;
	for(it1=Vnew.begin();it1!=Vnew.end();it1++)
	{
		for(it2=Vminus.begin();it2!=Vminus.end();it2++)
		{
			if((it1+1)==Vnew.end()){
				break;
			}
			if((it2+1)==Vminus.end()){
				break;
			}
			//			std::cout<<"in Vector minus: change iterator 1  "<<*it1<<std::endl;
			//			std::cout<<"in Vector minus: change iterator 2  "<<*it2<<std::endl;
			if(*it1==*it2){
				//				std::cout<<"in Vector minus: equal 1 = 2  "<<std::endl;
				//				std::cout<<"in Vector minus: equal 1 = 2  "<<Vnew.size() <<" " << ((it1+1)==Vnew.end())<<std::endl;
				Vnew.erase(it1);
				Vminus.erase(it2);
				continue;
			}
		}
	}
	return(Vnew);
}


template <typename TVector_minus>
std::vector<TVector_minus> operator -=(std::vector<TVector_minus> V1, std::vector<TVector_minus> V2){
	std::vector <TVector_minus> Vnew,Vminus;
	if(V1.size()==0 || V2.size()==0){
		return(Vnew);
	}

	Vnew=V1;
	Vminus=V2;
	////std::cout<<"in Vector minus: define Vnew  "<<Vnew.size()<<std::endl;
	////std::cout<<"in Vector minus: define Vnew end "<<Vnew[Vnew.size()-1]<<std::endl;
	////std::cout<<"in Vector minus: define Vminus end "<<Vminus[Vminus.size()-1]<<std::endl;

	typename std::vector<TVector_minus>::iterator it1=Vnew.begin();
	typename std::vector<TVector_minus>::iterator it2=Vminus.begin();
	//	std::cout<<"in Vector minus: define iterator  "<<Vnew.size()<<std::endl;
	for(it1=Vnew.begin();it1!=Vnew.end();it1++)
	{
		for(it2=Vminus.begin();it2!=Vminus.end();it2++)
		{
			if((it1+1)==Vnew.end()){
				break;
			}
			if((it2+1)==Vminus.end()){
				break;
			}
			//			std::cout<<"in Vector minus: change iterator 1  "<<*it1<<std::endl;
			//			std::cout<<"in Vector minus: change iterator 2  "<<*it2<<std::endl;
			if(*it1==*it2){
				//				std::cout<<"in Vector minus: equal 1 = 2  "<<std::endl;
				//				std::cout<<"in Vector minus: equal 1 = 2  "<<Vnew.size() <<" " << ((it1+1)==Vnew.end())<<std::endl;
				Vnew.erase(it1);
				Vminus.erase(it2);
				continue;
			}
		}
	}
	return(Vnew);
}


//APair  operator * (std::vector<AParticle*> &P1, std::vector<AParticle*> &P2){
//	APair Pnew;
//	Pnew.addPlus(P1);
//	Pnew.addMinus(P1);
//	Pnew.setPair();
//	return(Pnew);
//}
/*
template <typename TVector_exist>
bool Vec_Exist(std::vector<TVector_exist> &V1, TVector_exist input){
	if(V1.size()==0){return(false);}

	typename std::vector<TVector_exist>::iterator ret;
	ret = std::find(V1.begin(), V1.end(), input);
	if(ret == V1.end()){
		return(false);
	}
	else{
		return(true);
	}
}
*/

bool Vec_Exist(WVecstring V1, std::string input);

bool Vec_Exist(WVecint V1, int input);

bool Vec_Exist(WVecfloat V1, float input);

bool Vec_Exist(WVecdouble V1, double input);

bool Vec_Exist(WVecbool V1, bool input);

std::ostream & operator<< (std::ostream & ostr, const WVecbool &flo);

std::ostream & operator<< (std::ostream & ostr, const WVecdouble &flo);

std::ostream & operator<< (std::ostream & ostr, const WVecint &flo);

std::ostream & operator<< (std::ostream & ostr, const WVecfloat &flo);

std::ostream & operator<< (std::ostream & ostr, const WVecstring &str);

std::ostream & operator<< (std::ostream & ostr, const WVecVecint &flo);

std::ostream & operator<< (std::ostream & ostr, const WVecVecdouble &flo);

std::ostream & operator<< (std::ostream & ostr, const WVecVecfloat &flo);

std::ostream & operator<< (std::ostream & ostr, const WVecVecbool &flo);

std::ostream & operator<< (std::ostream & ostr, const WVecVecstring &flo);

#endif
