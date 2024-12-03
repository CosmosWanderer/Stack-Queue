#include "queue.h"
#include <gtest.h>

TEST(Queue, can_create_queue) {
	EXPECT_NO_THROW(Queue<int> Q);
}

TEST(Queue, can_set_memory) {
	EXPECT_NO_THROW(Queue<int> S(9));
}

TEST(Queue, can_use_copy_constructor) {
	Queue<int> Q1(5);

	EXPECT_NO_THROW(Queue<int> Q2(Q1));

	for (int i = 0; i < 3; i++) {
		Q1.push(i);
	}

	Queue<int> Q2(Q1);
	EXPECT_EQ(Q1, Q2);
}

TEST(Queue, can_use_copy_operator) {
	Queue<int> Q1(5);
	Queue<int> Q2(5);

	EXPECT_NO_THROW(Q1 = Q2);

	for (int i = 0; i < 3; i++) {
		Q1.push(i);
	}

	Q2 = Q1;
	EXPECT_EQ(Q1, Q2);
}

TEST(Queue, equal_queues_are_equal) {
	Queue<int> Q1;
	Queue<int> Q2;

	for (int i = 0; i < 20; i++) {
		Q1.push(i);
		Q2.push(i);
	}

	EXPECT_EQ(Q1, Q2);
}

TEST(Queue, not_equal_queues_are_not_equal) {
	Queue<int> Q1;
	Queue<int> Q2;
	Queue<int> Q3;
	Queue<int> Q4;

	for (int i = 0; i < 20; i++) {
		Q1.push(i);
		Q2.push(i);
		Q3.push(i);
		Q4.push(i);
	}

	Q2.push(21);
	Q3.pop();
	Q4.pop();
	Q4.push(21);

	bool isEq1 = (Q1 == Q2), isEq2 = (Q1 == Q3), isEq3 = (Q1 == Q4);

	EXPECT_FALSE(isEq1);
	EXPECT_FALSE(isEq2);
	EXPECT_FALSE(isEq3);
}

TEST(Queue, cycles_do_not_affect_equality) {
	Queue<int> Q1(6);
	Q1.push(1);
	Q1.push(2);
	Q1.push(1);
	Q1.push(2);
	Q1.push(1);
	Q1.push(2);
	// 1 2 1 2 1 2
	Q1.pop();
	Q1.pop();
	Q1.pop();
	Q1.pop();
	// _ _ _ _ 1 2
	Q1.push(1);
	Q1.push(2);
	// 1 2 _ _ 1 2
	
	Queue<int> Q2(6);
	Q2.push(1);
	Q2.push(2); 
	Q2.push(1);
	Q2.push(2);
	// 1 2 1 2 _ _

	EXPECT_EQ(Q1, Q2);
}

TEST(Queue, can_push_element) {
	Queue<int> Q(5);

	for (int i = 0; i < 10; i++) Q.push(i);

	EXPECT_NO_THROW(for (int i = 0; i < 10; i++) Q.pop());
}

TEST(Queue, can_pop_element) {
	Queue<int> Q(5);

	for (int i = 0; i < 10; i++) Q.push(i);

	EXPECT_NO_THROW(for (int i = 0; i < 10; i++) Q.pop());
}

TEST(Queue, cant_use_pop_on_empty_queue) {
	Queue<int> Q(5);

	EXPECT_ANY_THROW(Q.pop());
}

TEST(Queue, can_get_top_element) {
	Queue<int> Q(5);

	Q.push(4);

	EXPECT_NO_THROW(Q.top());

	Q.push(7);
	Q.push(3);

	EXPECT_EQ(Q.top(), 4);
}

TEST(Queue, cant_get_top_element_from_empty_queue) {
	Queue<int> Q;

	EXPECT_ANY_THROW(Q.top());
}

TEST(Queue, can_get_size) {
	Queue<int> Q(10);

	EXPECT_EQ(Q.size(), 0);

	Q.push(1);
	Q.push(2);
	Q.push(3);

	EXPECT_EQ(Q.size(), 3);
}

TEST(Queue, can_check_for_emptiness) {
	Queue<int> Q(10);

	EXPECT_TRUE(Q.empty());

	Q.push(1);

	EXPECT_FALSE(Q.empty());

	Q.pop();

	EXPECT_TRUE(Q.empty());
}

TEST(Queue, push_and_pop_elements_in_right_order) {
	Queue<int> Q(3);

	// Звёздочки - текущий top элемент

	Q.push(1);
	EXPECT_EQ(Q.top(), 1);
	Q.push(2);
	EXPECT_EQ(Q.top(), 1);
	Q.push(3);
	EXPECT_EQ(Q.top(), 1);
	// *1* 2 3
	Q.push(4);
	EXPECT_EQ(Q.top(), 1);
	Q.push(5);
	EXPECT_EQ(Q.top(), 1); 
	Q.push(6);
	EXPECT_EQ(Q.top(), 1); 
	// *1* 2 3 4 5 6

	Q.pop();
	EXPECT_EQ(Q.top(), 2);
	Q.pop();
	EXPECT_EQ(Q.top(), 3);
	Q.pop();
	EXPECT_EQ(Q.top(), 4);
	// _ _ _ *4* 5 6

	Q.push(7);
	EXPECT_EQ(Q.top(), 4);
	Q.push(8);
	EXPECT_EQ(Q.top(), 4);
	// 7 8 _ *4* 5 6
	Q.pop();
	EXPECT_EQ(Q.top(), 5);
	// 7 8 _ _ *5* 6

	Q.push(9);
	EXPECT_EQ(Q.top(), 5);
	Q.push(10);
	// 7 8 9 10 *5* 6
	EXPECT_EQ(Q.top(), 5);

	Q.push(11);
	EXPECT_EQ(Q.top(), 5);
	// *5* 6 7 8 9 10 11 _ _... 
	Q.pop();
	EXPECT_EQ(Q.top(), 6);
	Q.pop();
	EXPECT_EQ(Q.top(), 7);
	Q.pop();
	EXPECT_EQ(Q.top(), 8);
	Q.pop();
	EXPECT_EQ(Q.top(), 9);
	Q.pop();
	EXPECT_EQ(Q.top(), 10);
	Q.pop();
	EXPECT_EQ(Q.top(), 11);
}