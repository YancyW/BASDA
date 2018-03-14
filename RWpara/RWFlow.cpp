#include "Class/Flow.h"
void CFlow::   Read_Flow(CPath path){
	ShowMessage(3, "read flow");
	YAML::Node flow_node = YAML::LoadFile(path.flow_file      );
	RW_element("cut"             ,flow_node,this->cut             );
	RW_element("plot"            ,flow_node,this->plot            );
	RW_element("plot_object"     ,flow_node,this->plot_object     );
	RW_element("record_output"   ,flow_node,this->record_output   );
	RW_element("level"           ,flow_node,this->level           );

	RW_element("hmass"           ,flow_node,this->hmass           );
	RW_element("working_scenario",flow_node,this->working_scenario);

	RW_element("BeginObject"     ,flow_node,this->begin_object    );
	RW_element("record_event"    ,flow_node,this->record_event    );
	RW_element("BDT_training"    ,flow_node,this->BDT_training    );
	RW_element("BDT_level"       ,flow_node,this->BDT_level       );
	RW_element("BDT_weight"      ,flow_node,this->BDT_weight      );
}

