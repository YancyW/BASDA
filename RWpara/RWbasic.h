#include "TStyle.h"
#include <string> 
#include "yaml-cpp/yaml.h"

#include "Lib/MessageFormat.h"
#include "Function/Fbasic.h"
#include "Lib/YAML_Assistant.h"



void RW_element(std::string name, YAML::const_iterator it, double &variable_name);
void RW_element(std::string name, YAML::const_iterator it, float &variable_name);
void RW_element(std::string name, YAML::const_iterator it, Int_t    &variable_name);
void RW_element(std::string name, YAML::const_iterator it, Long64_t &variable_name);
void RW_element(std::string name, YAML::const_iterator it, Bool_t   &variable_name);
void RW_element(std::string name, YAML::const_iterator it, std::string  &variable_name);

void RW_element(std::string name, YAML::Node node_name, double &variable_name);
void RW_element(std::string name, YAML::Node node_name, float &variable_name);
void RW_element(std::string name, YAML::Node node_name, Int_t    &variable_name);
void RW_element(std::string name, YAML::Node node_name, Long64_t &variable_name);
void RW_element(std::string name, YAML::Node node_name, Bool_t   &variable_name);
void RW_element(std::string name, YAML::Node node_name, std::string  &variable_name);

void RW_element(std::string particle_name, std::string name, YAML::Node node_name, double &variable_name);
void RW_element(std::string particle_name, std::string name, YAML::Node node_name, float &variable_name);
void RW_element(std::string particle_name, std::string name, YAML::Node node_name, Int_t    &variable_name);
void RW_element(std::string particle_name, std::string name, YAML::Node node_name, Long64_t &variable_name);
void RW_element(std::string particle_name, std::string name, YAML::Node node_name, Bool_t   &variable_name);
void RW_element(std::string particle_name, std::string name, YAML::Node node_name, std::string  &variable_name);

void RW_vector_element(std::string name, int num, YAML::Node node_name, std::vector<double > &variable_name);
void RW_vector_element(std::string name, int num, YAML::Node node_name, std::vector<float> &variable_name);
void RW_vector_element(std::string name, int num, YAML::Node node_name, std::vector<Int_t>    &variable_name);
void RW_vector_element(std::string name, int num, YAML::Node node_name, std::vector<Long64_t >&variable_name);
void RW_vector_element(std::string name, int num, YAML::Node node_name, std::vector<Bool_t>   &variable_name);
void RW_vector_element(std::string name, int num, YAML::Node node_name, std::vector<std::string>  &variable_name);

void RW_vector_element(std::string particle_name, std::string name, int num,YAML::Node node_name, std::vector<double > &variable_name);
void RW_vector_element(std::string particle_name, std::string name, int num,YAML::Node node_name, std::vector<float> &variable_name);
void RW_vector_element(std::string particle_name, std::string name, int num,YAML::Node node_name, std::vector<Int_t>    &variable_name);
void RW_vector_element(std::string particle_name, std::string name, int num,YAML::Node node_name, std::vector<Long64_t >&variable_name);
void RW_vector_element(std::string particle_name, std::string name, int num,YAML::Node node_name, std::vector<Bool_t>   &variable_name);
void RW_vector_element(std::string particle_name, std::string name, int num,YAML::Node node_name, std::vector<std::string>  &variable_name);

