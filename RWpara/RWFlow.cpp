#include "Class/Flow.h"
void CFlow::   Read_Flow(CPath &path){
	ShowMessage(3, "read flow");
	YAML::Node flow_node = YAML::LoadFile(path.flow_file      );
	RW_element("cut"             ,flow_node,this->cut             );
	RW_element("plot"            ,flow_node,this->plot            );
	RW_element("plot_object"     ,flow_node,this->plot_object     );
	RW_element("record_output"   ,flow_node,this->record_output   );
	RW_element("level"           ,flow_node,this->level           );

	RW_element("signal_property" ,flow_node,this->signal_property );
	RW_element("working_scenario",flow_node,this->working_scenario);
	RW_element("MVA_method"      ,flow_node,this->MVA_method      );
	RW_element("pol_setting"     ,flow_node,this->pol_setting     );

	RW_element("BeginObject"     ,flow_node,this->begin_object    );
	RW_element("record_event"    ,flow_node,this->record_event    );
	RW_element("MVA_training"    ,flow_node,this->MVA_training    );
	RW_element("MVA_level"       ,flow_node,this->MVA_level       );
	RW_element("MVA_weight"      ,flow_node,this->MVA_weight      );


    bool JCom=Find_Str(this->begin_object,"Complete");
    bool JSum=Find_Str(this->begin_object,"Summarize");
    bool JSep=Find_Str(this->begin_object,"Separate");
	if(!JCom&&!JSum&&!JSep){
		if(this->pol_setting!="-1-1"&&this->pol_setting!="11"&&this->pol_setting!="-11"&&this->pol_setting!="1-1"){
			ShowMessage(2,"Error: in CFlow::Read_Flow", "wrong input for pol_setting, when single pol calculation, it should be like -1-1, 11, -11, 11",this->pol_setting);
			exit(0);
		}
		path.event_file   = path.event_file   + this->pol_setting;
		path.output_file  = path.output_file  + this->pol_setting;
		path.single_plot  = path.single_plot  + this->pol_setting;
		path.combine_plot = path.combine_plot + this->pol_setting;
		path.horizontal_summary_plot = path.horizontal_summary_plot + this->pol_setting;
	}

	ShowMessage(2,"event_file",path.event_file);
	flow_level=1;
}

