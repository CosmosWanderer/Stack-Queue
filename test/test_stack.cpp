#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_stack) {
	EXPECT_NO_THROW(Stack<int> S);
}

TEST(Stack, can_set_memory) {
	EXPECT_NO_THROW(Stack<int> S(9));
}

TEST(Stack, can_use_copy_constructor) {
	Stack<int> S1(5);

	EXPECT_NO_THROW(Stack<int> S2(S1));
	
	for (int i = 0; i < 3; i++) {
		S1.push(i);
	}

	Stack<int> S2(S1);
	EXPECT_EQ(S1, S2);
}	

TEST(Stack, can_use_copy_operator) {
	Stack<int> S1(5);
	Stack<int> S2(5);

	EXPECT_NO_THROW(S1 = S2);

	for (int i = 0; i < 3; i++) {
		S1.push(i);
	}

	S2 = S1;
	EXPECT_EQ(S1, S2);
}

TEST(Stack, equal_stacks_are_equal) {
	Stack<int> S1;
	Stack<int> S2;

	for (int i = 0; i < 20; i++) {
		S1.push(i);
		S2.push(i);
	}

	EXPECT_EQ(S1, S2);
}

TEST(Stack, not_equal_stacks_are_not_equal) {
	Stack<int> S1;
	Stack<int> S2;
	Stack<int> S3;
	Stack<int> S4;

	for(int i = 0; i < 20; i++) {
		S1.push(i);
		S2.push(i);
		S3.push(i);
		S4.push(i);
	}

	S2.push(21);
	S3.pop();
	S4.pop();
	S4.push(21);

	bool isEq1 = (S1 == S2), isEq2 = (S1 == S3), isEq3 = (S1 == S4);

	EXPECT_FALSE(isEq1);
	EXPECT_FALSE(isEq2);
	EXPECT_FALSE(isEq3);
}

TEST(Stack, can_push_element) {
	Stack<int> S(3);

	EXPECT_NO_THROW(for (int i = 0; i < 10; i++) S.push(i));
}

TEST(Stack, can_pop_element) {
	Stack<int> S(5);

	for (int i = 0; i < 10; i++) S.push(i);

	EXPECT_NO_THROW(for (int i = 0; i < 10; i++) S.pop());
}

TEST(Stack, cant_use_pop_on_empty_stack) {
	Stack<int> S(5);

	EXPECT_ANY_THROW(S.pop());
}

TEST(Stack, can_get_top_element) {
	Stack<int> S(5);

	S.push(4);

	EXPECT_NO_THROW(S.top());

	S.push(7);
	S.push(3);

	EXPECT_EQ(S.top(), 3);
}
 
TEST(Stack, cant_get_top_element_from_empty_stack) {
	Stack<int> S;

	EXPECT_ANY_THROW(S.top());
}

TEST(Stack, can_get_size) {
	Stack<int> S(10);

	EXPECT_EQ(S.size(), 0);

	S.push(1);
	S.push(2);
	S.push(3);

	EXPECT_EQ(S.size(), 3);
}

TEST(Stack, can_check_for_emptiness) {
	Stack<int> S(10);

	EXPECT_TRUE(S.empty());

	S.push(1);

	EXPECT_FALSE(S.empty());

	S.pop();

	EXPECT_TRUE(S.empty());
}

TEST(Stack, push_and_pop_elements_in_right_order) {
	Stack<int> S(3);

	// Звёздочки - текущий top элемент
	S.push(1);
	EXPECT_EQ(S.top(), 1);
	S.push(2);
	EXPECT_EQ(S.top(), 2);
	S.push(3);
	EXPECT_EQ(S.top(), 3);
	// 1 2 *3*
	S.push(4);
	EXPECT_EQ(S.top(), 4);
	S.push(5);
	EXPECT_EQ(S.top(), 5);
	S.push(6);
	EXPECT_EQ(S.top(), 6);
	// 1 2 3 4 5 *6*

	S.pop();
	EXPECT_EQ(S.top(), 5);
	S.pop();
	EXPECT_EQ(S.top(), 4);
	S.pop();
	EXPECT_EQ(S.top(), 3);
	// 1 2 *3* _ _ _
}