#include "Class/Debug.h"

void CDebug::Print(){
	ShowMessage(2,"The CDebug is ");
	ShowMessage(4,"num_debug_mode is ", num_debug_mode);
	ShowMessage(4,"level is ", level );
	for(unsigned int i=0;i<debug.size();i++){
		if(debug[i]){
			ShowMessage(4,"open ",debug[i]);
		}
	}
}


std::ostream & operator<< (std::ostream & ostr, CDebug str){
	str.Print();
	return ostr;
}

