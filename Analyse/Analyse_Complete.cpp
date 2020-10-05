#include "Analyse_Complete.h"


void Analyse_Complete(CDraw &para){
	float elec_pol                      = para.scenario.elec_pol;
	float posi_pol                      = para.scenario.posi_pol;

	std::string event_file              = para.path.event_file   ;
	std::string output_file             = para.path.output_file  ;
	std::string single_plot             = para.path.single_plot  ;
	std::string combine_plot            = para.path.combine_plot ;
	std::string horizontal_summary_plot = para.path.horizontal_summary_plot ;

	std::string MVA_dataset             = "";


	bool only_lr                        = false;
	if(para.scenario.Run_Ratio_Vec().size()==2){
		only_lr =true;
	}
	for(int i=-1;i<2;i=i+2){
		for(int j=-1;j<2;j=j+2){
			if(only_lr){
				if(i==j){continue;}
			}
			para.scenario.elec_pol     = i * elec_pol;
			para.scenario.posi_pol     = j * posi_pol;
			para.scenario.Cal_Pol();


			para.path.event_file   = event_file   + Int_to_String(i) + Int_to_String(j);
			para.path.output_file  = output_file  + Int_to_String(i) + Int_to_String(j);
			para.path.single_plot  = single_plot  + Int_to_String(i) + Int_to_String(j);
			para.path.combine_plot = combine_plot + Int_to_String(i) + Int_to_String(j);
			para.path.horizontal_summary_plot = horizontal_summary_plot + Int_to_String(i) + Int_to_String(j);

			para.path.Create_Folder();

			Analyse_Complete_Pol(para,true,MVA_dataset);
		}
	}

	para.path.event_file              = event_file   ;
	para.path.single_plot             = single_plot  ;
	para.path.output_file             = output_file;
	para.path.combine_plot            = combine_plot ;
	para.path.horizontal_summary_plot = horizontal_summary_plot;
	para.scenario.elec_pol            = elec_pol;
	para.scenario.posi_pol            = posi_pol;

	para.path.Create_Folder();

	Make_Complete_Table_Pre(para);

	Analyse_Sensitivity_Complete(para);
}


void Analyse_Complete_Pol(CDraw &para, bool MVA_train_switch,std::string &MVA_dataset){

			AFile file_name;

			get_file_name(para,file_name);

			ShowMessage(2,"open record significance file");
			std::ofstream sig_file;
			sig_file.open(file_name.significance);

			RecordMessage(sig_file,2,"electron pol       ",para.scenario.elec_pol);
			RecordMessage(sig_file,2,"positron pol       ",para.scenario.posi_pol);
			RecordMessage(sig_file,2,"running luminosity ",para.scenario.scenario[0].lumi);

			RecordMessage(sig_file,2,"event file         ",para.path.event_file);
			RecordMessage(sig_file,2,"output file        ",para.path.output_file);
			RecordMessage(sig_file,2,"single_plot file   ",para.path.single_plot);
			RecordMessage(sig_file,2,"combine_plot file  ",para.path.combine_plot);
			RecordMessage(sig_file,2,"horizontal_summary_plot ",para.path.horizontal_summary_plot);

    		Analyse_Pre_Cut_Content(para,file_name);
    		Analyse_MVA_Train(para,file_name);
    		MVA_dataset = file_name.dataset_MVA;
    		Analyse_MVA_Attach(para,file_name);
			Analyse_Direct_Cut(para,file_name);

			std::vector<std::string> ana_out_name;
			for(int i=0;i<file_name.Output_Num();i++){
				ana_out_name.push_back(file_name.output[i].ana_data);
			}

			float sig=Make_Table(para,0,ana_out_name,file_name.output_table);

			RecordMessage(sig_file,2,"significance is", sig);

			sig_file.close();
}



void Analyse_Complete_Direct_Cut(CDraw &para){
	float elec_pol                      = para.scenario.elec_pol;
	float posi_pol                      = para.scenario.posi_pol;

	std::string event_file              = para.path.event_file   ;
	std::string output_file             = para.path.output_file  ;
	std::string single_plot             = para.path.single_plot  ;
	std::string combine_plot            = para.path.combine_plot ;
	std::string horizontal_summary_plot = para.path.horizontal_summary_plot ;

	for(int i=-1;i<2;i=i+2){
		for(int j=-1;j<2;j=j+2){
			if(para.scenario.Run_Ratio_Vec().size()==2){
				if(i==j){continue;}
			}
			para.scenario.elec_pol            = i * elec_pol;
			para.scenario.posi_pol            = j * posi_pol;

			para.path.event_file              = event_file   + Int_to_String(i) + Int_to_String(j);
			para.path.output_file             = output_file  + Int_to_String(i) + Int_to_String(j);
			para.path.single_plot             = single_plot  + Int_to_String(i) + Int_to_String(j);
			para.path.combine_plot            = combine_plot + Int_to_String(i) + Int_to_String(j);
			para.path.horizontal_summary_plot = horizontal_summary_plot + Int_to_String(i) + Int_to_String(j);
			para.path.Create_Folder();

			AFile file_name;

			get_file_name(para,file_name);

			ShowMessage(2,"open record significance file");
			std::ofstream sig_file;
			sig_file.open(file_name.significance);

            RecordMessage(sig_file,2,"electron pol            ",para.scenario.elec_pol           );
            RecordMessage(sig_file,2,"positron pol            ",para.scenario.posi_pol           );
            RecordMessage(sig_file,2,"event file              ",para.path.event_file             );
            RecordMessage(sig_file,2,"output file             ",para.path.output_file            );
            RecordMessage(sig_file,2,"single_plot file        ",para.path.single_plot            );
            RecordMessage(sig_file,2,"combine_plot file       ",para.path.combine_plot           );
            RecordMessage(sig_file,2,"horizontal_summary_plot ",para.path.horizontal_summary_plot);
            RecordMessage(sig_file,2,"running luminosity      ",para.scenario.Lumi()             );
                        
    		Analyse_Direct_Cut(para,file_name);

    		std::vector<std::string> ana_out_name;
    		for(int i=0;i<file_name.Output_Num();i++){
    			ana_out_name.push_back(file_name.output[i].ana_data);
    		}
			//float sig=Make_Table(para,para.scenario.Lumi(),ana_out_name,file_name.output_table);
			float sig=Make_Table(para,0,ana_out_name,file_name.output_table);

    		RecordMessage(sig_file,2,"significance is", sig);

    		sig_file.close();
    	}
    }

    para.path.output_file  = output_file;
    Make_Complete_Table_Pre(para);
}
