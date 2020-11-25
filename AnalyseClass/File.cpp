
#include "AnalyseClass/File.h"

void AFile_Name::Init(){
	_output_lable = "";

}

void AFile_Name::Print(){
	ShowMessage(2, "The File_Name is ");
	ShowMessage(3,"The input            name :",name             );
	ShowMessage(3,"The input      latex name :",latex            );

	for(int j=0;j<Num();j++){
		ShowMessage(4,"The input  ana_basic_file:",basic_file[j] );
		ShowMessage(4,"The input  ana_xsection  :",xection   [j] );
	}

	ShowMessage(2,"The output Unpol_file name:",Unpol_file       );
	ShowMessage(2,"The output MVA_file   name:",MVA_file         );
	ShowMessage(2,"The output CUT_file   name:",CUT_file         );
	ShowMessage(2,"The output ana_Unpol  name:",ana_Unpol        );
	ShowMessage(2,"The output ana_data   name:",ana_data         );
	ShowMessage(2);
}

void AFile_Name::Set_OutputLable(std::string file_type){
	_output_lable = file_type;
}

std::string AFile_Name::Output_RootFile(){
	if(_output_lable==""){
		ShowMessage(2,"in AFile_Name::Output_RootFile, the output_lable didn't set");
		exit(0);
	}

	if(_output_lable=="unpol"){
		return(Unpol_file);
	}
	else if(_output_lable=="mva"){
		return(MVA_file);
	}
	else if(_output_lable=="cut"){
		return(CUT_file);
	}
	else{ 
		return("");
	}
}

std::string AFile_Name::Output_DataFile(){
	if(_output_lable==""){ShowMessage(2,"in AFile_Name::Output_DataFile, the output_lable didn't set");exit(0);}

	if(_output_lable=="unpol"){
		return(ana_Unpol);
	}
	else if(_output_lable=="cut"){
		return(ana_data);
	}
	else{ 
		return("");
	}

}
void AFile::Print(){
	ShowMessage(2, "The File is ");
	ShowMessage(3,"The data_folder:"             ,folder[0]);
	ShowMessage(3,"The plot_folder_name:"        ,folder[1]);
	ShowMessage(3,"The plot_combine_folder_name:",folder[2]);
	ShowMessage(3,"The event_Unpol_folder:"      ,folder[3]);
	ShowMessage(3,"The event_MVA_folder:"        ,folder[4]);
	ShowMessage(3,"The event_CUT_folder:"        ,folder[5]);
	ShowMessage(3,"The plot summary horizontaly" ,folder[6]);
	ShowMessage(3,"The plot summary horizontaly" ,folder[7]);
	ShowMessage(2);

	ShowMessage(3,"The significance file:"       ,significance  );
	ShowMessage(3,"The output_table file:"       ,output_table  );
	ShowMessage(3,"The reweight_table file:"     ,reweight_table);
	ShowMessage(3,"The sensitivity file :"       ,sensitivity   );
	ShowMessage(3,"The output_MVA file  :"       ,output_MVA    );
	ShowMessage(3,"The dataset_MVA file :"       ,dataset_MVA   );
	ShowMessage(2);

	for(int i=0;i<Input_Num();i++){
		input[i].Print();
	}

	ShowMessage(2);

	for(int i=0;i<Output_Num();i++){
		output[i].Print();
	}

	ShowMessage(2,"The output_total            name:",output_total.name        );
	ShowMessage(2,"The output_total latex      name:",output_total.latex       );
	ShowMessage(2,"The output_total Unpol_file name:",output_total.Unpol_file  );
	ShowMessage(2,"The output_total MVA_file   name:",output_total.MVA_file    );
	ShowMessage(2,"The output_total CUT_file   name:",output_total.CUT_file    );
	ShowMessage(2,"The output_total ana_Unpol  name:",output_total.ana_Unpol   );
	ShowMessage(2,"The output_total ana_data   name:",output_total.ana_data    );
	ShowMessage(2);
}


std::string AFile::change_name(std::string arg_string){
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


void AFile::get_file_name(CDraw &para){
	Clear();
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

		input.push_back(in_tmp);
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

	folder.push_back(data_folder_name);
	folder.push_back(plot_folder_name);
	folder.push_back(plot_combine_folder_name);
	folder.push_back(event_Unpol_folder_name);
	folder.push_back(event_MVA_folder_name);
	folder.push_back(event_CUT_folder_name);
	folder.push_back(plot_horizontal_summary_folder_name);
	folder.push_back(event_LIMIT_folder_name);

	ShowMessage(2);

	significance  =data_folder_name     +"significance_" +para.flow.signal_property+".dat";
	output_table  =data_folder_name     +"output_table_" +para.flow.signal_property+".dat";
	reweight_table=data_folder_name     +"reweight_table"+para.flow.signal_property+".dat";
	sensitivity   =event_LIMIT_folder_name+"sensitivity_"  +para.flow.signal_property+".root";
	output_MVA    =event_MVA_folder_name+input[0].name+"_MVA.root";
	dataset_MVA   =event_MVA_folder_name+input[0].name+"_dataset";
	plot_CUT      =event_CUT_folder_name+"all_plots.root";
	//dataset_MVA =input[0].name+"_dataset";

	ShowMessage(2);

	AFile_Name out_tmp;
	for(int i=0;i<Input_Num();i++){
		out_tmp.name      = input[i].name ;
		out_tmp.latex     = input[i].latex;

		out_tmp.Unpol_file= event_Unpol_folder_name+out_tmp.name+"_"+para.flow.signal_property+".root";
		out_tmp.MVA_file  = event_MVA_folder_name  +out_tmp.name+"_"+para.flow.signal_property+".root";
		out_tmp.CUT_file  = event_CUT_folder_name  +out_tmp.name+"_"+para.flow.signal_property+".root";
		out_tmp.ana_Unpol = data_folder_name       +out_tmp.name+"_"+para.flow.signal_property+"_Unpol.dat";
		out_tmp.ana_data  = data_folder_name       +out_tmp.name+"_"+para.flow.signal_property+".dat";

		output.push_back( out_tmp );
		out_tmp.Clear();
	}

	output_total.name      = "total_bkg";
	output_total.latex     = "total_bkg                      ";

	output_total.Unpol_file= event_Unpol_folder_name+output_total.name+"_"+para.flow.signal_property+".root";
	output_total.MVA_file  = event_MVA_folder_name  +output_total.name+"_"+para.flow.signal_property+".root";
	output_total.CUT_file  = event_CUT_folder_name  +output_total.name+"_"+para.flow.signal_property+".root";
	output_total.ana_Unpol = data_folder_name       +output_total.name+"_"+para.flow.signal_property+"_Unpol.dat";
	output_total.ana_data  = data_folder_name       +output_total.name+"_"+para.flow.signal_property+".dat";


	Print();

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


std::ostream & operator<<(std::ostream & ostr, AFile_Name &file_name){
	file_name.Print();
	return ostr;
}

std::ostream & operator<<(std::ostream & ostr, AFile &file_name){
	file_name.Print();
	return ostr;
}
