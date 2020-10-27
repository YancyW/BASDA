#include "Analyse_Find_Cut.h"
using iter::product;
using TPf= std::tuple<std::vector<float>, std::vector<float> >;
using ResType = std::vector<TPf>;

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

	std::vector<std::vector<std::vector<float> > > all_cut=para.cut_scan.All_Cut_Scan();
	std::vector<std::vector<std::vector<float> > > cut_combine=para.cut_scan.Cut_Combine();

	for(int k=0; k<cut_combine.size();k++){
		ShowMessage(2,"cut combine",cut_combine[k]);
	}

	get_compare_significance(sig_file,para, file_name, cut_combine, ana_out_name);


	sig_file.close();

}

void get_compare_significance(std::ofstream& sig_file, CDraw &para, AFile& file_name, std::vector<std::vector<std::vector<float> > > array, std::vector<std::string> ana_out_name){
	float final_k;
	float sig_max=0;
	float sig_tmp=0;


	for(int k=0; k<array.size();k++){
		// give value to all cuts
		for (int j=0;j<array[k].size();j++){
			int which_cut=para.var.Find_Var(para.cut_scan.Name(j));
			para.var.var[which_cut].cut_min = array[k][j][0];
			para.var.var[which_cut].cut_max = array[k][j][1];
			RecordMessage(sig_file,2,"cut name",para.var.var[which_cut].title_name,"cut value[", para.var.var[which_cut].cut_min,  para.var.var[which_cut].cut_max);
		}
		Analyse_Direct_Cut(para,file_name);
		sig_tmp=Make_Table(para,0,ana_out_name,file_name.output_table);
		if(sig_tmp>sig_max){
			sig_max=sig_tmp;
			final_k = k;
		}
		RecordMessage(sig_file,3, "significance is", sig_tmp);
	}
	RecordMessage(sig_file,2,"The largest significance is at ", final_k);
	RecordMessage(sig_file,2,"The largest significance is ", sig_max);
}
