#include "AnalyseClass/Cut.h"
#include "Function/Fbasic.h"

void ACut:: Read_Cut(CPath &path){
	ShowMessage(3, "read Cut");
	YAML::Node cut_node = YAML::LoadFile(path.cut_file);

	RW_element("cut_num" ,cut_node,this->cut_num);
    for(int i=0;i<cut_num;i++){
    	RW_vector_element("cut"          ,i,cut_node,this->cut);
    }

	ShowMessage(1);

    RW_element("pre_cut_num" ,cut_node,this->pre_cut_num);
    for(int i=0;i<pre_cut_num;i++){
    	RW_vector_element("pre_cut"          ,i,cut_node,this->pre_cut);
    }
}

