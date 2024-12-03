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

	/* --- ������������ --- */

	// ����������� (� ������������ ������� memory)
	Queue(size_t Mem = 8)
	{
		mem = Mem;
		data = new T[mem];
		sz = 0;

		startPos = 0;
		endPos = -1;
	};

	// ����������� �����������
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

	// ����������
	~Queue()
	{
		delete[] data;
	}

	// �������� ������������
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

	/* --- ������ --- */
 
	// ���������
	bool operator==(const Queue& Q) const { 
		if (Q.sz != sz) return 0;
		for (int i = 0; i < sz; i++) {
			// ���������� �������� � ������ ����������� - ������������ ��������� �� ����� ������ �� ���������
			if (data[(startPos + i) % mem] != Q.data[(Q.startPos + i) % Q.mem]) {
				return 0;
			}
		}
		return 1;
	}
	bool operator!=(const Queue& Q) const {
		return !(*this == Q);
	}

	// ��������� �������� � ����� ������� � ������ �����������
	void push(T elem)
	{
		// ���� ������� mem ������������, ����������� ��� � 2 ����
		if (sz >= mem) {
			T* tempData = new T[mem * 2];

			// ��������� ����������� � ���������� ���������� ������� ������ ������ ��� ������ ��� 
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

	// �������� �������� � ������� ������� � ������ �����������
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

	// ��������� �������� � ������� ������� 
	T top()
	{
		if (sz < 1) throw "Queue is empty";
		return data[startPos];   
	}

	// ��������� ���������� ���������
	size_t size()
	{
		return sz;
	}

	// ��������� ������� �� �������
	bool empty()
	{
		return sz == 0;
	}
};