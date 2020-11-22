#include "Class/Plot_Direct.h"

void CPlot_Direct::Read_Plot_Direct(CPath &path){
	ShowMessage(3, "Read Plot_Direct.dat",path.plot_direct_file);
	YAML::Node plot_node= YAML::LoadFile(path.plot_direct_file);

	if(plot_node["weight"])  {
		YAML::Node weight_nodes = plot_node["weight"];
		RW_element("Exist"       , weight_nodes,this->exist);
		RW_element("Weight_Type" , weight_nodes,this->type);
	}

	if(plot_node["var_label"]&& !plot_node["using_user_var"])  {
		RW_element("var_label", plot_node,this->var_label);
	}
	else if(plot_node["var_label"]&& plot_node["using_user_var"] ) {
		RW_element("using_user_var", plot_node,this->using_user_var);
		if(using_user_var==false){
			RW_element("var_label", plot_node,this->var_label);
		}
	}
	else if(!plot_node["var_label"]&& !plot_node["using_user_var"] ) {
		ShowMessage(2,"in CPlot_Direct::Read_Plot_Direct(), no enough input, there should either var_label or using_user_var and user_var!");
	}
	else{
		YAML::Node var_nodes = plot_node["user_var"];
    	this->plot_var=plot_node["user_var"].as<Avariable>();
	}
}

