#include "Analyse_Cut_NoMVA.h"
void Analyse_Cut_NoMVA_Pre(CDraw &para){
	AFile file_name;
	get_file_name(para,file_name);

	std::ofstream sig_file;
	sig_file.open(file_name.significance);

	if(file_name.input[0].basic_file.size()>1){
		Analyse_Pre_Cut_Content(para,file_name);
	}

	Analyse_Direct_Cut(para,file_name);

	std::vector<std::string> ana_out_name;
	for(int i=0;i<file_name.Output_Num();i++){
		ana_out_name.push_back(file_name.output[i].ana_data);
	}
	float sig=Make_Table(para,para.scenario.Lumi(),ana_out_name,file_name.output_table,true);

	RecordMessage(sig_file,2,"significance is", sig);

	sig_file.close();
}


