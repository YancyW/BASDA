#pragma once
#ifndef FUNCTION_CALC_H
#define FUNCTION_CALC_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>

#include "Lib/MessageFormat.h" 

float Get_Significance(float sig, float bkg);

float Get_S_over_B(float sig, float bkg);

float Get_Efficiency(float current, float origin);

float Calc_Round(float Value, int SignificantDigits);

float Calc_Round_Decimal(float Value, int SignificantDigits);
#endif
