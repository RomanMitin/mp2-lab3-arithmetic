// тесты для вычисления арифметических выражений

#include <gtest.h>
#include"arithmetic.h"

TEST(correct, brackets)
{
	std::string s= ")(";
	ASSERT_FALSE(correct(s));

	s = "()";
	ASSERT_TRUE(correct(s));

	s = "(()";
	ASSERT_FALSE(correct(s));

	s = "())";
	ASSERT_FALSE(correct(s));

	s = "()()";
	ASSERT_TRUE(correct(s));

	s = "(((";
	ASSERT_FALSE(correct(s));

	s = ")))";
	ASSERT_FALSE(correct(s));

	s = "";
	ASSERT_TRUE(correct(s));

	s = "(()())((()))";
	ASSERT_TRUE(correct(s));
}

TEST(correct, operations)
{
	std::string s = "5++4";
	ASSERT_FALSE(correct(s));

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
	ASSERT_FALSE(correct(s));

	s = "5**4";
	ASSERT_FALSE(correct(s));

	s = "5+";
	ASSERT_FALSE(correct(s));

	s = "3-";
	ASSERT_FALSE(correct(s));

	s = "*3";
	ASSERT_FALSE(correct(s));

	s = "5+2";
	ASSERT_TRUE(correct(s));

	s = "5-2";
	ASSERT_TRUE(correct(s));

	s = "5*2";
	ASSERT_TRUE(correct(s));

	s = "5/2";
	ASSERT_TRUE(correct(s));
}