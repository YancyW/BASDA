#pragma once
#ifndef ANALYSE_VARIABLE_H
#define ANALYSE_VARIABLE_H
#include "TStyle.h"
#include <string> 
#include <vector>
#include "yaml-cpp/yaml.h"

#include "Function/Fbasic.h"
#include "RWpara/RWbasic.h"
#include "Class/Path.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TSystem.h"



class Avariable{
	private:
	public:

		float         variable   ;
		float         cut_min    ;
		float         cut_max    ;
		float         cut_min_pre;
		float         cut_max_pre;

		TCanvas*      c          ;
		std::string   c_name     ;
		float         c_width    ;
		float         c_height   ;
		TLegend*      leg        ;
		float         leg_left   ;
		float         leg_up     ;
		float         leg_right  ;
		float         leg_down   ;
		std::string   leg_header ;
		std::string   title_name ;
		std::string   latex_name ;
		std::string   x_name     ;
		int           x_bin      ;
		float         x_min      ;
		float         x_max      ;
		std::string   y_name     ;
		int           y_bin      ;
		float         y_min      ;
		float         y_max      ;
		bool          cut_switch ;
		bool          plot_switch;
		bool          log_switch ;
		float         log_min    ;
		bool          norm_switch;
		bool          BDT_switch ;
		bool          show_title ;
		int           with_color_or_line; 
		int           line_width ; 

		Avariable(){
			variable    =-100.1 ;
			cut_min     =-100000.1 ;
			cut_max     = 100000.1 ;
			cut_min_pre =-100000.1 ;
			cut_max_pre = 100000.1 ;

		    c_name      = ""    ;
		    c_width     = 1.0   ;
		    c_height    = 1.0   ;
		    leg_left    = 1.0   ;
		    leg_up      = 1.0   ;
		    leg_right   = 1.0   ;
		    leg_down    = 1.0   ;
		    leg_header  = ""    ;
		    title_name  = ""    ;
		    latex_name  = ""    ;
		    x_name      = ""    ;
		    x_bin       = 1     ;
		    x_min       = 0.0001;
		    x_max       = 1.0001;
		    y_name      = ""    ;
		    y_bin       = 1     ;
		    y_min       = 0.0001;
		    y_max       = 1.0001;
		    cut_switch  = false ;
		    plot_switch = false ;
		    log_switch  = false ;
			log_min     = 0.1   ;
		    norm_switch = false ;
		    BDT_switch  = false ;
			show_title  = false ;
			with_color_or_line = -1;
			line_width  = -1;
		}

		void Copy(Avariable);

		void Init(){
			//c=new TCanvas(c_name.c_str()," ",c_width,c_height);
			leg=new TLegend(leg_left,leg_up,leg_right,leg_down);
			leg->SetHeader(leg_header.c_str(),"C");
		}
};

class Avariable_vec{
	private:
	public:

		std::vector<float>         variable   ;
		std::vector<float>        *var_ptr    ;

		std::string   title_name ;

		Avariable_vec(){
		    title_name  = ""    ;
			var_ptr = new std::vector<float>(); 
		}
};



class AVariable{
	public:
		int num;
		int num_vec;
		int numBDT;
		int cut_level;
		std::vector<Avariable> var;
		std::vector<Avariable_vec> vec;
		std::vector<Avariable> BDT;
		void Read_Var(CPath &path);

		AVariable(){
			num=0;
			num_vec=0;
			numBDT=0;
			var.clear();
			BDT.clear();
		}
};


namespace YAML{
	template<>
		struct convert<Avariable>{
			static bool decode(const Node& node, Avariable& var){ 
				for(YAML::const_iterator it=node.begin(); it != node.end(); ++it){
					if(it->first.as<std::string>()=="Canvas_name"){
						RW_element(it->first.as<std::string>(), it, var.c_name);
					}
					else if(it->first.as<std::string>()=="Canvas_width"){
						RW_element(it->first.as<std::string>(), it, var.c_width);
					}
					else if(it->first.as<std::string>()=="Canvas_height"){
						RW_element(it->first.as<std::string>(), it, var.c_height);
					}
					else if(it->first.as<std::string>()=="leg_left"){
						RW_element(it->first.as<std::string>(), it, var.leg_left);
					}
					else if(it->first.as<std::string>()=="leg_up"){
						RW_element(it->first.as<std::string>(), it, var.leg_up);
					}
					else if(it->first.as<std::string>()=="leg_right"){
						RW_element(it->first.as<std::string>(), it, var.leg_right);
					}
					else if(it->first.as<std::string>()=="leg_down"){
						RW_element(it->first.as<std::string>(), it, var.leg_down);
					}
					else if(it->first.as<std::string>()=="leg_header"){
						RW_element(it->first.as<std::string>(), it, var.leg_header);
					}
					else if(it->first.as<std::string>()=="title_name"){
						RW_element(it->first.as<std::string>(), it, var.title_name);
					}
					else if(it->first.as<std::string>()=="latex_name"){
						RW_element(it->first.as<std::string>(), it, var.latex_name);
					}
					else if(it->first.as<std::string>()=="xaxis_name"){
						RW_element(it->first.as<std::string>(), it, var.x_name);
					}
					else if(it->first.as<std::string>()=="xaxis_bin"){
						RW_element(it->first.as<std::string>(), it, var.x_bin);
					}
					else if(it->first.as<std::string>()=="xaxis_min"){
						RW_element(it->first.as<std::string>(), it, var.x_min);
					}
					else if(it->first.as<std::string>()=="xaxis_max"){
						RW_element(it->first.as<std::string>(), it, var.x_max);
					}
					else if(it->first.as<std::string>()=="yaxis_name"){
						RW_element(it->first.as<std::string>(), it, var.y_name);
					}
					else if(it->first.as<std::string>()=="yaxis_bin"){
						RW_element(it->first.as<std::string>(), it, var.y_bin);
					}
					else if(it->first.as<std::string>()=="yaxis_min"){
						RW_element(it->first.as<std::string>(), it, var.y_min);
					}
					else if(it->first.as<std::string>()=="yaxis_max"){
						RW_element(it->first.as<std::string>(), it, var.y_max);
					}
					else if(it->first.as<std::string>()=="cut_min"){
						RW_element(it->first.as<std::string>(), it, var.cut_min);
						if(var.cut_min_pre<-100000.09&&var.cut_min_pre>-100000.11){
							var.cut_min_pre = var.cut_min;
						}
					}
					else if(it->first.as<std::string>()=="cut_max"){
						RW_element(it->first.as<std::string>(), it, var.cut_max);
						if(var.cut_max_pre>100000.09&&var.cut_max_pre<100000.11){
							var.cut_max_pre = var.cut_max;
						}
					}
					else if(it->first.as<std::string>()=="cut_min_pre"){
						RW_element(it->first.as<std::string>(), it, var.cut_min_pre);
					}
					else if(it->first.as<std::string>()=="cut_max_pre"){
						RW_element(it->first.as<std::string>(), it, var.cut_max_pre);
					}
					else if(it->first.as<std::string>()=="cut_switch"){
						RW_element(it->first.as<std::string>(), it, var.cut_switch);
					}
					else if(it->first.as<std::string>()=="plot_switch"){
						RW_element(it->first.as<std::string>(), it, var.plot_switch);
					}
					else if(it->first.as<std::string>()=="log_yaxis"){
						RW_element(it->first.as<std::string>(), it, var.log_switch);
					}
					else if(it->first.as<std::string>()=="log_min"){
						RW_element(it->first.as<std::string>(), it, var.log_min);
					}
					else if(it->first.as<std::string>()=="normalization_switch"){
						RW_element(it->first.as<std::string>(), it, var.norm_switch);
					}
					else if(it->first.as<std::string>()=="BDT"){
						RW_element(it->first.as<std::string>(), it, var.BDT_switch);
					}
					else if(it->first.as<std::string>()=="show_title"){
						RW_element(it->first.as<std::string>(), it, var.show_title);
					}
					else if(it->first.as<std::string>()=="with_color_or_line"){
						RW_element(it->first.as<std::string>(), it, var.with_color_or_line);
					}
					else if(it->first.as<std::string>()=="line_width"){
						RW_element(it->first.as<std::string>(), it, var.line_width);
					}
					else{
						ShowMessage(2,"wrong input when load class Variable",it->first.as<std::string>());
					}
				}
				var.Init();
				ShowMessage(2,"finish one var");
				return true;
			}
		};
};

namespace YAML{
	template<>
		struct convert<Avariable_vec>{
			static bool decode(const Node& node, Avariable_vec& vec){ 
				for(YAML::const_iterator it=node.begin(); it != node.end(); ++it){
					if(it->first.as<std::string>()=="title_name"){
						RW_element(it->first.as<std::string>(), it, vec.title_name);
					}
					else{
						ShowMessage(2,"wrong input when load class Variable");
					}
				}
				return true;
			}
		};
};
#endif
