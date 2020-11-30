#include "Fram.h"
void Fram(CDraw &para)
{
	//read in the cross section
	ShowMessage(1,"begin to choose analysis mode"); 
	para.time.Begin_Time();

	// key treatments
	if (para.flow.begin_object == "Find_Cut" ){
		Analyse_Find_Cut(para);
	}
	else if (para.flow.begin_object == "Pre_Cut" ){
		Analyse_Pre_Cut(para);
	}
	else if (para.flow.begin_object == "Direct_Cut"){
		Analyse_Direct_Cut_Pre(para);
	}
	else if (para.flow.begin_object == "Direct_Cut_NoMVA" ){
		Analyse_Cut_NoMVA_Pre(para);
	}
	else if (para.flow.begin_object == "MVA_Train" ){
		Analyse_MVA_Train_Pre(para);
	}
	else if (para.flow.begin_object == "MVA_Attach" ){
		Analyse_MVA_Attach_Pre(para);
	}
	else if (para.flow.begin_object == "Sensitivity" ){
		Analyse_Sensitivity_Pre(para);
	}
	// one-click treatments
	else if (para.flow.begin_object == "Complete_Run" ){
		Analyse_Complete(para);
	}
	else if (para.flow.begin_object == "Full_Pol" ){
		Analyse_Complete_Pol(para);
	}
	else if (para.flow.begin_object == "Complete_Direct_Cut" ){
		Analyse_Complete_Direct_Cut(para);
	}
	else if (para.flow.begin_object == "Complete_Sensitivity" ){
		Analyse_Sensitivity_Complete(para);
	}
	else if (para.flow.begin_object == "Complete_Summarize_Plot" ){
		Analyse_Summarize_Plot_Complete_Pre(para);
	}
	// after treatments
	else if (para.flow.begin_object == "Signal_Scan" ){
		Analyse_Signal_Scan_Pre(para);
	}
	else if (para.flow.begin_object == "Summarize_Plot" ){
		Analyse_Summarize_Plot_Pre(para);
	}
	else if (para.flow.begin_object == "Make_Table" ){
		Make_Table_Pre(para);
	}
	else if (para.flow.begin_object == "Make_Complete_Table" ){
		Make_Complete_Table_Pre(para);
	}
	else if (para.flow.begin_object == "Plot_Direct" ){
		Analyse_Plot_Direct_Pre(para);
	}
	else if(para.flow.begin_object == "Test"){
		Test_Function();
	}
	else{
		ShowMessage(1,"wrong begin_object in control/flow.dat");
		return;
	}

	Record_Attach(para);

	ShowMessage(2);
	para.time.Current_Time();
	ShowMessage(2,"For this calculation ", para.flow.begin_object);
	para.time.Time_Interval();

	Record_Close(para);

}




