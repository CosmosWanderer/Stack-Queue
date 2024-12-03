#include <iostream>
#include <utility>

template <class T>
class Queue
{
	T* data;
	size_t sz;
	size_t mem;

	int startPos;
	int endPos;

public:

	/* --- Конструкторы --- */

	// Конструктор (с возможностью задания memory)
	Queue(size_t Mem = 8)
	{
		mem = Mem;
		data = new T[mem];
		sz = 0;

		startPos = 0;
		endPos = -1;
	};

	// Конструктор копирования
	Queue(const Queue& Q)
	{
		sz = Q.sz;
		mem = Q.mem;
		data = new T[mem];
		for (int i = 0; i < sz; i++) {
			data[i] = Q.data[i];
		}

		startPos = Q.startPos;
		endPos = Q.endPos;
	}

	// Деструктор
	~Queue()
	{
		delete[] data;
	}

	// Оператор присваивания
	Queue& operator=(const Queue& Q)
	{
		if (this != &Q) {
			sz = Q.sz;
			mem = Q.mem;
			data = new T[mem];
			for (int i = 0; i < sz; i++) {
				data[i] = Q.data[i];
			}

			startPos = Q.startPos;
			endPos = Q.endPos;
		}

		return *this;
	}

	/* --- Методы --- */
 
	// Сравнение
	bool operator==(const Queue& Q) const { 
		if (Q.sz != sz) return 0;
		for (int i = 0; i < sz; i++) {
			// Сравниваем элементы с учетом цикличности - расположение элементов не будет влиять на равенство
			if (data[(startPos + i) % mem] != Q.data[(Q.startPos + i) % Q.mem]) {
				return 0;
			}
		}
		return 1;
	}
	bool operator!=(const Queue& Q) const {
		return !(*this == Q);
	}

	// Помещение элемента в конец очереди с учётом цикличности
	void push(T elem)
	{
		// Если текущий mem недостаточен, увеличиваем его в 2 раза
		if (sz >= mem) {
			T* tempData = new T[mem * 2];

			// Учитываем цикличность и возвращаем правильный порядок просто потому что почему нет 
			for (size_t i = 0; i < sz; ++i) {
				tempData[i] = data[(startPos + i) % mem];
			}

			delete[] data;
			data = tempData;

			mem = mem * 2;
			startPos = 0;
			endPos = sz - 1; 
		}

		
		endPos = (endPos + 1) % mem;
		data[endPos] = elem;
		sz++;
	}

	// Удаление элемента с вершины очереди с учётом цикличности
	void pop()
	{
		if (sz < 1) throw "Queue is already empty";
		
		startPos = (startPos + 1) % mem;
		sz--;

		if (sz == 0) {
			startPos = 0;
			endPos = -1;
		}
	}

	// Получение значения с вершины очереди 
	T top()
	{
		if (sz < 1) throw "Queue is empty";
		return data[startPos];   
	}

	// Получение количества элементов
	size_t size()
	{
		return sz;
	}

	// Проверить очередь на пустоту
	bool empty()
	{
		return sz == 0;
	}
};