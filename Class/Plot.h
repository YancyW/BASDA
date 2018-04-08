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


class Cplot_setting{
	public:
		//stack
		bool show_title;

		//line
		int  line_width; 
		int  with_color_or_line; 
};

class Cplot_drawing{
	public:
		std::vector<std::string> single_plot;
		std::vector<std::string> class_plot;
};

class CPlot{
	private:
	public:
		Cplot_setting  setting;
		Cplot_drawing  drawing;
		void Read_Plot(CPath &path);
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
					else{
						ShowMessage(2,"wrong input when load class Cplot_drawing",it->first.as<std::string>());
					}
				}
				ShowMessage(2,"finish reading plot drawing");
				return true;
			}
		};
};
#endif
