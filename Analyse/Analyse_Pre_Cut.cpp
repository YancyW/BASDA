#include "Analyse_Pre_Cut.h"
void Analyse_Pre_Cut(CDraw &para){
	AFile file_name;
	get_file_name(para,file_name);

	std::ofstream sig_file;
	sig_file.open(file_name.significance);

	Analyse_Pre_Cut_Content(para,file_name);

	std::vector<std::string> ana_out_name;
	for(int i=0;i<file_name.Output_Num();i++){
		ana_out_name.push_back(file_name.output[i].ana_Unpol);
	}
	Make_Table(para,para.scenario.Lumi(),ana_out_name,file_name.output_table,true);

	sig_file.close();
}


void Analyse_Pre_Cut_Content(CDraw &para, AFile &file_name){

	ShowMessage(2,"analyse events");

	int filenum=file_name.Input_Num();

	std::vector<int>          filenum_i;
	for(int i=0;i<filenum;i++){
		filenum_i.push_back(file_name.input[i].Num());
	}


	std::vector<std::vector<float> >       xection         ;
	std::vector<std::vector<std::string> > filename        ;
	std::vector<std::vector<TFile*> >      in_file         ;
	std::vector<std::vector<long int> >         nevent     ;
	std::vector<std::vector<float> >       weight          ;
	std::vector<std::vector<TTree*> >      MyLCTuple       ;
	std::vector<std::vector<std::vector<float> > >      pass;

	std::vector<float >       xection_i         ;
	std::vector<std::string>  filename_i        ;
	std::vector<TFile*>       in_file_i         ;
	std::vector<long int>     nevent_i          ;
	std::vector<float>        weight_i          ;
	std::vector<TTree*>       MyLCTuple_i       ;
	std::vector<std::vector<float> >       pass_i ;
	std::vector<float> pass_i_cut;

	ACut cut;
	cut.Read_Cut(para.path);

	for(int i=0;i<filenum;i++){
		for(int j=0;j<filenum_i[i];j++){
			xection_i                .push_back(file_name.input[i].xection[j]            );
			filename_i               .push_back(file_name.input[i].basic_file[j]         );
			in_file_i                .push_back(new TFile(filename_i[j].c_str())         );
			in_file_i[j]->cd();
			MyLCTuple_i              .push_back((TTree*)in_file_i[j]->Get(para.file.root_head_MVA_name.c_str())   );
			nevent_i                 .push_back(MyLCTuple_i[j]->GetEntries()             );
			if(filenum_i[i]!=1){
				weight_i             .push_back(xection_i[j]/nevent_i[j]*para.scenario.pol[j]);
			}
			else{
				weight_i             .push_back(xection_i[j]/nevent_i[j]                 );
			}
			pass_i_cut.clear();
			for(int k=0;k<cut.pre_cut_num+2;k++){
				pass_i_cut.push_back(0.0);
			}
			pass_i                   .push_back(pass_i_cut                               );
		}
		filename_i                   .push_back("total");
		nevent_i                     .push_back(0.0    );
		pass_i_cut.clear();
		for(int k=0;k<cut.pre_cut_num+2;k++){
			pass_i_cut.push_back(0.0);
		}
		pass_i                       .push_back(pass_i_cut        );

		xection                      .push_back(xection_i         );
		filename                     .push_back(filename_i        );
		in_file                      .push_back(in_file_i         );
		MyLCTuple                    .push_back(MyLCTuple_i       );
		nevent                       .push_back(nevent_i          );
		weight                       .push_back(weight_i          );
		pass                         .push_back(pass_i            );

		xection_i                    .clear();
		filename_i                   .clear();
		MyLCTuple_i                  .clear();
		in_file_i                    .clear();
		nevent_i                     .clear();
		weight_i                     .clear();
		pass_i                       .clear();
	}









	//loop for all input files
	for(int cnum=0;cnum<filenum;cnum++){
		ShowMessage(1,"dealing with", file_name.output[cnum].name);
		std::ofstream myfile;
		if(para.flow.begin_object == "Pre_Cut"){
			ShowMessage(1,"the analyse file is", file_name.output[cnum].ana_Unpol);
			myfile.open(file_name.output[cnum].ana_Unpol);
			RecordMessage(myfile,1,"filenum", "");
		}


		TFile* otfile;
		TFile* otfile_MVA ;
		TTree* datatrain= new TTree();
		TTree* datatest = new TTree();
		TTree* datatest_MVA = new TTree();
		float  out_weight;
		std::vector<float>         rootvar;

		std::vector<std::vector<float> >         rootvar_vec;

		if(para.flow.record_event){
			otfile = TFile::Open( file_name.output[cnum].Unpol_file.c_str() , "RECREATE" );
			if (!otfile) {
				std::cout << "ERROR: could not open data file" << std::endl;
				exit(1);
			}
			otfile->cd();

			datatrain= new TTree(para.file.root_head_MVA_name.c_str() , "events" );
			rootvar     .resize(para.var.num);
			rootvar_vec .resize(para.var.num_vec);

			datatrain->Branch( "weight"              , &out_weight );        
			for(int i=0;i<para.var.num;i++){
				if(para.var.var[i].title_name=="MVA"){
					continue;
				}
				datatrain->Branch( para.var.var[i].title_name.c_str() , &rootvar[i] );        
			}
			for(int i=0;i<para.var.num_vec;i++){
				datatrain->Branch( para.var.vec[i].title_name.c_str() , &rootvar_vec[i] );        
			}

			if(para.flow.MVA_training){
				datatest= new TTree( para.file.root_head_name.c_str() , "events" );
				datatest->Branch( "weight"              , &out_weight );        
				for(int i=0;i<para.var.num;i++){
					if(para.var.var[i].title_name=="MVA"){
						continue;
					}
					datatest->Branch( para.var.var[i].title_name.c_str() , &rootvar[i] );        
				}
				for(int i=0;i<para.var.num_vec;i++){
					datatest->Branch( para.var.vec[i].title_name.c_str() , &rootvar_vec[i] );        
				}
			}


			otfile_MVA = TFile::Open( file_name.output[cnum].MVA_file.c_str() , "RECREATE" );
			if (!otfile_MVA) {
				std::cout << "ERROR: could not open data file" << std::endl;
				exit(1);
			}
			otfile_MVA->cd();

			if(para.flow.MVA_training){
				datatest_MVA = new TTree( para.file.root_head_name.c_str() , "events" );
				datatest_MVA->Branch( "weight"              , &out_weight );        
				for(int i=0;i<para.var.num;i++){
					if(para.var.var[i].title_name=="MVA"){
						continue;
					}
					datatest_MVA->Branch( para.var.var[i].title_name.c_str() , &rootvar[i] );        
				}
				for(int i=0;i<para.var.num_vec;i++){
					datatest_MVA->Branch( para.var.vec[i].title_name.c_str() , &rootvar_vec[i] );        
				}
			}
		}


		for(int i=0;i<filenum_i[cnum];i++){

			if(i==0){
				ShowMessage(2,"dealing with pol LR");
			}
			else if(i==1){
				ShowMessage(2,"dealing with pol RL");
			}
			else if(i==2){
				ShowMessage(2,"dealing with pol LL");
			}
			else if(i==3){
				ShowMessage(2,"dealing with pol RR");
			}


			//loop for init variables which are prepared for plot 
			for(int j=0;j<para.var.num;j++){
				if(para.var.var[j].title_name=="MVA"){
					continue;
				}
				Avariable info=para.var.var[j];
				MyLCTuple[cnum][i]->SetBranchAddress(info.title_name.c_str(), &para.var.var[j].variable);
			}


			for(int j=0;j<para.var.num_vec;j++){
				Avariable_vec info=para.var.vec[j];
				MyLCTuple[cnum][i]->SetBranchAddress(para.var.vec[j].title_name.c_str(), &para.var.vec[j].var_ptr);
			}
			//loop for reading variables and setting cuts 
			long int total_event=nevent[cnum][i];
			para.event.Init(total_event);
			for(long int event = para.event.Begin_Event(); event < para.event.End_Event(); ++event){

				para.Get_Event(event);
				CountNumber(event,para.Total_Event(),1000,"has dealed with number are");

				MyLCTuple[cnum][i]->GetEntry(event);

				if(para.flow.record_event){
					for(int j=0;j<para.var.num;j++){
						if(para.var.var[j].title_name=="MVA"){
							continue;
						}
						rootvar[j]=para.var.var[j].variable;
						out_weight=weight[cnum][i];
					}
				}

				// add cuts
				float event_rate=event/(float)total_event;

				if(para.flow.begin_object == "Pre_Cut"){
					if(para.flow.MVA_level==1){
						Fill_Tree(para,event_rate,datatest_MVA);
					}
					pass[cnum][i][cut.pre_cut_num+1]+=out_weight;

					bool pass_cut=true;
					for(int icut=0;icut<cut.pre_cut_num;icut++){
						if(!Apply_Cut(para, out_weight,  cut.pre_cut[icut],pass[cnum][i][icut])){
							pass_cut=false;
							break;
						}
					}

					if(!pass_cut){
						continue;
					}
					if(para.flow.MVA_level==2){
						Fill_Tree(para,event_rate,datatest_MVA);
					}
					Fill_Tree(para,event_rate,datatest,datatrain);
					pass[cnum][i][cut.pre_cut_num]+=out_weight;
				}
				else if(para.flow.begin_object == "Direct_Cut_NoMVA"){
					Fill_Tree(para,event_rate,datatest_MVA);
				}

			}

			if(para.flow.begin_object == "Pre_Cut"){
				for(int icut=0;icut<=cut.pre_cut_num+1;icut++){
					pass[cnum][filenum_i[cnum]][icut]+=pass[cnum][i][icut];
				}
				nevent         [cnum][filenum_i[cnum]]+=nevent         [cnum][i];

				RecordMessage(myfile,3,filename                      [cnum][i], ""                 );
				RecordMessage(myfile,4,"weight                         "      , weight          [cnum][i]);
				RecordMessage(myfile,4,"no cut MC event                "      , nevent          [cnum][i]);
				RecordMessage(myfile,4,"no cut                         "      , pass[cnum][i][cut.pre_cut_num+1]);

				for(int icut=0;icut<cut.pre_cut_num;icut++){
					RecordMessage(myfile,4,para.var.var[cut.pre_cut[icut]].latex_name     , pass[cnum][i][icut]);
				}
				RecordMessage(myfile,4,"all~cut"     , pass[cnum][i][cut.pre_cut_num]);
			}

		}

		if(para.flow.begin_object == "Pre_Cut"){
			RecordMessage(myfile,3,"total result"                    , ""                                    );
			RecordMessage(myfile,4,file_name.input[cnum].latex       , "[ 0" ,                        "0 ]"  );
			RecordMessage(myfile,4,"no cut MC event                " , "[  "+Float_to_String(nevent[cnum][filenum_i[cnum]]), Float_to_String(nevent[cnum][filenum_i[cnum]])+" ]");
			RecordMessage(myfile,4,"no cut                         " , "[  "+Float_to_String(pass[cnum][filenum_i[cnum]][cut.pre_cut_num+1]),Float_to_String(pass[cnum][filenum_i[cnum]][cut.pre_cut_num+1])+" ]");
			for(int icut=0;icut<cut.pre_cut_num;icut++){
				RecordMessage(myfile,4, para.var.var[cut.pre_cut[icut]].latex_name     , "[  "+Float_to_String(pass[cnum][filenum_i[cnum]][icut]),Float_to_String(pass[cnum][filenum_i[cnum]][icut])+" ]");
			}
			RecordMessage(myfile,4,"all~cut"     , "[ "+Float_to_String(pass[cnum][filenum_i[cnum]][cut.pre_cut_num]), Float_to_String(pass[cnum][filenum_i[cnum]][cut.pre_cut_num])+" ]");

			myfile.close();
		}

		ShowMessage(2);
		if(para.flow.record_event){
			otfile->cd();
			datatrain->Write();
			if(para.flow.MVA_training){
				datatest->Write();
			}
			otfile->Close();

			otfile_MVA->cd();
			if(para.flow.MVA_training){
				datatest_MVA->Write();
			}
			otfile_MVA->Close();
		}
	}


	ShowMessage(2,"delete all pointers!");

	for(int i=0;i<filenum;i++){
		for(int j=0;j<filenum_i[i];j++){
			delete in_file[i][j];
		}
	}

	return;
}

