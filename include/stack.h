// ���������� � ���������� ���������� �����
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

	void push_back(T elem) { v.push_back(elem); }	// - ������� �������� 
	T pop() { return v.pop(); }	// - ���������� �������� 
	T& top() { return v.top(); }	// - �������� �������� �������� (��� ��������)
	const T& top() const { return v.top(); }
	bool is_empty() const { return v.empty(); }	// - �������� �� �������
	size_t size() const { return v.size(); }	// - ��������� ���������� ��������� � �����
	void clear() { v.clear(); };	// - ������� �����

	~stack() {};
};