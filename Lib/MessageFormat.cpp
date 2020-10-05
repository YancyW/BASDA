#include "MessageFormat.h"
//------------------------------------------------------------------------------
//

std::ostream& Choose_Print_File(bool IsRecord, std::string file_name){
	std::streambuf * buf;
	std::ofstream of;

	if(!IsRecord){
		buf = std::cout.rdbuf();
	}
	else{
		of.open(file_name,std::ios::app);
		buf = of.rdbuf();
	}

	static std::ostream out_file(buf);
	return(out_file);
}
//

void RecordMessage(std::ofstream &file_name, int level){
	std::cout.setf(std::ios::left);

	file_name << "\n";
	std::cout << std::endl;
}




void ShowMessage(Int_t level, std::string mess){
	std::string fill1="";
	std::string fill2="      ";
	std::string fill3="            ";
	std::string fill4="                  ";
	std::string fill5="                        ";
	std::string fill6="                              ";
	std::string fill;
	std::string fillter;

	int  fillnum1=0;
	int  fillnum2=6;
	int  fillnum3=12;
	int  fillnum4=18;
	int  fillnum5=24;
	int  fillnum6=30;
	int  fillnum;

	switch(level){
		case 1:fill=fill1;fillnum=fillnum1;break;
		case 2:fill=fill2;fillnum=fillnum2;break;
		case 3:fill=fill3;fillnum=fillnum3;break;
		case 4:fill=fill4;fillnum=fillnum4;break;
		case 5:fill=fill5;fillnum=fillnum5;break;
		case 6:fill=fill6;fillnum=fillnum6;break;
		default:fill=fill1;
	}

	int size = mess.size();
	int fillsize= (130 - fillnum - size)/2; 
	int fillsize2= fillsize-fillnum; 
	if(size%2==1){
		fillter=" *";
	}
	else{
		fillter=" ";
	}
	std::cout << fill << std::setw(fillsize) << std::setfill('*') <<""<< " " << mess << fillter << std::setw(fillsize2) << std::setfill('*') << "" << std::endl ;
}

void ShowMessage(){
	std::cout << "" << std::endl;
}

void ShowMessage(Int_t level=1){
	for(int i=0;i<level;i++){
		std::cout << "" << std::endl;
	}
}
