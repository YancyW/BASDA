#include "Class/MVA.h"
void CMVA:: Read_MVA(CPath &path, CFlow &flow){
	ShowMessage(3, "read MVA");
	YAML::Node MVA_node = YAML::LoadFile(path.MVA_file);
	ShowMessage(1);

	YAML::Node nodes = MVA_node["MVA"];
	for(YAML::const_iterator it=nodes.begin(); it != nodes.end(); ++it){
		ShowMessage(3, "MVA methods",it->first.as<std::string>());
		this->mva.push_back(it->second.as<CMVA_Basic>());
	}

	bool get_mva=false;
	for(unsigned int i=0;i<=mva.size();i++){
		if(flow.MVA_method == this->mva[i].MVA_type){
			this->default_mva= this->mva[i];
			get_mva= true;
			break;
		}
	}
	if(!get_mva){
		ShowMessage(2,"do NOT have correct MVA method, please check advanced/MVA.dat");
		exit(0);
	}
};

