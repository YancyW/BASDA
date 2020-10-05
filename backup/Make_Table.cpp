#include "Make_Table.h"
#include "AnalyseClass/File.h"

void Print_Complete_Channel(CDraw &para, float lumi, std::ostream& out, AFile_List &fileList, ASort_List& data){

	Print_Table_Begin(out,"tiny", fileList.File_Num()+4);

	if(lumi==0){
		lumi=1;
	}

	Print_Table_First_Column(out, para.scenario.Lumi_Tex(), true,40);
	for(int i=0;i<fileList.File_Num();i++){
        Print_Table_First_Column(out, fileList.File_Name(i), true);
	}
    Print_Table_First_Column(out, " total bkg", false);
	Print_Table_First_Column(out, " efficiency", false);
	Print_Table_Last_Column (out, " significance", false);

	//j=0 --> weight 
	//j>=1  --> data after cut
	for(int j=1;j<fileList.Data_Num();j++){
		Print_Line(out);
		if(j!=0){
			Print_Line(out);
		}
		for(int i=0;i<fileList.File_Num();i++){

			float data_ij=0;
			long int event_ij=0;
			if(j==1){// row --- no cut 
				data_ij = fileList.Data_Content(j,i);
			}
			else{
				data_ij = fileList.Data_Content(j,i)*lumi;
			}
			event_ij = fileList.Event_Content(j,i);

			std::vector<std::pair<std::string, int> > pos;
			pos = para.bkg_sort.Find_Class(fileList.File_Name(i));
			data.Input_Element(pos,fileList.Data_Name(j),data_ij);

			if(i==0){
				Print_Table_First_Column(out, fileList.Data_Name(j),true, 40);
			}

			std::string data_str=Float_to_String(data_ij)+" ("+ Int_to_String(event_ij)+ ")";
			Print_Table_First_Column(out, data_str);

			if(i==fileList.Last_File_Num()){
				float total     = data.Data_Bkg(j-1);
				float signal    = data.Data_Sig(j-1);
				float signal_ori= data.Data_Sig(1);
				Print_Table_First_Column(out, total);
				Print_Table_First_Column(out, signal/signal_ori);
				Print_Table_Last_Column (out, Get_Significance(signal,total));
			}
		}
	}

	Print_Table_End(out,"tiny");
}




void Print_Complete_Sort(CDraw &para, std::ostream& out, ASort_List& data){

	// ------------------------------------------------------------------------------------------------------
	// plot table for classified results
	Print_Table_Begin(out,"tiny", data.Total_Unzero_Sort_Num()+4);


	Print_Table_First_Column(out, para.scenario.Lumi_Tex(),true,40);
	for(int k=0;k<data.Sort_Num();k++){
		for(int l=0;l<data.Sub_Sort_Num(k);l++){
			if(data.Data_Content(1,k,l)!=0){
				Print_Table_First_Column(out, data.Data_Name(0,k,l), true);
			}
		}
	}
	Print_Table_First_Column(out, " total~bkg", true);
	Print_Table_First_Column(out, " efficiency", false);
	Print_Table_Last_Column(out, " significance", false);

	for(int j=1;j<data.Data_Num();j++){
		Print_Line(out);
		Print_Table_First_Column(out, data.Data_Name(j), true, 40);
		for(int k=0;k<data.Sort_Num();k++){
			for(int l=0;l<data.Sub_Sort_Num(k);l++){
				if(data.Data_Content(1,k,l)!=0){
					Print_Table_First_Column(out, data.Data_Content(j,k,l) );
				}
			}
		}
		if( data.Total_Unzero_Sort_Num()>1){
			Print_Table_First_Column(out, data.Data_Bkg(j));
			Print_Table_First_Column(out, data.Data_Sig(j)/data.Data_Sig(1)); 
			Print_Table_Last_Column (out, Get_Significance(data.Data_Sig(j),data.Data_Bkg(j)));
		}
	}

	Print_Table_End(out,"tiny");
}



float Make_Table(CDraw &para, float lumi, std::vector<std::string> yaml_file,std::string out_file_name){


	ShowMessage(2,"make tables");
	ShowMessage(2,"use following input data for significance:");
	std::ofstream out_file;
	out_file.open(out_file_name);


	AFile_List  fileList;


	for(unsigned int i=0;i<yaml_file.size();i++){
		ShowMessage(2,"file for make table",yaml_file[i]);
		YAML::Node file_node = YAML::LoadFile(yaml_file[i]);

		YAML::Node nodes = file_node["filenum"];

		for(YAML::const_iterator it=nodes.begin(); it != nodes.end(); ++it){
			if(it->first.as<std::string>()=="total result"){
				fileList.Input_Element(it->second.as<AFile_Data>());
				break;
			}
		}

	}

	ASort_List data;
	Print_Complete_Channel(para,lumi,out_file,fileList,data);
	Print_Complete_Sort   (para,out_file,data);
	float significance = data.Significance();
	return(significance);
}


void Make_Table_Pre(CDraw &para){
	AFile file_name;
	get_file_name(para,file_name);

	std::ofstream sig_file;
	sig_file.open(file_name.significance);

	std::vector<std::string> ana_out_name;
	for(int i=0;i<file_name.Output_Num();i++){
		ana_out_name.push_back(file_name.output[i].ana_data);
	}
	float sig = Make_Table(para,para.scenario.Lumi(),ana_out_name,file_name.output_table);

	RecordMessage(sig_file,2,"significance is", sig);

	sig_file.close();
}

