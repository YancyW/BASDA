#include "AnalyseClass/AnalyseClass.h"


void Analyse_Figure::Init(Avariable &info, std::string name){

	if(info.plot_switch){
		std::string hname_origin=info.title_name+"_origin_"+name;
		std::string hname_before=info.title_name+"_before_"+name;
		std::string hname_after =info.title_name+"_after_" +name;
		std::string hname_final =info.title_name+"_final_" +name;
		hvariable_origin = new TH1F(hname_origin.c_str(),info.title_name.c_str(),info.x_bin,info.x_min,info.x_max);
		hvariable_before = new TH1F(hname_before.c_str(),info.title_name.c_str(),info.x_bin,info.x_min,info.x_max);
		hvariable_after  = new TH1F(hname_after .c_str(),info.title_name.c_str(),info.x_bin,info.x_min,info.x_max);
		hvariable_final  = new TH1F(hname_final .c_str(),info.title_name.c_str(),info.x_bin,info.x_min,info.x_max);
	}
	pass = 0.0;
	event= 0;
}



void Analyse_Figure::Init(){
	pass = 0.0;
	event =0;
	hvariable_origin = NULL;
	hvariable_before = NULL;
	hvariable_after  = NULL;
	hvariable_final  = NULL;
}

void Analyse_Figure::Clear(){
	pass = 0.0;
	event =0;
}

TH1F* Analyse_Figure::Hist_Origin(){
	return(hvariable_origin);
}

TH1F* Analyse_Figure::Hist_Before(){
	return(hvariable_before);
}

TH1F* Analyse_Figure::Hist_After(){
	return(hvariable_after);
}

TH1F* Analyse_Figure::Hist_Final(){
	return(hvariable_final);
}

TH1F* Analyse_Figure::Hist(std::string label){
	if(label == "origin"){
		return(hvariable_origin);
	}
	else if(label == "before"){
		return(hvariable_before);
	}
	else if(label == "after"){
		return(hvariable_after);
	}
	else if(label == "final"){
		return(hvariable_final);
	}
	else{
		ShowMessage(2,"wrong input for Analyse_Figure::Hist");
		return(NULL);
	}
}

void Analyse_Figure::Plot(float &variable, TH1F* &hvariable,float weight){
	hvariable->Fill(variable,weight);
}


void Analyse_Figure::Plot_Origin(float &variable, float weight){
	Plot(variable,hvariable_origin,weight);
}


void Analyse_Figure::Plot_Before(float &variable, float weight){
	Plot(variable,hvariable_before,weight);
}

void Analyse_Figure::Plot_After(float &variable, float weight){
	Plot(variable,hvariable_after,weight);
}

void Analyse_Figure::Plot_Final(float &variable, float weight){
	Plot(variable,hvariable_final,weight);
}


void Analyse_Figure::Set_Pass(float weight){
	pass = weight;
	event= 1;
}

void Analyse_Figure::Add_Pass(float weight){
	pass += weight;
	event++;
}





Analyse_Single_File::Analyse_Single_File(){

}

Analyse_Single_File::~Analyse_Single_File(){
	Clear();
}

void Analyse_Single_File::Clear(){
}


void Analyse_Single_File::Init(AVariable &var, TFile* plot_file, float extra_weight, bool record_switch, bool plot_switch,std::string figure_name, std::string file_name, std::vector<std::string> tree_name){

	_record_switch = record_switch ;
	_plot_switch   = plot_switch   ;
	_extra_weight  = extra_weight  ;

	_var_num = var.num;
	_tree_num= tree_name.size()    ;
	_name    = file_name           ;

	figure.resize(_var_num+3);

	plot_file->cd();

	if(_plot_switch){
		for(int k=0;k<_var_num;k++){
			figure[k].Init(var.var[k],figure_name);
		}
		for(int k=_var_num;k<_var_num+3;k++){
			figure[k].Init();
		}
	}


	if(_record_switch){
		_root_file = TFile::Open( file_name.c_str() , "RECREATE" );
		if (!_root_file) {
			std::cout << "ERROR: could not open data file" << std::endl;
			exit(1);
		}
		_root_file->cd();

		_rootvar .resize(var.num);
		for(int i=0;i<var.num;i++){
			_rootvar[i]=-100.1;
		}
		for(int i=0;i<_tree_num;i++){
			_tree.push_back(new TTree( tree_name[i].c_str() , "events" ));

			_tree[i]->Branch( "weight"              , &_out_weight );        
			for(int j=0;j<var.num;j++){
				_tree[i]->Branch( var.var[j].title_name.c_str() , &_rootvar[j] );        
			}
		}
	}


}

void Analyse_Single_File::Root_Init(){
	_root_file->cd();
}

void Analyse_Single_File::Root_Init_Var(){ 
	for(int j=0;j<_var_num;j++){
		_rootvar[j]=-100.1;
	}
}

void Analyse_Single_File::Root_Endow_Weight(){
	_out_weight    = in_weight * _extra_weight;
}


void Analyse_Single_File::Root_Endow_Unused_Var(AVariable &var, ACut &cut){
	//for those variables not in the cut
	for(int j=0;j<var.num;j++){
		bool counter=false;
		for(int k=0;k<cut.cut_num;k++){
			int index=cut.cut[k];
			if(j==index){counter=true;break;}
		}
		if(counter==false){
			_rootvar[j]=var.var[j].variable;
		}
	}
}

void Analyse_Single_File::Root_Endow_Var(AVariable &var){
	for(int j=0;j<var.num;j++){
		_rootvar[j]=var.var[j].variable;
	}
}

void Analyse_Single_File::Root_Fill(int rootnum){
	if(rootnum<_tree_num){
		_tree[rootnum]->Fill();
	}
}

void Analyse_Single_File::Root_Close_Tree(int rootnum){
	if(_tree[rootnum]){
		_tree[rootnum]->Write();
	}
}


void Analyse_Single_File::Root_Close_File(){
	if(_record_switch){
		_root_file->cd();
		for(int i=0;i<_tree_num;i++){
			Root_Close_Tree(i);
		}
		_root_file->Close();
	}
}

void Analyse_Single_File::Plot_Origin(AVariable &var){
	if(_plot_switch){
		for(int j=0;j<_var_num;j++){
			figure[j].Plot_Origin(var.var[j].variable,_out_weight);
		}
	}
}



void Analyse_Single_File::Plot_Final(AVariable &var){
	if(_plot_switch){
		for(int j=0;j<_var_num;j++){
			figure[j].Plot_Final(var.var[j].variable,_out_weight);
		}
	}
}




void Analyse_Single_File::Add_Pass_NoCut(){
	figure[_var_num]  .Add_Pass(_out_weight);
	figure[_var_num+2].Add_Pass(1);
}


void Analyse_Single_File::Add_Pass_AllCut(){
	figure[_var_num+1].Add_Pass(_out_weight);
}

bool Analyse_Single_File::Get_Cut(AVariable &var,ACut &cut){
	return(Loop_Cut(var,figure,_out_weight,cut));
}


bool Analyse_Single_File::Loop_Cut(AVariable & var, std::vector<Analyse_Figure> & figure, float weight, ACut &cut){
	for(int i=0;i<cut.cut_num;i++){
		int index=cut.cut[i];
		if(!Use_Cut(var.var[index],weight,figure[index])){
			_tree[0]->Fill();
			return(false);
		}
		else{
			// for variables after this cut i, 
			// if cut[i] is satisfied, then fill the variable behind this cut[i]
			_rootvar[index]=var.var[index].variable;
		}

	}
	// all cuts are satisfied
	Root_Endow_Unused_Var(var, cut);
	_tree[0]->Fill();
	return(true);
}


bool Analyse_Single_File::Use_Cut(Avariable &var, float weight, Analyse_Figure &figure){
	if(var.plot_switch&&_plot_switch){
		figure.Plot_Before(var.variable,weight);
	}
	if(var.cut_switch){
		if(GetCut(var.variable, var.cut_min,  var.cut_max)){
			figure.Add_Pass(weight);
		}
		else{
			return(false);
		}
	}
	if(var.plot_switch&&_plot_switch){
		figure.Plot_After(var.variable,weight);
	}
	return(true);
}





void Analyse_Single_File::Record_Information(std::ofstream &myfile, AVariable& var, ACut &cut, std::string sample_name){
	RecordMessage(myfile,3,"total result"     , ""                                                   );
	RecordMessage(myfile,4,sample_name        , "[ 0"                                        , "0 ]" );
	RecordMessage(myfile,4,"no cut MC event " , "[ "+Float_to_String(figure[_var_num+2].pass), Float_to_String(figure[_var_num+2].event)+" ]" );
	RecordMessage(myfile,4,"no cut          " , "[ "+Float_to_String(figure[_var_num  ].pass), Float_to_String(figure[_var_num  ].event)+" ]" );
	for(int i=0;i<cut.cut_num;i++){
		int index=cut.cut[i];
		std::string var_name = var.var[index].latex_name + " \\in [ " + Float_to_String(var.var[index].cut_min) + " ," + Float_to_String(var.var[index].cut_max) + " ] ";
		RecordMessage(myfile,4,var_name       , "[ "+Float_to_String(figure[index     ].pass), Float_to_String(figure[index     ].event)+" ]" );
	}
	RecordMessage(myfile,4,"all~cut "         , "[ "+Float_to_String(figure[_var_num+1].pass), Float_to_String(figure[_var_num+1].event)+" ]" );
}









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


void Analyse_Multi_File::Record_Information(int filenum,std::ofstream &myfile, std::string sample_name){
	file[filenum].Record_Information(myfile,var,_cut,sample_name);
}

//void Analyse_Multi_File::Record_Sort_Information(std::ofstream &myfile, std::string sample_name){
//	sort[k].second[j].Record_Information(myfile,var,_cut,sample_name);
//}

void Analyse_Multi_File::Record_Tot_Information(std::ofstream &myfile, std::string sample_name){
	ShowMessage(2,"combine all bkg results");
	RecordMessage(myfile,3,"result for all bkg "                , ""                    );
	RecordMessage(myfile,4,sample_name     , "[ 0"                                      , "0 ]" );
	RecordMessage(myfile,4,"no~cut "       , "[ "+ Float_to_String(file[_file_num].figure[_var_num  ].pass), Float_to_String(file[_file_num].figure[_var_num  ].event)+" ]" );
	for(int i=0;i<_cut.cut_num;i++){
		int index=_cut.cut[i];
		std::string var_name = var.var[index].latex_name + " \\in [ " + Float_to_String(var.var[index].cut_min) + " ," + Float_to_String(var.var[index].cut_max) + " ] ";
		RecordMessage(myfile,4,var_name    , "[ "+ Float_to_String(file[_file_num].figure[index     ].pass), Float_to_String(file[_file_num].figure[index     ].event)+" ]" );
	}
	RecordMessage(myfile,4,"all~cut "      , "[ "+ Float_to_String(file[_file_num].figure[_var_num+1].pass), Float_to_String(file[_file_num].figure[_var_num+1].event)+" ]" );
}

void Analyse_Multi_File::Draw_Single(CDraw &para, AFile& file_name,std::string hist_label){
	ShowMessage(2,"generate plot for "+hist_label+" results!");
	for(int j=0;j<_var_num;j++){
		Avariable info=var.var[j];
		ShowMessage(3,"generate plot for variable",info.title_name);
		info.Print();
		if(info.plot_switch){
			std::string leg_title = info.latex_name;
			info.leg->SetHeader(leg_title.c_str(),"l");
			std::string cname=info.c_name+"_"+Int_to_String(j);
			info.c=new TCanvas(cname.c_str()," ",info.c_width,info.c_height);

			gPad->SetGrid();
			std::vector<std::string> stack_title= Set_Stack_Title(para,info.title_name+"_"+hist_label);
			for (int i=0;i<stack_title.size();i++){
				std::cout << "stack name:  " << stack_title[i]<<std::endl;
			}
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
				Set_Line_Style(para,info,hist_tmp,i,i,false);
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
				Print_Plot(para, info, file_name.folder[1]+info.title_name+"_"+hist_label);
			}
			info.leg->Clear();
			delete info.c;
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
			for(int k=0;k<para.bkg_sort.Num();k++){
				for(int l=0;l<para.bkg_sort.sort[k].Sub_Num();l++){
					if(k==0 && l==0 && (k!=(para.bkg_sort.Num()-1) || l!=(para.bkg_sort.sort[k].Sub_Num()-1))){i++;continue;}
					double maxi = sort[k].second[l].figure[j].Hist(hist_label)->GetEntries();
					if(maxi>0){
						std::string sort_name = para.bkg_sort.sort[k].Legend(l); 
						TH1F* hist_tmp = (TH1F*) sort[k].second[l].figure[j].Hist(hist_label)->Clone();
						info.leg->AddEntry(hist_tmp,sort_name.c_str(),"l");
						Set_Line_Style(para,info,hist_tmp,i,i,info.norm_switch);
						ss->Add(hist_tmp);
						i++;
					}
					if(k==para.bkg_sort.Num()-1 && l==para.bkg_sort.sort[k].Sub_Num()-1){
						double maxi0 = sort[0].second[0].figure[j].Hist(hist_label)->GetEntries();
						if(maxi0>0){
							std::string sort_name = para.bkg_sort.sort[0].Legend(0); 
							TH1F* hist_tmp = (TH1F*) sort[0].second[0].figure[j].Hist(hist_label)->Clone();
							info.leg->AddEntry(hist_tmp,sort_name.c_str(),"l");
							Set_Line_Style(para,info,hist_tmp,0,0,info.norm_switch);
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
				Print_Plot(para, info, file_name.folder[2]+info.title_name+"_"+hist_label);
			}
			delete info.c;
			info.leg->Clear();
		}
	}
}

void Analyse_Multi_File::Draw_All_BKG(CDraw& para, AFile& file_name,std::string hist_label){
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
			std::vector<std::string> stack_title= Set_Stack_Title(para,info.title_name+"_allbkg_"+hist_label);
			THStack *ss = new THStack(stack_title[0].c_str(),stack_title[1].c_str() );

			TH1F* hist_sig= (TH1F*) file[0].figure[j].Hist(hist_label)->Clone();
			Set_Line_Style(para,info,hist_sig,0,0,info.norm_switch);
			info.leg->AddEntry(hist_sig,"sig","l");
			ss->Add(hist_sig);

			TH1F* hist_bkg=(TH1F*) file[1].figure[j].Hist(hist_label)->Clone();
			for(unsigned int i=2;i<file.size()-1;i++){
				TH1F* hist_tmp= (TH1F*) file[i].figure[j].Hist(hist_label)->Clone();
				hist_bkg->Add(hist_tmp);
			}
			Set_Line_Style(para,info,hist_bkg,1,1,info.norm_switch);
			info.leg->AddEntry(hist_bkg,"bkg","l");
			ss->Add(hist_bkg);

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
				Print_Plot(para, info, file_name.folder[9]+info.title_name+"_"+hist_label);
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

		std::string plot_lable="origin";
		if(Vec_Exist(para.plot.drawing.single_plot,plot_lable)){	
			Draw_Single(para, file_name,plot_lable);
		}

		plot_lable="before";
		if(Vec_Exist(para.plot.drawing.single_plot,plot_lable)){	
			Draw_Single(para, file_name,plot_lable);
		}

		plot_lable="after";
		if(Vec_Exist(para.plot.drawing.single_plot,plot_lable)){	
			Draw_Single(para, file_name, plot_lable);
		}

		plot_lable="final";
		if(Vec_Exist(para.plot.drawing.single_plot,plot_lable)){	
			Draw_Single(para, file_name, plot_lable);
		}

		ShowMessage(2,"generate combined plot!");
		ShowMessage(2,"The plots will be stored in ",file_name.folder[2]);
		plot_lable="origin";
		if(Vec_Exist(para.plot.drawing.single_plot,plot_lable)){	
			Draw_Sort(para, file_name,plot_lable);
		}
		plot_lable="before";
		if(Vec_Exist(para.plot.drawing.single_plot,plot_lable)){	
			Draw_Sort(para, file_name,plot_lable);
		}
		plot_lable="after";
		if(Vec_Exist(para.plot.drawing.single_plot,plot_lable)){	
			Draw_Sort(para, file_name, plot_lable);
		}
		plot_lable="final";
		if(Vec_Exist(para.plot.drawing.single_plot,plot_lable)){	
			Draw_Sort(para, file_name, plot_lable);
		}

		ShowMessage(2,"generate all bkg_combined plot!");
		ShowMessage(2,"The plots will be stored in ",file_name.folder.size(),file_name.folder[9]);
		plot_lable="origin";
		if(Vec_Exist(para.plot.drawing.single_plot,plot_lable)){	
			Draw_All_BKG(para, file_name,plot_lable);
		}
		plot_lable="before";
		if(Vec_Exist(para.plot.drawing.single_plot,plot_lable)){	
			Draw_All_BKG(para, file_name,plot_lable);
		}
		plot_lable="after";
		if(Vec_Exist(para.plot.drawing.single_plot,plot_lable)){	
			Draw_All_BKG(para, file_name, plot_lable);
		}
		plot_lable="final";
		if(Vec_Exist(para.plot.drawing.single_plot,plot_lable)){	
			Draw_All_BKG(para, file_name, plot_lable);
		}

		Fill_Figure();
		if(!para.flow.record_output){
			fclose(stdout);
			freopen("/dev/tty","w",stdout);
		}
	}
}
