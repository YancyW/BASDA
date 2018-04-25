#pragma once
#ifndef FFILE_H
#define FFILE_H
#include <string> 
#include <sys/stat.h> 
#include <iostream>
#include "TSystem.h"
#include "boost/filesystem.hpp"
#include "Lib/MessageFormat.h"



void Create_Folder(std::string folder_name);
void Create_File_Folder(std::string file_name);

bool Is_File_Exist(const std::string& fname);
void Is_File_Exist_And_Exit(const std::string& fname);

std::string Get_File_Folder(std::string input);
std::string Get_File_Ext(std::string input);
#endif
