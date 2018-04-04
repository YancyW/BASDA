#include "Analyse_Summarize_Plot.h"


void Analyse_Summarize_Plot_Pre(CDraw &para){
	AFile file_name;
	std::vector<std::string> sig_name;

	for(int i=0;i<para.mass_scan.mass_num;i++){
		para.flow.signal_property= para.mass_scan.mass[i];
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

	Analyse_Summarize_Plot(para,sig_name,file_name);

}





void Analyse_Summarize_Plot(CDraw &para, std::vector<std::string> &sig_name, AFile& file_name){

	int _colornum[20];
	int _stylenum[10];
	_colornum[0] =1;
	_colornum[1] =632;//red;
	_colornum[2] =600;//blue;
	_colornum[3] =880;//Violet;
	_colornum[4] =800;//Magenta;
	_colornum[5] =432;//Cyan;
	_colornum[6] =11;;
	_colornum[7] =30;
	_colornum[8] =33;
	_colornum[9] =38;
	_colornum[10]=40;
	_colornum[12]=41;
	_colornum[13]=42;
	_colornum[14]=43;
	_colornum[15]=44;
	_colornum[16]=45;
	_colornum[17]=46;
	_colornum[18]=47;
	_colornum[19]=48;
	_stylenum[0] =1 ;
	_stylenum[1] =7 ;
	_stylenum[2] =3 ;
	_stylenum[3] =2 ;
	_stylenum[4] =4 ;
	_stylenum[5] =5 ;
	_stylenum[6] =6 ;
	_stylenum[7] =8 ;
	_stylenum[8] =9 ;
	_stylenum[9] =10;

	int num=sig_name.size();

	APlot plot;

	for(unsigned int k=0;k<para.var.var.size();k++){
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
			std::string leg_name  = info.latex_name+" ~distribution";
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
			leg->SetHeader(leg_name.c_str(),"l"); 
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
				MyLCTuple->SetBranchAddress(title_name.c_str(), &variable);

				std::string hname=title_name+"_"+Int_to_String(i);
				hvariable[i] = new TH1F(hname.c_str(),title_name.c_str(),x_bin,x_min,x_max);
				hvariable[i]->SetTitle(hname.c_str());


				for(int event=0;event<nevent;event++){
					MyLCTuple->GetEntry(event);
					hvariable[i]->Fill(variable);
				}

				plot.Set_Line_Style(para,info,hvariable[i],_colornum[i],_stylenum[i]);
				std::string legname="M_{h}= "+Float_to_String(para.mass_scan.mass[i])+" GeV";
				leg->AddEntry(hvariable[i],legname.c_str(),"l");
			}



			THStack *ss = new THStack();
			if(info.log_switch){
				gPad->SetLogy();
				ss->SetMinimum(info.log_min);
			}
			for(int i=0;i<num;i++){
				ss->Add(hvariable[i]);
			}
			ss->Draw("HIST,nostack");
			ss->GetYaxis()->SetTitle(y_name.c_str());
			ss->GetXaxis()->SetTitle(x_name.c_str());
			leg->SetMargin(0.3);
			leg->Draw();

			plot.Print_Plot(info, file_name.folder[6]+info.title_name+"_summary.png");

			delete info.c;
			delete ss;
		}
	}


	return;
}

