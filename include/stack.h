#include <iostream>
#include <utility>

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
};