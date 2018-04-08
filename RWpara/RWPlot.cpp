#include "Class/Plot.h"

void CPlot::Read_Plot(CPath &path){
	ShowMessage(3, "read Plot");
	std::string file_name=path.plot_file;
	ShowMessage(3, "plot file name",file_name);
	YAML::Node plot_node = YAML::LoadFile(file_name);

	this->setting = plot_node["setting"].as<Cplot_setting>();
	this->drawing = plot_node["drawing"].as<Cplot_drawing>();
}

