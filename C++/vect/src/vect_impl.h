// Vaša implementacija dolazi ovdje.
#include <iostream>
#include "vect.h"
#include <memory>
#include <cmath>

template <typename T>
std::allocator<T> Vect<T>::alloc;

//Ctor
template <typename T>
Vect<T>::Vect(size_t n, T v){
	if (n > 0){
		mdata = alloc.allocate(n);
		for(unsigned int i = 0; i < n; ++i){
			alloc.construct(mdata + i, v);
		}
		mfirst_free = mdata + n;
		mend = mdata + n;
	}else {
		mdata = nullptr;
		mfirst_free = nullptr;
		mend = nullptr;
	}	
}

//CCtor
template <typename T>
Vect<T>::Vect(const Vect& v) : mdata(alloc.allocate(v.capacity())), mfirst_free(mdata + v.size()), mend(mdata + v.capacity()) {

	std::uninitialized_copy(v.mdata, v.mfirst_free, mdata);
}

//MCtor
template <typename T>
Vect<T>::Vect(Vect && v) noexcept : mdata(v.mdata), mfirst_free(v.mfirst_free), mend(v.mend) {
	v.mdata = nullptr;
	v.mfirst_free = nullptr;
	v.mend = nullptr;
}

//OP
template <typename T>
Vect<T>& Vect<T>::operator=(const Vect& v){

	if (mdata != v.mdata){
		free();
		mdata = alloc.allocate(v.capacity());
		std::uninitialized_copy(v.mdata, v.mfirst_free, mdata);
		mfirst_free = mdata + v.size();
		mend = mdata + v.capacity();
	}
	return *this;
}
//MOP

template <typename T>
Vect<T>& Vect<T>::operator=(Vect && v) noexcept {
	if(this != &v){
		free();
		mdata = v.mdata;
		mfirst_free = v.mfirst_free;
		mend = v.mend;

		v.mdata = nullptr;
		v.mfirst_free = nullptr;
		v.mend = nullptr;
	}
	return *this;
}

//DTOR  
template <typename T>
Vect<T>::~Vect(){
	free();
}

// dohvat elemenata
template <typename T>
T Vect<T>::operator[](unsigned int i) const{
	return *(mdata + i);
}

template <typename T>
T& Vect<T>::operator[](unsigned int i){
	return *(mdata + i);
}

//push_back metoda
template <typename T>
void Vect<T>::push_back(T v){

	if (capacity() <= size()) reallocate();
		
    	alloc.construct(mfirst_free, v);
	++mfirst_free;
	
}    
//info rutine
template<typename T>
size_t Vect<T>::size() const {
	return mfirst_free - mdata;
}

template<typename T>
size_t Vect<T>::capacity() const {
    	return mend - mdata;
}
// +=, -=, *=
template<typename T>
Vect<T>& Vect<T>::operator+=(const Vect<T>& v){
	if (size() != v.size()){
		throw "Zbrajanje vektora razlicitih velicina";
	}
	
	for(unsigned int i = 0; i < size(); ++i){
		*(mdata + i) += v[i];
	}
	return *this;	
}

template<typename T>
Vect<T>& Vect<T>::operator-=(const Vect<T>& v){
	if (size() != v.size()){
		throw "Oduzimanje vektora razlicitih velicina";
	}
	
	for(unsigned int i = 0; i < size(); ++i){
		*(mdata + i) -= v[i];
	}
	return *this;	
}

template<typename T>
Vect<T>& Vect<T>::operator*=(T const &k){
	for(unsigned int i = 0; i < size(); ++i){
		*(mdata + i) *= k;
	}
	return *this;	
}
//norma
template <typename T>
double Vect<T>::two_norm() const{
	double zbroj = 0.0;
	double x;
	for(unsigned int i = 0; i < size(); ++i){
		x = (double) *(mdata + i);
		zbroj += x * x;
	}
	return std::sqrt(zbroj);

}
template <typename T>
void Vect<T>::free(){
    
	for(unsigned int i = 0; i < size(); ++i){
		alloc.destroy(mdata + i);
	}

	alloc.deallocate(mdata, capacity());
}    

template <typename T>
void Vect<T>::reallocate(){
    
	if (capacity() == 0){
		mdata = alloc.allocate(1);
		mfirst_free = mdata;
		mend = mdata + 1;
	} else {
		unsigned int s = size();
		T* tmp = alloc.allocate(2 * s);
		std::uninitialized_copy(mdata, mend, tmp);
		free();
		mdata = tmp;	
		mfirst_free = mdata + s;
		mend = mdata + 2*s;
	}
} 
// zbrajanje i oduzimanje
template<typename T>
Vect<T> operator+(Vect<T> const & x, Vect<T> const & y){

	Vect<T> tmp(x);
	tmp += y;
	return tmp;
}

template<typename T>
Vect<T> operator-(Vect<T> const & x, Vect<T> const & y){

	Vect<T> tmp(x);
	tmp -= y;
	return tmp;
}
//ispis
template <typename T>
std::ostream & operator<<(std::ostream & out, Vect<T> const & v){
 	out << "[";
	for(unsigned int i = 0; i < v.size(); ++i){
		if (i == 0) out << v[i];
		else out << "," << v[i];
	}
	out << "]";
	return out;
}
