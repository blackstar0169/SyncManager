#ifndef READER_H
#define READER_H

#include <string>
#include <vector>
#include <fstream>
#include <regex>

#include "Function.h"

class Reader{
private:
	std::ifstream m_script;
	std::string m_scriptPath;
	Function m_readFunction;

	Function splitFunction(std::string str);
	int detect(std::string str, std::smatch& ret);

public:
	Reader();
	Reader(std::string path);
	~Reader();
	int open(std::string path);
	int open();
	int close();
	Function next();
	Function* getAll();
	std::string getPath();
	int setPath(std::string path);
};


#endif