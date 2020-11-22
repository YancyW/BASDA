#pragma once
#ifndef GLOBAL_PARA_PLOT_DIRECT_H
#define GLOBAL_PARA_PLOT_DIRECT_H
#include "TStyle.h"
#include <string> 
#include <vector>
#include "yaml-cpp/yaml.h"

#include "Function/Fbasic.h"
#include "RWpara/RWbasic.h"
#include "Class/Path.h"
#include "Class/Plot.h"
#include "AnalyseClass/Variable.h"


class CPlot_Direct: public AWeight{
	private:
		Avariable                plot_var;
	public:
		int                      var_label;
		bool                     using_user_var;

		Cplot_line               line_setting;

		void Read_Plot_Direct(CPath &path);

		CPlot_Direct(){
			var_label = 0;
			using_user_var  = false;
			exist = false;
		}

		Avariable Var(AVariable &var){
			if(!using_user_var){
				plot_var = var.var[var_label];
			}
			else{
				if(plot_var.title_name==""){
					ShowMessage(2,"in CPlot_Direct::Var wrong input, you set using_user_var=true, but there is no obsrvable title name.");
				}
				else{
					plot_var.plot_switch=true;
				}
			}
			return(plot_var);
		}
};

#endif
