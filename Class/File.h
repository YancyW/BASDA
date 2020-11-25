#pragma once
#ifndef GLOBAL_PARA_FILE 
#define GLOBAL_PARA_FILE
#include "TStyle.h"
#include <string> 
#include <vector>
#include "yaml-cpp/yaml.h"

#include "Lib/MessageFormat.h"
#include "Function/Fbasic.h"
#include "RWpara/RWbasic.h"
#include "Function/Ffile.h"
#include "Class/Path.h"


class CFile{
	private:
	public:
		Int_t                    file_num               ;
		Int_t                    channel_num            ;
		std::vector<std::string> file                   ;
		std::vector<std::string> file_descrip           ;
		std::string              root_head_name         ;
		std::string              root_head_MVA_name     ;

		void                     Read_File(CPath path)  ;
		void                     Print()                ;
};

std::ostream & operator<< (std::ostream & ostr, CFile str);

#endif
