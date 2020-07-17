#pragma once
#include <iostream>
const int DEFAULT_VECTOR_CAPACITY = 20;

template<class T>
class Vector
{
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

	void push_back(T obj);
	void pop();
	void remove(unsigned index);

	T at(unsigned index) const;
	T& at(unsigned index);
	T operator[](unsigned index) const;
	T& operator[](unsigned index);

private:
	T* data;
	unsigned vSize;
	unsigned vCapacity;

	void clear();
	void resize(unsigned newCapacity);
};

template <class T>
class Vector<T>::Iterator
{
public:
	Iterator(T* data) : currentData(data) {}

	Iterator& operator++()
	{
		currentData++;
		return *this;
	}

	Iterator& operator--()
	{
		currentData--;
		return *this;
	}

	T& operator*()
	{
		return *currentData;
	}

	T operator*() const
	{
		return *currentData;
	}

	T& operator->()
	{
		return currentData;
	}

	T operator->() const
	{
		return currentData;
	}

	bool operator==(const Iterator& other) const
	{
		return currentData == other.currentData;
	}

	bool operator!=(const Iterator& other) const
	{
		return !(*this == other);
	}

private:
	T* currentData;
};

template <class T>
void Vector<T>::clear()
{
	delete[] this->data;
	this->vCapacity = 0;
	this->vSize = 0;
}

template <class T>
Vector<T>::Vector(unsigned vCapacity)
	: vSize(0), vCapacity(vCapacity)
{
	data = new T[vCapacity];
}

template <class T>
Vector<T>::Vector(const Vector<T>& other)
	: vSize(other.vSize), vCapacity(other.vCapacity)
{
	data = new T[other.vCapacity];
	for (unsigned i = 0; i < other.vSize; i++)
	{
		data[i] = other.data[i];
	}
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this == &other)
	{
		return *this;
	}

	if (other.vSize > this->vCapacity)
	{
		this->vSize = other.vSize;
		this->vCapacity = other.vCapacity;
		delete[] data;
		data = new T[vCapacity];
	}

	for (unsigned i = 0; i < other.vSize; i++)
	{
		data[i] = other.data[i];
	}
	vSize = other.vSize;
	return *this;
}

template <class T>
inline Vector<T>::~Vector()
{
	clear();
}

template <class T>
inline typename Vector<T>::Iterator Vector<T>::begin()
{
	return Vector<T>::Iterator(&data[0]);
}

template <class T>
inline const typename Vector<T>::Iterator Vector <T>::begin() const
{
	return Vector<T>::Iterator(&data[0]);
}

template <class T>
inline typename Vector<T>::Iterator Vector <T>::end()
{
	return Vector<T>::Iterator(&data[vSize]);
}

template <class T>
inline const typename Vector<T>::Iterator Vector <T>::end() const
{
	return Vector<T>::Iterator(&data[vSize]);
}

template <class T>
inline unsigned const Vector<T>::size() const
{
	return vSize;
}

template <class T>
inline T Vector<T>::at(unsigned index) const
{
	if (index >= vSize)
	{
		throw std::out_of_range("The index is out of the range of the array.");
	}

	return this->data[index];
}

template <class T>
inline T& Vector<T>::at(unsigned index)
{
	if (index >= vSize)
	{
		throw std::out_of_range("The index is out of the range of the array.");
	}

	return this->data[index];
}

template <class T>
inline T Vector<T>::operator[](unsigned index) const
{
	if (index >= vSize)
	{
		throw std::out_of_range("The index is out of the range of the array.");
	}

	return this->data[index];
}

template <class T>
inline T& Vector<T>::operator[](unsigned index)
{
	if (index >= vSize)
	{
		throw std::out_of_range("The index is out of the range of the array.");
	}

	return this->data[index];
}

template <class T>
void Vector<T>::resize(unsigned newCapacity)
{
	if (newCapacity <= this->vCapacity)
	{
		return;
	}

	this->vCapacity = newCapacity;
	T* newdata = new T[newCapacity];
	for (unsigned i = 0; i < vSize; i++)
	{
		newdata[i] = this->data[i];
	}
	delete[] this->data;
	this->data = newdata;
}

template <class T>
inline void Vector<T>::push_back(T object)
{
	if (vSize >= this->vCapacity)
	{
		resize(this->vCapacity * 2);
	}

	this->data[this->vSize] = object;
	this->vSize++;
}

template <class T>
inline void Vector<T>::pop()
{
	if (this->vSize > 0)
	{
		this->vSize--;
	}
}

template <class T>
inline void Vector<T>::remove(unsigned index)
{
	if (index >= this->vSize)
	{
		throw std::out_of_range("The index is out of the range of the vector.");
	}
	for (int i = index; i < vSize - 1; i++)
	{
		data[i] = data[i + 1];
	}
	this->vSize--;
}

