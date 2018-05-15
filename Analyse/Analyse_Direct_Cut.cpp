#include "Analyse_Direct_Cut.h"


void Analyse_Direct_Cut_Pre(CDraw &para){
	AFile file_name;
	get_file_name(para,file_name);

	std::ofstream sig_file;
	sig_file.open(file_name.significance);

	Analyse_Direct_Cut(para,file_name);

	std::vector<std::string> ana_out_name;
	for(int i=0;i<file_name.Output_Num();i++){
		ana_out_name.push_back(file_name.output[i].ana_data);
	}
	float sig=Make_Table(para,para.scenario.Lumi(),ana_out_name,file_name.output_table,true);

	RecordMessage(sig_file,2,"significance is", sig);

	sig_file.close();
}

void Analyse_Direct_Cut(CDraw &para, AFile &file_name){

	ShowMessage(2,"analyse events");

	int filenum=file_name.Output_Num();



	Analyse_Multi_File        analyse(para,file_name);
	std::vector<TFile*>       in_file                ;
	std::vector<int>          nevent                 ;
	std::vector<TTree*>       MyLCTuple              ;


	for(int j=0;j<filenum;j++){
		if( para.flow.begin_object  == "Direct_Cut" ||
			(para.flow.begin_object == "Direct_Cut_NoMVA" && file_name.input[0].basic_file.size()>1) ||
			para.flow.begin_object  == "Complete_Direct_Cut"||
			para.flow.begin_object  == "Complete_Run"){

			in_file                .push_back(new TFile(file_name.output[j].MVA_file.c_str()));
			in_file[j]->cd();
			MyLCTuple              .push_back((TTree*)in_file[j]->Get(para.file.root_head_name.c_str()));
			nevent                 .push_back(MyLCTuple[j]->GetEntries()                     );

		}
		else if(para.flow.begin_object == "Direct_Cut_NoMVA" && file_name.input[0].basic_file.size()==1){
			std::string fname         = file_name.input[j].basic_file[0];
			in_file                   .push_back(new TFile(fname.c_str()));
			in_file[j]                ->cd();
			MyLCTuple                 .push_back((TTree*)in_file[j]->Get(para.file.root_head_name.c_str()));
			nevent                    .push_back(MyLCTuple[j]->GetEntries()                     );
		}
		if(analyse.var.weight_exist){
			if(analyse.var.weight_type=="F"){
				MyLCTuple[j]->SetBranchAddress("weight", &analyse.file[j].in_weight);
			}
			else if(analyse.var.weight_type=="D"){
				MyLCTuple[j]->SetBranchAddress("weight", &analyse.file[j].in_weight_d);
			}
			else if(analyse.var.weight_type=="I"){
				MyLCTuple[j]->SetBranchAddress("weight", &analyse.file[j].in_weight_i);
			}
		}
		else{
			analyse.file[j].in_weight = file_name.input[j].xection[0]/nevent[j];  
		}
		for(int k=0;k<analyse.Var_Num();k++){
			if(analyse.var.var[k].title_name=="weight"){
				continue;
			}
			if(analyse.var.var[k].variable_type=="F"){
				MyLCTuple[j]->SetBranchAddress(analyse.var.var[k].title_name.c_str(), &analyse.var.var[k].variable);
			}
			else if(analyse.var.var[k].variable_type=="I"){
				MyLCTuple[j]->SetBranchAddress(analyse.var.var[k].title_name.c_str(), &analyse.var.var[k].variable_i);
				analyse.var.var[k].variable = static_cast<float> (analyse.var.var[k].variable_i);
			}
			else if(analyse.var.var[k].variable_type=="D"){
				MyLCTuple[j]->SetBranchAddress(analyse.var.var[k].title_name.c_str(), &analyse.var.var[k].variable_d);
				analyse.var.var[k].variable = static_cast<float> (analyse.var.var[k].variable_d);
			}
		}
	}


	std::ofstream myfile_tot;
	if(filenum>1){
		myfile_tot.open(file_name.output_total.ana_data);
	}


	//loop for all input files
	for(int cnum=0;cnum<filenum;cnum++){
		ShowMessage(2,"dealing with", file_name.output[cnum].name);

		std::ofstream myfile;
		myfile.open(file_name.output[cnum].ana_data);

		RecordMessage(myfile,2,"filenum", "");


		//loop for reading variables and setting cuts 
		long int total_event=nevent[cnum];
		para.event.Init(total_event);
		analyse.Root_Init(para,file_name,cnum);
		for(long int event = para.event.Begin_Event(); event < para.event.End_Event(); ++event){

			CountNumber(event,para.Total_Event(),1000,"has dealed with number are");

			para.Get_Event(event);

			MyLCTuple[cnum]->GetEntry(event);

			if(analyse.var.weight_type=="D"){
				analyse.file[cnum].in_weight = static_cast<float> (analyse.file[cnum].in_weight_d);
			}
			else if(analyse.var.weight_type=="I"){
				analyse.file[cnum].in_weight = static_cast<float> (analyse.file[cnum].in_weight_i);
			}

			for(int k=0;k<analyse.Var_Num();k++){
				if(analyse.var.var[k].variable_type=="I"){
					analyse.var.var[k].variable = static_cast<float> (analyse.var.var[k].variable_i);
				}
				if(analyse.var.var[k].variable_type=="D"){
					analyse.var.var[k].variable = static_cast<float> (analyse.var.var[k].variable_d);
				}
			}
			analyse.Root_Init_Var    ( cnum );

			analyse.Root_Endow_Weight( cnum ) ;

			analyse.Plot_Origin      ( cnum ) ;

			analyse.Add_Pass_NoCut   ( cnum ) ;

			if( !analyse.Get_Cut     ( cnum ) ) {continue;}

			//analyse.Root_Endow_Var   ( cnum   ) ;

			analyse.Add_Pass_AllCut  ( cnum ) ;

			analyse.Plot_Final       ( cnum ) ;

			analyse.Root_Fill        ( cnum ) ;

		}                

		analyse.Record_Information(cnum,myfile,file_name.output[cnum].latex);

		analyse.Add_Tot_Pass(cnum);

		myfile.close();

		analyse.Root_Close(cnum);
		ShowMessage(2);
	}


	if(filenum>1){
		analyse.Record_Tot_Information(myfile_tot,file_name.output_total.latex);
	}

	analyse.Draw_Figure(para,file_name);

	analyse.Root_Close_Last(para);

	ShowMessage(2,"delete file pointers!");

	for(int i=0;i<filenum;i++){
		in_file[i]->cd();
		ShowMessage(2,"file name",in_file[i]->GetName());
		delete MyLCTuple[i];
		delete in_file[i];
	}

	ShowMessage(2,"Finish Direct Cut");
	return;
}

