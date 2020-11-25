#include "Record.h"
//------------------------------------------------------------------------------
//

void Record_Open(CDraw &para){
	if(para.flow.record_output){
		freopen(para.path.record_file.c_str() ,"w",stdout);
	}
}
void Record_Attach(CDraw &para){
	if(para.flow.record_output){
		freopen(para.path.record_file.c_str() ,"a",stdout);
	}
}
void Record_Close(CDraw &para){
	if(para.flow.record_output){
		fclose(stdout);
		freopen("/dev/tty","w",stdout);
	}
}


