#include "AnalyseClass/AnalyseClass.h"



/*****************************************************************************************
 * @Name: Init 
 *
 * @Param: para
 * @Param: file_name
 *****************************************************************************************/
void Analyse_Multi_File::Init(CDraw &para, AFile &file_name, std::string output_folder_type){

    ShowMessage(2,"Init Analyse parameters");
	_para      = para;
	_file_name = file_name;
    _Has_Drawn = false;

    _record_switch = _para.flow.record_event;
    _plot_switch   = _para.flow.plot;

    var=_para.var;
    _var_num = var.Var_Num();

    if(!_para.flow.record_output){
    	freopen(_para.path.record_file.c_str() ,"a",stdout);
    }
	_cut.Read_Cut(_para.path);

    if(!_para.flow.record_output){
    	fclose(stdout);
    	freopen("/dev/tty","w",stdout);
    }

    _file_num=_file_name.Input_Num();
	_root_head_name = _para.file.root_head_name;
	Init_All_Input_File();


    _root_file = TFile::Open( _file_name.plot_CUT.c_str() , "RECREATE" );
    _list      = new TList();
    ShowMessage(2,"finish input para, begin to analyse part");
}




void Analyse_Multi_File::Init_Input_File(std::string input_file_name, std::string root_head_name ){
	in_file.push_back(ARoot_File(input_file_name,root_head_name));
	in_file.back().Init_Var(var);
	in_file.back().Register_Var();
	in_file.back().Init_Para(_para);
	in_file.back().Init_Event();
}


void Analyse_Multi_File::Init_Input_File(std::vector<std::string> input_file_name, std::vector<std::string> root_head_name ){
	in_file.push_back(ARoot_File(input_file_name,root_head_name));
	in_file.back().Init_Var(var);
	in_file.back().Register_Var();
	in_file.back().Init_Para(_para);
	in_file.back().Init_Event();
}

void Analyse_Multi_File::Init_Input_File(std::vector<std::string> input_file_name, std::string root_head_name ){
	in_file.push_back(ARoot_File(input_file_name,root_head_name));
	in_file.back().Init_Var(var);
	in_file.back().Register_Var();
	in_file.back().Init_Para(_para);
	in_file.back().Init_Event();
}

void Analyse_Multi_File::Init_All_Input_File(){
    for(int j=0;j<_file_num;j++){
    	Init_Input_File(_file_name.output[j].Output_RootFile(),_root_head_name);
    }
}

void Analyse_Multi_File::Init_Output_File() {
    std::vector<std::string> normal_tree_name;
    normal_tree_name.push_back(_root_head_name) ;

    std::vector<std::string> final_tree_name ;
    final_tree_name.push_back("sig") ;
    final_tree_name.push_back("bkg") ;

    // for each channel
////for(int j=0;j<_file_num;j++){
////	ana_file[j].Init    (var,_root_file,_extra_weight, _record_switch, _plot_switch,Int_to_String(j)        , file_name.output[j].CUT_file   ,normal_tree_name );
////}
////ana_file[_file_num].Init(var,_root_file,_extra_weight, _record_switch, _plot_switch,Int_to_String(_file_num), file_name.output_total.CUT_file,final_tree_name  );

    ana_file.resize(_file_num);
    for(int j=0;j<_file_num;j++){
    	ana_file[j].Init(_root_file,_extra_weight, _record_switch, _plot_switch,Int_to_String(j)        , in_file[j]);
    }
	plot_file.Init(var,_root_file,_extra_weight, _record_switch, _plot_switch,Int_to_String(_file_num), _file_name.output_total.CUT_file,final_tree_name  );


////// combine some channel into different sorts, plot for each sort 
    sort.resize(_para.bkg_sort.Num());
    for(int k=0;k<_para.bkg_sort.Num();k++){
    	sort[k].second.resize(_para.bkg_sort.sort[k].Sub_Num());
    }
    for(int k=0;k<_para.bkg_sort.Num();k++){
    	for(int l=0;l<_para.bkg_sort.sort[k].Sub_Num();l++){
    		std::string sort_name = _file_name.folder[5]+"sort_"+_para.bkg_sort.sort[k].Name(l)+".root"; 
    		sort[k].second[l].Init(var,_root_file,_extra_weight, _record_switch, _plot_switch,Int_to_String(100+k*100+l), sort_name, normal_tree_name );
    	}
    }
    _which_sort = NULL;


}


void Analyse_Multi_File::Input_File_Delete(){
	for(unsigned int i=0; i< in_file.size(); i++){
		ShowMessage(2,"delete all input file pointers!");
		Input_File_Single_Delete(i);
		ShowMessage(2);
	}
}

void Analyse_Multi_File::Input_File_Single_Delete(int filenum){
	if(filenum<in_file.size()){
		ShowMessage(2,"delete file pointers!");
		in_file[filenum].Delete();
		ShowMessage(2);
	}
	else{
		ShowMessage(2,"Analyse_Multi_File::Input_File_Single_Delete");
	}
}

void Analyse_Multi_File::Clear(){
    for(int i=0;i<ana_file.size();i++){
    	ana_file[i].Delete();
    }
	plot_file.Delete();
    for(int i=0;i<sort.size();i++){
    	for(int j=0;j<sort[i].second.size();j++){
    		sort[i].second[j].Delete();
    	}
    }
    ShowMessage(2,"in Analyse_Multi_File::Clear, _root_file's ls");
    _root_file->ls() ;
    ShowMessage(2,"in Analyse_Multi_File::Clear, _list 's ls");
    _list->ls() ;
    _list->Delete();
	delete _list;
    _root_file->Close();
	delete _root_file;
    Input_File_Delete();
}
/*****************************************************************************************
 * @name  Analyse_Multi_File 
 * *****************************************************************************************/

void Analyse_Multi_File::_Find_Which_Sort (CDraw& para,  int filenum ) {
	std::size_t found_class,found_fs; 
	std::vector<std::string> strNew=Find_Str_in_Filename(_file_name.output[filenum].latex);
	for(int k=0;k<para.bkg_sort.Num();k++){
		found_class = _file_name.output[filenum].name.find(para.bkg_sort.sort[k].Class());
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

void Analyse_Multi_File::Init_Root(CDraw&para, int filenum){
	ana_file[filenum].Init_Root();
	_Find_Which_Sort(para, filenum);
}

void Analyse_Multi_File::Init_Root_Var(int filenum){ 
	_which_sort   ->Init_Root_Var();
	ana_file[filenum]  .Init_Root_Var();
	plot_file.Init_Root_Var();
}

void Analyse_Multi_File::Init_Data_File( std::ofstream &file_name, int filenum){
	if(filenum>=0){
		ana_file[filenum].Init_Data_File(file_name);
	}
	else{
		ShowMessage(2,"in Analyse_Multi_File::Data_File_Init, Haven't opened the file", filenum);
	}
}


void Analyse_Multi_File::Init_Total_Data_File( std::ofstream &file_name){
	if(file_name.is_open()){
		_data_file=&file_name;
	}
	else{
		ShowMessage(2,"in Analyse_Multi_File::Total_Data_File_Init, Haven't opened the file");
	}
}
bool Analyse_Multi_File::Init_Pol(int filenum){
	Weight_Extra(filenum);
	Get_Event(filenum,0);
}


bool Analyse_Multi_File::Get_Event(int filenum, long int num){
	in_file[filenum].Get_Event(num);
}


void Analyse_Multi_File::Weight_Extra(int filenum){
	if(_para.flow.begin_object=="Pre_Cut"){
//		_extra_weight = in_file[filenum].Get_Weight();
	}
	else{
		_extra_weight  = _para.flow.MVA_weight * _para.scenario.Lumi();
	}
}


void Analyse_Multi_File::Root_Get_Entry( int filenum, long int event){
	if(event)
	in_file[filenum].Get_Entry(event);
}

void Analyse_Multi_File::Root_Endow_Weight(int filenum){
	_which_sort   ->in_weight = ana_file[filenum].in_weight;
	_which_sort   ->Root_Endow_Weight();
	ana_file[filenum]  .Root_Endow_Weight();
	plot_file.Root_Endow_Weight();
}

void Analyse_Multi_File::Root_Endow_Var(int filenum){
	_which_sort     ->Root_Endow_Var();
	ana_file[filenum]    .Root_Endow_Unused_Var(_cut);
	plot_file  .Root_Endow_Var();
}

void Analyse_Multi_File::Root_Fill(int filenum){
	_which_sort ->Root_Fill(0);
	if(filenum==0){
		ana_file[_file_num].Root_Fill(0);
	}
	else{
		ana_file[_file_num].Root_Fill(1);
	}
}

void Analyse_Multi_File::Root_Close(int filenum){
	ana_file[filenum].Root_Close_File();

}

void Analyse_Multi_File::Data_File_Close(int filenum){
	if(filenum>=0){
		ana_file[filenum].Data_File_Close();
	}
	else{
		ShowMessage(2,"in Analyse_Multi_File::Data_File_Close, input file number is wrong", filenum);
	}
}


void Analyse_Multi_File::Total_Data_File_Close(){
	if(_data_file->is_open()){
		_data_file->close();
	}
	else{
		ShowMessage(2,"in Analyse_Multi_File::Total_Data_File_Close, total data file isn't open");
	}
}
void Analyse_Multi_File::Root_Close_Last(CDraw & para){
	for(int k=0;k<para.bkg_sort.Num();k++){
		for(int l=0;l<para.bkg_sort.sort[k].Sub_Num();l++){
			sort[k].second[l].Root_Close_File();
		}
	}

	plot_file.Root_Close_File();
}


void Analyse_Multi_File::Plot_Origin(int filenum){
	if(_plot_switch){
		ana_file[filenum].Plot_Origin();
	}
}



void Analyse_Multi_File::Plot_Final (int filenum){
	if(_plot_switch){
		ana_file[filenum].Plot_Final();
	}
}


void Analyse_Multi_File::Add_Pass_NoCut(int filenum){
	ana_file[filenum].Add_Pass_NoCut();
}

void Analyse_Multi_File::Add_Pass_AllCut(int filenum){
	ana_file[filenum].Add_Pass_AllCut();
}

void Analyse_Multi_File::Add_Tot_Pass(int filenum){
	if(filenum==0){return;}


	for(int i=0;i<_cut.cut_num;i++){
		int index=_cut.cut[i];
		_which_sort    ->figure[index].pass       +=ana_file[filenum].figure[index     ].pass ;
		_which_sort    ->figure[index].event      +=ana_file[filenum].figure[index     ].event;
		plot_file .figure[index].pass   +=ana_file[filenum].figure[index     ].pass ;
		plot_file .figure[index].event  +=ana_file[filenum].figure[index     ].event;
	}
	_which_sort    ->figure[_var_num]  .pass      +=ana_file[filenum].figure[_var_num  ].pass ;
	_which_sort    ->figure[_var_num]  .event     +=ana_file[filenum].figure[_var_num  ].event;
	_which_sort    ->figure[_var_num+1].pass      +=ana_file[filenum].figure[_var_num+1].pass ;
	_which_sort    ->figure[_var_num+1].event     +=ana_file[filenum].figure[_var_num+1].event;

	plot_file .figure[_var_num]  .pass  +=ana_file[filenum].figure[_var_num  ].pass ;
	plot_file .figure[_var_num]  .event +=ana_file[filenum].figure[_var_num  ].event;
	plot_file .figure[_var_num+1].pass  +=ana_file[filenum].figure[_var_num+1].pass ;
	plot_file .figure[_var_num+1].event +=ana_file[filenum].figure[_var_num+1].event;
}

bool Analyse_Multi_File::Get_Cut(int filenum){

	bool judge=ana_file[filenum].Get_Cut(_cut);

	if(judge){
		_which_sort   ->Root_Endow_Var();
	}

	return(judge);
}


//void Analyse_Multi_File::Record_Information(int filenum,std::ofstream &_adata_file, std::string sample_name){
void Analyse_Multi_File::Record_Information(int filenum, std::string sample_name){
	//file[filenum].Record_Information(var,_cut,sample_name);
	ana_file[filenum].Record_Information(_cut,sample_name);
}

//void Analyse_Multi_File::Record_Sort_Information(std::ofstream &myfile, std::string sample_name){
//	sort[k].second[j].Record_Information(myfile,var,_cut,sample_name);
//}

//void Analyse_Multi_File::Record_Tot_Information(std::ofstream &_adata_file, std::string sample_name){
void Analyse_Multi_File::Record_Tot_Information(std::string sample_name){
	ShowMessage(2,"combine all bkg results");
	RecordMessage(*_data_file,3,"result for all bkg "                , ""                    );
	RecordMessage(*_data_file,4,sample_name     , "[ 0"                                      , "0 ]" );
	RecordMessage(*_data_file,4,"no~cut "       , "[ "+ Float_to_String(plot_file.figure[_var_num  ].pass), Float_to_String(plot_file.figure[_var_num  ].event)+" ]" );
	for(int i=0;i<_cut.cut_num;i++){
		int index=_cut.cut[i];
		std::string var_name = var.var[index].latex_name + " \\in [ " + Float_to_String(var.var[index].cut_min) + " ," + Float_to_String(var.var[index].cut_max) + " ] ";
		RecordMessage(*_data_file,4,var_name    , "[ "+ Float_to_String(plot_file.figure[index     ].pass), Float_to_String(plot_file.figure[index     ].event)+" ]" );
	}
	RecordMessage(*_data_file,4,"all~cut "      , "[ "+ Float_to_String(plot_file.figure[_var_num+1].pass), Float_to_String(plot_file.figure[_var_num+1].event)+" ]" );
}

void Analyse_Multi_File::Draw_Single(CDraw &para,std::string hist_label){
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

			for(int nf=0;nf<_file_name.Output_Num()+1;nf++){
				int i;
				if(nf==0){continue;}
				if(nf==_file_name.Output_Num()){
					i=0;
				}
				else{
					i=nf;
				}
				TH1F* hist_tmp = (TH1F*) ana_file[i].figure[j].Hist(hist_label)->Clone();
				info.leg->AddEntry(hist_tmp,_file_name.output[i].name.c_str(),"l");
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
				Print_Plot(para, info, _file_name.folder[1]+info.title_name+"_"+hist_label+".png");
				delete info.c;
				info.leg->Clear();
			}
		}
	}
}

void Analyse_Multi_File::Draw_Sort(CDraw& para,std::string hist_label){
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

			for(int nf=0;nf<_file_name.Output_Num();nf++){
				_Find_Which_Sort(para,nf);
				_which_sort->figure[j].Hist(hist_label)->Add(ana_file[nf].figure[j].Hist(hist_label));
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
				Print_Plot(para, info, _file_name.folder[2]+info.title_name+"_"+hist_label+".png");
			}
			delete info.c;
			info.leg->Clear();
		}
	}
}

void Analyse_Multi_File::Fill_Figure(){
	plot_file._root_file->cd();
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


void Analyse_Multi_File::Draw_Figure(CDraw& para){
	if(_plot_switch){
		ShowMessage(2,"generate plot!");
		if(!para.flow.record_output){
			freopen(para.path.record_file.c_str() ,"a",stdout);
		}
		ShowMessage(2,"The plots will be stored in ",_file_name.folder[1]);

		if(Vec_Exist(para.plot.drawing.single_plot,"origin")){	
			Draw_Single(para,"origin");
		}
		if(Vec_Exist(para.plot.drawing.single_plot,"before")){	
			Draw_Single(para,"before");
		}
		if(Vec_Exist(para.plot.drawing.single_plot,"after")){	
			Draw_Single(para,"after" );
		}
		if(Vec_Exist(para.plot.drawing.single_plot,"final")){	
			Draw_Single(para,"final" );
		}

		ShowMessage(2,"generate combined plot!");
		ShowMessage(2,"The plots will be stored in ", _file_name.folder[2]);
		if(Vec_Exist(para.plot.drawing.single_plot,"origin")){	
			Draw_Sort(para,"origin");
		}
		if(Vec_Exist(para.plot.drawing.single_plot,"before")){	
			Draw_Sort(para,"before");
		}
		if(Vec_Exist(para.plot.drawing.single_plot,"after")){	
			Draw_Sort(para,"after" );
		}
		if(Vec_Exist(para.plot.drawing.single_plot,"final")){	
			Draw_Sort(para,"final" );
		}

		Fill_Figure();
		if(!para.flow.record_output){
			fclose(stdout);
			freopen("/dev/tty","w",stdout);
		}
	}
}









/*****************************************************************************************
 * output variable  
 *****************************************************************************************/

/*****************************************************************************************
 * @Name: Var_Num 
 *
 * @Returns: 
 *****************************************************************************************/
int Analyse_Multi_File::Var_Num(){
	return(_var_num);
}

