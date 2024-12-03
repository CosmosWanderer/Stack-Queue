#include <iostream>
#include <utility>
#include <vector>

template <class T>
class Stack 
{
	T* data;
	size_t sz;
	size_t mem;

public:

	/* --- ������������ --- */
	
	// ����������� (� ������������ ������� memory)
	Stack(size_t Mem = 8) 
	{
		mem = Mem;
		data = new T[mem]; 
		sz = 0;
	};

	// ����������� �����������
	Stack(const Stack& S) 
	{
		sz = S.sz;
		mem = S.mem;
		data = new T[mem];
		for (int i = 0; i < sz; i++) {
			data[i] = S.data[i];
		}
	}

	// ����������
	~Stack() 
	{
		delete[] data;
	}

	// �������� ������������
	Stack& operator=(const Stack& S) 
	{
		if (this != &S) {
			sz = S.sz;
			mem = S.mem;
			data = new T[mem];
			for (int i = 0; i < sz; i++) {
				data[i] = S.data[i];
			}
		}

		return *this;
	}

	/* --- ������ --- */

	// ���������
	bool operator==(const Stack& S) const {
		if (S.sz != sz) return 0;
		for (int i = 0; i < sz; i++) if (data[i] != S.data[i]) return 0;
		return 1;
	}
	bool operator!=(const Stack& S) const {
		return !(*this == S);
	}

	// ��������� �������� �� ������� �����
	void push(T elem) 
	{
		// ���� ������� mem ������������, ����������� ��� � 2 ����
		if (sz >= mem) {
			T* tmpData = new T[mem * 2];
			for (int i = 0; i < sz; i++) { 
				tmpData[i] = data[i]; 
			}
			std::swap(data, tmpData);
			delete[] tmpData;
			mem = mem * 2;

		}
		data[sz] = elem; 
		sz++;
	}

	// �������� �������� � ������� �����
	void pop() 
	{
		if (sz < 1) throw "Stack is already empty";
		sz--;
	}

	// ��������� �������� � ������� ����� 
	T top() 
	{
		if (sz < 1) throw "Stack is empty";
		return data[sz - 1]; 
	}

	// ��������� ���������� ��������
	size_t size() 
	{
		return sz;
	}

	// ��������� ���� �� �������
	bool empty() 
	{
		return sz == 0;
	}




	/* --- ������ --- */
 
	// ���������� �� ���� ������. �.�. ��� ������ ������, ����� �� ������������ � ������ ������������� ������ �����
	std::vector<int> stackSort(std::vector<int> vec) {
		Stack<int> S1;
		Stack<int> S2;

		for (int i = 0; i < vec.size(); i++) {
			while (!S1.empty() && S1.top() < vec[i]) {  
				S2.push(S1.top());
				S1.pop();
			}
			S1.push(vec[i]);
			while (!S2.empty()) {
				S1.push(S2.top());
				S2.pop();
			}
		}

		std::vector<int> sortedVec;

		while (!S1.empty()) {
			sortedVec.push_back(S1.top());
			S1.pop();
		}

		return sortedVec;
	}

	// ����������� ������ � ����� test_stack.cpp
};