
#include "AnalyseClass/Variable.h"

void Avariable::Copy(Avariable var){
	if(this->cut_min==minimum){
		this->cut_min= var.cut_min;
	}
	if(this->cut_max==maximum){
		this->cut_max= var.cut_max;
	}
	if(this->cut_min_pre==minimum){
		this->cut_min_pre= this->cut_min;
	}
	if(this->cut_max_pre==maximum){
		this->cut_max_pre= this->cut_max;
	}
	if(this->c_name==""){
		this->c_name= var.c_name;
	}
	if(this->c_width==1000.0){
		this->c_width= var.c_width;
	}
	if(this->c_height==700.0){
		this->c_height= var.c_height;
	}
	if(this->leg_left==0.6){
		this->leg_left= var.leg_left;
	}
	if(this->leg_up==0.6){
		this->leg_up= var.leg_up;
	}
	if(this->leg_right==0.9){
		this->leg_right= var.leg_right;
	}
	if(this->leg_down==0.9){
		this->leg_down= var.leg_down;
	}
	if(this->leg_header==""){
		this->leg_header= var.leg_header;
	}
	if(this->title_name==""){
		this->title_name= var.title_name;
	}
	if(this->latex_name==""){
		this->latex_name= var.latex_name;
	}
	if(this->x_name==""){
		this->x_name= var.x_name;
	}
	if(this->x_bin==1){
		this->x_bin= var.x_bin;
	}
	if(this->x_min==0.0){
		this->x_min= var.x_min;
	}
	if(this->x_max==1.0){
		this->x_max= var.x_max;
	}
	if(this->y_name==""){
		this->y_name= var.y_name;
	}
	if(this->y_bin==1){
		this->y_bin= var.y_bin;
	}
	if(this->y_min==0.0){
		this->y_min= var.y_min;
	}
	if(this->y_max==1.0){
		this->y_max= var.y_max;
	}
	if(this->cut_switch==false){
		this->cut_switch= var.cut_switch;
	}
	if(this->plot_switch==false){
		this->plot_switch= var.plot_switch;
	}
	if(this->log_switch==false){
		this->log_switch= var.log_switch;
	}
	if(this->log_min==0.1){
		this->log_min= var.log_min;
	}
	if(this->norm_switch==false){
		this->norm_switch= var.norm_switch;
	}
	if(this->MVA_switch==false){
		this->MVA_switch= var.MVA_switch;
	}
	if(this->show_title==false){
		this->show_title= var.show_title;
	}
	if(this->use_default_line_setting==-1){
		this->use_default_line_setting= var.use_default_line_setting;
		this->line_setting= var.line_setting;
	}
}

