// объ€вление и реализаци€ шаблонного стека
#pragma once
#include<initializer_list>
#include<utility>
#include"..\\include\vector.h"

template<typename T, class Container = vector<T>>
class stack
{
private:
	Container v;
public:
	stack() :v() {}

	stack(std::initializer_list<T> l) :v(l) {}
	stack(const stack& second) :v(second.v) {}
	stack(stack&& second) :v(std::move(second.v)) {}

	stack& operator=(const stack& second) { v = second.v; return *this; }
	stack& operator=(stack&& second) { v = std::move(second.v); return *this; }

	bool operator==(const stack& s) const { return v == s.v; }
	bool operator!=(const stack& s) const { return v != s.v; }

	void push_back(T elem) { v.push_back(elem); }	// - вставка элемента 
	T pop() { return v.pop(); }	// - извлечение элемента 
	T& top() { return v.top(); }	// - просмотр верхнего элемента (без удалени€)
	const T& top() const { return v.top(); }
	bool is_empty() const { return v.empty(); }	// - проверка на пустоту
	size_t size() const { return v.size(); }	// - получение количества элементов в стеке
	void clear() { v.clear(); };	// - очистка стека

	~stack() {};
};