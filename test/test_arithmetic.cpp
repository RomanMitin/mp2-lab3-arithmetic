// ����� ��� ���������� �������������� ���������

#include <gtest.h>
#include"arithmetic.h"

TEST(correct, brackets)
{
	std::string s= ")(";
	ASSERT_ANY_THROW(correct(s));

	s = "()";
	ASSERT_TRUE(correct(s));

	s = "(()";
	ASSERT_ANY_THROW(correct(s));

	s = "())";
	ASSERT_ANY_THROW(correct(s));

	s = "()()";
	ASSERT_TRUE(correct(s));

	s = "(((";
	ASSERT_ANY_THROW(correct(s));

	s = ")))";
	ASSERT_ANY_THROW(correct(s));

	s = "";
	ASSERT_TRUE(correct(s));

	s = "(()())((()))";
	ASSERT_TRUE(correct(s));
}

TEST(correct, operations)
{
	std::string s = "5++4";
	ASSERT_ANY_THROW(correct(s));

	s = "5+4";
	ASSERT_TRUE(correct(s));

	s = "5+-4";
	ASSERT_TRUE(correct(s));

	s = "-5+-4";
	ASSERT_TRUE(correct(s));

	s = "-5+4";
	ASSERT_TRUE(correct(s));

	s = "-(5+4)";
	ASSERT_TRUE(correct(s));

	s = "5-+4";
	ASSERT_ANY_THROW(correct(s));

	s = "5**4";
	ASSERT_ANY_THROW(correct(s));

	s = "5+";
	ASSERT_ANY_THROW(correct(s));

	s = "3-";
	ASSERT_ANY_THROW(correct(s));

	s = "*3";
	ASSERT_ANY_THROW(correct(s));

	s = "5+2";
	ASSERT_TRUE(correct(s));

	s = "5-2";
	ASSERT_TRUE(correct(s));

	s = "5*2";
	ASSERT_TRUE(correct(s));

	s = "5/2";
	ASSERT_TRUE(correct(s));
}

TEST(correct, numbers)
{
	std::string s = "0.0";
	ASSERT_TRUE(correct(s));

	s = "13";
	ASSERT_TRUE(correct(s));

	s = "0.12";
	ASSERT_TRUE(correct(s));

	s = "0.4500";
	ASSERT_TRUE(correct(s));

	s = "15.312.12";
	ASSERT_ANY_THROW(correct(s));

	s = "15.";
	ASSERT_ANY_THROW(correct(s));

	s = "15..";
	ASSERT_ANY_THROW(correct(s));

	s = ".0.";
	ASSERT_ANY_THROW(correct(s));
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
	t1.type = Number;
	t2.type = Operation;
	t3.type = Number;
	t4.type = Bracket;
	t5.type = Bracket;

	t1.num.val = 5.0;
	t2.oper.op = add;
	t1.num.val = 3.0;
	t4.brack.open = true;
	t5.brack.open = false;
	vector<token> exp = { t0,t4,t1,t2,t3,t5 };

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
	
}