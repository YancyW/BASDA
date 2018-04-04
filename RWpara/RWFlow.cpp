#include "Class/Flow.h"
void CFlow::   Read_Flow(CPath path){
	ShowMessage(3, "read flow");
	YAML::Node flow_node = YAML::LoadFile(path.flow_file      );
	RW_element("cut"             ,flow_node,this->cut             );
	RW_element("plot"            ,flow_node,this->plot            );
	RW_element("plot_object"     ,flow_node,this->plot_object     );
	RW_element("record_output"   ,flow_node,this->record_output   );
	RW_element("level"           ,flow_node,this->level           );

	RW_element("signal_property" ,flow_node,this->signal_property );
	RW_element("working_scenario",flow_node,this->working_scenario);

	RW_element("BeginObject"     ,flow_node,this->begin_object    );
	RW_element("record_event"    ,flow_node,this->record_event    );
	RW_element("MVA_training"    ,flow_node,this->MVA_training    );
	RW_element("MVA_level"       ,flow_node,this->MVA_level       );
	RW_element("MVA_weight"      ,flow_node,this->MVA_weight      );
}

