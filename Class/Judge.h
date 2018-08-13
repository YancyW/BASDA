
#pragma once
#ifndef AJUDGE_H
#define AJUDGE_H  
#include "Lib/MessageFormat.h"
class AJudge{
	private:
		bool _Exist;
	public:
		bool Exist(){return(_Exist);}

		void Set(){_Exist=true;}

		void Clear(){_Exist=false;}

};
#endif
