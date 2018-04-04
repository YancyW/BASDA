#include "Make_Complete_Table.h"
#include "AnalyseClass/File.h"

void Print_Complete_Combine(CDraw &para, std::ostream& out, std::vector<std::vector<float> >& final_cut){

	std::vector<float> combine_cut(final_cut[0].size(),0.0);
	float bkg=0.0;
	for(unsigned int i=0;i<final_cut.size();i++){
		for(unsigned int j=0;j<final_cut[i].size();j++){
			combine_cut[j]+=final_cut[i][j];
			if(j!=0){
				bkg+=final_cut[i][j];
			}
		}
	}

	Print_Table_Begin(out,"tiny", para.bkg_sort.Total_Sort_Num()+3);


	Print_Table_First_Column(out, para.scenario.Lumi_Tex(),true);
	for(int k=0;k<para.bkg_sort.Num();k++){
		for(int l=0;l<para.bkg_sort.sort[k].Sub_Num();l++){
			Print_Table_First_Column(out, para.bkg_sort.sort[k].Legend(l), true);
		}
	}
	Print_Table_First_Column(out, " total~bkg", true);
	Print_Table_Last_Column(out, " significance", false);

	Print_Line(out);
	Print_Table_First_Column(out, "combined events");

	for(int k=0;k<para.bkg_sort.Total_Sort_Num();k++){
		Print_Table_First_Column(out, combine_cut[k]);
	}
	Print_Table_First_Column(out, bkg);
	Print_Table_Last_Column (out, Get_Significance(combine_cut[0],bkg));

	Print_Table_End(out,"tiny");

}




float Make_Complete_Table(CDraw &para, float lumi, std::vector<std::string> yaml_file,std::string out_file_name,bool IsRecord, std::vector<float>& final_cut){


	std::ofstream out_file;
	if(IsRecord){
		out_file.open(out_file_name);
	}
	else{
		out_file.open(out_file_name,std::ios::app);
	}


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
	Print_Complete_Sort   (para,lumi,out_file,fileList,data);
	float significance = data.Significance();
	final_cut = data.Data_Final();
	return(significance);
}








void Make_Complete_Table_Pre(CDraw &para){
	float lumi                          = para.scenario.Lumi();

	ShowMessage(2,"make tables for all beam polariazation combination");

	std::ofstream sig_file;
	std::string combined_folder = para.default_path.output_file+"/"+para.flow.signal_property+"/data_combine_"+para.flow.signal_property+".dat";
	ShowMessage(2,"combined significance is in ",combined_folder);
	Create_File_Folder(combined_folder);
	sig_file.open(combined_folder);

	std::vector<std::vector<float> >final_cut;
	final_cut.resize(para.scenario.Run_Ratio_Vec().size());
	int index=0;

	bool only_lr                        = false;
	if(para.scenario.Run_Ratio_Vec().size()==2){
		only_lr =true;
	}

	Print_Item_Begin(sig_file);
	for(int i=-1;i<2;i=i+2){
		for(int j=-1;j<2;j=j+2){
			if(only_lr){
				if(i==j){continue;}
			}

			ShowMessage(2,"use following input data for significance:");
			para.path.output_file  = para.default_path.output_file  + Int_to_String(i) + Int_to_String(j);
			ShowMessage(2,"output file        ",para.path.output_file);
			para.path.Create_Folder();

			AFile file_name;
			get_file_name(para,file_name);

			para.scenario.default_scenario.lumi = lumi * para.scenario.Run_Ratio(i,j);
			Print_Item(sig_file,"$"+para.scenario.Run_Ratio_Marker(i,j)+"$ significance is:  ",1);

			ShowMessage(2,"make tables for beam pol ",i,j);
			std::vector<std::string> ana_out_name;
			for(int i=0;i<file_name.Output_Num();i++){
				ana_out_name.push_back(file_name.output[i].ana_Unpol);
			}
			float input_lumi = para.scenario.Lumi();
			Make_Complete_Table(para,input_lumi,ana_out_name,file_name.reweight_table,true,final_cut[index]);


			ana_out_name.clear();
			for(int i=0;i<file_name.Output_Num();i++){
				ana_out_name.push_back(file_name.output[i].ana_data);
			}
			input_lumi = para.scenario.Lumi()/lumi;
			float sig = Make_Complete_Table(para,input_lumi,ana_out_name,file_name.reweight_table,false,final_cut[index]);

			Print_Item(sig_file, sig,-1);

			index++;
		}
	}
	Print_Item_End(sig_file);

	Print_Complete_Combine(para, sig_file, final_cut);

	sig_file.close();
}


