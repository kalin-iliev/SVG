#pragma once
#include <iostream>
const int DEFAULT_VECTOR_CAPACITY = 20;

template<class T>
class Vector
{
private:
	T* vContainer;
	unsigned vSize;
	unsigned vCapacity;
public:
	Vector(unsigned capacity = DEFAULT_VECTOR_CAPACITY);
	Vector(const Vector<T>& other);
	Vector<T>& operator=(const Vector<T>& other);
	~Vector();

	class Iterator;
	Iterator begin();
	Iterator end();
	const Iterator begin() const;
	const Iterator end() const;


	unsigned const size() const;
	unsigned const capacity() const;

	void push_back(T obj);
	void pop();
	void remove(unsigned index);

	T at(unsigned index) const;
	T& at(unsigned index);
	T operator[](unsigned index) const;
	T& operator[](unsigned index);

private:
	void clear();
	void resize(unsigned newCapacity);
};

template <class T>
class Vector<T>::Iterator {
private:
	T* currentContainer;
public:
	Iterator(T* container) : currentContainer(container) {}

	Iterator& operator++() {
		currentContainer++;
		return *this;
	}

	Iterator& operator--() {
		currentContainer--;
		return *this;
	}

	T& operator*() {
		return *currentContainer;
	}

	T operator*() const {
		return *currentContainer;
	}

	T& operator->() {
		return currentContainer;
	}

	T operator->() const {
		return currentContainer;
	}

	bool operator==(const Iterator& other) const {
		return currentContainer == other.currentContainer;
	}

	bool operator!=(const Iterator& other) const {
		return !(*this == other);
	}
};

template <class T>
void Vector<T>::clear() {
	delete[] vContainer;
}

template <class T>
Vector<T>::Vector(unsigned capacity) : vSize(0), vCapacity(capacity) {
	vContainer = new T[capacity];
}

template <class T>
Vector<T>::Vector(const Vector<T>& other) : vSize(other.vSize), vCapacity(other.vCapacity) {
	vContainer = new T[other.vCapacity];
	for (unsigned i = 0; i < other.vSize; i++)
		vContainer[i] = other.vContainer[i];
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
	if (this == &other) return *this;

	if (other.vSize <= vCapacity)
	{
		for (unsigned i = 0; i < other.vSize; i++)
			vContainer[i] = other.vContainer[i];
		vSize = other.vSize;
		return *this;
	}

	vSize = other.vSize;
	vCapacity = other.vCapacity;
	delete[] vContainer;
	vContainer = new T[vCapacity];
	for (unsigned i = 0; i < other.vSize; i++)
		vContainer[i] = other.vContainer[i];

	return *this;
}

template <class T>
inline Vector<T>::~Vector() {
	clear();
}

template <class T>
inline typename Vector<T>::Iterator Vector<T>::begin() {
	return Vector<T>::Iterator(&vContainer[0]);
}

template <class T>
inline typename const Vector<T>::Iterator Vector <T>::begin() const {
	return Vector<T>::Iterator(&vContainer[0]);
}

template <class T>
inline typename Vector<T>::Iterator Vector <T>::end() {
	return Vector<T>::Iterator(&vContainer[vSize]);
}

template <class T>
inline typename const Vector<T>::Iterator Vector <T>::end() const {
	return Vector<T>::Iterator(&vContainer[vSize]);
}

template <class T>
inline unsigned const Vector<T>::size() const {
	return vSize;
}

template <class T>
inline unsigned const Vector<T>::capacity() const {
	return vCapacity;
}

template <class T>
inline T Vector<T>::at(unsigned index) const {
	if (index >= vSize)
		throw std::out_of_range("The index is out of the range of the array.");
	return this->vContainer[index];
}

template <class T>
inline T& Vector<T>::at(unsigned index) {
	if (index >= vSize)
		throw std::out_of_range("The index is out of the range of the array.");
	return this->vContainer[index];
}

template <class T>
inline T Vector<T>::operator[](unsigned index) const {
	if (index >= vSize)
		throw std::out_of_range("The index is out of the range of the array.");
	return this->vContainer[index];
}

template <class T>
inline T& Vector<T>::operator[](unsigned index){
	if (index >= vSize)
		throw std::out_of_range("The index is out of the range of the array.");
	return this->vContainer[index];
}

template <class T>
void Vector<T>::resize(unsigned newCapacity) {
	if (newCapacity <= vCapacity) return;

	vCapacity = newCapacity;
	T* newContainer = new T[vCapacity];
	for (unsigned i = 0; i < vSize; i++)
		newContainer[i] = vContainer[i];
	delete[] vContainer;
	vContainer = newContainer;
}

template <class T>
inline void Vector<T>::push_back(T object) {
	if (vSize >= vCapacity)
		resize(vCapacity * 2);
	this->vContainer[vSize++] = object;
}

template <class T>
inline void Vector<T>::pop() {
	if (this->vSize > 0)
		this->vSize--;
}

template <class T>
inline void Vector<T>::remove(unsigned index) {
	if (index >= vSize)
		throw std::out_of_range("The index is out of the range of the vector.");
	for (int i = index; i < vSize - 1; i++)
		vContainer[i] = vContainer[i + 1];
	vSize--;
}

