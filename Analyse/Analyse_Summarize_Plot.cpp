#include "Analyse_Summarize_Plot.h"


void Analyse_Summarize_Plot_Complete_Pre(CDraw &para){
	std::string event_file              = para.path.event_file   ;
	std::string output_file             = para.path.output_file  ;
	std::string single_plot             = para.path.single_plot  ;
	std::string combine_plot            = para.path.combine_plot ;
	std::string horizontal_summary_plot = para.path.horizontal_summary_plot ;

	std::string BDT_dataset             = "";
	std::vector<std::vector<std::string> >sig_name;
			


	bool only_lr                        = false;
	if(para.scenario.Run_Ratio_Vec().size()==2){
		only_lr =true;
	}
	for(int i=-1;i<2;i=i+2){
		for(int j=-1;j<2;j=j+2){
			if(only_lr){
				if(i==j){continue;}
			}
			para.path.event_file   = event_file   + Int_to_String(i) + Int_to_String(j);
			para.path.output_file  = output_file  + Int_to_String(i) + Int_to_String(j);
			para.path.single_plot  = single_plot  + Int_to_String(i) + Int_to_String(j);
			para.path.combine_plot = combine_plot + Int_to_String(i) + Int_to_String(j);
			para.path.horizontal_summary_plot = horizontal_summary_plot + Int_to_String(i) + Int_to_String(j);

			std::vector<std::string> sig_name_temp;
			AFile file_name;
			for(int i=0;i<para.signal_scan.property_num;i++){
				para.flow.signal_property = para.signal_scan.properties[i];
				get_file_name(para,file_name);
				if(para.flow.plot_object=="final_cut"){
					sig_name_temp.push_back(file_name.output_total.CUT_file);
				}
				else if(para.flow.plot_object=="before_cut"){
					ShowMessage(2,file_name.output[0].CUT_file);
					ShowMessage(2,"signal propperty is",para.flow.signal_property);
					sig_name_temp.push_back(file_name.output[0].CUT_file);
				}
			}
			para.flow.signal_property = "10";
			get_file_name(para,file_name);
			if(para.flow.plot_object=="before_cut"){
				for(int i=1;i<file_name.output.size();i++){
					ShowMessage(2,"bkg",file_name.output[i].CUT_file);
					sig_name_temp.push_back(file_name.output[i].CUT_file);
				}
			}
			sig_name.push_back(sig_name_temp);
		}
	}

	AFile file_name;
	para.path.event_file              = event_file   ;
	para.path.single_plot             = single_plot  ;
	para.path.output_file             = output_file;
	para.path.combine_plot            = combine_plot ;
	para.path.horizontal_summary_plot = horizontal_summary_plot;
	get_file_name(para,file_name);


	Analyse_Summarize_Plot_Complete(para,sig_name,file_name);

}





void Analyse_Summarize_Plot_Complete(CDraw &para, std::vector<std::vector<std::string> >&sig_name, AFile& file_name){

	int num_temp=sig_name.size();

	APlot plot;

	for(unsigned int k=0;k<para.var.var.size();k++){
		if(para.signal_scan.observables.size()==1&&para.signal_scan.observables[0]=="all"){
		}
		else if(para.signal_scan.observables.size()>=1&& Vec_Exist(para.signal_scan.observables, para.var.var[k].title_name)){
		}
		else{
			continue;
		}

		Avariable info=para.var.var[k];
		if(info.plot_switch){

			std::string cname=info.c_name+"_"+Int_to_String(k);
			info.c=new TCanvas(cname.c_str()," ",info.c_width,info.c_height);
			std::string leg_name  = "ILD preliminary";
			std::string x_name    = info.x_name;
			std::string y_name    = info.y_name;
			if(info.norm_switch){
				y_name = "Normalized "+y_name;
			}
			std::string axis_name = info.title_name;
			int x_bin             = info.x_bin;
			float x_min           = info.x_min;
			float x_max           = info.x_max;
			std::vector<TH1F*> hvariable;
			hvariable.resize(sig_name[0].size());
			std::string title_name= info.title_name;
			for(int i=0;i<sig_name[0].size();i++){
				std::string hname=title_name+"_"+Int_to_String(i);
				hvariable[i] = new TH1F(hname.c_str(),title_name.c_str(),x_bin,x_min,x_max);
				hvariable[i]->SetTitle(hname.c_str());
			}

			auto leg = new TLegend(info.leg_left,info.leg_up,info.leg_right,info.leg_down);
			leg->Clear();
			leg->SetHeader(leg_name.c_str(),"c"); 
			for(int j=0;j<num_temp;j++){
				int num=sig_name[j].size();
				std::vector<TFile*> in_file;
				for(int i=0;i<num;i++){
					TFile* in_file_tmp=new TFile(sig_name[j][i].c_str());
					in_file.push_back(in_file_tmp);
					TTree *MyLCTuple; 
					if(para.flow.plot_object=="final_cut"){
						MyLCTuple=(TTree*)in_file[i]->Get("sig");
					}
					else{
						MyLCTuple=(TTree*)in_file[i]->Get(para.file.root_head_name.c_str());
					}

					int nevent = MyLCTuple->GetEntries();
					float variable;
					float weight;
					MyLCTuple->SetBranchAddress(title_name.c_str(), &variable);
					MyLCTuple->SetBranchAddress("weight", &weight);



					for(int event=0;event<nevent;event++){
						MyLCTuple->GetEntry(event);
						hvariable[i]->Fill(variable,weight);
					}

					if(j==num_temp-1){
						if(i<para.signal_scan.property_num){
							plot.Set_Line_Style_Test(para,info,hvariable[i],para.signal_scan.plot_sig);
							std::string legname=para.signal_scan.properties[i]+" GeV";
							TLegendEntry* leg_entry= leg->AddEntry(hvariable[i],legname.c_str(),"f");
						}
						else{
							plot.Set_Line_Style_Test(para,info,hvariable[i],para.signal_scan.plot_bkg);
						}
					}
				}
				if(j==num_temp-1){
					if(para.signal_scan.property_num%2==1){
						TH1F* hvariable_empty = new TH1F("empty","",1,0,0);
						TLegendEntry* leg_entry_empty =leg->AddEntry(hvariable_empty,"","");
					}
					TLegendEntry* leg_entry_bkg   =leg->AddEntry(hvariable[num-1],"SM backgrounds","f");
				}
			}


			int i = 3;
			THStack *ss_large = new THStack("name","@250 GeV ILC with 2000 fb^{-1} luminosities");
			if(info.log_switch){
				gPad->SetLogy();
				ss_large->SetMinimum(info.log_min);
			}
    		for(int j=para.signal_scan.property_num;j<sig_name[0].size();j++){
    			if(hvariable[j]->GetEntries()!=0){
    				ss_large->Add(hvariable[j]);
        		}
    		}
			if(hvariable[i]->GetEntries()!=0){
				ss_large->Add(hvariable[i]);
			}
			ss_large->Draw("hist");
			ss_large->GetYaxis()->SetTitle(y_name.c_str());
			ss_large->GetXaxis()->SetTitle(x_name.c_str());

			for(int i=0;i<para.signal_scan.property_num;i++){
				if(i==3){
					continue;
				}
				THStack *ss = new THStack();
				if(info.log_switch){
					gPad->SetLogy();
					ss->SetMinimum(info.log_min);
				}
    			for(int j=para.signal_scan.property_num;j<sig_name[0].size();j++){
    				if(hvariable[j]->GetEntries()!=0){
    					ss->Add(hvariable[j]);
    				}
    			}
				if(hvariable[i]->GetEntries()!=0){
					ss->Add(hvariable[i]);
				}
				ss->Draw("hist,Same");
				ss->GetYaxis()->SetTitle(y_name.c_str());
				ss->GetXaxis()->SetTitle(x_name.c_str());
			}
			leg->SetMargin(0.4);
			leg->SetNColumns(2);
			leg->SetTextSize(0.02);
			leg->SetColumnSeparation(-0.5);
		    TLegendEntry *header = (TLegendEntry*)leg->GetListOfPrimitives()->First();
            header->SetTextAlign(22);
            header->SetTextColor(1);
            header->SetTextSize(.04);
			leg->Draw();

			//plot.DrawLogo();
			plot.Print_Plot(para, info, file_name.folder[6]+info.title_name+"_summary"+para.plot.drawing.plot_type);

			delete info.c;
		}
	}


	return;
}

void Analyse_Summarize_Plot_Pre(CDraw &para){
	AFile file_name;
	std::vector<std::string> sig_name;

	for(int i=0;i<para.signal_scan.property_num;i++){
		para.flow.signal_property = para.signal_scan.properties[i];
		get_file_name(para,file_name);
		if(para.flow.plot_object=="final_cut"){
			sig_name.push_back(file_name.output_total.CUT_file);
		}
		else if(para.flow.plot_object=="before_cut"){
			ShowMessage(2,file_name.output[0].CUT_file);
			ShowMessage(2,"mass",para.flow.signal_property);
			sig_name.push_back(file_name.output[0].CUT_file);
		}
	}
	para.flow.signal_property = "10";
	get_file_name(para,file_name);
	if(para.flow.plot_object=="before_cut"){
		for(int i=1;i<file_name.output.size();i++){
			ShowMessage(2,"bkg",file_name.output[i].CUT_file);
			sig_name.push_back(file_name.output[i].CUT_file);
		}
	}

	Analyse_Summarize_Plot(para,sig_name,file_name);

}





void Analyse_Summarize_Plot(CDraw &para, std::vector<std::string> &sig_name, AFile& file_name){

	int _colornum[50];
	int _stylenum[50];
	_colornum[0] =kRed-2;
	_colornum[1] =kRed;
	_colornum[2] =kRed+2;
	_colornum[3] =kBlue-2;
	_colornum[4] =kBlue;
	_colornum[5] =kBlue+2;
	_colornum[6] =kMagenta-2;
	_colornum[7] =kMagenta;
	_colornum[8] =kMagenta+2;
	_colornum[9] =kCyan-2;
	_colornum[10]=kCyan;
	_colornum[11]=kCyan+2;
	_colornum[12]=kOrange-2;
	_colornum[13]=kOrange;
	_colornum[14]=kOrange+2;
	_colornum[15]=kPink-2;
	_colornum[16]=kPink;
	_colornum[17]=kPink+2;
	_colornum[18]=kAzure;
	_colornum[19]=kViolet;
	_colornum[20]=kSpring-3;
	_colornum[21]=kSpring-2;
	_colornum[22]=kSpring-1;
	_colornum[23]=kSpring;
	_colornum[24]=kSpring+1;
	_colornum[25]=kSpring+2;
	_colornum[26]=kSpring+3;
	_colornum[27]=kGreen-3;
	_colornum[28]=kGreen-2;
	_colornum[29]=kGreen-1;
	_colornum[30]=kGreen;
	_colornum[31]=kGreen+1;
	_colornum[32]=kGreen+2;
	_colornum[33]=kGreen+3;
	_colornum[34]=kTeal-3;
	_colornum[35]=kTeal-2;
	_colornum[36]=kTeal-1;
	_colornum[37]=kTeal;
	_colornum[38]=kTeal+1;
	_colornum[39]=kTeal+2;
	_colornum[40]=kTeal+3;

	_stylenum[0] =1 ;
	_stylenum[1] =7 ;
	_stylenum[2] =3 ;
	_stylenum[3] =7 ;
	_stylenum[4] =3 ;
	_stylenum[5] =5 ;
	_stylenum[6] =7 ;
	_stylenum[7] =8 ;
	_stylenum[8] =9 ;
	_stylenum[9] =10;
	for(int i=10;i<50;i++){
		_stylenum[i]=10;
	}
	int num=sig_name.size();

	APlot plot;

	for(unsigned int k=0;k<para.var.var.size();k++){
		if(para.signal_scan.observables.size()==1&&para.signal_scan.observables[0]=="all"){
		}
		else if(para.signal_scan.observables.size()>=1&& Vec_Exist(para.signal_scan.observables, para.var.var[k].title_name)){
		}
		else{
			continue;
		}

		Avariable info=para.var.var[k];
		if(info.plot_switch){
			std::vector<TFile*> in_file;
			for(int i=0;i<num;i++){
				TFile* in_file_tmp=new TFile(sig_name[i].c_str());
				in_file.push_back(in_file_tmp);
			}

			std::string cname=info.c_name+"_"+Int_to_String(k);
			info.c=new TCanvas(cname.c_str()," ",info.c_width,info.c_height);
			std::vector<TH1F*> hvariable;
			hvariable.resize(num);
			std::string title_name= info.title_name;
			//std::string leg_name  = info.latex_name+"  distribution";
			//std::string leg_name  = "e^{+}e^{-}#rightarrow  #mu^{+}#mu^{-}h";
			std::string leg_name  = "ILD preliminary";
			std::string x_name    = info.x_name;
			std::string y_name    = info.y_name;
			if(info.norm_switch){
				y_name = "Normalized "+y_name;
			}
			std::string axis_name = info.title_name;
			int x_bin             = info.x_bin;
			float x_min           = info.x_min;
			float x_max           = info.x_max;

			auto leg = new TLegend(info.leg_left,info.leg_up,info.leg_right,info.leg_down);
			leg->Clear();
			leg->SetHeader(leg_name.c_str(),"c"); 
			for(int i=0;i<num;i++){
				TTree *MyLCTuple; 
				if(para.flow.plot_object=="final_cut"){
					MyLCTuple=(TTree*)in_file[i]->Get("sig");
				}
				else{
					MyLCTuple=(TTree*)in_file[i]->Get(para.file.root_head_name.c_str());
				}

				int nevent = MyLCTuple->GetEntries();
				float variable;
				float weight;
				MyLCTuple->SetBranchAddress(title_name.c_str(), &variable);
				MyLCTuple->SetBranchAddress("weight", &weight);

				std::string hname=title_name+"_"+Int_to_String(i);
				hvariable[i] = new TH1F(hname.c_str(),title_name.c_str(),x_bin,x_min,x_max);
				hvariable[i]->SetTitle(hname.c_str());


				for(int event=0;event<nevent;event++){
					MyLCTuple->GetEntry(event);
					hvariable[i]->Fill(variable,weight);
				}

				if(i<para.signal_scan.property_num){
					plot.Set_Line_Style(para,info,hvariable[i],i,i);
					hvariable[i]->SetFillColor(_colornum[i]);
					std::string legname=para.signal_scan.properties[i]+" GeV";
					leg->AddEntry(hvariable[i],legname.c_str(),"l");
				}
				else{
					//int bkg_color=i-para.signal_scan.property_num+20;
					int bkg_color=28;
					//plot.Set_Line_Style(para,info,hvariable[i],_colornum[bkg_color],0);
				    hvariable[i]->SetLineColor(_colornum[bkg_color]);
				}
			}
			TH1F* hvariable_empty = new TH1F("empty","",1,0,0);
			leg->AddEntry(hvariable_empty,"","");
			leg->AddEntry(hvariable[num-1],"SM backgrounds","f");


			int i = 8;
			THStack *ss = new THStack("name","250 GeV ILC with 900 fb^{-1} (-80\%, +30\%) beam polarization");
			if(info.log_switch){
				gPad->SetLogy();
				ss->SetMinimum(info.log_min);
			}
			for(int j=para.signal_scan.property_num;j<num;j++){
				//int bkg_color=j-para.signal_scan.property_num+20;
				int bkg_color=28;
				if(hvariable[j]->GetEntries()!=0){
					hvariable[j]->SetFillColor(_colornum[bkg_color]);
					ss->Add(hvariable[j]);
				}
			}
			if(hvariable[i]->GetEntries()!=0){
				ss->Add(hvariable[i]);
			}
			ss->Draw("hist");
			ss->GetYaxis()->SetTitle(y_name.c_str());
			ss->GetXaxis()->SetTitle(x_name.c_str());

			//for(int i=para.signal_scan.property_num-1;i>0;i--){
			for(int i=0;i<para.signal_scan.property_num;i++){
				if(i==8){
					continue;
				}
				THStack *ss = new THStack();
				if(info.log_switch){
					gPad->SetLogy();
					ss->SetMinimum(info.log_min);
				}
				for(int j=para.signal_scan.property_num;j<num;j++){
					//int bkg_color=j-para.signal_scan.property_num+20;
					int bkg_color=28;
					if(hvariable[j]->GetEntries()!=0){
						hvariable[j]->SetFillColor(_colornum[bkg_color]);
						ss->Add(hvariable[j]);
					}
				}
				if(hvariable[i]->GetEntries()!=0){
					ss->Add(hvariable[i]);
				}
				ss->Draw("hist,Same");
				ss->GetYaxis()->SetTitle(y_name.c_str());
				ss->GetXaxis()->SetTitle(x_name.c_str());
			}
			leg->SetMargin(0.3);
			leg->SetNColumns(2);
			leg->SetTextSize(0.02);
			leg->Draw();

			plot.DrawLogo();
			plot.Print_Plot(para, info, file_name.folder[6]+info.title_name+"_summary"+para.plot.drawing.plot_type);

			delete info.c;
		}
	}


	return;
}

