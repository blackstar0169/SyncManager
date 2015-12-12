#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include "Function.h"
#include "Reader.h"
#include "Sync.h"

using namespace std;

int main(void){
	string p="./scripts/save.dat";
	Function f;

	Reader rdr(p);
	rdr.open();
	f=rdr.next();

	Sync synchronizer("tstdir", "tstdir");
	int res = synchronizer.run();
	if(res<0)
		cout << "ERROR : "<<res<<endl;


	return 0;
}



