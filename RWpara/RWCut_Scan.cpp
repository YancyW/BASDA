#include "Class/Cut_Scan.h"
#include "Function/Fbasic.h"
#include "RWpara/RWbasic.h"

void CCut_Scan::Read_Cut_Scan(std::string cut_scan_file, AVariable var){
	ShowMessage(3, "read Cut_Scan",cut_scan_file);
	YAML::Node scan_node = YAML::LoadFile(cut_scan_file);

	std::vector<int> input_cut_value;
	std::vector<std::string> input_scan_name;
	std::vector<std::string> _string_tmp;

	RW_element("scan_num" ,scan_node,this->_scan_num);
	if(scan_node["sub_scan_name"]){
		input_scan_name = scan_node["sub_scan_name"].as<std::vector<std::string> >();
	}

	scan.resize(_scan_num);
	for(int i=0;i<_scan_num;i++){
		if(scan_node[input_scan_name[i]]){
			scan[i].scan= scan_node[input_scan_name[i]].as<std::vector<float> >();
			if(scan[i].scan.size()!=3){
				ShowMessage(2,"In CCut_Scan, Read_Cut_Scan: input cut scan values number are not 3 for the ", i,  "th input");
			}
			scan[i].Set_Name(input_scan_name[i]);
		}
	}


	Set_Which_Cut(var);
	Set();
	ShowMessage(3,"scan size",Num());
	for(int i=0;i<Num();i++){
		ShowMessage(4,"scan ",i,"th scan name",scan[i].Name(), scan[i].Cut_Value_Print());
	}
}

