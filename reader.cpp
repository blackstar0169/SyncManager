#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <regex>
#include <iostream>
#include <fstream>

#include "Function.h"

#define FUNCTION 1
#define VARIABLE 2
#define PATH 3
#define OPEN_FUNCTION 4
#define CLOSE_FUNCTION 5

using namespace std;

Function splitFunction(string str){
	smatch cm;
	string name;
	Function f;

	regex elem("[^(,){}\\s]+");

	//On récupère le nom de la fonction
	regex_search(str, cm, elem);
	name = cm.str();
	f.setName(name);
	cout << "name : " << name << endl;
	str.replace(cm.position(0), cm.length(0), "");//On supprime le nom
	//Récupération des arguments
	cout << "args : " << endl;
	while(regex_search(str, cm, elem)){
		cout << cm.str() << endl;
		f.addArgument(cm.str());
		str.replace(cm.position(0), cm.length(0), "");
	}
	return f;
}


int whatIsIt(string str, smatch& ret){
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

int main(void){
	int code;
	bool funcDected=false, inFunction=false;
	string buff;
	smatch ret;
	Function func;
	//Overture du script
	cout<<"START:"<<endl;
	ifstream fichier("test.txt", ios::in);
	if(!fichier){
		perror("Erreur lors de l'ouverture du fichier");
		exit(1);
	}
	//Tant que l'on est pas à la fin du script
	while(!(fichier.eof())){
		//Si on est pas encore dans une fonction
		if(!inFunction){
			//Lire tant que l'on ne match pas une fonction
			do{
				getline(fichier, buff);
				do{
					cout<<"BUFF:"<<buff<<endl;
					code = whatIsIt(buff, ret);
					if(code==OPEN_FUNCTION && funcDected){
						cout<<"OPEN:"<<endl;
						inFunction=true;
					}else if(code==FUNCTION){
						funcDected = true;
						func = splitFunction(ret.str());
					}

					if(code>0){
						buff.replace(ret.position(0), ret.length(0), "");
					}
				}while(code>0 && !inFunction);

			}while(!inFunction && !(fichier.eof()));
		}else{//Si l'on est dans une fonction
			cout << "Type:" << func.getName() << " | src:" << func.getArgument(0) << " | dest:" << func.getArgument(1) << endl;
			do{
				//Lire les chemins
				getline(fichier, buff);
				code = whatIsIt(buff, ret);
				if(code==PATH){
					cout<<"path : "<<ret.str()<<endl;
				}if(code==CLOSE_FUNCTION){
					funcDected = false;
					inFunction=false;
					cout<<"CLOSE:"<<endl;
				}
				//Remplacer les $D en début de chemin par le point de montage
			}while(code!=CLOSE_FUNCTION && !(fichier.eof()));//Tant que l'on ne rencontre pas de "}"
		}
	}
	fichier.close();
	cout<<"END:"<<endl;
	return 0;
}



