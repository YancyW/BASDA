#include "Class/Plot.h"

void CPlot::Read_Plot(CPath &path){
	ShowMessage(3, "read Plot");
	std::string file_name=path.plot_file;
	ShowMessage(3, "plot file name",file_name);
	YAML::Node plot_node = YAML::LoadFile(file_name);

	this->setting = plot_node["setting"].as<Cplot_setting>();
	this->drawing = plot_node["drawing"].as<Cplot_drawing>();
}




void Cplot_basic1::_Init_Color(){
	_colornum.resize(_max_color_num);
	_colornum[0] =kRed-1;
	_colornum[1] =kRed;
	_colornum[2] =kRed+3;
	_colornum[3] =kBlue-1;
	_colornum[4] =kBlue;
	_colornum[5] =kBlue+3;
	_colornum[6] =kMagenta-1;
	_colornum[7] =kMagenta;
	_colornum[8] =kMagenta+3;
	_colornum[9] =kCyan-2;
	_colornum[10]=kCyan;
	_colornum[11]=kCyan+3;
	_colornum[12]=kOrange-2;
	_colornum[13]=kOrange;
	_colornum[14]=kOrange+2;
	_colornum[15]=kPink-2;
	_colornum[16]=kPink;
	_colornum[17]=kPink+2;
	_colornum[18]=kAzure;
	_colornum[19]=kViolet;
	_colornum[20]=kSpring-3;
	_colornum[21]=kSpring-2;
	_colornum[22]=kSpring-1;
	_colornum[23]=kSpring;
	_colornum[24]=kSpring+1;
	_colornum[25]=kSpring+2;
	_colornum[26]=kSpring+3;
	_colornum[27]=kGreen-3;
	_colornum[28]=kGreen-2;
	_colornum[29]=kGreen-1;
	_colornum[30]=kGreen;
	_colornum[31]=kGreen+1;
	_colornum[32]=kGreen+2;
	_colornum[33]=kGreen+3;
	_colornum[34]=kTeal-3;
	_colornum[35]=kTeal-2;
	_colornum[36]=kTeal-1;
	_colornum[37]=kTeal;
	_colornum[38]=kTeal+1;
	_colornum[39]=kTeal+2;
	_colornum[40]=kTeal+3;
}

void Cplot_basic1::_Init_Style(){
	_stylenum.resize(_max_style_num);
	_stylenum[0] =1 ;
	_stylenum[1] =7 ;
	_stylenum[2] =3 ;
	_stylenum[3] =2 ;
	_stylenum[4] =4 ;
	_stylenum[5] =5 ;
	_stylenum[6] =6 ;
	_stylenum[7] =8 ;
	_stylenum[8] =9 ;
	_stylenum[9] =10;
	for(int i=10;i<_max_color_num;i++){
		_stylenum[i]=10;
	}
}


