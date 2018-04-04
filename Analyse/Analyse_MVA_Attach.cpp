#include "Analyse/Analyse_MVA_Attach.h"

void Analyse_MVA_Attach_Pre(CDraw &para){
	AFile file_name;
	get_file_name(para,file_name);

	Analyse_MVA_Attach(para,file_name);

}
void Analyse_MVA_Attach(CDraw &para, AFile &file_name)
{

	ShowMessage(2,"Start TMVA Attaching");
	// --- Create the Reader object
	for(int i=0;i<file_name.Output_Num();i++){
		ShowMessage(3,"The attached file are",file_name.output[i].MVA_file);
	}


	TMVA::Reader *reader= new TMVA::Reader("!Color:!Silent" );
	for(int i=0;i<para.var.numMVA;i++){
		reader->AddVariable(para.var.MVA[i].title_name.c_str(), &para.var.MVA[i].variable);
	}

	// --- Book the MVA methods
	std::string weight_file=file_name.dataset_MVA+" "+para.MVA.MVA_type+"/weights/TMVAClassification_MVA.weights.xml";
	reader->BookMVA("mymethod",weight_file.c_str());

	for(int i=0;i<file_name.Output_Num();i++){

		TFile* input = TFile::Open( file_name.output[i].MVA_file.c_str(),"update" );

		if (!input) {
			ShowMessage(2, "ERROR: could not open data file" );
			exit(1);
		}
		ShowMessage(3, "TMVAClassificationApp    : Using input file: " ,input->GetName() );

		// --- Event loop

		ShowMessage(3, "TMVAClassificationApp    : Using branch: " ,para.file.root_head_name );
		TTree* tree3 = (TTree*)input->Get(para.file.root_head_name.c_str());

		float MVAGoutput;
		TBranch *br = tree3->Branch("MVA",&MVAGoutput);

		ShowMessage(3, "Processing: " ,tree3->GetEntries() ," events" );
		TStopwatch sw;
		sw.Start();

		Int_t nEvent = tree3->GetEntries();
		for (Long64_t ievt=0; ievt<nEvent; ievt++) {
			CountNumber(ievt,nEvent,1000,"has dealed with number are");
			tree3->GetEntry(ievt);

			std::vector<float> f;
			f.resize(para.var.numMVA);
			for(int nvar=0;nvar<para.var.numMVA;nvar++){
				TTreeFormula f1("n",para.var.MVA[nvar].title_name.c_str(),tree3);
				f[nvar] = f1.EvalInstance(ievt);
			}
			MVAGoutput = reader->EvaluateMVA(f,"mymethod");
			br->Fill();
		}
		tree3->Write();
		input->Close();
	}

	ShowMessage(3, "Created root file containing the MVA output" );

	delete reader;

	ShowMessage(2, "TMVAClassificationApplication is done!" ); 

}
