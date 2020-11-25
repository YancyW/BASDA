#include "Root_File.h"

ARoot_File_Single::ARoot_File_Single(std::string input_file, std::string head_name){
	Read(input_file, head_name);
}

ARoot_File_Single::ARoot_File_Single(std::string input_file, std::string head_name, float xsection){
	Read(input_file, head_name);
	Init_Xsection(xsection);
}

void ARoot_File_Single::Read(std::string input_file, std::string head_name){
	file   = new TFile(input_file.c_str());
	file   ->cd();
	tree   =(TTree*)file->Get(head_name.c_str());
	_nevent= tree->GetEntries();
}

void ARoot_File_Single::Delete(){
	ShowMessage(2,"file is deleting",file->GetName());
	file    ->cd();
	_nevent =0;
	delete  tree;
	delete  file;
}

ARoot_File_Single::~ARoot_File_Single(){
}

void ARoot_File_Single::Init_Xsection(float xsection){
	_xsection = xsection;
}

void ARoot_File_Single::Init_Var(AVariable* input_var){
	_var = input_var;
}

void ARoot_File_Single::SetBranchAddress(std::string var_name, float* var){
	tree->SetBranchAddress(var_name.c_str(), var);
}

void ARoot_File_Single::SetBranchAddress(std::string var_name, double* var){
	tree->SetBranchAddress(var_name.c_str(), var);
}

void ARoot_File_Single::SetBranchAddress(std::string var_name, long int* var){
	tree->SetBranchAddress(var_name.c_str(), var);
}

void ARoot_File_Single::Register_Var(){

		for(int k=0;k<_var->Var_Num();k++){
			if(_var->weight_exist){
				if(_var->weight.variable_type=="F"){
					SetBranchAddress(_var->weight.title_name.c_str(), &(_var->weight.variable));
				}
				else if(_var->weight.variable_type=="I"){
					SetBranchAddress(_var->weight.title_name.c_str(), &(_var->weight.variable_i));
				}
				else if(_var->weight.variable_type=="D"){
					SetBranchAddress(_var->weight.title_name.c_str(), &(_var->weight.variable_d));
				}
			}
			else{
				_var->weight.variable = _xsection/_nevent;  
			}
			if(_var->var[k].variable_type=="F"){
				SetBranchAddress(_var->var[k].title_name.c_str(), &(_var->var[k].variable));
			}
			else if(_var->var[k].variable_type=="I"){
				SetBranchAddress(_var->var[k].title_name.c_str(), &(_var->var[k].variable_i));
			}
			else if(_var->var[k].variable_type=="D"){
				SetBranchAddress(_var->var[k].title_name.c_str(), &(_var->var[k].variable_d));
			}
		}
}


void ARoot_File_Single::Get_Entry(int event){
	tree->GetEntry(event);
}


AVariable* ARoot_File_Single::Var_Ptr(){
	return(_var);
}

float ARoot_File_Single::Xsection(){
	return(_xsection);
}

long int ARoot_File_Single::Nevent(){
	return(_nevent);
}

std::string ARoot_File_Single::File_Name(){
	return(_file_name);
}

std::string ARoot_File_Single::Tree_Name(){
	return(_tree_name);
}
