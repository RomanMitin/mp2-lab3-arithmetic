#pragma once
#include<initializer_list>
#include<utility>

constexpr double multiplier = 1.5;

template<typename T>
class vector
{
private:
	T* mem;
	size_t _top;
	size_t _size;
public:
	vector() :_top(0), mem(new T[10]), _size(10) {}

	vector(std::initializer_list<T> l)
		:_size(l.size()), _top(l.size())
	{
		mem = new T[_size];
		auto it = l.begin();
		for (size_t i = 0; i < _size; i++)
		{
			mem[i] = *it;
			++it;
		}
	}

	vector(const vector& second);
	vector(vector&& second);

	vector& operator=(const vector& second);
	vector& operator=(vector&& second);

	T& operator[](size_t i);
	const T& operator[](size_t i) const;
	bool operator==(const vector& s) const;
	bool operator!=(const vector& s) const;

	void sort();
	void push_back(T elem);
	T pop();
	T& top();
	const T& top() const { return const_cast<const T&>(this->top()); }
	bool empty() const { return _top == 0; }
	size_t size() const { return _top; }
	void clear();

	~vector() { delete[] mem; }
};

template<typename T>
vector<T>::vector(const vector<T>& second)
	:_top(second.size()), _size(second.size())
{
	mem = new T[_size];
	for (size_t i = 0; i < _size; i++)
	{
		mem[i] = second.mem[i];
	}
}

template<typename T>
vector<T>::vector(vector<T>&& second)
	:_top(second.size()), _size(second.size()), mem(second.mem)
{
	second.mem = nullptr;
	second._size = 0;
	second._top = 0;
}

template<typename T>
vector<T>& vector<T>::operator=(const vector<T>& second)
{
	if (this == &second)
	{
		return *this;
	}

	T* tmp = new T[second.size()];
	_size = _top = second.size();
	mem = tmp;
	for (size_t i = 0; i < _top; i++)
	{
		mem[i] = second.mem[i];
	}
}

template<typename T>
vector<T>& vector<T>::operator=(vector<T>&& second)
{
	if (this == &second)
	{
		return *this;
	}

	mem = second.mem;
	_size = second._size;
	_top = second._top;

	second.mem = nullptr;
	second._size = second._top = 0;
}

template<typename T>
T& vector<T>::operator[](size_t i)
{
	return mem[i];
}

template<typename T>
const T& vector<T>::operator[](size_t i) const
{
	return mem[i];
}

template<typename T>
bool vector<T>::operator==(const vector<T>& s) const
{
	if (this == &s)
		return true;
	if (_top != s._top)
		return false;
	for (size_t i = 0; i < _top; i++)
		if (mem[i] != s.mem[i])
			return false;
	return true;
}

template<typename T>
bool vector<T>::operator!=(const vector<T>& s) const
{
	return !(s == *this);
}

template<typename T>
void vector<T>::sort()
{
	for (int i = 0; i < _top; i++)
	{
		bool flag = true;
		for (int j = 0; j < _top - (i + 1); j++)
		{
			if (mem[j] > mem[j + 1]) 
			{
				flag = false;
				std::swap(mem[j], mem[j + 1]);
			}
		}
		if (flag) {
			break;
		}
	}
}

template<typename T>
void vector<T>::push_back(T elem)
{
	if (_top == _size)
	{
		if (size_t(_size * multiplier) != _size)
		{
			_size *= multiplier;
		}
		else
			_size = 1 / (multiplier - 1) + 1;
		T* tmp = new T[_size];
		for (size_t i = 0; i < _top; i++)
		{
			tmp[i] = mem[i];
		}
		mem = tmp;
	}
	mem[_top++] = elem;
}

template<typename T>
T vector<T>::pop()
{
	if (this->empty())
		throw std::exception("vector is empty");

	T result = std::move(mem[--_top]);
	mem[_top].~T();
	return result;
}

template<typename T>
T& vector<T>::top()
{
	if (this->empty())
		throw std::exception("vector is empty");

	return mem[_top - 1];
}

template<typename T>
void vector<T>::clear()
{
	delete[] mem;
	_top = 0;
	_size = 10;
	mem = new T[_size];
}