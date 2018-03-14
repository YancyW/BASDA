#include "Class/Event.h"
void CEvent::  Read_Event(CPath path){
	ShowMessage(3, "read Event");
	YAML::Node event_node = YAML::LoadFile(path.analyse_file);

	RW_element("special_events_num"        ,event_node,this->_num_special_events);
	RW_element("first_events_num"          ,event_node,this->_num_first_events);


}

