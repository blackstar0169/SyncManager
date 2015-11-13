#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stack>
#include <string>
#include <regex>
#include <iostream>

#define FUNCTION 1
#define VARIABLE 2
#define PATH 3
#define OPEN_FUNCTION 4
#define CLOSE_FUNCTION 5

using namespace std;

void splitFunction(string str){
	smatch cm;
	string name;

	regex elem("\\w+");

	//On récupère le nom de la fonction
	regex_search(str, cm, elem);
	name = cm.str();
	cout << "name : " << name << endl;
	str.replace(cm.position(0), cm.length(0), "");//On supprime le nom
	//Récupération des arguments
	while(regex_search(str, cm, elem)){
		cout << cm.str() << endl;
		str.replace(cm.position(0), cm.length(0), "");
	}
}


int whatIsIt(string str, smatch *ret){
	smatch cm;
	regex func("\\w+\\s*\\((\\s*\\w+\\s*,*)*\\)");
	regex var("\\w+\\s*=\\s*(.)+\\s*;");
	regex path("(~|\\.|\\/)*(\\w+\\/)+(\\w+)(\\.\\w+)*");
	regex openFunction("\\{{1,1}");
	regex closeFunction("\\}{1,1}");
	
	if(regex_search(str, cm, func)){
		*ret = cm;
		return FUNCTION;
	}else if(regex_search(str, cm, var)){
		*ret = cm;
		return VARIABLE;
	}else if(regex_search(str, cm, path)){
		*ret = cm;
		return PATH;
	}else if(regex_search(str, cm, openFunction)){
		*ret = cm;
		return OPEN_FUNCTION;
	}else if(regex_search(str, cm, closeFunction)){
		*ret = cm;
		return CLOSE_FUNCTION;
	}
	return 0;
}

int main(void){
	string str[11];
	str[0]="function(arg1,arg2, arg3){}";
	str[1] = "function(arg1,arg2) x=12";
	str[2] = "function  ( arg1,arg2 ){";
	str[3] = "der1_id= 56 ; ";
	str[4] = "der1_id= \"ok\" ;";
	str[5] = "der1_id= 56;	";
	str[6] = "./opt/dssd/opt.media";
	str[7] = "./opt/dssd/opt";
	str[8] = "/opt/dssd/opt.media";
	str[9] = "opt/dssd/opt.media";
	str[10] = "~/opt/dssd/opt.media";	
	for(int i=0; i<11; i++){
		string tmp = str[i];		
		int code;

		cout << str[i] << " : " ;
		do{
			smatch retour;
			code = whatIsIt(tmp, &retour);
			
			if(code>0){
				cout << " [" << code << "] "<<retour.str() << " | " ;
				if(code==FUNCTION){
					splitFunction(retour.str());
				}
				tmp.replace(retour.position(0), retour.length(0), "");
			}	
		}while(code>0);
		cout<<endl;
	}
		

	/*FILE * scriptFile;
	string uuid;
	string path="./scripts/"
	bool eof=0;
	stack<string> funcStack;

	cout << "UUID de la partition a synchroniser" << endl;
	cin >> uuid;

	if(exist(uuid)){
		path+=uuid;
		scriptFile = fopen(path.c_str(), "r");
		jumptochar(scriptFile);
		while(!eof){
			char* str[256];
			str=fgets(str, scriptFile);//On lit une ligne
			if(stack.empty()){//Si la pile est vide alors on se prépare a lire une fonction/variable
				
			}else{

			}
		}
	}*/
	return 0;
}



