#include "AnalyseClass/Plot.h"

void APlot::Init(){
	_Has_Input = false ;

	_sig_num   = -1;
	_bkg_num   = -1;

	_weight    = 0;
	_value     = -100.1;
}


void APlot::Clear(){
////delete _sig_histo_total;
////delete _bkg_histo_total;

////for(int i=0;i<_sig_num;i++){
////	delete _sig_histo[i];
////	delete _sig_Tree[i];
////	delete _sig_File[i];
////}
////for(int i=0;i<_bkg_num;i++){
////	delete _bkg_histo[i];
////	delete _bkg_Tree[i];
////	delete _bkg_File[i];
////}

	_Has_Input = false ;

	_sig_num   = -1;
	_bkg_num   = -1;

	_weight    = 0;
	_value     = -100.1;
}


bool APlot::Set_Line_Style_Test(CDraw& para, Avariable &info, TH1F * histo, Cplot_line setting){
	histo->SetLineColor(setting.Color());
	histo->SetLineStyle(setting.Style());
	histo->SetLineWidth(setting.Width());
	if(setting.fill_switch){
		histo->SetFillColor(setting.fill_switch);
	}

	if(setting.norm_switch){
		if(histo->GetEntries()!=0){
			float norm=1./histo->Integral();
			if(norm>0){histo->Scale(norm);}
		}
		else{
			return(false);
		}
	}
	return(true);
}

bool APlot::Set_Line_Style(CDraw& para, Avariable &info, TH1F * histo, int color, int linestyle){
	if(info.with_color_or_line==-1){
		if(para.plot.setting.with_color_or_line == 1){
			histo->SetLineColor(color);
		}
		else if(para.plot.setting.with_color_or_line == -1){
			histo->SetLineStyle(linestyle);
		}
		else{
			histo->SetLineColor(color);
			histo->SetLineStyle(linestyle);
		}
	}
	else{
		if(info.with_color_or_line == 1){
			histo->SetLineColor(color);
		}
		else if(info.with_color_or_line == -1){
			histo->SetLineStyle(linestyle);
		}
		else{
			histo->SetLineColor(color);
			histo->SetLineStyle(linestyle);
		}

	}
	if(info.line_width==-1){
		histo->SetLineWidth(para.plot.setting.line_width);
	}
	else{
		histo->SetLineWidth(info.line_width);
	}

	if(info.norm_switch){
		if(histo->GetEntries()!=0){
			float norm=1./histo->Integral();
			if(norm>0){histo->Scale(norm);}
		}
		else{
			return(false);
		}
	}
	return(true);
}


std::vector<std::string> APlot::Set_Stack_Title(CDraw& para, std::string name){
	std::vector<std::string> stack_title= {"",""};
	stack_title[0]= name;
	if(para.plot.setting.show_title){
		stack_title[1]= name;
	}
	return(stack_title);
}

void APlot::Set_Stack_Style(CDraw& para, Avariable &info, THStack* ss, TVirtualPad* pad, std::string hist_label){
	if(info.log_switch){
		pad->SetLogy();
		ss->SetMinimum(info.log_min);
	}
	std::string y_name;
	if(info.norm_switch){
		y_name = "Normalized "+info.y_name;
		if(hist_label=="after"||hist_label=="final"){
			TH1F* last_hist=(TH1F*) (ss->GetHists()->Last());
			float sig_max=last_hist->GetMaximum();
			std::cout<<"max y"<< sig_max << std::endl;
			ss->GetHistogram()->SetMaximum(sig_max);
		}
	}
	else{
		y_name = info.y_name;
	}
	ss->GetYaxis()->SetTitle(y_name.c_str());
	ss->GetXaxis()->SetTitle(info.x_name.c_str());
	pad->Update();
	ss->Draw("HIST,nostack");
}


void APlot::Print_Plot(CDraw &para, Avariable& info, std::string name){
	if(para.plot.drawing.plot_type == ".pdf"){
		TPDF pdf(name.c_str(),-111);
		info.c->Update();
        //DrawLogo();
		pdf.Close();
	}
	else if(para.plot.drawing.plot_type == ".eps"){
		TPostScript ps(name.c_str(),113);
	    ps.Range(16,24);
        //DrawLogo();
		info.c->Update();
		ps.Close();
	}
	else{
        //DrawLogo();
		info.c->Update();
		TImage *img = TImage::Create();
		img->FromPad(info.c);
		img->WriteImage(name.c_str());
	}

}

bool APlot::Get_Input_File(CDraw &para, Avariable &info, std::vector<std::string> input_sig, std::vector<std::string> input_bkg){

	_sig_num = input_sig.size();
	for(unsigned int i=0;i<input_sig.size();i++){
		ShowMessage(2,"sig file:",input_sig[i]);
	}

	_bkg_num = input_bkg.size();
	for(unsigned int i=0;i<input_bkg.size();i++){
		ShowMessage(2,"bkg file:",input_bkg[i]);
	}

	if(_sig_num!=0 && _bkg_num!=0){
		_Has_Input = true;
	}
	else{
		ShowMessage(2,"Input files are not enough, please check the input sig and bkg.");
		return false;
	}


	for(unsigned int i=0;i<_sig_num;i++){
		_sig_File.push_back(new TFile(input_sig[i].c_str(),"READ"));
		_sig_File[i]->cd();
		_sig_Tree.push_back((TTree*) _sig_File[i]->Get(para.file.root_head_name.c_str()));

		_sig_Tree[i]->SetBranchAddress("weight", &_weight);
		_sig_Tree[i]->SetBranchAddress(info.title_name.c_str(), &_value);

		std::string sig_histo_name=info.title_name+"_sig"+Int_to_String(i);
		_sig_histo.push_back(new TH1F(sig_histo_name.c_str(),sig_histo_name.c_str(),info.x_bin,info.x_min,info.x_max));
	}
	std::string sig_histo_name=info.title_name+"_sig";
	_sig_histo_total   = new TH1F("new sig total",sig_histo_name.c_str(),info.x_bin,info.x_min,info.x_max);

	for(unsigned int i=0;i<_bkg_num;i++){
		_bkg_File.push_back(new TFile(input_bkg[i].c_str(),"READ")) ;
		_bkg_File[i]->cd();
		_bkg_Tree.push_back((TTree*) _bkg_File[i]->Get(para.file.root_head_name.c_str()));

		_bkg_Tree[i]->SetBranchAddress("weight", &_weight);
		_bkg_Tree[i]->SetBranchAddress(info.title_name.c_str(), &_value);

		std::string bkg_histo_name=info.title_name+"_bkg"+Int_to_String(i);
		_bkg_histo.push_back(new TH1F(bkg_histo_name.c_str(),sig_histo_name.c_str(),info.x_bin,info.x_min,info.x_max));
	}


	std::string bkg_histo_name=info.title_name+"_bkg";
	_bkg_histo_total   = new TH1F("new bkg total",bkg_histo_name.c_str(),info.x_bin,info.x_min,info.x_max);

	return true;
}


bool APlot::Get_Histogram(CDraw &para, Avariable &input_info,std::string output_folder){

	if(!_Has_Input){
		ShowMessage(2,"Input files are not enough, please check the input sig and bkg.");
		return false;
	}

	Avariable info=input_info;
	info.leg->Clear();
	std::string leg_name  = info.latex_name;
	info.leg->SetHeader(leg_name.c_str(),"l");
	info.c=new TCanvas(info.c_name.c_str()," ",info.c_width,info.c_height);
	gPad->SetGrid();
	std::vector<std::string> stack_title = Set_Stack_Title(para, info.title_name+"_limit");
	THStack *ss = new THStack(stack_title[0].c_str(),stack_title[1].c_str() );


	ShowMessage(2,"Begin to fill data for signal.");
	float weight_sig_total = 0;
	float weight_bkg_total = 0;
	for(unsigned int i=0;i<_sig_num;i++){
		_sig_File[i]->cd();
		Long64_t nEvent = _sig_Tree[i]->GetEntries();
		ShowMessage(3,"signal",_sig_File[i]->GetName());
		float weight_sig= 0;
		for (Long64_t ievt=0; ievt<nEvent; ievt++) {
			_sig_Tree[i]->GetEntry(ievt);
			_sig_histo_total->Fill(_value,_weight);

			if(_value>-100){
				_sig_histo[i]->Fill(_value,_weight);
				weight_sig += _weight;
				weight_sig_total += _weight;
			}
		}
		ShowMessage(3,"MC number, simulated number",nEvent,weight_sig);
		info.leg->AddEntry(_sig_histo[i],"sig","l");
		Set_Line_Style(para,info,_sig_histo[i],i,i);
		ss->Add(_sig_histo[i]);
	}


	ShowMessage(2,"Begin to fill data for background.");
	for(unsigned int i=0;i<_bkg_num;i++){
		_bkg_File[i]->cd();
		Int_t nEvent = _bkg_Tree[i]->GetEntries();
		ShowMessage(3,"background",_bkg_File[i]->GetName());
		float weight_bkg= 0;
		for (Long64_t ievt=0; ievt<nEvent; ievt++) {
			_bkg_Tree[i]->GetEntry(ievt);
			_bkg_histo_total->Fill(_value,_weight);

			if(_value>-100){
				_bkg_histo[i]->Fill(_value,_weight);
				weight_bkg += _weight;
				weight_bkg_total += _weight;
			}
		}

		ShowMessage(3,"MC number, simulated number",nEvent,weight_bkg);

		std::string bkg_leg_name=Get_File_Ext(_bkg_File[i]->GetName());
////	boost::filesystem::path dir(_bkg_File[i]->GetName());
////	//std::string bkg_leg_name=dir.stem().string();
////	std::string bkg_leg_name="";
		info.leg->AddEntry(_bkg_histo[i],bkg_leg_name.c_str(),"l");
		Set_Line_Style(para,info,_bkg_histo[i],i+_bkg_num,i+_bkg_num);
		ss->Add(_bkg_histo[i]);
	}

	ShowMessage(2,"input events number for sig and bkg",weight_sig_total,weight_bkg_total);
	ShowMessage(2,"Begin to generate seperate plot.");
	ss->Draw("HIST,nostack");
	info.leg->Draw();
	Set_Stack_Style(para,info,ss,gPad,"");
	Print_Plot(para, info, output_folder+"input_for_sensitivity.png");
	delete ss;
	delete info.c;
	info.leg->Clear();
	info.leg = input_info.leg;




	// for combined signal and bkg histogram
	ShowMessage(2,"Begin to generate combined plot.");
	info.c=new TCanvas(info.c_name.c_str()," ",info.c_width,info.c_height);
	gPad->SetGrid();
	std::vector<std::string> stack_total_title = Set_Stack_Title(para, info.title_name+"_total_limit");
	THStack *ss_total = new THStack(stack_total_title[0].c_str(),stack_total_title[1].c_str() );


	info.leg->AddEntry(_sig_histo_total,"sig","l");
	info.leg->AddEntry(_bkg_histo_total,"bkg","l");

	Set_Line_Style(para,info,_sig_histo_total,0,0);
	Set_Line_Style(para,info,_bkg_histo_total,1,1);
	ss_total->Add(_sig_histo_total);
	ss_total->Add(_bkg_histo_total);

	ss_total->Draw("HIST,nostack");
	info.leg->Draw();
	Set_Stack_Style(para,info,ss_total,gPad,"");
	Print_Plot(para, info, output_folder+"input_combined_for_sensitivity.png");


	delete ss_total;
	delete info.c;

	return true;
}

void APlot::DrawLogo(){

   TImage *img = TImage::Open("ILD-logo.png");

   if (!img) {
      printf("Could not create an image... exit\n");
      return;
   }
   TPad *l = new TPad("l","l",0.25,0.70,0.45,0.90);
   //gPad->cd(0);
   l->Draw();
   l->cd();
   img->Draw();
}
