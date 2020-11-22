namespace YAML{
	template<>
		struct convert<Cplot_basic_color_style>{
			static bool decode(const Node& node, Cplot_basic_color_style& plot){ 
				for(YAML::const_iterator it=node.begin(); it != node.end(); ++it){
					std::cout << "reach here" << it->first.as<std::string>() << std::endl;
					if(it->first.as<std::string>()=="user_basic_color_style"){
						plot.user_basic_color_style= it->second.as<bool>();	
					}
					else if(it->first.as<std::string>()=="user_width"){
						plot.user_width=it->second.as<bool>();	
					}
					else if(it->first.as<std::string>()=="width"){
						plot.Get_Width(it->second.as<int>());	
					}
					else if(it->first.as<std::string>()=="user_style"){
						plot.user_style=it->second.as<bool>();	
					}
					else if(it->first.as<std::string>()=="style"){
						plot.Get_Style(it->second.as<int>());	
					}
					else if(it->first.as<std::string>()=="user_color"){
						plot.user_color=it->second.as<bool>();	
					}
					else if(it->first.as<std::string>()=="color"){
						plot.Get_Color(it->second.as<int>());	
					}
					else{
						ShowMessage(2,"wrong input when load class Cplot_basic_color_style",it->first.as<std::string>());
					}
				}
				ShowMessage(2,"finish reading Cplot_basic_color_style");
				return true;
			}
		};
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
					else if(it->first.as<std::string>()=="norm_switch"){
						plot.norm_switch= it->second.as<int>();	
					}

					else if(it->first.as<std::string>()=="fill_color"){
						plot.fill_color.Get_Color(it->second.as<int>());	
					}
					else if(it->first.as<std::string>()=="line_setting"){
						plot.line_setting = it->second.as<Cplot_basic_color_style>();
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

namespace YAML{
	template<>
		struct convert<Cplot_setting>{
			static bool decode(const Node& node, Cplot_setting& plot){ 
				for(YAML::const_iterator it=node.begin(); it != node.end(); ++it){
					if(it->first.as<std::string>()=="show_title"){
						RW_element(it->first.as<std::string>(), it, plot.show_title);
					}
					else if(it->first.as<std::string>()=="line_setting"){
						plot.line_setting = it->second.as<Cplot_basic_color_style>();
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


namespace YAML{
	template<>
		struct convert<Cplot_stack>{
			static bool decode(const Node& node, Cplot_stack& plot){ 
				for(YAML::const_iterator it=node.begin(); it != node.end(); ++it){
					if(it->first.as<std::string>()=="stack_draw"){
						plot.draw_option= it->second.as<std::string>();	
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


namespace YAML{
	template<>
		struct convert<Cplot_legend>{
			static bool decode(const Node& node, Cplot_legend& plot){ 
				for(YAML::const_iterator it=node.begin(); it != node.end(); ++it){
					if(it->first.as<std::string>()=="head_name"){
						plot.header= it->second.as<std::string>();	
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

