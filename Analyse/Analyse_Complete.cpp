#include "Analyse_Complete.h"


void Analyse_Complete(CDraw &para){
	float elec_pol                      = para.scenario.elec_pol;
	float posi_pol                      = para.scenario.posi_pol;

	std::string event_file              = para.path.event_file   ;
	std::string output_file             = para.path.output_file  ;
	std::string single_plot             = para.path.single_plot  ;
	std::string combine_plot            = para.path.combine_plot ;
	std::string horizontal_summary_plot = para.path.horizontal_summary_plot ;



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

			Analyse_Complete_Pol(para);
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

	Make_Complete_Efficiency_Plot_Pre(para);

	Analyse_Sensitivity_Complete(para);
}


void Analyse_Complete_Pol(CDraw &para){

			AFile file_name;

			get_file_name(para,file_name, true);

			ShowMessage(2,"in Analyse_Complete_Pol::open record significance file");
			std::ofstream sig_file;
			sig_file.open(file_name.significance);

			RecordMessage(sig_file,2,"electron pol       ",para.scenario.elec_pol);
			RecordMessage(sig_file,2,"positron pol       ",para.scenario.posi_pol);
			RecordMessage(sig_file,2,"running luminosity ",para.scenario.default_scenario.lumi);

			RecordMessage(sig_file,2,"event file         ",para.path.event_file);
			RecordMessage(sig_file,2,"output file        ",para.path.output_file);
			RecordMessage(sig_file,2,"single_plot file   ",para.path.single_plot);
			RecordMessage(sig_file,2,"combine_plot file  ",para.path.combine_plot);
			RecordMessage(sig_file,2,"horizontal_summary_plot ",para.path.horizontal_summary_plot);

    		Analyse_Pre_Cut_Content(para,file_name);
			if(para.var.num_MVA>0){
				Analyse_MVA_Train(para,file_name,1);
			}
		    if((para.var.num_MVA1>0)&&(para.MVA.mva.size()==2)){
				Analyse_MVA_Train(para,file_name,2);
			}
			if(para.var.num_MVA>0){
				Analyse_MVA_Attach(para,file_name,1);
			}
		    if((para.var.num_MVA1>0)&&(para.MVA.mva.size()==2)){
				Analyse_MVA_Attach(para,file_name,2);
			}
			Analyse_Direct_Cut(para,file_name);

			std::vector<std::string> ana_out_name;
			for(int i=0;i<file_name.Output_Num();i++){
				ana_out_name.push_back(file_name.output[i].ana_data);
			}

			float sig=Make_Table(para,0,ana_out_name,file_name.output_table);

    		Make_Efficiency_Plot(para,ana_out_name,file_name.efficiency_plot);

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

			get_file_name(para,file_name,true);

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
            RecordMessage(sig_file,2,"running luminosity      ",para.scenario.Pol_Lumi()         );
                        
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

	para.path                  = para.default_path ;
	para.scenario.elec_pol            = elec_pol;
	para.scenario.posi_pol            = posi_pol;
    Make_Complete_Table_Pre(para);
	Make_Complete_Efficiency_Plot_Pre(para);
}



void Analyse_Complete_MVA_Train(CDraw &para){
	for(int i=-1;i<2;i=i+2){
		for(int j=-1;j<2;j=j+2){
			if(para.scenario.Run_Ratio_Vec().size()==2){
				if(i==j){continue;}
			}
			para.scenario.elec_pol            = i * para.default_scenario.elec_pol;
			para.scenario.posi_pol            = j * para.default_scenario.posi_pol;
			para.scenario.Cal_Pol();
			para.scenario.Cal_Lumi(i,j);

			para.path.event_file   = para.default_path.event_file   + Int_to_String(i) + Int_to_String(j);
			para.path.output_file  = para.default_path.output_file  + Int_to_String(i) + Int_to_String(j);
			para.path.single_plot  = para.default_path.single_plot  + Int_to_String(i) + Int_to_String(j);
			para.path.combine_plot = para.default_path.combine_plot + Int_to_String(i) + Int_to_String(j);
			para.path.horizontal_summary_plot = para.default_path.horizontal_summary_plot + Int_to_String(i) + Int_to_String(j);
			para.path.Create_Folder();

			AFile file_name;

			get_file_name(para,file_name, true);

			if(para.var.num_MVA>0){
				Analyse_MVA_Train(para,file_name,1);
			}
			if(para.var.num_MVA1>0){
				Analyse_MVA_Train(para,file_name,2);
			}

    	}
    }

	para.path                  = para.default_path ;
	para.scenario              = para.default_scenario;
}

void Analyse_Complete_MVA_Attach(CDraw &para){

	for(int i=-1;i<2;i=i+2){
		for(int j=-1;j<2;j=j+2){
			if(para.scenario.Run_Ratio_Vec().size()==2){
				if(i==j){continue;}
			}
			para.scenario.elec_pol            = i * para.default_scenario.elec_pol;
			para.scenario.posi_pol            = j * para.default_scenario.posi_pol;
			para.scenario.Cal_Pol();
			para.scenario.Cal_Lumi(i,j);

			para.path.event_file   = para.default_path.event_file   + Int_to_String(i) + Int_to_String(j);
			para.path.output_file  = para.default_path.output_file  + Int_to_String(i) + Int_to_String(j);
			para.path.single_plot  = para.default_path.single_plot  + Int_to_String(i) + Int_to_String(j);
			para.path.combine_plot = para.default_path.combine_plot + Int_to_String(i) + Int_to_String(j);
			para.path.horizontal_summary_plot = para.default_path.horizontal_summary_plot + Int_to_String(i) + Int_to_String(j);
			para.path.Create_Folder();

			AFile file_name;

			get_file_name(para,file_name, true);

			if(para.var.num_MVA>0){
				Analyse_MVA_Attach(para,file_name,1);
			}
			if(para.var.num_MVA1>0){
				Analyse_MVA_Attach(para,file_name,2);
			}

    	}
    }

	para.path                  = para.default_path ;
	para.scenario              = para.default_scenario;
}


void Analyse_Complete_Direct_Cut_And_After(CDraw &para){

	bool only_lr                        = false;
	if(para.scenario.Run_Ratio_Vec().size()==2){
		only_lr =true;
	}
	for(int i=-1;i<2;i=i+2){
		for(int j=-1;j<2;j=j+2){
			if(only_lr){
				if(i==j){continue;}
			}
			para.scenario.elec_pol     = i * para.default_scenario.elec_pol;
			para.scenario.posi_pol     = j * para.default_scenario.posi_pol;
			para.scenario.Cal_Pol();
			para.scenario.Cal_Lumi(i,j);


			para.path.event_file   = para.default_path.event_file   + Int_to_String(i) + Int_to_String(j);
			para.path.output_file  = para.default_path.output_file  + Int_to_String(i) + Int_to_String(j);
			para.path.single_plot  = para.default_path.single_plot  + Int_to_String(i) + Int_to_String(j);
			para.path.combine_plot = para.default_path.combine_plot + Int_to_String(i) + Int_to_String(j);
			para.path.horizontal_summary_plot = para.default_path.horizontal_summary_plot + Int_to_String(i) + Int_to_String(j);

			para.path.Create_Folder();

			Analyse_Complete_Pol_Direct_Cut_And_After(para);
		}
	}

	para.path                  = para.default_path ;
	para.scenario              = para.default_scenario;

	para.path.Create_Folder();

	Make_Complete_Table_Pre(para);

	Make_Complete_Efficiency_Plot_Pre(para);

	Analyse_Sensitivity_Complete(para);
}

void Analyse_Complete_Pol_Direct_Cut_And_After(CDraw &para){

			AFile file_name;

			get_file_name(para,file_name,true);

			ShowMessage(2,"open record significance file");
			std::ofstream sig_file;
			sig_file.open(file_name.significance);

			RecordMessage(sig_file,2,"electron pol       ",para.scenario.elec_pol);
			RecordMessage(sig_file,2,"positron pol       ",para.scenario.posi_pol);
			RecordMessage(sig_file,2,"running luminosity ",para.scenario.Lumi());

			RecordMessage(sig_file,2,"event file         ",para.path.event_file);
			RecordMessage(sig_file,2,"output file        ",para.path.output_file);
			RecordMessage(sig_file,2,"single_plot file   ",para.path.single_plot);
			RecordMessage(sig_file,2,"combine_plot file  ",para.path.combine_plot);
			RecordMessage(sig_file,2,"horizontal_summary_plot ",para.path.horizontal_summary_plot);

			Analyse_Direct_Cut(para,file_name);

			std::vector<std::string> ana_out_name;
			for(int i=0;i<file_name.Output_Num();i++){
				ana_out_name.push_back(file_name.output[i].ana_data);
			}

			float sig=Make_Table(para,0,ana_out_name,file_name.output_table);

    		Make_Efficiency_Plot(para,ana_out_name,file_name.efficiency_plot);

			RecordMessage(sig_file,2,"significance is", sig);

			sig_file.close();
}
