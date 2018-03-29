#include "Analyse_Sensitivity.h"


void Analyse_Sensitivity_Pre(CDraw &para){
	AFile file_name;
	get_file_name(para,file_name);
	std::vector<std::string> input_sigfile_name;
	std::vector<std::string> input_bkgfile_name;

	std::string output_file_name   =file_name.sensitivity;
	std::string output_folder      =file_name.folder[7];

	input_sigfile_name.push_back(file_name.output[0].CUT_file);
	for(unsigned int i=1;i<file_name.output.size();i++){
		input_bkgfile_name.push_back(file_name.output[i].CUT_file);
	}

	APlot plot;
	Avariable info=para.var.var[3];
	plot.Get_Input_File(para, info, input_sigfile_name, input_bkgfile_name);
	plot.Get_Histogram(para, info, output_folder);
	Analyse_Sensitivity(para, plot, output_file_name, output_folder);
	ShowMessage(2,"finish analyse sensitivity.");
}

void Analyse_Sensitivity_Complete(CDraw &para){

	AFile file_name;
	get_file_name(para,file_name);
	std::vector<std::string> input_sigfile_name;
	std::vector<std::string> input_bkgfile_name;

	std::string output_file_name   =file_name.sensitivity;
	std::string output_folder      =file_name.folder[7];

	std::string output_path = para.path.output_file  ;
	std::string event_path  = para.path.event_file   ;

	for(int i=-1;i<2;i=i+2){
		for(int j=-1;j<2;j=j+2){
			para.path.output_file  = output_path+ Int_to_String(i) + Int_to_String(j);
			para.path.event_file   = event_path+ Int_to_String(i) + Int_to_String(j);
			para.path.Create_Folder();
			get_file_name(para,file_name);

			input_sigfile_name.push_back(file_name.output[0].CUT_file);
			for(unsigned int i=1;i<file_name.output.size();i++){
				input_bkgfile_name.push_back(file_name.output[i].CUT_file);
			}
		}
	}
	APlot plot;
	Avariable info=para.var.var[3];
	plot.Get_Input_File(para, info, input_sigfile_name, input_bkgfile_name);
	plot.Get_Histogram(para, info, output_folder);
	Analyse_Sensitivity(para, plot, output_file_name,output_folder);
}


void Analyse_Sensitivity(CDraw &para, APlot &plot, std::string output_file_name, std::string output_folder){

	Double_t _xvalue=para.flow.hmass;
	Double_t ExpCL = para.sensitivity.ExpCL; 
	ShowMessage(2," Expected Confidence level is:",ExpCL);  

	std::string output_histo_name  = output_folder + "Sensitivity_plot";
	std::string output_beam_name   = output_folder + "Beam spectra";


	TFile * output_file = new TFile(output_file_name.c_str(),"recreate");
	output_file->cd();

	TList* list = new TList();
	TTree * t1=new TTree("Parameters","All parameters used in calculation");
	t1->Branch("ExpCL", &ExpCL, "new_v/D"); 

	TH1F* Sensitivity = new TH1F(output_histo_name.c_str(),output_histo_name.c_str(),250,1,250);
	TH1F* beamspec    = new TH1F("Beam spectra","Beam spectra",300,0.0,300.0);

	// SYSError 
	
////std::cout<<" Calculation with systematic errors  :"<<std::endl;
////// consider NSYS systematic sources
////// create histograms with relative errors
////Int_t NSYS=5;
////TString sys_names[NSYS];
////sys_names[0]="luminosity";
////sys_names[1]="polp";
////sys_names[2]="pole";
////sys_names[3]="beam";
////sys_names[4]="select";   
////TH1F *histBgrSys[NSYS][2];
////TH1F *histSignalSys[NSYS][2];
////for(Int_t s=0;s<NSYS;s++) {
////	for(Int_t ds=0;ds<2;ds++) {
////		TString name("Sys_error_");
////		name += sys_names[s];

////		TString name1,name2;

////		name2 =name+"_background";
////		name2 +=ds;
////		std::cout<<name2<<std::endl;
////		histBgrSys[s][ds]=new TH1F(name2,"Background errors",300,0.0,300.0);

////		name1 =name+"_signal";
////		name1 +=ds;
////		histSignalSys[s][ds]=new TH1F(name1,"Signal errors",300,0.0,300.0);
////		std::cout<<name1<<std::endl;
////	}
////}

    plot.Sig_Histo_Total()->Scale(std::pow(91.2,2));


////// Fill errors histograms
////std::cout<<"BINS = "<<histBgrSys[0][0]->GetNbinsX()<<std::endl;

//////FILL  LUMINOSITY Systematic errors
////Int_t s=0;

////for(Int_t i=1;i<=histBgrSys[s][0]->GetNbinsX();i++){
////	Double_t bg_sys=0.0011,sig_sys=0.0011;
////	if(i==1){
////		t1->Branch("bg_sys_lumi", &bg_sys);
////		t1->Branch("sig_sys_lumi", &sig_sys);}	
////	histBgrSys[s][0]->Fill(i,bg_sys);
////	histSignalSys[s][0]->Fill(i,sig_sys);
////}

//////FILL  Pp Systematic errors 
////s=1;

////for(Int_t i=1;i<=histBgrSys[s][0]->GetNbinsX();i++){
////	Double_t error_size= 0.0025;
////	//	Double_t error_size= 0.001;	
////	if(i==1){std::cout<<"POL P eroor ="<<error_size<<std::endl;
////		t1->Branch("Pp_Systematic_error", &error_size);}
////	Double_t signal_bin = sig_histo->GetBinContent(i);
////	Double_t bg_bin = bkg_histo->GetBinContent(i);	
////	//	std::cout<<"signal_bin = "<<signal_bin<<"| bg_bin = "<<bg_bin<<" ;"<<std::endl;

////	Double_t 	 bg_sysup=bg_bin*(1.0+error_size);
////	Double_t 	 bg_sysdown=bg_bin*(1.0-error_size);
////	Double_t	 sig_sysup=signal_bin*(1.0+error_size);
////	Double_t	 sig_sysdown=signal_bin*(1.0-error_size);

////	histBgrSys[s][0]->Fill(i,bg_sysup);
////	histBgrSys[s][1]->Fill(i,bg_sysdown);	
////	histSignalSys[s][0]->Fill(i,sig_sysup);
////	histSignalSys[s][1]->Fill(i,sig_sysdown);	

////}


//////FILL  Pe Systematic errors 
////s=2;
////for(Int_t i=1;i<=histBgrSys[s][0]->GetNbinsX();i++){
////	Double_t error_size= 0.0025;
////	//	Double_t error_size= 0.001;	
////	if(i==1){std::cout<<"POL E eroor ="<<error_size<<std::endl;
////		t1->Branch("Pe_Systematic_error", &error_size);}	
////	Double_t signal_bin = sig_histo->GetBinContent(i);
////	Double_t bg_bin = bkg_histo->GetBinContent(i);	
////	//	std::cout<<"signal_bin = "<<signal_bin<<"| bg_bin = "<<bg_bin<<" ;"<<std::endl;

////	Double_t 	 bg_sysup=bg_bin*(1.0+error_size);
////	Double_t 	 bg_sysdown=bg_bin*(1.0-error_size);
////	Double_t	 sig_sysup=signal_bin*(1.0+error_size);
////	Double_t	 sig_sysdown=signal_bin*(1.0-error_size);

////	//        std::cout<<"sig_sys = "<<sig_sys<<"| bg_sys  = "<<bg_sys<<" ;"<<std::endl;

////	histBgrSys[s][0]->Fill(i,bg_sysup);
////	histBgrSys[s][1]->Fill(i,bg_sysdown);	
////	histSignalSys[s][0]->Fill(i,sig_sysup);
////	histSignalSys[s][1]->Fill(i,sig_sysdown);	

////}

//////##########################################################################
//////FILL  Beam spectra parameters   
////for(Int_t i=10;i<=110;i++){
////	Double_t error_size=0;
////	//	Double_t signal_bin = sh->GetBinContent(i);
////	//	Double_t bg_bin = bh->GetBinContent(i);	
////	//	std::cout<<"signal_bin = "<<signal_bin<<"| bg_bin = "<<bg_bin<<" ;"<<std::endl;

////	if(i<=20) {error_size=-0.0006;}	
////	else if(i<=30) {error_size= 0.0035;} 
////	else if(i<=40) {error_size= 0.0013;}
////	else if(i<=50) {error_size=-0.0012;}
////	else if(i<=60) {error_size=-0.002; }
////	else if(i<=70) {error_size=-0.0058;}
////	else if(i<=80) {error_size=-0.008; }
////	else if(i<=90) {error_size=-0.01;  }
////	else if(i<=100){error_size=-0.0056;}
////	else if(i<=110){error_size=-0.0072;}
////	else {std::cout<<"Same size";}

////	//     std::cout<<"i = "<<i<<"| error_size  = "<<error_size<<" ;"<<std::endl;


////	beamspec->Fill(i,error_size);
////}

//////FILL  Beam spectra parameters   errors 
////s=3;


////histBgrSys[s][0]->Multiply(bkg_histo,beamspec);
////histBgrSys[s][0]->Add(bkg_histo);	

////histBgrSys[s][1]->Multiply(bkg_histo,beamspec,-1);
////histBgrSys[s][1]->Add(bkg_histo);

////histSignalSys[s][0]->Multiply(sig_histo,beamspec);
////histSignalSys[s][0]->Add(sig_histo);

////histSignalSys[s][1]->Multiply(sig_histo,beamspec,-1);
////histSignalSys[s][1]->Add(sig_histo);




//////FILL  Selection Systematic errors
////s=4;

////for(Int_t i=1;i<=histBgrSys[s][0]->GetNbinsX();i++){
////	Double_t bg_sys=0.0043,sig_sys=0.0043;	
////	if(i==1){
////		t1->Branch("Selection_Systematic_errors_bg", &bg_sys);
////		t1->Branch("Selection_Systematic_errors_sig`", &sig_sys);}	
////	histBgrSys[s][0]->Fill(i,bg_sys);
////	histSignalSys[s][0]->Fill(i,sig_sys);
////}







////std::cout<<" reach here           :"<<std::endl;  
////std::cout<<" Integral before           :"<<sig_histo->Integral()<<std::endl;  
//////   	sh->Scale(pow(_lambda,4));



    ShowMessage(2,"Before add channel");
    TSysLimitChannel *channel=new TSysLimitChannel();
    channel->SetData(plot.Bkg_Histo_Total());
    channel->SetPrediction(plot.Sig_Histo_Total(),plot.Bkg_Histo_Total(),0); // without errors (sh,bh,0)


    //################# NUMBER OF SYSError ########################
////NSYS=5;
////// ADD 	SYSTEMATIC ERRORS
////for(Int_t m=0;m<NSYS;m++) {
////	TString name("Sys_error_");
////	if(m==0){name += "luminosity";
////		std::cout<< "DONE "<<name<<std::endl;
////		channel->AddSysRelative(histSignalSys[m][0],histBgrSys[m][0],name,1); // correlative add 1 
////	}else if (m==3) {
////		name += "beam spectra";
////		std::cout<< "DONE "<<name<<std::endl;
////		channel->AddSysUpDown(histSignalSys[m][0],histSignalSys[m][1],histBgrSys[m][0],histBgrSys[m][1],name,1); // correlative add 1 
////	} else if (m==4) {name += "selection";
////		name +=m;
////		std::cout<< "DONE "<<name<<std::endl;
////		channel->AddSysRelative(histSignalSys[m][0],histBgrSys[m][0],name,1); // correlative add 1
////		//	    channel->AddSysUpDown(histSignalSys[m][0],histSignalSys[m][1],histBgrSys[m][0],histBgrSys[m][1],name,1);
////	}else {name += "polarization";
////		name +=m;
////		std::cout<< "DONE "<<name<<std::endl;
////		channel->AddSysUpDown(histSignalSys[m][0],histSignalSys[m][1],histBgrSys[m][0],histBgrSys[m][1],name,1);
////	}
////}



	TSysLimit limit(0); 
	limit.AddChannel(channel);


	Double_t CL_observed = 0.0;
	Double_t CL_expected = 0.0;
	Double_t k           = 100.0;
	Double_t k_last      = 100.0;
	Double_t stepwidth   = 256;
	Double_t factor      = 0;
	int  counter         = 0;



	while(stepwidth>0.0044)
	{
		CL_observed = 0.0;
		counter     = 0;
		while( CL_observed < (1-ExpCL))
		{
			factor =pow(k,-para.sensitivity.sig_scale_pow);

			limit.CalculateCL(factor,50000);
			TSysLimitResult const *result=limit.GetResult(3); // Log(S+B/B)
			result->Print();
			CL_observed = result->GetDataCLs();   
			CL_expected = result->GetDataCLs();   
			ShowMessage(2,"CLs expected   = ",CL_expected);
			ShowMessage(2,"CLs observed   = ",CL_observed, "k =" , k);
			ShowMessage(2,"1-CLs observed = ",1-CL_observed);



			if (CL_observed < (1-ExpCL)){
				k_last = k;
			}

			k += stepwidth; 

			counter++;
			ShowMessage(2," COUNTER = "  ,counter  );
			ShowMessage(2," stepwidth = ",stepwidth);
			ShowMessage(2," k in CL_observed loop= "  ,k);
			if (counter>40)break;

		}

		k = k_last;
		ShowMessage(2," k in stepwidth loop = "  ,k);
		stepwidth *= 0.5;
		ShowMessage(2," COUNTER AFTER = ",counter);
	}

	Sensitivity->Fill(_xvalue,k);
	list->Add(Sensitivity);

	ShowMessage(2,"Lambda out  = " ,k               ); 
	ShowMessage(2,"CLs         = " ,CL_observed     );


	channel->Delete();

	list->Add(beamspec);

	list->Add(plot.Sig_Histo_Total());
	list->Add(plot.Bkg_Histo_Total());

	output_file->cd();
	list->Print();
	list->Write();


	t1->Write();
	t1->Fill();
	t1->Print();
	output_file->Close();
	ShowMessage(2,"SAVE FILE");  





	return ;
}

