#include "Make_Complete_Efficiency_Plot.h"
#include "AnalyseClass/File.h"


void Make_Complete_Efficiency_Plot_Pre(CDraw &para){
	ShowMessage(2,"make efficiency plots for all beam polariazation combination");

	bool only_lr                        = false;
	if(para.scenario.Run_Ratio_Vec().size()==2){
		only_lr =true;
	}

	for(int i=-1;i<2;i=i+2){
		for(int j=-1;j<2;j=j+2){
			if(only_lr){
				if(i==j){continue;}
			}

			ShowMessage(2,"use following input data for significance:");
			para.path.output_file  = para.default_path.output_file  + Int_to_String(i) + Int_to_String(j);
			ShowMessage(2,"output file        ",para.path.output_file);

			AFile file_name;
			get_file_name(para,file_name);

			ShowMessage(2,"make effi plots for beam pol ",i,j);
			std::vector<std::string> ana_out_name;
			for(int i=0;i<file_name.Output_Num();i++){
				ana_out_name.push_back(file_name.output[i].ana_data);
			}
    		Make_Efficiency_Plot(para,ana_out_name,file_name.efficiency_plot);
		}
	}
	para.path = para.default_path ;
}


