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

std::string Get_File_Name_wo_Ext_From_Dir(std::string directory_name){
	boost::filesystem::path dir(directory_name);
//	std::string file_name = dir.stem().string();
	std::string file_name=""; 
	return(file_name);
}

bool Is_File_Exist(const std::string& fname){
	struct stat buffer;
	return(stat(fname.c_str(),& buffer)==0);
}


void Is_File_Exist_And_Exit(const std::string& fname){
	if(!Is_File_Exist(fname)){ShowMessage(2,"Error: the file is not exist:",fname);exit(EXIT_FAILURE);}
}


std::string Get_File_Folder(std::string input){
	boost::filesystem::path dir(input);
	boost::filesystem::path parent_path = dir.parent_path();
	std::string folder_name=parent_path.string();
	return(folder_name);
}

std::string Get_File_Ext(std::string input){
////boost::filesystem::path dir(input);
////std::string ext_name=dir.stem().string();
////return(ext_name);
}


std::vector<int> QueryResult::Get_Lines_Num(){
	std::vector<int> line_vec;
	for(auto num : *(this->lines)){
		line_vec.push_back(num+1);
	}
	return(line_vec);
}

std::vector<std::string> QueryResult::Get_Lines_Content(){
	std::vector<std::string> line_vec;
	for(auto num : *(this->lines)){
		line_vec.push_back(*(this->file->begin()+num));
	}
	return(line_vec);
}

TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>)
{
	std::string text;
	while (std::getline(is, text)) {
		file->push_back(text);
		int n = file->size() - 1;
		std::istringstream line(text);
		std::string word;
		while (line >> word) {
			auto& lines = wm[word];
			if (!lines)
				lines.reset(new std::set<line_no>);
			lines->insert(n);

		}

	}

}


/*找到指定sought的集合, 返回迭代器, 传入string和set*/
QueryResult TextQuery::query(const std::string& sought) const {
	static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
	auto loc = wm.find(sought);
	if (loc == wm.end())
		return QueryResult(sought, nodata, file); //没有找到, 不打印
	else
		return QueryResult(sought, loc->second, file); //按行号打印

};

std::string make_plural (std::size_t ctr, const std::string& word,
		const std::string ending)
{
	return (ctr > 1) ? word + ending : word;

}

std::ostream& print(std::ostream& os, const QueryResult &qr){
	os << qr.sought << " occurs " << qr.lines->size() << " "
		<< make_plural(qr.lines->size(), "time", "s") << std::endl;
	for(auto num : *qr.lines)
		os << "\t(line " << num+1 << ") " << *(qr.file->begin()+num) << std::endl;
	return os;

}

