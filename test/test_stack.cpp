// тесты для стека

#include <gtest.h>
#include "stack.h"


TEST(stack, can_create_stack)
{
	ASSERT_NO_THROW(stack<int> ());
}

TEST(stack, can_create_stack_with_init_list)
{
	//ASSERT_NO_THROW(stack<int> { 1,2,3 });
}

TEST(stack, can_copy_stack)
{
	stack<int> exp{ 1,2,3 };
	stack<int> act(exp);

	EXPECT_EQ(exp, act);
}

TEST(stack, can_move_stack)
{
	stack<int> exp{ 1,2,3 };
	stack<int> tmp(exp);
	stack<int> act(std::move(tmp));

	EXPECT_EQ(exp, act);
}

TEST(stack, can_assign_stack)
{
	stack<int> exp{ 1,2,3 };
	stack<int> act{ 1,5,2,3 };
	act = exp;
	EXPECT_EQ(exp, act);
}

TEST(stack, can_assign_stack_to_it_self)
{
	stack<int> exp{ 1,2,3 };
	stack<int> act(exp);

	act = act;

	EXPECT_EQ(exp, act);
}

TEST(stack, can_assign_stack_with_move)
{
	stack<int> exp{ 1,2,3 };
	stack<int> tmp(exp);
	stack<int> act{ 1,5,2,3 };
	act = std::move(tmp);
	EXPECT_EQ(exp, act);
}

TEST(stack, can_acces_last_elem)
{
	stack<int> s{ 1,2,3 };
	EXPECT_EQ(3, s.top());
}

TEST(stack, can_get_size)
{
	stack<int> s{ 1,5,10 };
	EXPECT_EQ(3, s.size());
}

TEST(stack, can_push_back_elem)
{
	stack<int> s{ 1 };
	int elem = 10;
	std::pair<int, int> exp(2, elem);

	s.push_back(elem);

	std::pair<int, int> act(s.size(), s.top());
	EXPECT_EQ(exp, act);
}

TEST(stack, can_pop)
{
	stack<int> s{ 2,6 };
	std::pair<int, int> exp(1, 6);

	std::pair<int, int> act(0, s.pop());
	act.first = s.size();
	EXPECT_EQ(exp, act);
}

TEST(stack, cant_pop_empty_elem)
{
	stack<int> s{};
	ASSERT_ANY_THROW(s.pop());
}

TEST(stack, can_check_empty_stack)
{
	stack<int> s{};
	EXPECT_EQ(true, s.is_empty());
	s.push_back(1);
	EXPECT_EQ(false, s.is_empty());
}

TEST(vector, can_sort_vector)
{
	vector<int> v{ 5,2,4,1,0,-3 };
	vector<int> exp{ -3,0,1,2,4,5 };
	v.sort();
	EXPECT_EQ(exp, v);
}
