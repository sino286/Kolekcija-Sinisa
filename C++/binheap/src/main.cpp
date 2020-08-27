#include <iostream>
#include "binHeap.h"

using namespace std;

int main()
{
	MaxHeap<int> h;
    
	//cout << h.size() << endl;

	h.push(2);
	h.push(7);

	//cout << h.top() << endl;

	h.pop();

	//cout << h.top() << endl;

	//cout << h.empty() << endl;

	std::vector<double> v{2.5, 3.4, 3.1, 4.015, 4.0, 9.1, 1.0, 3.1};

	MaxHeap<double> h2(v.begin(), v.end());

	cout << h2.size() << endl;

	cout << h2.top() << endl;

	cout << h2.empty() << endl;

    	
	cout << h2.top() << endl;

	h2.sort(v);

	for(auto x : v) cout << x << " " ;

	cout << endl;
	
	return 0;
}
