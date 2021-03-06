#include "Class/Path.h"
void CPath::Read_Path(std::string steering_file){
	YAML::Node path_node = YAML::LoadFile(steering_file);
	RW_element("OUTPUT_FOLDER"  ,path_node,this->output_folder         );
	RW_element("RECORD_FILE"    ,path_node,this->record_file   );
	if(this->output_folder != "NULL"){
		this->record_file= this->output_folder+"/"+this->record_file;
	}
	Create_File_Folder(this->record_file);

	ShowMessage(4,"Please check the RECORD_FILE for detail arguments setting!");
	ShowMessage(1);
  	freopen(this->record_file.c_str() ,"w",stdout);

	ShowMessage(3, "read path");
	RW_element("PROCESS"                ,path_node,this->process               );

	RW_element("OUTPUT_FILE"            ,path_node,this->output_file           );
	RW_element("EVENT_FILE"             ,path_node,this->event_file            );
	RW_element("SINGLE_PLOT"            ,path_node,this->single_plot           );
	RW_element("COMBINE_PLOT"           ,path_node,this->combine_plot          );
	RW_element("HORIZONTAL_SUMMARY_PLOT",path_node,this->horizontal_summary_plot);

	if(this->output_folder != "NULL"){
		this->output_file = this->output_folder+"/"+this->output_file;
		this->event_file  = this->output_folder+"/"+this->event_file ;
		this->single_plot = this->output_folder+"/"+this->single_plot;
		this->combine_plot= this->output_folder+"/"+this->combine_plot;
		this->horizontal_summary_plot = this->output_folder+"/"+this->horizontal_summary_plot;
	}
	this->Create_Folder();

	RW_element("DEBUG_FILE"             ,path_node,this->debug_file            );
	RW_element("ANALYSIS_FILE"          ,path_node,this->analyse_file          );
	RW_element("FLOW_FILE"              ,path_node,this->flow_file             );
	RW_element("PLOT_FILE"              ,path_node,this->plot_file             );
	RW_element("MVA_FILE"               ,path_node,this->MVA_file              );
	RW_element("INPUT_FILE"             ,path_node,this->input_file            );

	RW_element("CUT_FILE"               ,path_node,this->cut_file              );
	RW_element("VAR_FILE"               ,path_node,this->var_file              );
	RW_element("SENSITIVITY_FILE"       ,path_node,this->sensitivity_file      );
	RW_element("MASS_SCAN_FILE"         ,path_node,this->mass_scan_file        );
	RW_element("BKG_SORT_FILE"          ,path_node,this->bkg_sort_file         );
	RW_element("SCENARIO_FILE"          ,path_node,this->scenario_file         );
}

