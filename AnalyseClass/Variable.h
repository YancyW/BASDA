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
#include "Class/Plot.h"



class Avariable{
	private:
		float         minimum;
		float         maximum;
		double        minimum_d;
		double        maximum_d;
		long int      minimum_i;
		long int      maximum_i;
	public:

		std::string   variable_type;
		std::string   setting_type;

		float         variable     ;
		float         cut_min      ;
		float         cut_max      ;
		float         cut_min_pre  ;
		float         cut_max_pre  ;

		double        variable_d   ;
		double        cut_min_d    ;
		double        cut_max_d    ;
		double        cut_min_pre_d;
		double        cut_max_pre_d;

	    long int           variable_i   ;
	    long int           cut_min_i    ;
	    long int           cut_max_i    ;
	    long int           cut_min_pre_i;
	    long int           cut_max_pre_i;

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
		bool          MVA_switch ;
		bool          show_title ;
		bool          use_default_line_setting;
		Cplot_basic_color_style line_setting;

		std::vector<int> label_2d;

		Avariable(){
			minimum      =-100000.1;
			maximum      = 100000.1;
			minimum_d    =-100000.1;
			maximum_d    = 100000.1;
			minimum_i    =-100000;
			maximum_i    = 100000;

			variable_type= "F"   ;
			setting_type = "default";

			variable     = minimum  ;
			cut_min      = minimum  ;
			cut_max      = maximum  ;
			cut_min_pre  = minimum  ;
			cut_max_pre  = maximum  ;

			variable_d   = minimum_d;
			cut_min_d    = minimum_d;
			cut_max_d    = maximum_d;
			cut_min_pre_d= minimum_d;
			cut_max_pre_d= maximum_d;

			variable_i   = minimum_i; 
			cut_min_i    = minimum_i; 
			cut_max_i    = maximum_i; 
			cut_min_pre_i= minimum_i; 
			cut_max_pre_i= maximum_i; 

		    c_name       = ""    ;
		    c_width      = 1000.0   ;
		    c_height     = 700.0   ;
		    leg_left     = 0.6   ;
		    leg_up       = 0.6   ;
		    leg_right    = 0.9   ;
		    leg_down     = 0.9   ;
		    leg_header   = ""    ;
		    title_name   = ""    ;
		    latex_name   = ""    ;
		    x_name       = ""    ;
		    x_bin        = 1     ;
		    x_min        = 0.0   ;
		    x_max        = 1.0   ;
		    y_name       = ""    ;
		    y_bin        = 1     ;
		    y_min        = 0.0   ;
		    y_max        = 1.0   ;
		    cut_switch   = false ;
		    plot_switch  = false ;
		    log_switch   = false ;
			log_min      = 0.1   ;
		    norm_switch  = false ;
		    MVA_switch   = false ;
			show_title   = false ;
			use_default_line_setting = true;
		}

		void Copy(Avariable);

		void Init(){
			//c=new TCanvas(c_name.c_str()," ",c_width,c_height);
			leg=new TLegend(leg_left,leg_up,leg_right,leg_down);
			leg->SetHeader(leg_header.c_str(),"C");
		}

		bool Is_Minimum(float val){
			if(val==minimum){
				return(true);
			}
			return(false);
		}

		bool Is_Minimum(double val){
			if(val==minimum_d){
				return(true);
			}
			return(false);
		}

		bool Is_Minimum(long int val){
			if(val==minimum_i){
				return(true);
			}
			return(false);
		}

		bool Is_Maximum(float val){
			if(val==maximum){
				return(true);
			}
			return(false);
		}

		bool Is_Maximum(double val){
			if(val==minimum_d){
				return(true);
			}
			return(false);
		}

		bool Is_Maximum(long int val){
			if(val==maximum_i){
				return(true);
			}
			return(false);
		}

		float Minimum(){
			return(minimum);
		}

		float Maximum(){
			return(maximum);
		}

		bool Use_Default_Line_Setting(){
			return(use_default_line_setting);
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
		int num_var;
		int num_vec;
		int num_MVA;
		int cut_level;

		bool        weight_exist;
		Avariable              weight;

		std::vector<Avariable> var;
		std::vector<Avariable_vec> vec;
		std::vector<Avariable> MVA;

		void Read_Var(CPath &path);

		AVariable(){
			weight_exist = false;
			num_var=0;
			num_vec=0;
			num_MVA=0;
			var.clear();
			MVA.clear();
		}

		int Var_Num();
		int Vec_Num();
		int MVA_Num();
};


namespace YAML{
	template<>
		struct convert<Avariable>{
			static bool decode(const Node& node, Avariable& var){ 
				for(YAML::const_iterator it=node.begin(); it != node.end(); ++it){
					if(it->first.as<std::string>()=="variable_type"){
						RW_element(it->first.as<std::string>(), it, var.variable_type);
					}
					else if(it->first.as<std::string>()=="setting_type"){
						RW_element(it->first.as<std::string>(), it, var.setting_type);
					}
					else if(it->first.as<std::string>()=="Canvas_name"){
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
						if(var.variable_type=="F"){
							RW_element(it->first.as<std::string>(), it, var.cut_min);
						}
						else if(var.variable_type=="D"){
							RW_element(it->first.as<std::string>(), it, var.cut_min_d);
							var.cut_min = static_cast<float> (var.cut_min_d);
						}
						else if(var.variable_type=="I"){
							RW_element(it->first.as<std::string>(), it, var.cut_min_i);
							var.cut_min = static_cast<float> (var.cut_min_i);
						}
						if(var.Is_Minimum(var.cut_min_pre)){
							var.cut_min_pre = var.cut_min;
						}
					}
					else if(it->first.as<std::string>()=="cut_max"){
						RW_element(it->first.as<std::string>(), it, var.cut_max);
						if(var.variable_type=="F"){
							RW_element(it->first.as<std::string>(), it, var.cut_max);
						}
						else if(var.variable_type=="D"){
							RW_element(it->first.as<std::string>(), it, var.cut_max_d);
							var.cut_max = static_cast<float> (var.cut_max_d);
						}
						else if(var.variable_type=="I"){
							RW_element(it->first.as<std::string>(), it, var.cut_max_i);
							var.cut_max = static_cast<float> (var.cut_max_i);
						}
						if(var.Is_Maximum(var.cut_max_pre)){
							var.cut_max_pre = var.cut_max;
						}
					}
					else if(it->first.as<std::string>()=="cut_min_pre"){
						RW_element(it->first.as<std::string>(), it, var.cut_min_pre);
						if(var.variable_type=="F"){
							RW_element(it->first.as<std::string>(), it, var.cut_min_pre);
						}
						else if(var.variable_type=="D"){
							RW_element(it->first.as<std::string>(), it, var.cut_min_pre_d);
							var.cut_min_pre = static_cast<float> (var.cut_min_pre_d);
						}
						else if(var.variable_type=="I"){
							RW_element(it->first.as<std::string>(), it, var.cut_min_pre_i);
							var.cut_min_pre = static_cast<float> (var.cut_min_pre_i);
						}
					}
					else if(it->first.as<std::string>()=="cut_max_pre"){
						RW_element(it->first.as<std::string>(), it, var.cut_max_pre);
						if(var.variable_type=="F"){
							RW_element(it->first.as<std::string>(), it, var.cut_max_pre);
						}
						else if(var.variable_type=="D"){
							RW_element(it->first.as<std::string>(), it, var.cut_max_pre_d);
							var.cut_max_pre = static_cast<float> (var.cut_max_pre_d);
						}
						else if(var.variable_type=="I"){
							RW_element(it->first.as<std::string>(), it, var.cut_max_pre_i);
							var.cut_max_pre = static_cast<float> (var.cut_max_pre_i);
						}
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
					else if(it->first.as<std::string>()=="MVA"){
						RW_element(it->first.as<std::string>(), it, var.MVA_switch);
					}
					else if(it->first.as<std::string>()=="show_title"){
						RW_element(it->first.as<std::string>(), it, var.show_title);
					}
					else if(it->first.as<std::string>()=="use_default_line_setting"){
						RW_element(it->first.as<std::string>(), it, var.use_default_line_setting);
						if(var.use_default_line_setting){
							if(it->first.as<std::string>()=="line_setting"){
								var.line_setting = it->second.as<Cplot_basic_color_style>();
							}
						}
					}
					else if(it->first.as<std::string>()=="plot_2d"){
						var.label_2d = it->second.as<std::vector<int> >();	
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
