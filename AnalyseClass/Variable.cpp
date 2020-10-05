
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
	if(this->c_name=="canvas"){
		this->c_name= var.c_name;
	}
	if(this->c_width==1.0){
		this->c_width= var.c_width;
	}
	if(this->c_height==1.0){
		this->c_height= var.c_height;
	}
	if(this->leg_left==0.0){
		this->leg_left= var.leg_left;
	}
	if(this->leg_up==0.0){
		this->leg_up= var.leg_up;
	}
	if(this->leg_right==0.0){
		this->leg_right= var.leg_right;
	}
	if(this->leg_down==0.0){
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
	if(this->x_bin==0){
		this->x_bin= var.x_bin;
	}
	if(this->x_min==0.0){
		this->x_min= var.x_min;
	}
	if(this->x_max==0.0){
		this->x_max= var.x_max;
	}
	if(this->y_name==""){
		this->y_name= var.y_name;
	}
	if(this->y_bin==0){
		this->y_bin= var.y_bin;
	}
	if(this->y_min==0.0){
		this->y_min= var.y_min;
	}
	if(this->y_max==0.0){
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
	if(this->show_title==false){
		this->show_title= var.show_title;
	}
	if(this->with_color_or_line==-1){
		this->with_color_or_line= var.with_color_or_line;
	}
	if(this->line_width==-1){
		this->line_width= var.line_width;
	}
}

void Avariable::Print(int i,bool has_title){
	if(has_title){
		ShowMessage(i,"The Variable is","");
	}

	ShowMessage(i+1,"content name","content value");

	ShowMessage(i+1, "minimum      "      , this->minimum);
	ShowMessage(i+1, "maximum      "      , this->maximum);
	ShowMessage(i+1, "minimum_d    "      , this->minimum_d);
	ShowMessage(i+1, "maximum_d    "      , this->maximum_d);
	ShowMessage(i+1, "minimum_i    "      , this->minimum_i);
	ShowMessage(i+1, "maximum_i    "      , this->maximum_i);
	ShowMessage(i+1, "variable_type"      , this->variable_type);
	ShowMessage(i+1, "setting_type "      , this->setting_type);
	ShowMessage(i+1, "variable     "      , this->variable);
	ShowMessage(i+1, "cut_min      "      , this->cut_min);
	ShowMessage(i+1, "cut_max      "      , this->cut_max);
	ShowMessage(i+1, "cut_min_pre  "      , this->cut_min_pre);
	ShowMessage(i+1, "cut_max_pre  "      , this->cut_max_pre);
	ShowMessage(i+1, "variable_d   "      , this->variable_d);
	ShowMessage(i+1, "cut_min_d    "      , this->cut_min_d);
	ShowMessage(i+1, "cut_max_d    "      , this->cut_max_d);
	ShowMessage(i+1, "cut_min_pre_d"      , this->cut_min_pre_d);
	ShowMessage(i+1, "cut_max_pre_d"      , this->cut_max_pre_d);
	ShowMessage(i+1, "variable_i   "      , this->variable_i);
	ShowMessage(i+1, "cut_min_i    "      , this->cut_min_i);
	ShowMessage(i+1, "cut_max_i    "      , this->cut_max_i);
	ShowMessage(i+1, "cut_min_pre_i"      , this->cut_min_pre_i);
	ShowMessage(i+1, "cut_max_pre_i"      , this->cut_max_pre_i);
	ShowMessage(i+1, "c_name       "      , this->c_name);
	ShowMessage(i+1, "c_width      "      , this->c_width);
	ShowMessage(i+1, "c_height     "      , this->c_height);
	ShowMessage(i+1, "leg_left     "      , this->leg_left);
	ShowMessage(i+1, "leg_up       "      , this->leg_up);
	ShowMessage(i+1, "leg_right    "      , this->leg_right);
	ShowMessage(i+1, "leg_down     "      , this->leg_down);
	ShowMessage(i+1, "leg_header   "      , this->leg_header);
	ShowMessage(i+1, "title_name   "      , this->title_name);
	ShowMessage(i+1, "latex_name   "      , this->latex_name);
	ShowMessage(i+1, "x_name       "      , this->x_name);
	ShowMessage(i+1, "x_bin        "      , this->x_bin);
	ShowMessage(i+1, "x_min        "      , this->x_min);
	ShowMessage(i+1, "x_max        "      , this->x_max);
	ShowMessage(i+1, "y_name       "      , this->y_name);
	ShowMessage(i+1, "y_bin        "      , this->y_bin);
	ShowMessage(i+1, "y_min        "      , this->y_min);
	ShowMessage(i+1, "y_max        "      , this->y_max);
	ShowMessage(i+1, "cut_switch   "      , this->cut_switch);
	ShowMessage(i+1, "plot_switch  "      , this->plot_switch);
	ShowMessage(i+1, "log_switch   "      , this->log_switch);
	ShowMessage(i+1, "log_min      "      , this->log_min);
	ShowMessage(i+1, "norm_switch  "      , this->norm_switch);
	ShowMessage(i+1, "MVA_switch   "      , this->MVA_switch);
	ShowMessage(i+1, "show_title   "      , this->show_title);
	ShowMessage(i+1, "with_color_or_line" , this->with_color_or_line); 
	ShowMessage(i+1, "line_width   "      , this->line_width); 
}




