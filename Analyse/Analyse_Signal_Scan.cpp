#include "Analyse_Signal_Scan.h"

void Analyse_Signal_Scan_Pre(CDraw &para){


	AFile file_name;
	std::vector<std::string> scan_root;




	for(int i=0;i<para.signal_scan.property_num;i++){
		para.flow.signal_property= para.signal_scan.properties[i];
        get_file_name(para,file_name);
        scan_root.push_back(file_name.output_total.CUT_file);
	}




	std::ofstream sig_file;
	sig_file.open(para.path.output_file+"/signal_scan/signal_properties_scan.dat");


	sig_file.close();
}
