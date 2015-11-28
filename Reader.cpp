#include "Reader.h"

#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <regex>
#include <iostream>

#define ERROR_OPEN -1
#define ERROR_NO_FILEDESC -2
#define ERROR_NO_PATH -3
#define ERROR_CLOSE -4
#define ERROR_READ -5
#define ERROR_IS_OPEN -6

#define FUNCTION 1
#define VARIABLE 2
#define PATH 3
#define OPEN_FUNCTION 4
#define CLOSE_FUNCTION 5

using namespace std;


Reader::Reader(){
	m_scriptPath.clear();
}
Reader::Reader(string path){
	m_scriptPath=path;
}
Reader::~Reader(){
	m_scriptPath.clear();
	if(m_script.is_open())
		m_script.close();
}

int Reader::open(){
	if(m_script.is_open()){return ERROR_IS_OPEN;}

	m_script.open(m_scriptPath);
	if(!m_script){
		return ERROR_OPEN;
	}
	return 0;
}
int Reader::open(string path){
	m_scriptPath.clear();
	m_scriptPath=path;
	return this->open();
}
int Reader::close(){
	m_script.open(m_scriptPath);
	if(!m_script){
		return ERROR_OPEN;
	}
}
Function Reader::next(){
	Function func;
	int code;
	string buff;
	smatch ret;
	bool funcDected=false, inFunction=false;

	buff.clear();
	do{
		getline(m_script, buff);
		do{			
			code = this->detect(buff, ret);
			if(code==OPEN_FUNCTION && funcDected){				
				inFunction=true;
			}else if(code==FUNCTION){
				funcDected = true;
				func = this->splitFunction(ret.str());
			}

			if(code>0){
				buff.replace(ret.position(0), ret.length(0), "");
			}
		}while(code>0 && !inFunction);

	}while(!inFunction && !(m_script.eof()));
	do{
		//Lire les chemins
		getline(m_script, buff);
		code = this->detect(buff, ret);
		if(code==PATH){
			func.addPath(ret.str());
		}if(code==CLOSE_FUNCTION){
			funcDected = false;
			inFunction=false;
		}
		//Remplacer les $D en début de chemin par le point de montage
	}while(code!=CLOSE_FUNCTION && !(m_script.eof()));//Tant que l'on ne rencontre pas de "}"

	m_readFunction=func;
	return m_readFunction;
}

Function Reader::splitFunction(string str){
	smatch cm;
	string name;
	Function f;

	regex elem("[^(,){}\\s]+");

	//On récupère le nom de la fonction
	regex_search(str, cm, elem);
	name = cm.str();
	f.setName(name);
	str.replace(cm.position(0), cm.length(0), "");//On supprime le nom
	//Récupération des arguments
	while(regex_search(str, cm, elem)){
		f.addArgument(cm.str());
		str.replace(cm.position(0), cm.length(0), "");
	}
	return f;
}


int Reader::detect(string str, smatch& ret){
	smatch cm;
	regex func("\\w+\\s*\\((\\s*.\\s*,{0,1}*)*\\)");
	regex var("\\w+\\s*=\\s*(.)+\\s*;");
	regex path("(\\$|~|\\.|\\/)*(\\w+\\/)+(\\w+)(\\.\\w+|\\/)*");
	regex openFunction("\\{{1,1}");
	regex closeFunction("\\}{1,1}");
	
	if(regex_search(str, cm, func)){
		ret = cm;
		return FUNCTION;
	}else if(regex_search(str, cm, var)){
		ret = cm;
		return VARIABLE;
	}else if(regex_search(str, cm, path)){
		ret = cm;
		return PATH;
	}else if(regex_search(str, cm, openFunction)){
		ret = cm;
		return OPEN_FUNCTION;
	}else if(regex_search(str, cm, closeFunction)){
		ret = cm;
		return CLOSE_FUNCTION;
	}
	return 0;
}