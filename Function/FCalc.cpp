#include "FCalc.h"
float Get_Significance(float sig, float bkg){
	float significance =Calc_Round_Decimal(sig/std::sqrt(sig+bkg),2);
	return(significance);
}

float Get_S_over_B(float sig, float bkg){
	float significance =Calc_Round_Decimal(sig/bkg,2);
	return(significance);
}

float Get_Efficiency(float current, float origin){
	float effi=current/(current+origin);
	return(effi);
}


float Calc_Round(float Value, int SignificantDigits){
	 int log_exp = (int)( Value != 0 ? floor( TMath::Log10( TMath::Abs( Value  )  )  ) : 0  );
	 Value *= pow(10, -log_exp);                                                                                                                                                                                                            
	 Value *= pow(10, (SignificantDigits>0 ? SignificantDigits-1 : 0) );
	 Value = (Value >= 0 ? floor(Value + 0.5) : ceil(Value - 0.5));
	 Value *= pow(10, -(SignificantDigits>0 ? SignificantDigits-1 : 0) );
	 Value *= pow(10, log_exp);
	 return Value;
}

float Calc_Round_Decimal(float Value, int SignificantDigits){
     int log_exp = (int)( Value != 0 ? floor( TMath::Log10( TMath::Abs( Value  )  )  ) : 0  );
     SignificantDigits =SignificantDigits + log_exp +1;
     Value *= pow(10, -log_exp);
     Value *= pow(10, (SignificantDigits>0 ? SignificantDigits-1 : 0) );
     Value = (Value >= 0 ? floor(Value + 0.5) : ceil(Value - 0.5));
     Value *= pow(10, -(SignificantDigits>0 ? SignificantDigits-1 : 0) );
     Value *= pow(10, log_exp);
     return Value;
}
