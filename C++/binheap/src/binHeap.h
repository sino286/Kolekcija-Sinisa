#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>

// Predložak klase koji implementira maximalnu hrpu. 
template <typename T>
class MaxHeap{
public:
    using size_type = typename std::vector<T>::size_type;
	// Konstruktor
    MaxHeap() = default;
    // Parametrizirani konstruktor koji preuzima elemente iz raspona [begin, end).
    template <typename RAIT>
    MaxHeap(RAIT begin, RAIT end);
	// Gurni novi element na hrpu.
    void push(T);
	// Ukloni vodeći (maksimalni) element sa hrpe.
    void pop();
	// Vrati vodeći element hrpe.
    T top() const;
    // Je li hrpa prazna?
    bool empty() const;
	// Broj elemenata u hrpi.
    size_type size() const;
    // Ispiši sortirane vijednosti u vektor vec. 
	// MaxHeap ostaje prazan nakon sortiranja.
    void sort(std::vector<T> & vec);
protected:
    std::vector<T> mData;
  // Eventualne dodatne metode stavljati u ovu sekciju.
    void correct_heap(int i);
    void vrati_poredak(int i);
};


template <typename T>
template <typename RAIT>
MaxHeap<T>::MaxHeap(RAIT begin, RAIT end){
	
	std::copy(begin, end, back_inserter(mData));
	for(int l = (size()-2) / 2 ; l  >= 0; --l ){

		correct_heap(l);
	}
}

template <typename T>
void MaxHeap<T>::push(T elem){
	
	mData.push_back(elem);
	vrati_poredak(size() - 1);
	
	  
}

template <typename T>
void MaxHeap<T>::pop(){
    
	std::swap(mData.front(), mData.back());
	mData.pop_back();
    
	correct_heap(0);
    
}

template <typename T>
T MaxHeap<T>::top() const{
	return mData.front();
}

template <typename T>
bool MaxHeap<T>::empty() const {
	return size() == 0;
}

template <typename T>
typename MaxHeap<T>::size_type MaxHeap<T>::size() const {
	return mData.size();
}

template <typename T>
void MaxHeap<T>::sort(std::vector<T> & vec){
	
	std::vector<T> v;
	
	while(!mData.empty()){
		v.insert(v.begin(), top());
		pop();
	}
	
	std::copy(v.begin(), v.end(), vec.begin());
}

template <typename T>
void MaxHeap<T>::correct_heap(int k){
	unsigned int lijevo = 2 * k + 1 ;
	unsigned int desno = 2 * k + 2 ;
	int najveci = k;

	if(lijevo < size() && mData[k] < mData[lijevo]) najveci = lijevo;

	if(desno < size() && mData[najveci] < mData[desno]) najveci = desno;

	if(najveci != k){
	std::swap(mData[k], mData[najveci]);
	correct_heap(najveci);
	}
}

template <typename T>
void MaxHeap<T>::vrati_poredak(int k){
	unsigned int roditelj = (k - 1) /2;
	
	if (k > 0 && mData[k] > mData[roditelj]){
		std::swap(mData[k], mData[roditelj]);
		vrati_poredak(roditelj);
	}
}
#endif
