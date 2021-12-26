// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#pragma once
#include<string>
#include<iostream>
#include<exception>
#include"..\\include\stack.h"

enum token_type { Variable, Number, Operation, Bracket, Function };
enum oper_type { add, sub, mul, divide };

class variable
{
public:
	char name;
	double value;

	variable(char c = '\0', double val = INFINITY) :name(c), value(val)  {}

	bool operator==(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
	bool operator!=(char c) { return !(*this == c); }

	friend std::ostream& operator<<(std::ostream& str, const variable v) { str << v.name; return str; }
};

class number
{
public:
	double val;
	number(double val = 0.0) :val(val) {}

	bool operator==(char c) { return c >= '0' && c <= '9' || c == '.'; }
	bool operator!=(char c) { return !(*this == c); }

	friend std::ostream& operator<<(std::ostream& str, const number v) { str << v.val;  return str; }
};

class operation
{
public:
	oper_type op;
	operation(oper_type op = add) :op(op) {}
	operation(char oper);
	double operator()(double a, double b);

	bool operator==(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }
	bool operator!=(char c) { return !(*this == c); }

	friend std::ostream& operator<<(std::ostream& str, const operation v);
};

class bracket
{
public:
	bool open;
	bracket(bool open = false) :open(open) {}

	bool operator==(char c) { return c == '(' || c == ')'; }
	bool operator!=(char c) { return !(*this == c); }

	friend std::ostream& operator<<(std::ostream& str, const bracket v);
};

class function
{
	token_type get_token_name() { return Function; }

	friend std::ostream& operator<<(std::ostream& str, const function f) { str << '-'; return str; }
};

//typedef std::variant<variable, number, operation, bracket> token;

class token
{
public:
	variable var;
	number num;
	operation oper;
	bracket brack;
	function func;

	token_type type;

	token& operator=(const token& sec);

	bool operator==(const token& sec) const;
	bool operator!=(const token& sec) const;
};

std::ostream& operator<<(std::ostream& str, const token v);

bool correct(std::string);

int oper_priority(operation op);

token getnumber(std::string s, int& index);

vector<token> parcer(std::string);

vector<token> to_polish(vector<token>);

void get_variables(vector<token>&);

double compute(vector<token>);

class exception:public std::exception
{
public:
	int index;
	exception(std::string s, int index = -1) :std::exception(s.c_str()), index(index) {}
};