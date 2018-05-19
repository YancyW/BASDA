#include "Class/Plot.h"
CColor::CColor(){
	_max_color_num = 41;
	_color= 0; 
	user_color = false;
	_Init_Color();
}

void CColor::_Init_Color(){
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

int CColor::Color(){
	if(user_color){
		return(_color);
	}
	else{
		if(_color!=-1){
			return(_colornum[_color]);
		}
		else{
			_auto_color_num++;
			int output_color = _colornum[(_auto_color_num)%41];
			return(output_color);
		}
	}
}

int CColor::Last_Color(){
	if(user_color){
		return(_color);
	}
	else{
		if(_color!=-1){
			return(_colornum[_color]);
		}
		else{
			int output_color = _colornum[(_auto_color_num)%41];
			return(output_color);
		}
	}
}

int CColor::Origin_Color(){
	return(_color);
}


void CColor::Get_Color(int input){
	_color = input;
}





CStyle::CStyle(){
	_max_style_num = 10;
	_style= 1; 
	user_style= false;
	_Init_Style();
}

void CStyle::_Init_Style(){
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
}

int CStyle::Style(){
	if(user_style){
		return(_style);
	}
	else{
		return(_stylenum[(_style/10)]);
	}
}

void CStyle::Get_Style(int input){
	_style = input;
}




CWidth::CWidth(){
	_width = 3; 
	user_width= false;
}

int CWidth::Width(){
	if(user_width){
		return(_width);
	}
	else{
		return(_width);
	}
}

void CWidth::Get_Width(int width){
	_width = width;
}



std::ostream & operator<< (std::ostream & ostr, Cplot_basic_color_style str){
	ShowMessage(1); 
	ShowMessage(3,"The Cplot_basic_color_style is:"); 
	ShowMessage(4,"user_basic_color_style: ", str.user_basic_color_style);
	ShowMessage(4,"user_color: "      , str.user_color);
	ShowMessage(4,"user_style: "      , str.user_style);
	ShowMessage(4,"user_width: "      , str.user_width);
	ShowMessage(4,"_origin_color: "   , str.Origin_Color());
	ShowMessage(4,"_output_color: "   , str.Color());
	ShowMessage(4,"_auto_color_num: " , CColor::Auto_Color_Num());
	ShowMessage(4,"_style: "          , str.Style());
	ShowMessage(4,"_width: "          , str.Width());
	return ostr;
}

std::ostream & operator<< (std::ostream & ostr, Cplot_line str){
	ShowMessage(1); 
	ShowMessage(2,"The Cplot_line is:"); 
	ShowMessage(3,"include                 : ", str.include);
	ShowMessage(3,"fill_switch             : ", str.fill_switch);
	ShowMessage(3,"norm_switch             : ", str.norm_switch);
	ShowMessage(3,"fill_origin_color       : ", str.fill_color.Origin_Color());
	ShowMessage(3,"fill_output_color       : ", str.fill_color.Color());
	ShowMessage(3,"current _auto color_num : ", str.fill_color.Auto_Color_Num());
	ShowMessage(3,"line_setting            : ", str.line_setting);
	return ostr;
}
