#pragma once
#ifndef CMVA_H
#define CMVA_H
#include "yaml-cpp/yaml.h"

#include "RWpara/RWbasic.h"
#include "Class/Path.h"

class CMVA{
	private:
	public:
		std::string             MVA_type             ;
		Int_t                   MVA_level            ;
	    float                   MVA_weight           ;
};


#endif
