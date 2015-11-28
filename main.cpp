#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include "Function.h"
#include "Reader.h"


using namespace std;

int main(void){
	string p="./scripts/save.dat";
	Function f;

	Reader rdr(p);
	rdr.open();
	f=rdr.next();

	cout<<"Function : "<<f.getName()<<endl;
	for(int i=0; i<f.countArguments();i++)
		cout<<"arg"<<i<<" : "<<f.getArgument(i)<<endl;
	for(int i=0; i<f.countPaths();i++)
		cout<<"path"<<i<<" : "<<f.getPath(i)<<endl;

	f=rdr.next();

	cout<<"Function : "<<f.getName()<<endl;
	for(int i=0; i<f.countArguments();i++)
		cout<<"arg"<<i<<" : "<<f.getArgument(i)<<endl;
	for(int i=0; i<f.countPaths();i++)
		cout<<"path"<<i<<" : "<<f.getPath(i)<<endl;


	return 0;
}



