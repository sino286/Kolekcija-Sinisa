#include "zadatak.h"
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

void print_permutation(std::string str){

	sort(str.begin(), str.end());
	cout << str << endl;
	
	while(next_permutation(str.begin(), str.end())){
		cout << str << endl;
	}
 }

// Ovdje dolazi vaš kod za Zadatak 1 i Zadatak 3.
void normalize_phone_number(std::vector<std::string> & vec_str){
   
	for(auto & x : vec_str){
		x.erase(remove(x.begin(), x.end(), ' '), x.end());

		if( x[0] != '+') x.insert(0,1,'+');

		if( x.substr(0,4) != "+385"){
			if( x[1] == '0') x.erase(1,1);
			else x.insert(1,1,'1');
			
			x.insert(1,"385");
		}
	
	}
}

