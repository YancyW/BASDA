#pragma once
#ifndef FFILE_H
#define FFILE_H
#include <string> 
#include <sys/stat.h> 
#include <iostream>
#include "TSystem.h"
#include "boost/filesystem.hpp"
#include "Lib/MessageFormat.h"


class QueryResult {
	friend std::ostream& print (std::ostream&, const QueryResult& );
	public:
	using line_no = std::vector<std::string>::size_type;
	QueryResult (std::string s,
			std::shared_ptr<std::set<line_no> > p,
			std::shared_ptr<std::vector<std::string>> f) :
		sought(s), lines(p), file(f) {}
	std::vector<int> Get_Lines_Num();
	std::vector<std::string> Get_Lines_Content();

	private:
	std::string sought; //查找字符串
	std::shared_ptr<std::set<line_no> > lines; //行号集合
	std::shared_ptr<std::vector<std::string> > file; //文件集合

};
std::ostream& print(std::ostream& os, const QueryResult &qr);

class TextQuery {
	public:
		using line_no = std::vector<std::string>::size_type;
		TextQuery(std::ifstream& );
		QueryResult query(const std::string& ) const;
	private:
		std::shared_ptr<std::vector<std::string> > file; //文件内容
		std::map<std::string, std::shared_ptr<std::set<line_no> > > wm; //词和行号的集合

};


void Create_Folder(std::string folder_name);
void Create_File_Folder(std::string file_name);

bool Is_File_Exist(const std::string& fname);
void Is_File_Exist_And_Exit(const std::string& fname);

std::string Get_File_Folder(std::string input);
std::string Get_File_Ext(std::string input);
#endif
