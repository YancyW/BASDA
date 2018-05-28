#include "AnalyseClass/AnalyseClass_Single.h"


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

void Analyse_Single_File::File_Init(std::ofstream &file_name){
	if(file_name.is_open()){
		_data_file=&file_name;
		RecordMessage(*_data_file,2,"filenum", "");
	}
	else{
		ShowMessage(2,"in Analyse_Single_File::File_Init, Haven't opened the file");
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


void Analyse_Single_File::File_Close(){
	if(_data_file->is_open()){
		_data_file->close();
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





//void Analyse_Single_File::Record_Information(std::ofstream &_adata_file, AVariable& var, ACut &cut, std::string sample_name){
void Analyse_Single_File::Record_Information(AVariable& var, ACut &cut, std::string sample_name){
	RecordMessage(*_data_file,3,"total result"     , ""                                                   );
	RecordMessage(*_data_file,4,sample_name        , "[ 0"                                        , "0 ]" );
	RecordMessage(*_data_file,4,"no cut MC event " , "[ "+Float_to_String(figure[_var_num+2].pass), Float_to_String(figure[_var_num+2].event)+" ]" );
	RecordMessage(*_data_file,4,"no cut          " , "[ "+Float_to_String(figure[_var_num  ].pass), Float_to_String(figure[_var_num  ].event)+" ]" );
	for(int i=0;i<cut.cut_num;i++){
		int index=cut.cut[i];
		std::string var_name = var.var[index].latex_name + " \\in [ " + Float_to_String(var.var[index].cut_min) + " ," + Float_to_String(var.var[index].cut_max) + " ] ";
		RecordMessage(*_data_file,4,var_name       , "[ "+Float_to_String(figure[index     ].pass), Float_to_String(figure[index     ].event)+" ]" );
	}
	RecordMessage(*_data_file,4,"all~cut "         , "[ "+Float_to_String(figure[_var_num+1].pass), Float_to_String(figure[_var_num+1].event)+" ]" );
}









