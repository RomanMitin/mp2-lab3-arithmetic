// тесты для вычисления арифметических выражений

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

TEST(parcer, 1)
{

}

TEST(to_polish, operations)
{
	
}