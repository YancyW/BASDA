#include "Analyse_Plot_Direct.h"


void Analyse_Plot_Direct_Pre(CDraw &para){
	AFile file_name;
	std::string sig_name;

	get_file_name(para,file_name);
	for(int i=0;i<file_name.Input_Num();i++){
		sig_name=file_name.input[i].basic_file[0];

		Analyse_Plot_Direct(para,sig_name,file_name);
	}

}





void Analyse_Plot_Direct(CDraw &para, std::string &sig_name, AFile& file_name){

	APlot plot;

	Avariable info=para.plot_direct.Var(para.var);
	if(info.plot_switch){
		TFile* in_file=new TFile(sig_name.c_str());

		info.c=new TCanvas(info.c_name.c_str()," ",info.c_width,info.c_height);

		auto leg = new TLegend(info.leg_left,info.leg_up,info.leg_right,info.leg_down);
		leg->Clear();
		leg->SetHeader(info.leg_header.c_str(),"c"); 
		TTree *MyLCTuple=(TTree*)in_file->Get(para.file.root_head_name.c_str());

		int nevent = MyLCTuple->GetEntries();
		float variable, weight;
		MyLCTuple->SetBranchAddress(info.title_name.c_str(), &variable);
		if(para.plot_direct.weight_exist){
			MyLCTuple->SetBranchAddress("weight", &weight);
		}
		else{
			weight = 1;
		}

		TH1F* hvariable = new TH1F(info.title_name.c_str(),info.title_name.c_str(),info.x_bin,info.x_min,info.x_max);

		for(int event=0;event<nevent;event++){
			MyLCTuple->GetEntry(event);
			hvariable->Fill(variable,weight);
		}

		plot.Set_Line_Style_Test(para,info,hvariable,para.plot_direct.line_setting);
		leg->AddEntry(hvariable,info.title_name.c_str(),"l");

		hvariable->Draw();

		plot.DrawLogo();
		plot.Print_Plot(para, info, file_name.Plot_Origin_Folder()+info.title_name+"_"+sig_name+para.plot.drawing.plot_type);

		delete info.c;
	}

	return;
}

