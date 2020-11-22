#include "Class/Event.h"

void CEvent::Print(){
	ShowMessage(2,"The CEvent is ");
	ShowMessage(3,"event_num is ", event_num );
	ShowMessage(3,"total_num is ", total_num );
	ShowMessage(3,"begin num is ", _loop_begin );
	ShowMessage(3,"end   num is ", _loop_end   );
}


std::ostream & operator<< (std::ostream & ostr, CEvent str){
	str.Print();
	return ostr;
}



