#pragma once

template <typename T> class cList {

	T* items;
	int magnitude;
	int current;
public:
	cList() {
		items = new T[1];
		magnitude = 1;
		current = 0;
	}

	~cList() {
		delete[] items;
	}

	void Add(T element) {
		if (current == magnitude) {
			T* temp = new T[2 * magnitude];

			for (int i = 0; i < magnitude; i++)
				temp[i] = items[i];

			delete[] items;
			magnitude *= 2;
			items = temp;
		}

		items[current] = element;
		current++;
	}

	void Add(T element, int index) {
		if (index == magnitude)
			Add(element);
		else
			items[index] = element;
	}

	T Get(int index) {
		if (index < current)
			return items[index];
	}

	void Delete(int index) {
		for (int i = 0; i < current; i++) {
			if (i == index) {
				if (i == 0) {
					delete[] items;
					//new cList<T>();
					items = new T[1];
					magnitude = 1;
					current = 0;
					return;
				}
				for (int j = i; j < (current - 1); j++)
					items[j] = items[j + 1];
				i--;
				current--;
				magnitude--;
			}
		}
	}

	int Size() {
		return current;
	}

	int GetMagnitude() {
		return magnitude;
	}
};


