#include "Analyse/Analyse_BDT_Train.h"

void Analyse_BDT_Train_Pre(CDraw &para){
	AFile file_name;
	get_file_name(para,file_name);

	std::ofstream sig_file;
	sig_file.open(file_name.significance);

	Analyse_BDT_Train(para,file_name);

	sig_file.close();
}


void Analyse_BDT_Train(CDraw &para, AFile &file_name){

	TMVA::Tools::Instance();
	std::map<std::string,int> Use;

	// --- Boosted Decision Trees
	Use["BDTG"]             = 1; // uses Adaptive Boost

	ShowMessage(2,"Start TMVAClassification");

	TFile* outputFile = TFile::Open( file_name.output_MVA.c_str(), "RECREATE" );
	ShowMessage(2,"The output file is",file_name.output_MVA);

	TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
			"!V:!Silent:Color:!DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

	TMVA::DataLoader *dataloader=new TMVA::DataLoader(file_name.dataset_MVA.c_str());
	ShowMessage(2,"The dataset for MVA is",file_name.dataset_MVA);

	std::string cuts_des = "";
	std::string cutb_des = "";
	for(int i=0;i<para.var.numBDT;i++){
		dataloader->AddVariable(para.var.BDT[i].title_name.c_str(), 'F' );
		cuts_des+=  para.var.BDT[i].title_name+">-100";
		cutb_des+=  para.var.BDT[i].title_name+">-100";
		if(i!=para.var.numBDT-1){
			cuts_des+= "&&";
			cutb_des+= "&&";
		}
	} 

	//TFile *inputS = TFile::Open( fileS );
	ShowMessage(2,"The input signal file is",file_name.output[0].Unpol_file);

	TChain chainsigtrain(para.file.root_head_BDT_name.c_str());
	chainsigtrain.Add(file_name.output[0].Unpol_file.c_str());
	TChain chainsigtest(para.file.root_head_name.c_str());
	chainsigtest.Add(file_name.output[0].Unpol_file.c_str());

	TChain chainbgtrain(para.file.root_head_BDT_name.c_str());
	TChain chainbgtest(para.file.root_head_name.c_str());

	for(int i=1;i<file_name.Output_Num();i++){
		ShowMessage(2,"The input background file are",file_name.output[i].Unpol_file);
		chainbgtrain.Add(file_name.output[i].Unpol_file.c_str());
		chainbgtest .Add(file_name.output[i].Unpol_file.c_str());
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

	dataloader->PrepareTrainingAndTestTree( mycuts, mycutb, "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );

	ShowMessage(2);
	ShowMessage(2, "Booking Start");
	if (Use["BDTG"]) {
		factory->BookMethod(dataloader,  TMVA::Types::kBDT, "BDTG",
            "!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=5" );
	} // Adaptive Boost

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

