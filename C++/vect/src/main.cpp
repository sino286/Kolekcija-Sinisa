#include "vect.h"
#include <vector>

using namespace std;

int main()
{
    // Vaši testovi dolaze ovdje.    

    	Vect<int> v(5,5);
	cout << v.size() << endl;
	cout << v.capacity() << endl;
	v.push_back(3);
	v.push_back(3);
	v.push_back(3);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	Vect<int> v2(v);
	
	cout << v2.size() << endl;
	cout << v2.capacity() << endl;
	v2.push_back(3);
	v2.push_back(3);
	v2.push_back(3);
	cout << v2.size() << endl;
	cout << v2.capacity() << endl;

	v = v2;
	cout << v2.size() << endl;
	cout << v2.capacity() << endl;
	v2.push_back(3);
	v2.push_back(3);
	v2.push_back(3);
	cout << v2.size() << endl;
	cout << v2.capacity() << endl;

	vector<Vect<int>> t;

	t.push_back(v);
	t.push_back(v);
	t.push_back(v2);
	
	v[1] = v2[0];
	cout << v[1]<< ' ' << v[6]<< endl;

	Vect<int> v3(3,5);
	cout << v3.two_norm() << endl;

	Vect<int> v4(3,2);
	v3 += v4;
	cout << v3[0] << endl;
	v3 -= v4;
	cout << v3[0] << endl;
	v3 *= 5;
	cout << v3[0] << endl;

	Vect<int> v5;
	v5 = v3 + v4;
	cout << v5[0] << endl;

	v5 = v3 - v4;
	cout << v5[0] << endl;

	Vect<double> v6;

	cout << v << endl;
	cout << v2 << endl;
	cout << v3 << endl;
	cout << v4 << endl;
	cout << v5 << endl;
	cout << v6 << endl;
    	return 0;


 

   
}
