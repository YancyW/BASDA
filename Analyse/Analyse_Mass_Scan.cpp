#include "Analyse_Mass_Scan.h"

void Analyse_Mass_Scan_Pre(CDraw &para){


	AFile file_name;
	std::vector<std::string> mass_root;




	for(int i=0;i<para.mass_scan.mass_num;i++){
		para.flow.hmass = para.mass_scan.mass[i];
        get_file_name(para,file_name);
        mass_root.push_back(file_name.output_total.CUT_file);
	}




	std::ofstream sig_file;
	sig_file.open(para.path.output_file+"/mass_scan/mass_scan.dat");


	sig_file.close();
}
