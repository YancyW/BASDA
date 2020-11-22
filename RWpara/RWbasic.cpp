#include "RWbasic.h"


void RW_element(std::string name, YAML::const_iterator it, double &variable_name){
	variable_name = it->second.as<double>();	
	ShowMessage(4, name + " is         ",variable_name);
}
void RW_element(std::string name, YAML::const_iterator it, float &variable_name){
	variable_name = it->second.as<float>();	
	ShowMessage(4, name + " is         ",variable_name);
}
void RW_element(std::string name, YAML::const_iterator it, Int_t    &variable_name){
	variable_name = it->second.as<int>();	
	ShowMessage(4, name + " is         ",variable_name);
}
void RW_element(std::string name, YAML::const_iterator it, long int &variable_name){
	variable_name = it->second.as<long>();	
	ShowMessage(4, name + " is         ",variable_name);
}
void RW_element(std::string name, YAML::const_iterator it, Long64_t &variable_name){
	variable_name = it->second.as<long>();	
	ShowMessage(4, name + " is         ",variable_name);
}
void RW_element(std::string name, YAML::const_iterator it, Bool_t   &variable_name){
	variable_name = it->second.as<bool>();	
	ShowMessage(4, name + " is         ",variable_name);
}
void RW_element(std::string name, YAML::const_iterator it, std::string  &variable_name){
	variable_name = it->second.as<std::string>();	
	ShowMessage(4, name + " is         ",variable_name);
}

void RW_element(std::string name, YAML::Node node_name, double &variable_name){
	variable_name = node_name[name].as<double>();	
	ShowMessage(4, name + " is         ",variable_name);
}
void RW_element(std::string name, YAML::Node node_name, float &variable_name){
	variable_name = node_name[name].as<float>();	
	ShowMessage(4, name + " is         ",variable_name);
}
void RW_element(std::string name, YAML::Node node_name, Int_t    &variable_name){
	variable_name = node_name[name].as<int>();	
	ShowMessage(4, name + " is         ",variable_name);
}
void RW_element(std::string name, YAML::Node node_name, long int &variable_name){
	variable_name = node_name[name].as<long>();	
	ShowMessage(4, name + " is         ",variable_name);
}
void RW_element(std::string name, YAML::Node node_name, Long64_t &variable_name){
	variable_name = node_name[name].as<long>();	
	ShowMessage(4, name + " is         ",variable_name);
}
void RW_element(std::string name, YAML::Node node_name, Bool_t   &variable_name){
	variable_name = node_name[name].as<bool>();	
	ShowMessage(4, name + " is         ",variable_name);
}
void RW_element(std::string name, YAML::Node node_name, std::string  &variable_name){
	variable_name = node_name[name].as<std::string>();	
	ShowMessage(4, name + " is         ",variable_name);
}

void RW_element(std::string particle_name, std::string name, YAML::Node node_name, double &variable_name){
	std::string fname=name+"_"+particle_name;
	variable_name = node_name[fname].as<double>();	
	ShowMessage(4, fname + " is         ",variable_name);
}
void RW_element(std::string particle_name, std::string name, YAML::Node node_name, float &variable_name){
	std::string fname=name+"_"+particle_name;
	variable_name = node_name[fname].as<float>();	
	ShowMessage(4, fname + " is         ",variable_name);
}
void RW_element(std::string particle_name, std::string name, YAML::Node node_name, Int_t    &variable_name){
	std::string fname=name+"_"+particle_name;
	variable_name = node_name[fname].as<int>();	
	ShowMessage(4, fname + " is         ",variable_name);
}
void RW_element(std::string particle_name, std::string name, YAML::Node node_name, long int &variable_name){
	std::string fname=name+"_"+particle_name;
	variable_name = node_name[fname].as<long>();	
	ShowMessage(4, fname + " is         ",variable_name);
}
void RW_element(std::string particle_name, std::string name, YAML::Node node_name, Long64_t &variable_name){
	std::string fname=name+"_"+particle_name;
	variable_name = node_name[fname].as<long>();	
	ShowMessage(4, fname + " is         ",variable_name);
}
void RW_element(std::string particle_name, std::string name, YAML::Node node_name, Bool_t   &variable_name){
	std::string fname=name+"_"+particle_name;
	variable_name = node_name[fname].as<bool>();	
	ShowMessage(4, fname + " is         ",variable_name);
}
void RW_element(std::string particle_name, std::string name, YAML::Node node_name, std::string  &variable_name){
	std::string fname=name+"_"+particle_name;
	variable_name = node_name[fname].as<std::string>();	
	ShowMessage(4, fname + " is         ",variable_name);
}

void RW_vector_element(std::string name, int num, YAML::Node node_name, std::vector<double> &variable_name){
	std::string	fnum=Int_to_String(num) ;
	std::string fname=name+"_"+fnum;
	variable_name.push_back(node_name[fname].as<double>());	
	ShowMessage(4, fname + " is         ",variable_name[num]);
}
void RW_vector_element(std::string name, int num, YAML::Node node_name, std::vector<float> &variable_name){
	std::string	fnum=Int_to_String(num) ;
	std::string fname=name+"_"+fnum;
	variable_name.push_back(node_name[fname].as<float>());	
	ShowMessage(4, fname + " is         ",variable_name[num]);
}
void RW_vector_element(std::string name, int num, YAML::Node node_name, std::vector<Int_t>    &variable_name){
	std::string	fnum=Int_to_String(num) ;
	std::string fname=name+"_"+fnum;
	variable_name.push_back(node_name[fname].as<int>());	
	ShowMessage(4, fname + " is         ",variable_name[num]);
}
void RW_vector_element(std::string name, int num, YAML::Node node_name, std::vector<long int >    &variable_name){
	std::string	fnum=Int_to_String(num) ;
	std::string fname=name+"_"+fnum;
	variable_name.push_back(node_name[fname].as<long>());	
	ShowMessage(4, fname + " is         ",variable_name[num]);
}
void RW_vector_element(std::string name, int num, YAML::Node node_name, std::vector<Long64_t>    &variable_name){
	std::string	fnum=Int_to_String(num) ;
	std::string fname=name+"_"+fnum;
	variable_name.push_back(node_name[fname].as<long>());	
	ShowMessage(4, fname + " is         ",variable_name[num]);
}
void RW_vector_element(std::string name, int num, YAML::Node node_name, std::vector<Bool_t>   &variable_name){
	std::string	fnum=Int_to_String(num) ;
	std::string fname=name+"_"+fnum;
	variable_name.push_back(node_name[fname].as<bool>());	
	ShowMessage(4, fname + " is         ",variable_name[num]);
}
void RW_vector_element(std::string name, int num, YAML::Node node_name, std::vector<std::string>  &variable_name){
	std::string	fnum=Int_to_String(num) ;
	std::string fname=name+"_"+fnum;
	variable_name.push_back(node_name[fname].as<std::string>());	
	ShowMessage(4, fname + " is         ",variable_name[num]);
}

void RW_vector_element(std::string particle_name, std::string name, int num, YAML::Node node_name, std::vector<double> &variable_name){
	std::string	fnum=Int_to_String(num) ;
	std::string fname=name+"_"+particle_name+"_"+fnum;
	variable_name.push_back(node_name[fname].as<double>());	
	ShowMessage(4, fname + " is         ",variable_name[num]);
}
void RW_vector_element(std::string particle_name, std::string name, int num, YAML::Node node_name, std::vector<float> &variable_name){
	std::string	fnum=Int_to_String(num) ;
	std::string fname=name+"_"+particle_name+"_"+fnum;
	variable_name.push_back(node_name[fname].as<float>());	
	ShowMessage(4, fname + " is         ",variable_name[num]);
}
void RW_vector_element(std::string particle_name, std::string name, int num, YAML::Node node_name, std::vector<Int_t>    &variable_name){
	std::string	fnum=Int_to_String(num) ;
	std::string fname=name+"_"+particle_name+"_"+fnum;
	variable_name.push_back(node_name[fname].as<int>());	
	ShowMessage(4, fname + " is         ",variable_name[num]);
}
void RW_vector_element(std::string particle_name, std::string name, int num, YAML::Node node_name, std::vector<long int>    &variable_name){
	std::string	fnum=Int_to_String(num) ;
	std::string fname=name+"_"+particle_name+"_"+fnum;
	variable_name.push_back(node_name[fname].as<long>());	
	ShowMessage(4, fname + " is         ",variable_name[num]);
}
void RW_vector_element(std::string particle_name, std::string name, int num, YAML::Node node_name, std::vector<Long64_t>    &variable_name){
	std::string	fnum=Int_to_String(num) ;
	std::string fname=name+"_"+particle_name+"_"+fnum;
	variable_name.push_back(node_name[fname].as<long>());	
	ShowMessage(4, fname + " is         ",variable_name[num]);
}
void RW_vector_element(std::string particle_name, std::string name, int num, YAML::Node node_name, std::vector<Bool_t>   &variable_name){
	std::string	fnum=Int_to_String(num) ;
	std::string fname=name+"_"+particle_name+"_"+fnum;
	variable_name.push_back(node_name[fname].as<bool>());	
	ShowMessage(4, fname + " is         ",variable_name[num]);
}
void RW_vector_element(std::string particle_name, std::string name, int num, YAML::Node node_name, std::vector<std::string>  &variable_name){
	std::string	fnum=Int_to_String(num) ;
	std::string fname=name+"_"+particle_name+"_"+fnum;
	variable_name.push_back(node_name[fname].as<std::string>());	
	ShowMessage(4, fname + " is         ",variable_name[num]);
}

