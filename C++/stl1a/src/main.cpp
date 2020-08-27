#include "zadatak.h"
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <utility>

using namespace std;

int main()
{
    // Vaše testiranje koda dolazi ovdje.
	string str("dcba");
	//print_permutation(str); 

	vector<int> v{1,2,3};
	list <char> l {'i','j','k','l'};
	vector<std::pair<int,char>> v2(4);

	zip(v.begin(), v.end(), l.begin(), l.end(), v2.begin());
	
	//for(auto x : v2) cout << x.first << ","<< x.second << endl;

	vector<int> ve1{1,2,3,4,5,6,7,8};
	vector<char> ve2{ 'i', 'j','k','l'};
	vector<pair<int,char>> ve3 = zip(ve1,ve2);
	
	//for(auto x : ve3) cout << x.first << ","<< x.second << endl;

	vector<string> s{"0911234567","011234567","021123456","+385 1 1234567","385 1 1234567","1234567"};
	
	for(auto x : s) cout << x << ",";
	cout<<endl;

	normalize_phone_number(s);
	
	for(auto x : s) cout << x << ",";
	cout<<endl;



    return 0;
}
