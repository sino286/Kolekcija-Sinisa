#include "zadatak.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <map>
#include <iterator>

namespace std{

    template <typename T, typename U>    
    ostream & operator << (ostream & out, pair<T, U> const & p){
        out << p.first;
        return out;
    }
}

using namespace std;

void readFile(std::string const & fileName, 
              std::vector<std::string> & words)
{
	vector<char> const ukloni {',','.',';',':',')','(', '"'};

	ifstream in (fileName);
	if (!in) throw runtime_error(fileName + " se ne moze otvoriti za citanje");

	string line;
	while(getline(in, line)){
		stringstream ss(line);
		string word;

		while(ss >> word){

			word.erase(remove_if(word.begin(), word.end(), [](unsigned char c){return isspace(c);}), word.end());
		
			for(auto x : ukloni){
				if (word.front() == x) word.erase(0,1);
				if (word.back() == x) word.pop_back();
			}
		words.push_back(word);
		}

	}
	in.close();
		
}

// konstruktor
X::X(std::vector<std::string> const & words){
	vector<char> const samoglasnici {'a','e','i','o','u','A', 'E', 'I', 'O', 'U'};
	int broj_suglasnika = 0;

	for(auto x : words){
		for(auto y : x){
			if(find(samoglasnici.begin(), samoglasnici.end(), y) == end(samoglasnici)) ++broj_suglasnika;
		} 

	rijeci.insert(make_pair(x, broj_suglasnika));
	broj_suglasnika = 0;
	}
}


int X::max_br_suglasnika() const{
	int maxS = 0;
	
	for(auto x : rijeci){
		if(x.second > maxS) maxS = x.second;
	}
	return maxS;
}


void X::print(std::ostream &out, int k) const{
	copy_if(rijeci.begin(), rijeci.end(), ostream_iterator<pair<const string, int>>(out, " "), [k](pair<string,int> p){return p.second == k;} );
}

