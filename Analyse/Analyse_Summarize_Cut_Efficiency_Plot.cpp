#include "Analyse/Analyse_Summarize_Cut_Efficiency_Plot.h"

void Analyse_Complete_Summarize_Cut_Efficiency_Plot(CDraw &para){

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
			ShowMessage(2,"use following input data for significance:");
			para.path.horizontal_summary_plot = para.default_path.horizontal_summary_plot + Int_to_String(i) + Int_to_String(j);
			ShowMessage(2,"output file        ",para.path.horizontal_summary_plot);

			Analyse_Summarize_Cut_Efficiency_Plot(para);
		}
	}


}





void Analyse_Summarize_Cut_Efficiency_Plot(CDraw &para){


	ShowMessage(2,"make summarize cut efficiency plot");


	ASort_List summarized_sort;
	std::string cut_name="cos\\theta_{mis} \\in [ -0.99 ,0.99 ]";

	ShowMessage(1,"cut",cut_name);
	AFile file_name;
	file_name.Clear();
	for(int i=0;i<para.signal_scan.property_num;i++){
		std::string ori_mass=para.flow.signal_property;
		para.flow.signal_property= para.signal_scan.properties[i];
		std::string new_mass=para.flow.signal_property;

		std::string new_bkg_file= para.path.bkg_sort_file.replace(para.path.bkg_sort_file.find(ori_mass), ori_mass.length(), new_mass); 
		if(!para.flow.record_output){
			freopen(para.path.record_file.c_str() ,"a",stdout);
		}
		para.bkg_sort.Read_BKG_Sort_Test(para.path);
		if(!para.flow.record_output){
			fclose(stdout);
			freopen("/dev/tty","w",stdout);
		}
		ShowMessage(2,"make effi plots for mass",para.flow.signal_property);
		ShowMessage(2,"new_bkg_file",new_bkg_file);

		get_file_name(para,file_name);
		AFile_List  fileList;
		
		std::vector<std::string> ana_out_name;
		for(int i=0;i<file_name.Output_Num();i++){
			YAML::Node file_node = YAML::LoadFile(file_name.output[i].ana_data);
		
			YAML::Node nodes = file_node["filenum"];
		
			for(YAML::const_iterator it=nodes.begin(); it != nodes.end(); ++it){
				if(it->first.as<std::string>()=="total result"){
					fileList.Input_Element(it->second.as<AFile_Data>());
					break;
				}
			}
		}

		ASort_List data;
		Extract_Sort_Data(para,fileList,data);

		AFile_Data subsort_data;
		subsort_data=data.Get_Row_Data(cut_name);

		summarized_sort.Add_Sort(para.flow.signal_property, cut_name, subsort_data);
	}

	para.path = para.default_path ;
	para.flow = para.default_flow;
	para.bkg_sort= para.default_bkg_sort;
	get_file_name(para,file_name);

	std::string output_plot=file_name.folder[7]+"Summarize_Cut_Efficiency_Plot.png" ;
	ShowMessage(1,"horizontal_summary_plot",output_plot);
	summarized_sort.Print();
	Draw_Summarize_Cut_Efficiency_Plot(para,summarized_sort,output_plot);

}


void Draw_Summarize_Cut_Efficiency_Plot(CDraw &para, ASort_List data, std::string output_plot){
	(void) para;


	TH1F*  fvariable;
	TCanvas *c1=new TCanvas("c1","c1",1000,700);
	TPad *center_pad = new TPad("center_pad", "center_pad",0.05,0.05,0.90,0.90);
	center_pad->Draw();


	float xaxis[3];
	xaxis[0]=data.Total_Unzero_Sort_Num();
	xaxis[1]=0;
	xaxis[2]=xaxis[0];

	fvariable = new TH1F("effi_plot","effi_plot",xaxis[0],xaxis[1],xaxis[2]);

	data.Print();
	data._list[0].second[0].second.Set_Data_Pos("Improvement_I");
	int pos=data._list[0].second[0].second.Data_Pos();
	ShowMessage(1,"pos",pos);
	for(int k=0;k<data.Sort_Num();k++){
		ShowMessage(2,"content",data.Data_Content(pos,k,0));
		fvariable->Fill(data.Sort_Name(k).c_str(),data.Data_Content(pos,k,0));
	}

	center_pad->cd();
	gStyle->SetPalette(1);
	gStyle->SetTitleAlign(33);
	gStyle->SetTitleY(1.00);
	fvariable->GetYaxis()->SetTitle("relative improvement");
	fvariable->GetXaxis()->SetTitle("mass");
	fvariable->Draw("HIST");

	c1->Update();
	TImage *img_2d = TImage::Create();
	img_2d->FromPad(c1);
	std::string pngname_2d=output_plot;
	std::cout<<pngname_2d << std::endl;
	img_2d->WriteImage(pngname_2d.c_str());
	delete fvariable;
	delete c1;

	return;
}

