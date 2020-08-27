#ifndef ZADATAK_IS_INCLUDED             
#define ZADATAK_IS_INCLUDED             

#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

// Zadatak 1
void print_permutation(std::string str);


// Zadatak 2
template <typename InputIt1, typename InputIt2, typename OutputIt>
void zip(InputIt1 beg1, InputIt1  end1, InputIt2 beg2, InputIt2 end2, OutputIt beg3)
{	
	//std::transform(beg1, end1, beg2, beg3, [](auto a, auto b){return std::make_pair(a, b);});
	auto it1 = beg1;
	auto it2 = beg2;
	auto it3 = beg3;

	while( it1 != end1 && it2 != end2){
	
	*it3 = std::make_pair(*it1, *it2);
	
	it1++;
	it2++;
	it3++;
		
	}
}

template <typename T, typename S>
std::vector<std::pair<T,S>> 
zip(std::vector<T> const & vec1, std::vector<S> const & vec2)
{
	std::vector<std::pair<T,S>> vec3(std::min(vec1.size(),vec2.size()));

	zip(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), vec3.begin());

	return vec3;
}


// Zadatak 3
void normalize_phone_number(std::vector<std::string> & vec_str);

#endif
