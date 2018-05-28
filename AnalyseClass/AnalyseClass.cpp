#include "AnalyseClass/AnalyseClass.h"


/*****************************************************************************************
 * @name  Analyse_Multi_File 
 * *****************************************************************************************/

void Analyse_Multi_File::_Find_Which_Sort (CDraw& para, AFile & file_name, int filenum ) {
	std::size_t found_class,found_fs; 
	std::vector<std::string> strNew=Find_Str_in_Filename(file_name.output[filenum].latex);
	for(int k=0;k<para.bkg_sort.Num();k++){
		found_class = file_name.output[filenum].name.find(para.bkg_sort.sort[k].Class());
		if (strNew[0]==para.bkg_sort.sort[k].Class()){
			for(int l=0;l<para.bkg_sort.sort[k].Sub_Num();l++){
				if (strNew[2]==para.bkg_sort.sort[k].Sub_Class(l)){
					_which_sort = &sort[k].second[l];
					return;
				}
			}
		}
	}
}



int Analyse_Multi_File::Var_Num(){
	return(_var_num);
}

/*****************************************************************************************
 * @Name: Init 
 *
 * @Param: para
 * @Param: file_name
 *****************************************************************************************/
void Analyse_Multi_File::Init(CDraw &para, AFile &file_name){

	if(para.flow.begin_object=="Pre_Cut"){
		_extra_weight = 1;
	}
	else{
		_extra_weight  = para.flow.MVA_weight * para.scenario.Lumi();
	}

	_root_file = TFile::Open( file_name.plot_CUT.c_str() , "RECREATE" );
	_list      = new TList();
	_Has_Drawn = false;

	_record_switch = para.flow.record_event;
	_plot_switch   = para.flow.plot;

	if(!para.flow.record_output){
		freopen(para.path.record_file.c_str() ,"a",stdout);
	}
	var=para.var;
	_var_num = var.num;


	_cut.Read_Cut(para.path);

	ShowMessage(2,"finish input para, begin to analyse part");
	if(!para.flow.record_output){
		fclose(stdout);
		freopen("/dev/tty","w",stdout);
	}
	_file_num=file_name.Output_Num();
	file.resize(_file_num+1);



	std::vector<std::string> normal_tree_name;
	normal_tree_name.push_back(para.file.root_head_name) ;

	std::vector<std::string> final_tree_name ;
	final_tree_name.push_back("sig") ;
	final_tree_name.push_back("bkg") ;

	// for each channel
	for(int j=0;j<_file_num;j++){
		file[j].Init    (var,_root_file,_extra_weight, _record_switch, _plot_switch,Int_to_String(j)        , file_name.output[j].CUT_file   ,normal_tree_name );
	}
	file[_file_num].Init(var,_root_file,_extra_weight, _record_switch, _plot_switch,Int_to_String(_file_num), file_name.output_total.CUT_file,final_tree_name  );



	// combine some channel into different sorts, plot for each sort 
	sort.resize(para.bkg_sort.Num());
	for(int k=0;k<para.bkg_sort.Num();k++){
		sort[k].second.resize(para.bkg_sort.sort[k].Sub_Num());
	}
	for(int k=0;k<para.bkg_sort.Num();k++){
		for(int l=0;l<para.bkg_sort.sort[k].Sub_Num();l++){
			std::string sort_name = file_name.folder[5]+"sort_"+para.bkg_sort.sort[k].Name(l)+".root"; 
			sort[k].second[l].Init(var,_root_file,_extra_weight, _record_switch, _plot_switch,Int_to_String(100+k*100+l), sort_name, normal_tree_name );
		}
	}
	_which_sort = NULL;

}

void Analyse_Multi_File::Clear(){
	delete _list;
	delete _root_file;
}

void Analyse_Multi_File::Root_Init(CDraw&para, AFile &file_name, int filenum){
	if(_record_switch){
		file[filenum].Root_Init();
	}
	_Find_Which_Sort(para, file_name, filenum);
}

void Analyse_Multi_File::Root_Init_Var(int filenum){ 
	_which_sort   ->Root_Init_Var();
	file[filenum]  .Root_Init_Var();
	file[_file_num].Root_Init_Var();
}

void Analyse_Multi_File::File_Init( std::ofstream &file_name, int filenum){
	if(filenum!=-1){
		file[filenum].File_Init(file_name);
	}
	else{
		if(file_name.is_open()){
			_data_file=&file_name;
		}
		else{
			ShowMessage(2,"in Analyse_Multi_File::File_Init, Haven't opened the file");
		}
	}
}

void Analyse_Multi_File::Root_Endow_Weight(int filenum){
	_which_sort   ->in_weight = file[filenum].in_weight;
	_which_sort   ->Root_Endow_Weight();
	file[filenum]  .Root_Endow_Weight();
	file[_file_num].Root_Endow_Weight();
}

void Analyse_Multi_File::Root_Endow_Var(int filenum){
	if(_record_switch){
		_which_sort     ->Root_Endow_Var(var);
		file[filenum]    .Root_Endow_Unused_Var(var,_cut);
		file[_file_num]  .Root_Endow_Var(var);
	}
}

void Analyse_Multi_File::Root_Fill(int filenum){
	if(_record_switch){
		_which_sort ->Root_Fill(0);
		if(filenum==0){
			file[_file_num].Root_Fill(0);
		}
		else{
			file[_file_num].Root_Fill(1);
		}
	}
}

void Analyse_Multi_File::Root_Close(int filenum){
	if(_record_switch){
		file[filenum].Root_Close_File();
	}
}

void Analyse_Multi_File::File_Close(int filenum){
	if(filenum!=-1){
		file[filenum].File_Close();
	}
	else{
		if(_data_file->is_open()){
			_data_file->close();
		}
	}
}


void Analyse_Multi_File::Root_Close_Last(CDraw & para){
	for(int k=0;k<para.bkg_sort.Num();k++){
		for(int l=0;l<para.bkg_sort.sort[k].Sub_Num();l++){
			sort[k].second[l].Root_Close_File();
		}
	}

	if(_record_switch){
		file[_file_num].Root_Close_File();
	}
}


void Analyse_Multi_File::Plot_Origin(int filenum){
	if(_plot_switch){
		file[filenum].Plot_Origin(var);
	}
}



void Analyse_Multi_File::Plot_Final (int filenum){
	if(_plot_switch){
		file[filenum].Plot_Final(var);
	}
}


void Analyse_Multi_File::Add_Pass_NoCut(int filenum){
	file[filenum].Add_Pass_NoCut();
}

void Analyse_Multi_File::Add_Pass_AllCut(int filenum){
	file[filenum].Add_Pass_AllCut();
}

void Analyse_Multi_File::Add_Tot_Pass(int filenum){
	if(filenum==0){return;}


	for(int i=0;i<_cut.cut_num;i++){
		int index=_cut.cut[i];
		_which_sort    ->figure[index].pass   +=file[filenum].figure[index     ].pass ;
		_which_sort    ->figure[index].event  +=file[filenum].figure[index     ].event;
		file[_file_num] .figure[index].pass   +=file[filenum].figure[index     ].pass ;
		file[_file_num] .figure[index].event  +=file[filenum].figure[index     ].event;
	}
	_which_sort    ->figure[_var_num]  .pass  +=file[filenum].figure[_var_num  ].pass ;
	_which_sort    ->figure[_var_num]  .event +=file[filenum].figure[_var_num  ].event;
	_which_sort    ->figure[_var_num+1].pass  +=file[filenum].figure[_var_num+1].pass ;
	_which_sort    ->figure[_var_num+1].event +=file[filenum].figure[_var_num+1].event;

	file[_file_num] .figure[_var_num]  .pass  +=file[filenum].figure[_var_num  ].pass ;
	file[_file_num] .figure[_var_num]  .event +=file[filenum].figure[_var_num  ].event;
	file[_file_num] .figure[_var_num+1].pass  +=file[filenum].figure[_var_num+1].pass ;
	file[_file_num] .figure[_var_num+1].event +=file[filenum].figure[_var_num+1].event;
}

bool Analyse_Multi_File::Get_Cut(int filenum){

	bool judge=file[filenum].Get_Cut(var,_cut);

	if(judge){
		_which_sort   ->Root_Endow_Var(var);
	}

	return(judge);
}


//void Analyse_Multi_File::Record_Information(int filenum,std::ofstream &_adata_file, std::string sample_name){
void Analyse_Multi_File::Record_Information(int filenum, std::string sample_name){
	//file[filenum].Record_Information(var,_cut,sample_name);
	file[filenum].Record_Information(var,_cut,sample_name);
}

//void Analyse_Multi_File::Record_Sort_Information(std::ofstream &myfile, std::string sample_name){
//	sort[k].second[j].Record_Information(myfile,var,_cut,sample_name);
//}

//void Analyse_Multi_File::Record_Tot_Information(std::ofstream &_adata_file, std::string sample_name){
void Analyse_Multi_File::Record_Tot_Information(std::string sample_name){
	ShowMessage(2,"combine all bkg results");
	RecordMessage(*_data_file,3,"result for all bkg "                , ""                    );
	RecordMessage(*_data_file,4,sample_name     , "[ 0"                                      , "0 ]" );
	RecordMessage(*_data_file,4,"no~cut "       , "[ "+ Float_to_String(file[_file_num].figure[_var_num  ].pass), Float_to_String(file[_file_num].figure[_var_num  ].event)+" ]" );
	for(int i=0;i<_cut.cut_num;i++){
		int index=_cut.cut[i];
		std::string var_name = var.var[index].latex_name + " \\in [ " + Float_to_String(var.var[index].cut_min) + " ," + Float_to_String(var.var[index].cut_max) + " ] ";
		RecordMessage(*_data_file,4,var_name    , "[ "+ Float_to_String(file[_file_num].figure[index     ].pass), Float_to_String(file[_file_num].figure[index     ].event)+" ]" );
	}
	RecordMessage(*_data_file,4,"all~cut "      , "[ "+ Float_to_String(file[_file_num].figure[_var_num+1].pass), Float_to_String(file[_file_num].figure[_var_num+1].event)+" ]" );
}

void Analyse_Multi_File::Draw_Single(CDraw &para, AFile& file_name,std::string hist_label){
	ShowMessage(2,"generate plot for "+hist_label+" results!");
	for(int j=0;j<_var_num;j++){
		Avariable info=var.var[j];
		ShowMessage(3,"generate plot for variable",info.title_name);
		if(info.plot_switch){
			info.leg->Clear();
			std::string leg_title = info.latex_name;
			info.leg->SetHeader(leg_title.c_str(),"l");
			std::string cname=info.c_name+"_"+Int_to_String(j);
			info.c=new TCanvas(cname.c_str()," ",info.c_width,info.c_height);

			gPad->SetGrid();
			std::vector<std::string> stack_title= Set_Stack_Title(para,info.title_name+"_"+hist_label);
			THStack *ss = new THStack(stack_title[0].c_str(),stack_title[1].c_str() );

			for(int nf=0;nf<file_name.Output_Num()+1;nf++){
				int i;
				if(nf==0){continue;}
				if(nf==file_name.Output_Num()){
					i=0;
				}
				else{
					i=nf;
				}
				TH1F* hist_tmp = (TH1F*) file[i].figure[j].Hist(hist_label)->Clone();
				info.leg->AddEntry(hist_tmp,file_name.output[i].name.c_str(),"l");
				bool set_line=Set_Line_Style(para,info,hist_tmp,i,i);
				ss->Add(hist_tmp);

			}

			if(ss->GetNhists()>0){
				_root_file->cd();
				ss->Draw("HIST,nostack");
				ss->Write();
				Set_Stack_Style(para,info,ss,gPad,hist_label);

				std::string leg_name = stack_title[0]+"_legend";
				info.leg->SetName(leg_name.c_str());
				info.leg->Draw();
				info.leg->Write();
				_list->Add(ss);


				//print to png
				Print_Plot(para, info, file_name.folder[1]+info.title_name+"_"+hist_label+".png");
				delete info.c;
				info.leg->Clear();
			}
		}
	}
}

void Analyse_Multi_File::Draw_Sort(CDraw& para, AFile& file_name,std::string hist_label){
	ShowMessage(2,"generate combined plot for sorted "+hist_label+" results!");
	for(int j=0;j<_var_num;j++){
		Avariable info=var.var[j];
		ShowMessage(3,"generate plot for variable",info.title_name);
		if(info.plot_switch){
			info.leg->Clear();
			std::string leg_header = info.latex_name;
			info.leg->SetHeader(leg_header.c_str(),"l");
			std::string cname=info.c_name+"_"+Int_to_String(j);
			info.c=new TCanvas(cname.c_str()," ",info.c_width,info.c_height);

			gPad->SetGrid();
			std::vector<std::string> stack_title= Set_Stack_Title(para,info.title_name+"_sort_"+hist_label);
			THStack *ss = new THStack(stack_title[0].c_str(),stack_title[1].c_str() );

			for(int nf=0;nf<file_name.Output_Num();nf++){
				_Find_Which_Sort(para,file_name,nf);
				_which_sort->figure[j].Hist(hist_label)->Add(file[nf].figure[j].Hist(hist_label));
			}

			int i=0;
			std::cout << "sort: " << para.bkg_sort.Num() << std::endl;
			for(int k=0;k<para.bkg_sort.Num();k++){
				std::cout << "sub sort: " << para.bkg_sort.sort[k].Sub_Num() << std::endl;
				for(int l=0;l<para.bkg_sort.sort[k].Sub_Num();l++){
					if(k==0 && l==0 && (k!=(para.bkg_sort.Num()-1) || l!=(para.bkg_sort.sort[k].Sub_Num()-1))){i++;continue;}
					double maxi = sort[k].second[l].figure[j].Hist(hist_label)->GetEntries();
					std::cout << "sort: " <<para.bkg_sort.sort[k].Legend(l)<< " " << maxi <<std::endl;
					if(maxi>0){
						std::string sort_name = para.bkg_sort.sort[k].Legend(l); 
						TH1F* hist_tmp = (TH1F*) sort[k].second[l].figure[j].Hist(hist_label)->Clone();
						info.leg->AddEntry(hist_tmp,sort_name.c_str(),"l");
						Set_Line_Style(para,info,hist_tmp,i,i);
						ss->Add(hist_tmp);
						i++;
					}
					if(k==para.bkg_sort.Num()-1 && l==para.bkg_sort.sort[k].Sub_Num()-1){
						double maxi0 = sort[0].second[0].figure[j].Hist(hist_label)->GetEntries();
						std::cout << "sort: " <<para.bkg_sort.sort[0].Legend(0)<< std::endl;
						if(maxi0>0){
							std::string sort_name = para.bkg_sort.sort[0].Legend(0); 
							TH1F* hist_tmp = (TH1F*) sort[0].second[0].figure[j].Hist(hist_label)->Clone();
							info.leg->AddEntry(hist_tmp,sort_name.c_str(),"l");
							Set_Line_Style(para,info,hist_tmp,0,0);
							ss->Add(hist_tmp);
						}
						i++;
					}
				}
			}

			if(ss->GetNhists()>0){
				_root_file->cd();
				ss->Draw("HIST,nostack");
				ss->Write();
				Set_Stack_Style(para,info,ss,gPad,hist_label);

				std::string leg_name = stack_title[0]+"_legend";
				info.leg->SetName(leg_name.c_str());
				info.leg->Draw();
				info.leg->Write();

				_list->Add(ss);


				//print to png
				Print_Plot(para, info, file_name.folder[2]+info.title_name+"_"+hist_label+".png");
			}
			delete info.c;
			info.leg->Clear();
		}
	}
}

void Analyse_Multi_File::Fill_Figure(){
	_root_file->cd();
	file[_file_num]._root_file->cd();
	TObjLink *lnk = _list->FirstLink();
	while (lnk) {
		std::cout <<"list name: "<< lnk->GetObject()->GetName()<<std::endl;
		lnk = lnk->Next();
	}

	if(_Has_Drawn){
		return;
	}
	_list->Write();

	ShowMessage(2,"All figures are printed!");
}


void Analyse_Multi_File::Draw_Figure(CDraw& para,AFile& file_name){
	if(_plot_switch){
		ShowMessage(2,"generate plot!");
		if(!para.flow.record_output){
			freopen(para.path.record_file.c_str() ,"a",stdout);
		}
		ShowMessage(2,"The plots will be stored in ",file_name.folder[1]);

		if(Vec_Exist(para.plot.drawing.single_plot,"origin")){	
			Draw_Single(para, file_name,"origin");
		}
		if(Vec_Exist(para.plot.drawing.single_plot,"before")){	
			Draw_Single(para, file_name,"before");
		}
		if(Vec_Exist(para.plot.drawing.single_plot,"after")){	
			Draw_Single(para, file_name,"after" );
		}
		if(Vec_Exist(para.plot.drawing.single_plot,"final")){	
			Draw_Single(para, file_name,"final" );
		}

		ShowMessage(2,"generate combined plot!");
		ShowMessage(2,"The plots will be stored in ",file_name.folder[2]);
		if(Vec_Exist(para.plot.drawing.single_plot,"origin")){	
			Draw_Sort(para, file_name,"origin");
		}
		if(Vec_Exist(para.plot.drawing.single_plot,"before")){	
			Draw_Sort(para, file_name,"before");
		}
		if(Vec_Exist(para.plot.drawing.single_plot,"after")){	
			Draw_Sort(para, file_name,"after" );
		}
		if(Vec_Exist(para.plot.drawing.single_plot,"final")){	
			Draw_Sort(para, file_name,"final" );
		}

		Fill_Figure();
		if(!para.flow.record_output){
			fclose(stdout);
			freopen("/dev/tty","w",stdout);
		}
	}
}
