#pragma once
#include "src/main.cpp"



class Pool {
	void poolPixel(Queue<PixelJob>& queue) {
		while (true) {
			PixelJob* j = queue.pop();
			if (j == nullptr) {
				break;
			}
			j->run();
			delete j;
		}
	}

	std::vector<std::thread> threads;
	Queue<Job> queue;

public:
	Pool(int qsize) {
		Queue<Job> queue(qsize);
		this->queue = queue;
	};

	~Pool() {};

	void start(int Nthread) {
		
	}
};