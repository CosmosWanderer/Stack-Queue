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

	/* --- Конструкторы --- */
	
	// Конструктор (с возможностью задания memory)
	Stack(size_t Mem = 8) 
	{
		mem = Mem;
		data = new T[mem]; 
		sz = 0;
	};

	// Конструктор копирования
	Stack(const Stack& S) 
	{
		sz = S.sz;
		mem = S.mem;
		data = new T[mem];
		for (int i = 0; i < sz; i++) {
			data[i] = S.data[i];
		}
	}

	// Деструктор
	~Stack() 
	{
		delete[] data;
	}

	// Оператор присваивания
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

	/* --- Методы --- */

	// Сравнение
	bool operator==(const Stack& S) const {
		if (S.sz != sz) return 0;
		for (int i = 0; i < sz; i++) if (data[i] != S.data[i]) return 0;
		return 1;
	}
	bool operator!=(const Stack& S) const {
		return !(*this == S);
	}

	// Помещение элемента на вершину стека
	void push(T elem) 
	{
		// Если текущий mem недостаточен, увеличиваем его в 2 раза
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

	// Удаление элемента с вершины стека
	void pop() 
	{
		if (sz < 1) throw "Stack is already empty";
		sz--;
	}

	// Получение значения с вершины стека 
	T top() 
	{
		if (sz < 1) throw "Stack is empty";
		return data[sz - 1]; 
	}

	// Получение количества элемента
	size_t size() 
	{
		return sz;
	}

	// Проверить стек на пустоту
	bool empty() 
	{
		return sz == 0;
	}




	/* --- Задача --- */
 
	// Сортировка на двух стеках. Т.к. это просто задача, решил не запариваться и просто отсортировать вектор интов
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

	// Демострация работы в конце test_stack.cpp
};