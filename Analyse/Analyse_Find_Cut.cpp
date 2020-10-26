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

    ShowMessage(2,"cut combine",cut_combine.size());
    for(int k=0; k<cut_combine.size();k++){
    	ShowMessage(2,"cut combine",cut_combine[k]);
    }

//  auto p = product(all_cut[0], all_cut[1]);
//  ResType v(std::begin(p), std::end(p));

//  ShowMessage(2,"v_size",v.size());
//  for(int i=0; i<v.size();i++){
//  	std::vector<std::vector<float> > intvi=to_vector(v[i]); 
//  	ShowMessage(2,"intvi",intvi);
//  }
 
    exit(0);
//	get_combine(all_cut,pos);
	std::vector<std::vector<int> > pos;

	float final_j;
	float sig_max=0;
	float sig_tmp=0;


	ShowMessage(3,"pos",pos.size());
	for(int k=0; k<pos.size();k++){
		ShowMessage(3,"pos k",pos[k].size());
		for (int j=0;j<pos[k].size();j++){
			ShowMessage(3,"num",pos[k][j]);
		}
			////para.var.var[cut_name[k]].cut_min = all_cut[k][j][0];
			////para.var.var[cut_name[k]].cut_max = all_cut[k][j][1];
			////for(int i=0; i<all_cut.size()-1;i++){
			////	ShowMessage(2,"cut name",para.var.var[cut_name[i]].title_name,"cut value[", para.var.var[cut_name[i]].cut_min,  para.var.var[cut_name[i]].cut_max, "]");
			////}
			////Analyse_Direct_Cut(para,file_name);
			////sig_tmp=Make_Table(para,0,ana_out_name,file_name.output_table);
			////if(sig_tmp>sig_max){
			////	sig_max=sig_tmp;
			////	final_j = j;
			////}
			////RecordMessage(sig_file,3,"j is", j, "sig is", sig_tmp);
	}
	RecordMessage(sig_file,2,"final j is", final_j, "sig is", sig_max);

	sig_file.close();

}

void get_combine(std::vector<std::vector<std::vector<float> > > array, std::vector<std::vector<int> > & pos ){
	for(int i=0; i<array.size();i++){
		std::vector<int> pos_basic;
		for(int j=0;j<array[i].size();j++){
			std::vector<int>::iterator ret;
		}
		pos.push_back(pos_basic);
	}
	
	if(array.size()<=pos.size()){
		get_combine(array,pos);
	}
}
