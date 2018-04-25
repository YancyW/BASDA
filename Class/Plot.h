#pragma once
#ifndef GLOBAL_PARA_PLOT_H
#define GLOBAL_PARA_PLOT_H
#include "TStyle.h"
#include <string> 
#include <vector>
#include "yaml-cpp/yaml.h"

#include "Function/Fbasic.h"
#include "RWpara/RWbasic.h"
#include "Class/Path.h"

class Cplot_basic1{
	private:
		int  _max_color_num   ;
		int  _max_style_num   ;

	protected:
		std::vector<int>      _colornum;
		std::vector<int>      _stylenum;

		void _Init_Color();
		void _Init_Style();

	public:
		//stack
		bool user_basic1;
		int  width; 
		int  style; 
		int  color; 

		Cplot_basic1(){
			_max_color_num = 50;
			_max_style_num = 50;
			_Init_Color();
			_Init_Style();
			user_basic1 = false;
		    width = 3; 
		    style = 1; 
		    color = 0; 
		}

		
		void Clear(){
			_colornum.clear();
			_stylenum.clear();
		}

		int Color(){
			if(user_basic1){
				return(color);
			}
			else{
				return(_colornum[color]);
			}
		}

		int Style(){
			if(user_basic1){
				return(style);
			}
			else{
				return(_stylenum[style]);
			}
		}

		int Width(){
			return(style);
		}
};

namespace YAML{
	template<>
		struct convert<Cplot_basic1>{
			static bool decode(const Node& node, Cplot_basic1& plot){ 
				for(YAML::const_iterator it=node.begin(); it != node.end(); ++it){
					if(it->first.as<std::string>()=="user_basic1"){
						plot.user_basic1= it->second.as<bool>();	
					}
					else if(it->first.as<std::string>()=="width"){
						plot.width= it->second.as<int>();	
					}
					else if(it->first.as<std::string>()=="style"){
						plot.style= it->second.as<int>();	
					}
					else if(it->first.as<std::string>()=="color"){
						plot.color= it->second.as<int>();	
					}
					else{
						ShowMessage(2,"wrong input when load class Cplot_basic1",it->first.as<std::string>());
					}
				}
				ShowMessage(2,"finish reading Cplot_basic1");
				return true;
			}
		};
};

class Cplot_line: public Cplot_basic1{
	public:
		//stack
		bool include;
		bool fill_switch;
		int  fill_color; 
		bool norm_switch;

		Cplot_line(){
			include = true;
			fill_switch= false;
			fill_color = 0;
		    norm_switch= false;
		}
};

namespace YAML{
	template<>
		struct convert<Cplot_line>{
			static bool decode(const Node& node, Cplot_line& plot){ 
				for(YAML::const_iterator it=node.begin(); it != node.end(); ++it){
					if(it->first.as<std::string>()=="include"){
						plot.include= it->second.as<bool>();	
					}
					else if(it->first.as<std::string>()=="fill_switch"){
						plot.fill_switch= it->second.as<bool>();	
					}
					else if(it->first.as<std::string>()=="fill_color"){
						plot.fill_color= it->second.as<int>();	
					}
					else if(it->first.as<std::string>()=="norm_switch"){
						plot.norm_switch= it->second.as<int>();	
					}
					else{
						ShowMessage(2,"wrong input when load class Cplot_line",it->first.as<std::string>());
					}
				}
				ShowMessage(2,"finish reading Cplot_line");
				return true;
			}
		};
};

class Cplot_stack{
	public:
		//stack
		std::string draw_option; 

		Cplot_stack(){
		    draw_option = "Hist, nostack"; 
		}
};


class Cplot_setting{
	public:
		//stack
		bool show_title;

		//line
		int  line_width; 
		int  with_color_or_line; 

		Cplot_setting(){
			show_title = false;
			line_width = 3;
			with_color_or_line = 1;
		}
};

namespace YAML{
	template<>
		struct convert<Cplot_setting>{
			static bool decode(const Node& node, Cplot_setting& plot){ 
				for(YAML::const_iterator it=node.begin(); it != node.end(); ++it){
					if(it->first.as<std::string>()=="show_title"){
						RW_element(it->first.as<std::string>(), it, plot.show_title);
					}
					else if(it->first.as<std::string>()=="with_color_or_line"){
						RW_element(it->first.as<std::string>(), it, plot.with_color_or_line);
					}
					else if(it->first.as<std::string>()=="line_width"){
						RW_element(it->first.as<std::string>(), it, plot.line_width);
					}
					else{
						ShowMessage(2,"wrong input when load class Cplot_setting",it->first.as<std::string>());
					}
				}
				ShowMessage(2,"finish reading plot setting");
				return true;
			}
		};
};






class Cplot_drawing{
	public:
		std::string plot_type;
		std::vector<std::string> single_plot;
		std::vector<std::string> class_plot;
		Cplot_drawing(){
			plot_type = ".png";
		}
};


namespace YAML{
	template<>
		struct convert<Cplot_drawing>{
			static bool decode(const Node& node, Cplot_drawing& plot){ 
				for(YAML::const_iterator it=node.begin(); it != node.end(); ++it){
					if(it->first.as<std::string>()=="single_plot"){
						plot.single_plot= it->second.as<std::vector<std::string> >();	
					}
					else if(it->first.as<std::string>()=="class_plot"){
						plot.class_plot = it->second.as<std::vector<std::string> >();	
					}
					else if(it->first.as<std::string>()=="plot_type"){
						plot.plot_type= "."+it->second.as<std::string>();	
					}
					else{
						ShowMessage(2,"wrong input when load class Cplot_drawing",it->first.as<std::string>());
					}
				}
				ShowMessage(2,"finish reading plot drawing");
				return true;
			}
		};
};

class Cplot_canvas{
	public:
		Int_t border_mode;
		Int_t border_size;
		Int_t color;
		Int_t height;
		Int_t width;
		Int_t Xpos;
		Int_t Ypos;
};
/*
namespace YAML{
	template<>
		struct convert<Cplot_rootset>{
			static bool decode(const Node& node, Cplot_rootset& rset){ 
				for(YAML::const_iterator it=node.begin(); it != node.end(); ++it){
					if(it->first.as<std::string>()=="Canvas"){
						rset.single_plot= it->second.as<std::vector<std::string> >();	
					}
					else if(it->first.as<std::string>()=="Pad"){
						rset.class_plot = it->second.as<std::vector<std::string> >();	
					}
					else{
						ShowMessage(2,"wrong input when load class Cplot_rootset",it->first.as<std::string>());
					}
				}
				ShowMessage(2,"finish reading plot rootset");
				return true;
			}
		};
};
*/

class Cplot_rootset{
	public:
		Cplot_canvas canvas;
};

class CPlot{
	private:
	public:
		Cplot_setting  setting;
		Cplot_drawing  drawing;
		Cplot_rootset  rootset;
		void Read_Plot(CPath &path);
};
#endif
