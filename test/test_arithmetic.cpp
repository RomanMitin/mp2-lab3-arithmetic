// тесты для вычисления арифметических выражений

#include <gtest.h>
#include"..\\include\arithmetic.h"

TEST(correct, brackets)
{
	std::string s= ")(";
	EXPECT_ANY_THROW(correct(s));

	s = "()";
	EXPECT_TRUE(correct(s));

	s = "(()";
	EXPECT_ANY_THROW(correct(s));

	s = "())";
	EXPECT_ANY_THROW(correct(s));

	s = "()()";
	EXPECT_TRUE(correct(s));

	s = "(((";
	EXPECT_ANY_THROW(correct(s));

	s = ")))";
	EXPECT_ANY_THROW(correct(s));

	s = "";
	EXPECT_TRUE(correct(s));

	s = "(()())((()))";
	EXPECT_TRUE(correct(s));
}

TEST(correct, operations)
{
	std::string s = "5++4";
	EXPECT_ANY_THROW(correct(s));

	s = "5+4";
	EXPECT_TRUE(correct(s));

	s = "5+-4";
	EXPECT_TRUE(correct(s));

	s = "-5+-4";
	EXPECT_TRUE(correct(s));

	s = "-5+4";
	EXPECT_TRUE(correct(s));

	s = "-(5+4)";
	EXPECT_TRUE(correct(s));

	s = "5-+4";
	EXPECT_ANY_THROW(correct(s));

	s = "5**4";
	EXPECT_ANY_THROW(correct(s));

	s = "5+";
	EXPECT_ANY_THROW(correct(s));

	s = "3-";
	EXPECT_ANY_THROW(correct(s));

	s = "*3";
	EXPECT_ANY_THROW(correct(s));

	s = "5+2";
	EXPECT_TRUE(correct(s));

	s = "5-2";
	EXPECT_TRUE(correct(s));

	s = "5*2";
	EXPECT_TRUE(correct(s));

	s = "5/2";
	EXPECT_TRUE(correct(s));
}

TEST(correct, numbers)
{
	std::string s = "0.0";
	EXPECT_TRUE(correct(s));

	s = "13";
	EXPECT_TRUE(correct(s));

	s = "0.12";
	EXPECT_TRUE(correct(s));

	s = "0.4500";
	EXPECT_TRUE(correct(s));

	s = "15.312.12";
	EXPECT_ANY_THROW(correct(s));

	s = "15.";
	EXPECT_ANY_THROW(correct(s));

	s = "15..";
	EXPECT_ANY_THROW(correct(s));

	s = ".0.";
	EXPECT_ANY_THROW(correct(s));
}

TEST(correct, brackets2)
{
	std::string s = "x(3+5)";

	EXPECT_ANY_THROW(correct(s));

	s = "2(3+4)";
	EXPECT_ANY_THROW(correct(s));

	s = "(3+4)2";
	EXPECT_ANY_THROW(correct(s));

	s = "(3+4)x";
	EXPECT_ANY_THROW(correct(s));
}

TEST(getnumber, numbers)
{
	std::string s = "3145";
	int i = 0;
	EXPECT_DOUBLE_EQ(3145.0, getnumber(s, i).num.val);

	s = "31.45";
	i = 0;
	EXPECT_DOUBLE_EQ(31.45, getnumber(s, i).num.val);

	s = "0";
	i = 0;
	EXPECT_DOUBLE_EQ(0.0, getnumber(s, i).num.val);

	s = "0.3145";
	i = 0;
	EXPECT_DOUBLE_EQ(0.3145, getnumber(s, i).num.val);

	s = "0.314500000000";
	i = 0;
	EXPECT_DOUBLE_EQ(0.3145, getnumber(s, i).num.val);

	s = "00000.314";
	i = 0;
	EXPECT_DOUBLE_EQ(0.314, getnumber(s, i).num.val);
}

TEST(parcer, var)
{
	std::string s = "x";
	auto act = parcer(s);
	token t1;
	t1.type = Variable;

	t1.var.name = 'x';
	
	vector<token> exp = { t1 };

	EXPECT_EQ(exp, act);
}

TEST(parcer, num)
{
	std::string s = "x";
	auto act = parcer(s);
	token t1;
	t1.type = Variable;

	t1.var.name = 'x';

	vector<token> exp = { t1 };

	EXPECT_EQ(exp, act);
}

TEST(parcer, oper)
{
	std::string s = "+";
	auto act = parcer(s);
	token t1;
	t1.type = Operation;

	t1.oper.op = add;

	vector<token> exp = { t1 };

	EXPECT_EQ(exp, act);
}

TEST(parcer, brack)
{
	std::string s = "(";
	auto act = parcer(s);
	token t1;
	t1.type = Bracket;

	t1.brack.open = true;

	vector<token> exp = { t1 };

	EXPECT_EQ(exp, act);
}

TEST(parcer, func)
{
	std::string s = "-";
	auto act = parcer(s);
	token t1;
	t1.type = Function;

	vector<token> exp = { t1 };

	EXPECT_EQ(exp, act);
}

TEST(parcer, par1)
{
	std::string s = "5+3";
	auto act = parcer(s);
	token t1, t2, t3;
	t1.type = Number;
	t2.type = Operation;
	t3.type = Number;
	t1.num.val = 5.0;
	t2.oper.op = add;
	t3.num.val = 3.0;
	vector<token> exp = { t1,t2,t3 };

	EXPECT_EQ(exp, act);
}

TEST(parcer, par2)
{
	std::string s = "-(5+3)";
	auto act = parcer(s);
	token t1, t2, t3, t0, t4,t5;
	t0.type = Function;
	t1.type = Bracket;
	t2.type = Number;
	t3.type = Operation;
	t4.type = Number;
	t5.type = Bracket;

	t1.brack.open = true;
	t2.num.val = 5.0;
	t3.oper.op = add;
	t4.num.val = 3.0;
	t5.brack.open = false;

	vector<token> exp = { t0,t1,t2,t3,t4,t5 };
	EXPECT_EQ(exp, act);
}

TEST(parcer, par3)
{
	std::string s = "5+-3*2";
	auto act = parcer(s);
	token t1, t2, t3, t0, t4, t5;
	
	t0.type = Number;
	t1.type = Operation;
	t2.type = Function;
	t3.type = Number;
	t4.type = Operation;
	t5.type = Number;

	t0.num.val = 5.0;
	t1.oper = add;
	t3.num.val = 3.0;
	t4.oper = mul;
	t5.num.val = 2.0;

	vector<token> exp = { t0, t1,t2,t3,t4,t5 };

	EXPECT_EQ(exp, act);
}

TEST(to_polish, operations)
{
	std::string s = "3+3";
	token t1, t2, t3;
	t1.type = t3.type = Number;
	t2.type = Operation;

	t2.oper.op = add;
	t1.num.val = t3.num.val = 3.0;

	auto act = to_polish(parcer(s));
	vector<token> exp = { t1,t3,t2 };
	EXPECT_EQ(exp, act);
}

TEST(to_polish, 1)
{
	std::string s = "5+3";
	auto act = to_polish(parcer(s));
	token t1, t2, t3;
	t1.type = Number;
	t2.type = Operation;
	t3.type = Number;
	t1.num.val = 5.0;
	t2.oper.op = add;
	t3.num.val = 3.0;
	vector<token> exp = { t1,t3,t2 };

	EXPECT_EQ(exp, act);
}

TEST(to_polish, 2)
{
	std::string s = "-(5+3)";
	auto act = to_polish(parcer(s));
	token t1, t2, t3, t0, t4, t5;
	t0.type = Function;
	t1.type = Bracket;
	t2.type = Number;
	t3.type = Operation;
	t4.type = Number;
	t5.type = Bracket;

	t1.brack.open = true;
	t2.num.val = 5.0;
	t3.oper.op = add;
	t4.num.val = 3.0;
	t5.brack.open = false;

	vector<token> exp = { t2,t4,t3,t0 };
	EXPECT_EQ(exp, act);
	//EXPECT_EQ(exp, act);
}

TEST(to_polish, 3)
{
	std::string s = "5+-3*2";
	auto act = to_polish(parcer(s));
	token t1, t2, t3, t0, t4, t5;

	t0.type = Number;
	t1.type = Operation;
	t2.type = Function;
	t3.type = Number;
	t4.type = Operation;
	t5.type = Number;

	t0.num.val = 5.0;
	t1.oper = add;
	t3.num.val = 3.0;
	t4.oper = mul;
	t5.num.val = 2.0;

	vector<token> exp = { t0,t3,t5,t4,t2,t1 };

	EXPECT_EQ(exp, act);
}

TEST(compute, 1)
{
	std::string s = "1+1";
	double act = compute(to_polish(parcer(s)));
	EXPECT_EQ(2, act);
}


TEST(compute, 2)
{
	std::string s = "-1+1";
	double act = compute(to_polish(parcer(s)));
	EXPECT_EQ(0, act);
}

TEST(compute, 3)
{
	std::string s = "-(1+1)";
	double act = compute(to_polish(parcer(s)));
	EXPECT_EQ(-2, act);
}

TEST(compute, 4)
{
	std::string s = "1+1*2";
	double act = compute(to_polish(parcer(s)));
	EXPECT_EQ(3, act);
}

TEST(compute, 5)
{
	std::string s = "1+-1";
	double act = compute(to_polish(parcer(s)));
	EXPECT_EQ(0, act);
}

TEST(compute, 6)
{
	std::string s = "1+-1";
	double act = compute(to_polish(parcer(s)));
	EXPECT_EQ(0, act);
}

TEST(compute, 7)
{
	std::string s = "1*-1+-2";
	double act = compute(to_polish(parcer(s)));
	EXPECT_EQ(-3, act);
}

TEST(compute, 8)
{
	std::string s = "(3+1)*-2-2*3";
	double act = compute(to_polish(parcer(s)));
	EXPECT_EQ(-14, act);
}

TEST(compute, complex)
{
	std::string s = "(3 + 4 * 2) - (10 - 2 * 5) + ((1))";
	double act = compute(to_polish(parcer(s)));
	EXPECT_EQ(12, act);
	system("pause");
}