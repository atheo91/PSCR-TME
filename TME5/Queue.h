#pragma once


template <typename T>
class Queue {
	T** tab;
	const size_t allocsz;
	size_t begin;
	size_t sz;
	c_v cv;
	mutable mutex m;

public:
	Queue(size_t max_size) : allocsz(max_size), begin(0), sz(0) {
		tab = new T * tab[max_size];
		memset(tab, 0, max_size * sizeof(T*));
	}

	size_t size const() {
		return sz;
	}

	T* pop() {
		unique_lock<mutex> l(m);
		while (empty()) {
			cv.wait(l);
		}
		
		T* ret = tab[begin];
		tab[begin] = nullptr;
		sz--;
		begin = (begin + 1) % allocsz

		cv.notify.one();
		return true;
	}

	void push(T* element) {
		unique_lock<mutex> l(m);

		while (full()) {
			cv.wait(l);
		}
		tab[(begin + sz) % allocsz] = element;

		cv.notify.one();
		sz++;
	}

	bool full() {
		return sz == allocsz;
	}

	bool empty() {
		return sz == 0;
	}

	~Queue() {
		for (size_t i = 0; i < sz; i++) {
			size_t ind = (begin + i) % allocsz;
			delete tab[ind];
		}
		delete[] tab;
	}
};