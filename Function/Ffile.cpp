#include "Function/Ffile.h"
void Create_Folder(std::string folder_name){
	boost::filesystem::path dir(folder_name);
	if(!boost::filesystem::exists(dir)){
		boost::filesystem::create_directories(dir);  //目录不存在，创建
		std::cerr<<"Directory Created:  " << folder_name << std::endl;
    }
}

void Create_File_Folder(std::string file_name){
	boost::filesystem::path dir(file_name);
	boost::filesystem::path parent_path = dir.parent_path();
	if(!boost::filesystem::exists(parent_path)){
		boost::filesystem::create_directories(parent_path);  //目录不存在，创建
		std::cerr<<"Directory Created:  " << parent_path.string()<< std::endl;
    }
}

bool Is_File_Exist(const std::string& fname){
	struct stat buffer;
	return(stat(fname.c_str(),& buffer)==0);
}


void Is_File_Exist_And_Exit(const std::string& fname){
	if(!Is_File_Exist(fname)){ShowMessage(2,"Error: the file is not exist:",fname);exit(EXIT_FAILURE);}
}
