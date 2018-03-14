
#include "Analyse/Abasic.h"







bool Apply_Cut(CDraw &para, float weight, int cut_level, float &pass_num){
	if(para.var.var[cut_level].cut_switch){
		if(!GetCut(para.var.var[cut_level].variable, para.var.var[cut_level].cut_min_pre,  para.var.var[cut_level].cut_max_pre,  pass_num, weight)){
                    return(false);
                }
	}
	return(true);
}


bool Apply_Cut(CDraw &para, std::vector<TH1F*> &hvariable, std::vector<TH1F*> &hvariable_tot,float weight, int level,float &pass_num){
	if(para.var.var[level].plot_switch){
		hvariable[level]->Fill(para.var.var[level].variable,weight);
	}
	if(para.var.var[level].cut_switch){
		if(!GetCut(para.var.var[level].variable, para.var.var[level].cut_min,  para.var.var[level].cut_max,  pass_num, weight)){return(false);}
	}
	if(para.var.var[level].plot_switch){
		hvariable_tot[level]->Fill(para.var.var[level].variable,weight);
	}
	return(true);
}




void Fill_Tree(CDraw &para, float event_rate, TTree* data0, TTree* data1, TTree* data2){
	if(para.flow.BDT_training ){
		if(event_rate<1/para.flow.BDT_weight){
			data0->Fill();
			data2->Fill();
		}
		else{
			data1->Fill();
		}
	}
	else{
		data1->Fill();
	}
}


void Fill_Tree(CDraw &para, float event_rate, TTree* data0, TTree* data1){
	if(para.flow.BDT_training ){
		if(event_rate<1/para.flow.BDT_weight){
			data0->Fill();
		}
		else{
			data1->Fill();
		}
	}
	else{
		data1->Fill();
	}
}


void Fill_Tree(CDraw &para, float event_rate, TTree* data0){
	if(event_rate<1/para.flow.BDT_weight)
	{
		data0->Fill();
	}
}
