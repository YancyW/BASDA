#include "Analyse_Direct_Cut.h"

void Analyse_Direct_Cut_Pre(CDraw &para){
	AFile file_name;
	file_name.get_file_name(para);

	std::ofstream sig_file;
	sig_file.open(file_name.significance);

	Analyse_Direct_Cut(para,file_name);

	std::vector<std::string> ana_out_name;
	for(int i=0;i<file_name.Output_Num();i++){
		ana_out_name.push_back(file_name.output[i].ana_data);
	}
////float sig=Make_Table(para,para.scenario.Lumi(),ana_out_name,file_name.output_table,true);

////RecordMessage(sig_file,2,"significance is", sig);

	sig_file.close();
}

//void Analyse_Direct_Cut_Operation_Type(CDraw& para){

//}


void Analyse_Direct_Cut(CDraw &para, AFile &file_name){

	ShowMessage(2,"analyse events");

	int filenum=file_name.Output_Num();



	Analyse_Multi_File        analyse(para,file_name,"CUT");
    std::vector<ARoot_File>   in_file                ;


    //		Assistant_Direct_Cut(para.flow.begin_object,in_file,file_name);
//  if( para.flow.begin_object  == "Direct_Cut" ||
//  		(para.flow.begin_object == "Direct_Cut_NoMVA" && file_name.input[0].basic_file.size()>1) ||
//  		para.flow.begin_object  == "Complete_Direct_Cut"||
//  		para.flow.begin_object  == "Complete_Run"){

//  	//			analyse.in_file.push_back(ARoot_File(file_name.output[j].MVA_file,para.file.root_head_name));
//  	for(int j=0;j<filenum;j++){
//  		analyse.Init_Input_File(file_name.output[j].MVA_file     ,para.file.root_head_name);
//  	}

//  }
//  else if(para.flow.begin_object == "Direct_Cut_NoMVA" && file_name.input[0].basic_file.size()==1){
//  	//			analyse.in_file.push_back(ARoot_File(file_name.input[j].basic_file[0],para.file.root_head_name));
//  	for(int j=0;j<filenum;j++){
//  		analyse.Init_Input_File( file_name.input[j].basic_file[0],para.file.root_head_name);
//  	}
//  }
    analyse.Init_All_Input_File();



    std::ofstream myfile_tot;
    if(filenum>1){
    	myfile_tot.open(file_name.output_total.ana_data);
    	analyse.Init_Total_Data_File(myfile_tot);
    }


    //loop for all input files
    for(int cnum=0;cnum<filenum;cnum++){
    	std::ofstream myfile;
    	myfile.open(file_name.output[cnum].ana_data);

    	ShowMessage(2,"dealing with", file_name.output[cnum].name);

    	//loop for reading variables and setting cuts 

    	analyse.Init_Root(para,cnum);
    	analyse.Init_Data_File(myfile,cnum);

    	for(long int event = analyse.in_file[cnum].Begin_Event(); event < analyse.in_file[cnum].End_Event(); ++event){

			ShowMessage(2,"begin with", event);

    		CountNumber(event,analyse.in_file[cnum].Total_Event(),1000,"has dealed with number are");

    	    //analyse.Init_Pol(cnum, event) ;
    		analyse.Get_Event(cnum, event);

    		analyse.Root_Get_Entry(cnum, event);

    		if(analyse.var.weight.variable_type=="I"){
    			analyse.var.weight.variable= static_cast<float> (analyse.var.weight.variable_i);
    		}
			else if(analyse.var.weight.variable_type=="D"){
    			analyse.var.weight.variable= static_cast<float> (analyse.var.weight.variable_d);
    		}

    		for(int k=0;k<analyse.Var_Num();k++){
    			if(analyse.var.var[k].variable_type=="I"){
    				analyse.var.var[k].variable = static_cast<float> (analyse.var.var[k].variable_i);
    			}
    			if(analyse.var.var[k].variable_type=="D"){
    				analyse.var.var[k].variable = static_cast<float> (analyse.var.var[k].variable_d);
    			}
    		}
    		analyse.Init_Root_Var    ( cnum );

    		analyse.Root_Endow_Weight( cnum ) ;

    		analyse.Plot_Origin      ( cnum ) ;

    		analyse.Add_Pass_NoCut   ( cnum ) ;

    		if( !analyse.Get_Cut     ( cnum ) ) {continue;}

    		//analyse.Root_Endow_Var   ( cnum   ) ;

    		analyse.Add_Pass_AllCut  ( cnum ) ;

    		analyse.Plot_Final       ( cnum ) ;

    		analyse.Root_Fill        ( cnum ) ;
    	}                

    	analyse.Record_Information(cnum,file_name.output[cnum].latex);

    	analyse.Add_Tot_Pass(cnum);

    	analyse.Data_File_Close(cnum);

    	analyse.Root_Close(cnum);

//    	analyse.Input_File_Delete(cnum);
    }


    if(filenum>1){
    	analyse.Record_Tot_Information(file_name.output_total.latex);
    	analyse.Total_Data_File_Close();
    }

    analyse.Draw_Figure(para);

    analyse.Root_Close_Last(para);

    ShowMessage(2,"Finish Direct Cut");
    return;
  
    ShowMessage(2,"end of Analysis function");
}

