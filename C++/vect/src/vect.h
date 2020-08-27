#ifndef _VECT_H_IS_INCLUDED_
#define _VECT_H_IS_INCLUDED_

#include <iostream>
#include <string>

// deklaracija potrebna za testiranje
template <typename> class VectTest;

template <typename T>
class Vect
{
    	friend class VectTest<T>;  // da testovi mogu dohvatiti privatne varijable
    	friend class VectTestPair;
public:	
	explicit Vect(size_t n = 0, T v= {});  // Ctor
	// Kontrola kopiranja dolazi ovdje
	// CCtor
	Vect(const Vect& v);
	// MCtor
	Vect(Vect && v) noexcept;
	// OP
	Vect& operator=(const Vect& v);
	// MOP
	Vect& operator=(Vect && v) noexcept;
	// DTOR
	~Vect();

    	// dohvat elemenata (operator [])
	T operator[](unsigned int i) const;
        T& operator[](unsigned int i);

    	// push_back metoda
	void push_back(T v);

     	// info rutine size() i capacity()
	size_t size() const;
	size_t capacity() const;
    	
	// operatori +=, -=, *=
	Vect& operator+=(const Vect& v);
	Vect& operator-=(const Vect& v);
	Vect& operator*=(T const & k);
	// euklidska norma vraća double !
     	double two_norm() const;
private:
        T *mdata;       // pokazivač na prvi element
        T *mfirst_free; // pokazivač na prvo slobodno mjesto
        T *mend;        // pokazivač na kraj alociranog prostora
                             // (jedno mjesto iza posljednjeg)
  
        // Oslobodi zauzeti prostor (pomoću alokatora)
        void free();

      	// realociraj na novu lokaciju. Povećaj dimenziju vektora 2 puta; ako je 
        // vektor prazan alociraj jedan element. 
        void reallocate();

        // dodati vlastite privatne metode.
	
        // alokator ne mora imati pristup varijablama članicama klase pa ga činimo 
        // statičkim. Ne zaboraviti definirati ga.
        static std::allocator<T> alloc;
};

// Deklaracija operator +, - i << 
template<typename T>
Vect<T> operator+(Vect<T> const & x, Vect<T> const & y);

template<typename T>
Vect<T> operator-(Vect<T> const & x, Vect<T> const & y);

template <typename T>
std::ostream & operator<<(std::ostream & out, Vect<T> const & v);

// Implementacija je u posebnoj .h datoteci
#include "vect_impl.h"

#endif
