// реализация функций и классов для вычисления арифметических выражений
#include"..\\include\arithmetic.h"


double operation::operator()(double a, double b)
{
	switch (this->op)
	{
	case add:
		return a + b;
		break;
	case sub:
		return a - b;
		break;
	case mul:
		return a * b;
		break;
	case divide:
		return a / b;
		break;
	}
}

std::ostream& operator<<(std::ostream& str, const operation oper)
{
	switch (oper.op)
	{
	case add:
		str << '+';
		break;
	case sub:
		str << '-';
		break;
	case mul:
		str << '*';
		break;
	case divide:
		str << '/';
		break;
	}
	return str;
}

std::ostream& operator<<(std::ostream& str, const bracket br)
{
	if (br.open)
		str << '(';
	else
		str << ')';
	return str;
}

token& token::operator=(const token& sec)
{
	if (this == &sec)
		return *this;

	type = sec.type;
	switch (type)
	{
	case Variable:
		var = sec.var;
		break;
	case Number:
		num = sec.num;
		break;
	case Operation:
		oper = sec.oper;
		break;
	case Bracket:
		brack = sec.brack;
		break;
	case Function:
		break;
	}
}

std::ostream& operator<<(std::ostream& str, const token tok)
{
	switch (tok.type)
	{
	case Variable:
		str << tok.var;
		break;
	case Number:
		str << tok.num;
		break;
	case Operation:
		str << tok.oper;
		break;
	case Bracket:
		str << tok.brack;
	}
}

bool correct(std::string input)
{
	int count_brack = 0;
	int open_brack_ind = -1;
	bool is_open = false;

	for (int i = 0; i < input.size(); i++)
	{
		if (variable() != input[i] && number() != input[i] && operation() != input[i] && bracket() != input[i])
			throw exception("Wrong symbol", i);
		if (bracket() == input[i])
		{
			if (input[i] == '(')
			{
				if (!count_brack)
					open_brack_ind = i;
				count_brack++;
				is_open = true;
			}
			else
			{
				if (count_brack == 0)
					throw exception("The opening parenthesis is missing", i);
				count_brack--;
			}
		}
		if (i != 0 && variable() == input[i] && variable() == input[i - 1])
			throw exception("Name for variable is too long, use one symbol for variable", i);
	}
	if (is_open)
		throw exception("The closing parenthesis is missing", open_brack_ind);
}

token getnumber(std::string s, int& index)
{
	double result = 0.0;
	while (index < s.size() && s[index] >= '0' && s[index] <= '9')
	{
		result *= 10.0;
		result += s[index] - '0';
		index++;
	}
	token tmp;
	tmp.type = Variable;
	tmp.var = variable(result);
	return tmp;
}

int oper_priority(operation type)
{
	switch (type.op)
	{
	case add:
	case sub:
		return 2;
	case mul:
	case divide:
		return 1;
	}
}

vector<token> to_polish(vector<token> vec)
{
	vector<token> result;
	stack<token> st;

	for (int i = 0; i < vec.size(); i++)
	{
		switch (vec[i].type)
		{
		case Variable:
		case Number:
			result.push_back(vec[i]);
			break;
		case Operation:
			while (oper_priority(vec[i].oper) >= oper_priority(st.top().oper))
				result.push_back(st.pop());
			st.push_back(vec[i]);
			break;
		case Bracket:
			if (vec[i].brack.open)
			{
				st.push_back(vec[i]);
			}
			else
			{
				while (st.top().brack != '(')
					result.push_back(st.pop());
				st.pop();
			}
			break;
		}
	}

}

bool check_names(vector<token*>& vars)
{
	for (int i = 0; i < vars.size(); i++)
		if (vars[i]->var.name == '\0')
			return false;
	return true;
}

void get_variables(vector<token>& tok)
{
	vector<token*> vars;

	for (int i = 0; i < tok.size(); i++)
		if (tok[i].type == Variable)
			vars.push_back(&tok[i]);

	std::string name;

	while (check_names(vars))
	{
		std::getline(std::cin, name);
		if (variable() != name[0])
		{
			std::cout << "Wrong name for variable\n";
			continue;
		}
		int i = 1;
		double value;
		while (i < name.size() && name[i] == ' ' || name[i] == '=')
		{
		
				if (number() == name[i])
					value = getnumber(name, i).var.value;
			i++;
		}
		if (i != name.size())
		{
			std::cout << "Wrong symbol in number\n";
			continue;
		}

		for (int i = 0; i < vars.size(); i++)
		{
			if (vars[i]->var.name == name[0])
			{
				vars[i]->var.value = value;
				break;
			}
		}
	}

}

double compute(vector<token> expr)
{
	stack<double> result;

	for (int i = 0; i < expr.size(); i++)
	{
		switch (expr[i].type)
		{
		case Variable:
			result.push_back(expr[i].var.value);
			break;
		case Number:
			result.push_back(expr[i].num.val);
			break;
		case Operation:
			double tmp = result.pop();
			tmp = expr[i].oper.operator()(tmp, result.pop());
			result.push_back(tmp);
			break;
		default:
			break;
		}
	}
	return result.pop();
}

//double operation::operator()(double a, double b)
//{
//	switch (this->op)
//	{
//	case add:
//		return a + b;
//		break;
//	case sub:
//		return a - b;
//		break;
//	case mul:
//		return a * b;
//		break;
//	case div:
//		return a / b;
//		break;
//	}
//}
//
//token getnumber(std::string s,int& index)
//{
//	double result = 0.0;
//	while (index < s.size() && s[index] >= '0' && s[index] <= '9')
//	{
//		result *= 10.0;
//		result += s[index] - '0';
//		index++;
//	}
//
//	//if (s[index] == 'e')
//	//{
//	//	if (s[++index] == '+')
//	//	{
//	//		double power = 0.0;
//	//		while (index < s.size() && s[index] >= '0' && s[index] <= '9')
//	//		{
//	//			power *= 10.0;
//	//			power += s[index] - '0';
//	//			index++;
//	//		}
//	//	}
//	//}
//
//	if (s[index] == '.')
//	{
//		index++;
//	}
//	else
//	{
//		return number(result);
//	}
//
//	double power = 0.1;
//	while (index < s.size() && s[index] >= '0' && s[index] <= '9')
//	{
//		result += (s[index] - '0') * power;
//		power *= 0.1;
//		index++;
//	}
//	
//	
//	return number(result);
//}
//
//token getvariable(std::string s, int& index)
//{
//	std::string name;
//	while (index < s.size() && (s[index] >= 'a' && s[index] <= 'z' || s[index] >= 'A' && s[index] <= 'Z'))
//	{
//		name.push_back(s[index]);
//		index++;
//	}
//	std::string value;
//	std::getline(std::cin, value);
//	int i = 0;
//	while (i < value.size() && (value[i] < '0' || value[i]>'9'))
//		i++;
//	if (i == value.size())
//	{
//		auto tmp = std::string("No value for variable ") + name;
//		throw std::exception(tmp.c_str());
//	}
//}
//
//token getbracket(std::string s, int& index)
//{
//	index++;
//	token result;
//	if (s[index] == '(')
//		result = bracket(true);
//	if (s[index] == ')')
//		result = bracket(false);
//	return result;
//}
//
//token getoperation(std::string s, int& index)
//{
//	index++;
//	token tok;
//	switch (s[index])
//	{
//	case '+':
//		tok = operation(add);
//		break;
//	case '-':
//		tok = operation(sub);
//		break;
//	case '*':
//		tok = operation(mul);
//		break;
//	case '/':
//		tok = operation(div);
//		break;
//	}
//	return tok;
//}
//
//token check(std::string s, int& index)
//{
//	if (s[index] >= '0' && s[index] <= '9')
//		return getnumber(s, index);
//
//	if (s[index] >= 'a' && s[index] <= 'z' || s[index] >= 'A' && s[index] <= 'Z')
//		return getvariable(s, index);
//
//	if (s[index] == '(' || s[index] == ')')
//		return getbracket(s, index);
//
//	if (s[index] == '+' || s[index] == '-' || s[index] == '*' || s[index] == '+') // Обработать функции
//		return getoperation(s, index);
//
//	throw std::exception("Wrond simbol");
//}
//
//
//stack<token> parcer(std::string s)
//{
//	stack<token> result;
//
//	int count = 0;
//
//	for (int i = 0; i < s.size(); i++)
//	{
//		result.push_back(check(s, i));
//		token tok = result.top();
//		if (tok.index() == Bracket)
//		{
//			if (std::get<bracket>(tok).open)
//			{
//				count++;
//			}
//			else
//			{
//				if (!count)
//					count--;
//				else
//					throw std::exception("Incorrect bracket sequence");
//			}
//		}
//	}
//}
