#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <vector>

class Function{
private:
	std::string m_name;
	std::vector<std::string> m_args;
	std::vector<std::string> m_paths;

public:
	Function();
	Function(std::string name);
	~Function();
	void addArgument(std::string arg);
	void addPath(std::string path);
	std::string getPath(int index);
	std::string* getAllPaths();
	int countPaths();
	std::string getArgument(int index);
	std::string* getAllArguments();
	std::string getName();
	void setName(std::string name);
	int countArguments();
	Function& operator=(const Function& copy);
};


#endif