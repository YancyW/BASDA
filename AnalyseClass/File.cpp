
#include "AnalyseClass/File.h"

std::ostream & operator<<(std::ostream & ostr, AFile &file_name){

	ShowMessage(2);
	ShowMessage(2,"The data_folder:"             ,file_name.Data_Folder());
	ShowMessage(2,"The plot_folder_name:"        ,file_name.Plot_Single_Folder());
	ShowMessage(2,"The plot_sort_folder_name:"   ,file_name.Plot_Sort_Folder());
	ShowMessage(2,"The event_Unpol_folder:"      ,file_name.Event_Unpol_Folder());
	ShowMessage(2,"The event_MVA_folder:"        ,file_name.Event_MVA_Folder());
	ShowMessage(2,"The event_CUT_folder:"        ,file_name.Event_CUT_Folder());
	ShowMessage(2,"The plot summary horizontaly" ,file_name.Plot_Summary_Folder());
	ShowMessage(2,"The event limitation"         ,file_name.Event_Limit_Folder());
	ShowMessage(2,"The single origin plot"       ,file_name.Plot_Direct_Folder());
	ShowMessage(2);

	ShowMessage(2,"The significance file:"       ,file_name.Significance  ());
	ShowMessage(2,"The output_table file:"       ,file_name.Output_Table  ());
	ShowMessage(2,"The reweight_table file:"     ,file_name.Reweight_Table());
	ShowMessage(2,"The sensitivity file :"       ,file_name.Sensitivity   ());
	ShowMessage(2,"The output_MVA file  :"       ,file_name.Output_MVA    ());
	ShowMessage(2,"The dataset_MVA file :"       ,file_name.Dataset_MVA   ());
	ShowMessage(2);

	for(int i=0;i<file_name.Input_Num();i++){
		ShowMessage(2,"The input            name :",file_name.input [i].name             );
		ShowMessage(2,"The input      latex name :",file_name.input [i].latex            );

		for(int j=0;j<file_name.input[i].Num();j++){
			ShowMessage(2,"The input  ana_basic_file:",file_name.input[i].basic_file[j] );
			ShowMessage(2,"The input  ana_xsection  :",file_name.input[i].xection   [j] );
		}
		ShowMessage(2);

	}

	ShowMessage(2);

	for(int i=0;i<file_name.Output_Num();i++){
		ShowMessage(2,"The output           name :",file_name.output[i].name             );
		ShowMessage(2,"The output     latex name :",file_name.output[i].latex            );
		ShowMessage(2,"The output Unpol_file name:",file_name.output[i].Unpol_file       );
		ShowMessage(2,"The output MVA_file   name:",file_name.output[i].MVA_file         );
		ShowMessage(2,"The output CUT_file   name:",file_name.output[i].CUT_file         );
		ShowMessage(2,"The output ana_Unpol  name:",file_name.output[i].ana_Unpol        );
		ShowMessage(2,"The output ana_data   name:",file_name.output[i].ana_data         );
		ShowMessage(2);
	}

	ShowMessage(2,"The output_total           name :",file_name.output_total.name        );
	ShowMessage(2,"The output_total     latex name :",file_name.output_total.latex       );
	ShowMessage(2,"The output_total Unpol_file name:",file_name.output_total.Unpol_file  );
	ShowMessage(2,"The output_total MVA_file   name:",file_name.output_total.MVA_file    );
	ShowMessage(2,"The output_total CUT_file   name:",file_name.output_total.CUT_file    );
	ShowMessage(2,"The output_total ana_Unpol  name:",file_name.output_total.ana_Unpol   );
	ShowMessage(2,"The output_total ana_data   name:",file_name.output_total.ana_data    );
	ShowMessage(2);
	return ostr;
}


std::string change_name(std::string arg_string){
	std::string out_name=arg_string;
	int fs1=out_name.find("{");
	out_name.replace(fs1,1,"");
	fs1=out_name.find("{",fs1+1);
	out_name.replace(fs1,1,"");
	fs1=out_name.find("}");
	out_name.replace(fs1,1,"");
	fs1=out_name.find("}",fs1+1);
	out_name.replace(fs1,1,"");
	fs1=out_name.find("^");
	out_name.replace(fs1,1,"_");
	return(out_name);
}


void get_file_name(CDraw &para, AFile &file_name){
	file_name.Clear();
	freopen(para.path.record_file.c_str() ,"a",stdout);
	ShowMessage(2,"get file name");

	std::string yaml_file_name=para.file.file[0];

	ShowMessage(2,"The basic input filelist is",yaml_file_name);
	Is_File_Exist_And_Exit(yaml_file_name);
	std::vector<std::pair<std::string,AFile_Data> >  fileList;

	YAML::Node file_node = YAML::LoadFile(yaml_file_name);
	std::string yaml_node_name="root_file_"+para.flow.signal_property;
	YAML::Node nodes = file_node[yaml_node_name];
	ShowMessage(2,"the input files are");
	for(YAML::const_iterator it=nodes.begin(); it != nodes.end(); ++it){
		if(para.file.file_descrip[0]=="all"){
			if(it->second.as<AFile_Data>().data[0].first!="no such class"){
				ShowMessage(3,"read channel",it->first.as<std::string>());
				fileList.push_back(std::make_pair(it->first.as<std::string>(),it->second.as<AFile_Data>()));
			}
		}
		else{
			for(unsigned int i=0;i<para.file.file_descrip.size();i++){
				std::string selected_channel=para.file.file_descrip[i];
				if(selected_channel=="nh"){
					selected_channel="nh_{"+para.flow.signal_property+"}^{"+para.flow.signal_property+"}";
				}
				else if(selected_channel=="higgs"){
					selected_channel="higgs_{"+para.flow.signal_property+"}^{"+para.flow.signal_property+"}";
				}
				if(it->first.as<std::string>()==selected_channel){
					if(it->second.as<AFile_Data>().data[0].first!="no such class"){
						ShowMessage(3,"read channel",selected_channel);
						fileList.push_back(std::make_pair(it->first.as<std::string>(),it->second.as<AFile_Data>()));
					}
				}
			}

		}
	}

	ShowMessage(2);
	if(fileList.size()==0){
		ShowMessage(1,"no input file in get_file_name!");
		ShowMessage(1,"Exit program!");
		exit(EXIT_FAILURE);
	}


	AFile_Name in_tmp;
	for(unsigned int i=0;i<fileList.size();i++){
		for(unsigned int j=0;j<fileList[i].second.data.size();j++){
			in_tmp.basic_file.push_back(fileList[i].second.data[j].first);
			in_tmp.xection.push_back(fileList[i].second.data[j].second);
		}
		in_tmp.name=change_name(fileList[i].first);
		in_tmp.latex=fileList[i].first;

		in_tmp.MVA_file  ="";
		in_tmp.Unpol_file="";
		in_tmp.CUT_file  ="";
		in_tmp.ana_data  ="";

		file_name.input.push_back(in_tmp);
		in_tmp.Clear();
	}


	ShowMessage(2);

	std::string data_folder_name  = para.path.output_file+"/"+para.flow.signal_property+"/";
	Create_Folder(data_folder_name);

	std::string plot_folder_name=para.path.single_plot+"/"+para.flow.signal_property+"/";
	Create_Folder(plot_folder_name);

	std::string plot_combine_folder_name=para.path.combine_plot+"/"+para.flow.signal_property+"/";
	Create_Folder(plot_combine_folder_name);

	std::string event_Unpol_folder_name = para.path.event_file+"/"+para.flow.signal_property+"_Unpol/";
	Create_Folder(event_Unpol_folder_name);

	std::string event_MVA_folder_name = para.path.event_file+"/"+para.flow.signal_property+"_MVA/";
	Create_Folder(event_MVA_folder_name);

	std::string event_CUT_folder_name = para.path.event_file+"/"+para.flow.signal_property+"_CUT/";
	Create_Folder(event_CUT_folder_name);

	std::string plot_horizontal_summary_folder_name=para.path.horizontal_summary_plot+"/";
	Create_Folder(plot_horizontal_summary_folder_name);

	std::string event_LIMIT_folder_name = para.path.event_file+"/"+para.flow.signal_property+"_LIMIT/";
	Create_Folder(event_LIMIT_folder_name);

	std::string single_plot_folder_name = para.path.single_plot+"/"+para.flow.signal_property+"/single_plot/";
	Create_Folder(single_plot_folder_name);

	std::string plot_combine_bkg_folder_name= para.path.combine_plot+"_bkg/"+para.flow.signal_property+"/";
	Create_Folder(plot_combine_bkg_folder_name);

	file_name.folder.push_back(data_folder_name);
	file_name.folder.push_back(plot_folder_name);
	file_name.folder.push_back(plot_combine_folder_name);
	file_name.folder.push_back(event_Unpol_folder_name);
	file_name.folder.push_back(event_MVA_folder_name);
	file_name.folder.push_back(event_CUT_folder_name);
	file_name.folder.push_back(plot_horizontal_summary_folder_name);
	file_name.folder.push_back(event_LIMIT_folder_name);
	file_name.folder.push_back(single_plot_folder_name);
	file_name.folder.push_back(plot_combine_bkg_folder_name);

	ShowMessage(2);

	file_name.significance  =data_folder_name     +"significance_" +para.flow.signal_property+".dat";
	file_name.output_table  =data_folder_name     +"output_table_" +para.flow.signal_property+".dat";
	file_name.reweight_table=data_folder_name     +"reweight_table"+para.flow.signal_property+".dat";
	file_name.sensitivity   =event_LIMIT_folder_name+"sensitivity_"  +para.flow.signal_property+".root";
	file_name.output_MVA    =event_MVA_folder_name+file_name.input[0].name+"_MVA.root";
	file_name.dataset_MVA   =event_MVA_folder_name+file_name.input[0].name+"_dataset";
	file_name.plot_CUT      =event_CUT_folder_name+"all_plots.root";
	//file_name.dataset_MVA =file_name.input[0].name+"_dataset";

	ShowMessage(2);

	AFile_Name out_tmp;
	for(int i=0;i<file_name.Input_Num();i++){
		out_tmp.name      = file_name.input[i].name ;
		out_tmp.latex     = file_name.input[i].latex;

		out_tmp.Unpol_file= event_Unpol_folder_name+out_tmp.name+"_"+para.flow.signal_property+".root";
		out_tmp.MVA_file  = event_MVA_folder_name  +out_tmp.name+"_"+para.flow.signal_property+".root";
		out_tmp.CUT_file  = event_CUT_folder_name  +out_tmp.name+"_"+para.flow.signal_property+".root";
		out_tmp.ana_Unpol = data_folder_name       +out_tmp.name+"_"+para.flow.signal_property+"_Unpol.dat";
		out_tmp.ana_data  = data_folder_name       +out_tmp.name+"_"+para.flow.signal_property+".dat";

		file_name.output.push_back( out_tmp );
		out_tmp.Clear();
	}

	file_name.output_total.name      = "total_bkg";
	file_name.output_total.latex     = "total_bkg                      ";

	file_name.output_total.Unpol_file= event_Unpol_folder_name+file_name.output_total.name+"_"+para.flow.signal_property+".root";
	file_name.output_total.MVA_file  = event_MVA_folder_name  +file_name.output_total.name+"_"+para.flow.signal_property+".root";
	file_name.output_total.CUT_file  = event_CUT_folder_name  +file_name.output_total.name+"_"+para.flow.signal_property+".root";
	file_name.output_total.ana_Unpol = data_folder_name       +file_name.output_total.name+"_"+para.flow.signal_property+"_Unpol.dat";
	file_name.output_total.ana_data  = data_folder_name       +file_name.output_total.name+"_"+para.flow.signal_property+".dat";

	ShowMessage(1,"The file_name is:",file_name);


	if(!para.flow.record_output){
		fclose(stdout);
		freopen("/dev/tty","w",stdout);
	}
}


void AFile::Clear(){
	input.clear();
	output.clear();
	output_total.Clear();
	folder.clear();
	significance  ="";
	output_table  ="";
	reweight_table="";
	sensitivity   ="";
	output_MVA    ="";
	dataset_MVA   ="";

}
