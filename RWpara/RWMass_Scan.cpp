#include "Class/Mass_Scan.h"

void CMass_Scan:: Read_Mass_Scan(CPath &path){
	ShowMessage(3, "Read Mass_Scan");
	YAML::Node mass_node = YAML::LoadFile(path.mass_scan_file);

	RW_element("mass_num" ,mass_node,this->mass_num);
    for(int i=0;i<mass_num;i++){
    	RW_vector_element("mass",i,mass_node,this->mass);
    }
}

