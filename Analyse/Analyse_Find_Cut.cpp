#include "Analyse_Find_Cut.h"

void Analyse_Find_Cut(CDraw &para){

	AFile file_name;

	get_file_name(para,file_name);

	std::vector<std::string> ana_out_name;
	for(int i=0;i<file_name.Output_Num();i++){
		ana_out_name.push_back(file_name.output[i].ana_data);
	}

	ShowMessage(2,"open record significance file");
	std::ofstream sig_file;
	sig_file.open(file_name.significance);


	float final_i1;
	float sig_max=0;
	float sig_tmp=0;

	for (float i1=-1;i1<=1;i1=i1+0.05){
            para.var.var[12].cut_min = i1;
			Analyse_Direct_Cut(para,file_name);
			sig_tmp=Make_Table(para,0,ana_out_name,file_name.output_table,true);
			if(sig_tmp>sig_max){
				sig_max=sig_tmp;
				final_i1 = i1;
			}
			RecordMessage(sig_file,3,"i1 is", i1, "sig is", sig_tmp);
	}
	RecordMessage(sig_file,2,"final i1 is", final_i1, "sig is", sig_max);

	sig_file.close();

}
