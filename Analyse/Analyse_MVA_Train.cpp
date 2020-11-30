#include "Analyse/Analyse_MVA_Train.h"

void Analyse_MVA_Train_Pre(CDraw &para){
	AFile file_name;
	if(para.flow.flow_level==0){
		get_file_name(para,file_name,true);
	}
	else{
		get_file_name(para,file_name);
	}

	std::ofstream sig_file;
	sig_file.open(file_name.significance);

	if(para.var.num_MVA>0){
		Analyse_MVA_Train(para,file_name,1);
	}
	if((para.var.num_MVA1>0)&&(para.MVA.mva.size()==2)){
		Analyse_MVA_Train(para,file_name,2);
	}

	sig_file.close();
}


void Analyse_MVA_Train(CDraw &para, AFile &file_name, int MVA_layer){

	TMVA::Tools::Instance();
	std::map<std::string,int> Use;

	// --- Boosted Decision Trees
	Use[para.MVA.MVA_Type()]             = 1; // uses Adaptive Boost

	ShowMessage(2,"Start TMVAClassification");

	std::string MVA_outfile_name;
	if(MVA_layer==1){
		MVA_outfile_name=file_name.output_MVA+"_1";
	}
	else if(MVA_layer==2){
		MVA_outfile_name=file_name.output_MVA+"_2";
	}
	

	TFile* outputFile = TFile::Open( file_name.output_MVA.c_str(), "RECREATE" );
	ShowMessage(2,"The output file is",file_name.output_MVA);

	//TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
	//		"!V:!Silent:Color:!DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
	TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,para.MVA.MVA_Factory_Setting().c_str());

	//TMVA::DataLoader *dataloader=new TMVA::DataLoader(file_name.dataset_MVA.c_str());

	std::string dataset_name;
	if(MVA_layer==1){
		dataset_name="MVA_dataset_"+para.path.output_folder.substr(11)+"_1_"+para.flow.signal_property;
	}
	else if(MVA_layer==2){
		dataset_name="MVA_dataset_"+para.path.output_folder.substr(11)+"_2_"+para.flow.signal_property;
	}
	TMVA::DataLoader *dataloader=new TMVA::DataLoader(dataset_name.c_str());
	ShowMessage(2,"The dataset for MVA is",dataset_name);

	std::string cuts_des = "";
	std::string cutb_des = "";
	if(MVA_layer==1){
		for(int i=0;i<para.var.num_MVA;i++){
			dataloader->AddVariable(para.var.MVA1[i]->title_name.c_str(), 'F' );
			cuts_des+=  para.var.MVA[i]->title_name+">-100.2";
			cutb_des+=  para.var.MVA[i]->title_name+">-100.2";
			if(i!=para.var.num_MVA-1){
				cuts_des+= "&&";
				cutb_des+= "&&";
			}
		} 
	}
	else{
		for(int i=0;i<para.var.num_MVA1;i++){
			dataloader->AddVariable(para.var.MVA1[i]->title_name.c_str(), 'F' );
			cuts_des+=  para.var.MVA1[i]->title_name+">-100.2";
			cutb_des+=  para.var.MVA1[i]->title_name+">-100.2";
			if(i!=para.var.num_MVA1-1){
				cuts_des+= "&&";
				cutb_des+= "&&";
			}
		} 
	}

	//TFile *inputS = TFile::Open( fileS );
	TChain chainsigtrain(para.file.root_head_MVA_name.c_str());
	TChain chainsigtest(para.file.root_head_name.c_str());
	TChain chainbgtrain(para.file.root_head_MVA_name.c_str());
	TChain chainbgtest(para.file.root_head_name.c_str());


	std::vector<std::string> input_MVA_file;
	if(para.MVA.default_mva.MVA_file[0]=="all"){
		input_MVA_file=file_name.Get_Output_Unpol_Files(); 
	}
	else{
		if(MVA_layer==1){
			input_MVA_file=file_name.Get_Output_Unpol_Files(para.MVA.mva[0].MVA_file);
		}
		else if(MVA_layer==2){
			input_MVA_file=file_name.Get_Output_Unpol_Files(para.MVA.mva[1].MVA_file);
		}
	}

	ShowMessage(2,"The input signal file is",input_MVA_file[0]);
	chainsigtrain.Add(input_MVA_file[0].c_str());
	chainsigtest .Add(input_MVA_file[0].c_str());
	
	for(unsigned int i=1;i<input_MVA_file.size();i++){
		ShowMessage(2,"The input background file are",input_MVA_file[i]);
		chainbgtrain.Add(input_MVA_file[i].c_str());
		chainbgtest .Add(input_MVA_file[i].c_str());
	}

	TChain *signalTrain     = &chainsigtrain;
	TChain *signalTest      = &chainsigtest ;
	TChain *backgroundTrain = &chainbgtrain ;
	TChain *backgroundTest  = &chainbgtest  ;

	// global event weights per tree (see below for setting event-wise weights)
	Double_t signalWeight     = 1.0;
	Double_t backgroundWeight = 1.0;

	dataloader->SetSignalWeightExpression("weight");
	dataloader->SetBackgroundWeightExpression("weight");

	dataloader->AddSignalTree    ( signalTrain    , signalWeight    , "Training" );
	dataloader->AddSignalTree    ( signalTest     , signalWeight    , "Test"     );
	dataloader->AddBackgroundTree( backgroundTrain, backgroundWeight, "Training" );
	dataloader->AddBackgroundTree( backgroundTest , backgroundWeight, "Test"     );

	// Apply additional cuts on the signal and background samples (can be different)

	TCut mycuts = cuts_des.c_str();
	TCut mycutb = cutb_des.c_str();

	dataloader->PrepareTrainingAndTestTree( mycuts, mycutb, para.MVA.MVA_Event_Setting().c_str() );

	ShowMessage(2);
	ShowMessage(2, "Booking Start");
//if (Use["BDTG"]) {
//	factory->BookMethod(dataloader,  TMVA::Types::kBDT, "BDTG",
//			"!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=5" );
//} // Adaptive Boost
	if (Use[para.MVA.MVA_Type()]) {
		factory->BookMethod(dataloader,  TMVA::Types::kBDT, para.MVA.MVA_Type().c_str(),para.MVA.MVA_Method_Setting().c_str() );
	}

	ShowMessage(2, "Training Start");
	// Train MVAs using the set of training events
	factory->TrainAllMethods();
	ShowMessage(2, "Training End");

	// ---- Evaluate all MVAs using the set of test events
	ShowMessage(2, "Testing Start");
	factory->TestAllMethods();
	ShowMessage(2, "Testing End");

	// ----- Evaluate and compare performance of all configured MVAs
	ShowMessage(2, "Evaluation Start");
	factory->EvaluateAllMethods();
	ShowMessage(2, "Evaluation End");

	// --------------------------------------------------------------

	// Save the output
	outputFile->Close();

	ShowMessage(2,"Wrote root file: " ,outputFile->GetName());
	ShowMessage(2,"TMVAClassification is done!");

	// Clean up
	delete factory;
	delete dataloader;
	if(!gROOT->IsBatch()) TMVA::TMVAGui( file_name.output_MVA.c_str());
}

