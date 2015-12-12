#ifndef SYNC_H
#define SYNC_H

#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <dirent.h>

class Sync{
private:
	std::string m_src;
	std::string m_dest;
	DIR *m_dir;
	dirent *m_ent;

public:
	Sync();
	Sync(std::string src, std::string dest);
	~Sync();
	int run();
	int readDir(std::string path);
	std::string getSource();
	std::string getDestination();
	void setSource(std::string path);
	void setDestination(std::string path);
};


#endif