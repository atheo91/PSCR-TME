#pragma once

#include "Vec3D.h"
#include "Rayon.h"
#include "Sphere.h"
#include "Scene.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <limits>
#include <random>
#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>

namespace pr {

class Pool {
	Queue<PixelJob> *queue;
	std::vector<std::thread> threads;
public:
	Pool(int qsize) {
		queue = new Queue<PixelJob>(qsize);
	};
	void start(int nbthread) {
		PixelJob* pixelJob;
		while (queue->size() > 0) {
			for (int n = 0; n < nbthread; n++) {
				pixelJob = queue->pop();
				if(pixelJob != nullptr){
					threads.emplace_back(std::thread(pixelJob->run()));
				}
			}

			for (std::thread& th : threads) {
				th.join();
			}

		}
	}
	void submit(PixelJob* job) {
		queue->push(job);
	}
	void stop() ;


	~Pool() {
		delete queue;
	};
};

}
