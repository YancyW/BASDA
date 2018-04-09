#include "AnalyseClass/Cut.h"
#include "Function/Fbasic.h"

void ACut:: Read_Cut(CPath &path){
	ShowMessage(3, "read Cut");
	YAML::Node cut_node = YAML::LoadFile(path.cut_file);

    RW_element("pre_cut_num" ,cut_node,this->pre_cut_num);
	if(cut_node["pre_cut_order"]){
		pre_cut= cut_node["pre_cut_order"].as<std::vector<int> >();
	}
	if(pre_cut.size()!=0){
		ShowMessage(3,"pre cut is",pre_cut);
	}
	ShowMessage(1);

	RW_element("cut_num" ,cut_node,this->cut_num);
	if(cut_node["cut_order"]){
		cut= cut_node["cut_order"].as<std::vector<int> >();
	}
	if(cut.size()!=0){
		ShowMessage(3,"normal cut is",cut);
	}


}

