#include "Make_Efficiency_Plot.h"
#include "AnalyseClass/File.h"

void  Extract_Sort_Data(CDraw &para, AFile_List &fileList, ASort_List& data){
	for(int j=0;j<fileList.Data_Num();j++){
		for(int i=0;i<fileList.File_Num();i++){

			float data_ij=0;
			if(j==0){// row --- no cut 
				data_ij = 0;
			}
			else{// row --- no cut 
				data_ij = fileList.Data_Content(j,i);
			}

			std::vector<std::pair<std::string, int> > pos;
			pos = para.bkg_sort.Find_Class(fileList.File_Name(i));
			data.Input_Element(pos,fileList.Data_Name(j,i),data_ij);
		}
	}
	data.Set_Sort("no cut MC event");
}


void Draw_Efficiency_Plot(CDraw &para, ASort_List& data,std::string out_file_name){

	(void) para;
	TH2F*  fvariable;
	TCanvas *c1=new TCanvas("c1","c1",1000,700);
	TPad *center_pad = new TPad("center_pad", "center_pad",0.05,0.05,0.90,0.90);
	center_pad->Draw();


	float xaxis[3];
	xaxis[0]=data.Total_Unzero_Sort_Num();
	xaxis[1]=0;
	xaxis[2]=xaxis[0];

	float yaxis[3];
	yaxis[0]=120;
	yaxis[1]=0;
	yaxis[2]=0.6;
	fvariable = new TH2F("effi_plot","effi_plot",xaxis[0],xaxis[1],xaxis[2],yaxis[0],yaxis[1],yaxis[2]);

	for(int j=1;j<data.Data_Num()-1;j++){
		for(int k=0;k<data.Sort_Num();k++){
			if(data._list[k].first=="Significance"||data._list[k].first=="Efficiency"||data._list[k].first=="Improvement"||data._list[k].first=="Total Background"){
				continue;
			}
			for(int l=0;l<data.Sub_Sort_Num(k);l++){
				int pos=data.Data_Pos(k,l);
				if(data.Data_Content(pos+1,k,l)!=0){
					float effi=data.Data_Content(pos+j,k,l)/data.Data_Content(pos+1,k,l);
					if(j==1||(j>1&&data.Data_Content(pos+j,k,l)!=data.Data_Content(pos+j-1,k,l))){
						fvariable->Fill(data.Full_Sort_Name(k,l).c_str(), effi,   data.Data_Content(pos+j,k,l));
					}
				}
			}
		}
	}

	center_pad->cd();
	gStyle->SetPalette(1);
	gStyle->SetTitleAlign(33);
	gStyle->SetTitleY(1.00);
	fvariable->GetYaxis()->SetTitle("efficiency");
	fvariable->GetXaxis()->SetTitle("sort name");
	int pos=data.Data_Pos(0,0);
	fvariable->SetMaximum(data.Data_Content(pos+1,0,0));
	fvariable->Draw("COLZ");

	c1->Update();
	TImage *img_2d = TImage::Create();
	img_2d->FromPad(c1);
	std::string pngname_2d=out_file_name;
	std::cout<<pngname_2d << std::endl;
	img_2d->WriteImage(pngname_2d.c_str());
	delete fvariable;
	delete c1;

}



void Make_Efficiency_Plot(CDraw &para, std::vector<std::string> yaml_file,std::string out_file_name){


	ShowMessage(2,"make efficiency plot");
	ShowMessage(2,"use following input data for plots:");

	AFile_List  fileList;

	for(unsigned int i=0;i<yaml_file.size();i++){
		ShowMessage(2,"file for make efficiency plots",yaml_file[i]);
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
	Extract_Sort_Data(para,fileList,data);
	Draw_Efficiency_Plot(para,data,out_file_name);
}


void Make_Efficiency_Plot_Pre(CDraw &para){
	AFile file_name;
	get_file_name(para,file_name);

	std::vector<std::string> ana_out_name;
	for(int i=0;i<file_name.Output_Num();i++){
		ana_out_name.push_back(file_name.output[i].ana_data);
	}
	Make_Efficiency_Plot(para,ana_out_name,file_name.efficiency_plot);

}

