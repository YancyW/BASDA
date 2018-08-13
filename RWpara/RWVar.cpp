#include "AnalyseClass/Variable.h"

void AVariable::Read_Var(CPath &path){
	ShowMessage(3, "read Var");
	std::string file_name=path.var_file;
	ShowMessage(3, "variable file name",file_name);
	YAML::Node var_node = YAML::LoadFile(file_name);

	YAML::Node weight_nodes = var_node["weight"];
	RW_element("Exist"       , weight_nodes,this->weight_exist);

	YAML::Node nodes = var_node["variable"];
	int k=0;
	for(YAML::const_iterator it=nodes.begin(); it != nodes.end(); ++it){
		std::string input_var_name = it->first.as<std::string>();
		ShowMessage(3, "Var name",input_var_name);
		if(input_var_name=="weight"||input_var_name=="Weight"){
			weight_exist = true;
			this->weight=it->second.as<Avariable>();
		}
		else{
			this->var.push_back(it->second.as<Avariable>());
		}
		if(k>0){
			if(this->var[k].setting_type=="previous"){
				this->var[k].Copy(this->var[k-1]);
			}
			else{
				for(int newk=0;newk<k;newk++){
					if(this->var[k].setting_type==this->var[newk].title_name){
						this->var[k].Copy(this->var[newk]);
						continue;
					}
				}
			}
		}
		k++;
	}
	num_var = var.size();
	for(int i=0;i<num_var;i++){
		if(var[i].MVA_switch){
			num_MVA++;
			MVA.push_back(var[i]);
		}
	}
	YAML::Node nodes_vec = var_node["variable_vec"];
	for(YAML::const_iterator it=nodes_vec.begin(); it != nodes_vec.end(); ++it){
		ShowMessage(3, "Vec name",it->first.as<std::string>());
		this->vec.push_back(it->second.as<Avariable_vec>());
	}
	num_vec = vec.size();
}

