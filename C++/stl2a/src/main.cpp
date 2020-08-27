#include <iostream>
#include "zadatak.h"
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main()
{
	vector<string> r;
	readFile("text.txt", r);

	for(auto x : r) cout << x << "\n";
	cout<<endl;

	
  	X testX(r);
	cout << testX.max_br_suglasnika() << endl;

	testX.print(cout, 5);
	cout << endl;

	return 0;	
}
