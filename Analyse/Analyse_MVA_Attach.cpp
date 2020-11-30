#include "Analyse/Analyse_MVA_Attach.h"

void Analyse_MVA_Attach_Pre(CDraw &para){
	AFile file_name;
	if(para.flow.flow_level==0){
		get_file_name(para,file_name,true);
	}
	else{
		get_file_name(para,file_name);
	}

	if(para.var.num_MVA>0){
		Analyse_MVA_Attach(para,file_name,1);
	}
	if((para.var.num_MVA1>0)&&(para.MVA.mva.size()==2)){
		Analyse_MVA_Attach(para,file_name,2);
	}


}
void Analyse_MVA_Attach(CDraw &para, AFile &file_name, int MVA_layer)
{

	ShowMessage(2,"Start TMVA Attaching");
	// --- Create the Reader object
	for(int i=0;i<file_name.Output_Num();i++){
		ShowMessage(3,"The attached file are",file_name.output[i].MVA_file);
	}


	TMVA::Reader *reader= new TMVA::Reader("!Color:!Silent" );
	if(MVA_layer==1){
		for(int i=0;i<para.var.num_MVA1;i++){
			reader->AddVariable(para.var.MVA1[i]->title_name.c_str(), &para.var.MVA1[i]->variable);
		}
	}
	else if(MVA_layer==2){
		for(int i=0;i<para.var.num_MVA1;i++){
			reader->AddVariable(para.var.MVA1[i]->title_name.c_str(), &para.var.MVA1[i]->variable);
		}
	}

	// --- Book the MVA methods
	//std::string weight_file=file_name.dataset_MVA+"/weights/TMVAClassification_MVA.weights.xml";
	std::string dataset_name;
	if(MVA_layer==1){
	    dataset_name="MVA_dataset_"+para.path.output_folder.substr(11)+"_1_"+para.flow.signal_property;
	}
	else if(MVA_layer==2){
		dataset_name="MVA_dataset_"+para.path.output_folder.substr(11)+"_2_"+para.flow.signal_property;
	}
	std::string weight_file=dataset_name+"/weights/TMVAClassification_"+para.MVA.MVA_Type()+".weights.xml";
	ShowMessage(2,"The weight file is", weight_file);
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

		float MVAoutput;
		TBranch *br ;
		if(MVA_layer==1){
			br = tree3->Branch("MVA",&MVAoutput);
		}
		else if(MVA_layer==2){
			br = tree3->Branch("MVA1",&MVAoutput);
		}

		ShowMessage(3, "Processing: " ,tree3->GetEntries() ," events" );
		TStopwatch sw;
		sw.Start();

		Int_t nEvent = tree3->GetEntries();
		for (Long64_t ievt=0; ievt<nEvent; ievt++) {
			CountNumber(ievt,nEvent,1000,"has dealed with number are");
			tree3->GetEntry(ievt);

			std::vector<float> f;
			f.resize(para.var.num_MVA1);
			if(MVA_layer==1){
				for(int nvar=0;nvar<para.var.num_MVA1;nvar++){
					TTreeFormula f1("n",para.var.MVA1[nvar]->title_name.c_str(),tree3);
					f[nvar] = f1.EvalInstance(ievt);
				}
			}
			else if(MVA_layer==2){
				for(int nvar=0;nvar<para.var.num_MVA1;nvar++){
					TTreeFormula f1("n",para.var.MVA1[nvar]->title_name.c_str(),tree3);
					f[nvar] = f1.EvalInstance(ievt);
				}
			}
	
			MVAoutput = reader->EvaluateMVA(f,"mymethod");
			br->Fill();
		}
		tree3->Write();
		input->Close();
	}

	ShowMessage(3, "Created root file containing the MVA output" );

	delete reader;

	ShowMessage(2, "TMVAClassificationApplication is done!" ); 

}
