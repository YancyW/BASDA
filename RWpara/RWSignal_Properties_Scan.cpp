#include "Class/Signal_Properties_Scan.h"

void CSignal_Property_Scan::Read_Signal_Properties_Scan(CPath &path){
	ShowMessage(3, "Read Signal_Property Scan");
	YAML::Node property_node = YAML::LoadFile(path.signal_property_scan_file);

	RW_element("property_num" ,property_node,this->property_num);
	if(property_node["properties"]){
		properties= property_node["properties"].as<std::vector<std::string> >();
	}
	if(property_node["observable"]){
		observables= property_node["observable"].as<std::vector<std::string> >();
	}
	if(property_node["signal_setting"]){
		plot_sig = property_node["signal_setting"].as<Cplot_line>();
	}
	if(property_node["background_setting"]){
		plot_bkg= property_node["background_setting"].as<Cplot_line>();
	}
}

