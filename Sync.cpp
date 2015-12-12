#include "Sync.h"

#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <dirent.h>

#define ERROR_OPENDIR -1

using namespace std;


Sync::Sync(){
	m_src.clear();
	m_dest.clear();
}
Sync::Sync(string src, string dest){
	m_src = src;
	m_dest = dest;
}
Sync::~Sync(){
	m_src.clear();
	m_dest.clear();
}

int Sync::run(){
	return this->readDir(m_src);
}

int Sync::readDir(string path){
	string readPath;
	DIR * dir = opendir((char*)path.c_str());
	dirent *ent;

	if(dir==NULL)
		return ERROR_OPENDIR;

	cout << "OPEN : " << path << endl;	
	while((ent = readdir(dir)) != NULL){
		if(ent==NULL){break;}
		if(strcmp(ent->d_name, ".")!=0 && strcmp(ent->d_name, "..")!=0){
			readPath = path + "/" + ent->d_name;
			if(ent->d_type==DT_DIR){
				this->readDir(readPath);
			}else if(ent->d_type==DT_REG){
				cout << "FILE : " << readPath << endl;
			}
		}
	}
	closedir(dir);
	return 0;
}

string Sync::getSource(){
	return m_src;
}
string Sync::getDestination(){
	return m_dest;
}
void Sync::setSource(string path){
	m_src=path;
}
void Sync::setDestination(string path){
	m_dest=path;
}

