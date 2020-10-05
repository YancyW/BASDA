#pragma once
#ifndef Record_H
#define Record_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include <string> 
#include <iomanip> 

#include "Class/DrawClass.h" 

void Record_Open(CDraw &para);
void Record_Attach(CDraw &para);
void Record_Close(CDraw &para);


#endif
