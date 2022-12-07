#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include "Vec3D.h"
#include "Pool.h"


namespace pr {

class Job {
public:
	virtual void run () = 0;
	virtual ~Job() {};
};

// Job concret : exemple


class PixelJob : public Job {
	void calculPixel(Scene scene, const Scene::screen_t screen, vector<Vec3D> lights, Color* pixels ,int x ) {
		for (int y = 0; y < scene.getHeight(); y++) {
			// le point de l'ecran par lequel passe ce rayon
			auto& screenPoint = screen[y][x];
			// le rayon a inspecter
			Rayon  ray(scene.getCameraPos(), screenPoint);

			int targetSphere = findClosestInter(scene, ray);

			if (targetSphere == -1) {
				// keep background color
				continue;
			}
			else {
				const Sphere& obj = *(scene.begin() + targetSphere);
				// pixel prend la couleur de l'objet
				Color finalcolor = computeColor(obj, ray, scene.getCameraPos(), lights);
				// le point de l'image (pixel) dont on vient de calculer la couleur
				Color& pixel = pixels[y * scene.getHeight() + x];
				// mettre a jour la couleur du pixel dans l'image finale.
				pixel = finalcolor;
			}

		}
	}

	Scene scene;
	const Scene::screen_t screen;
	vector<Vec3D> lights;
	Color* pixels;
	int x;


public :
	PixelJob( Scene scene, const Scene::screen_t screen, vector<Vec3D> lights, Color* pixels, int x) : scene(scene), screen(screen), lights(lights), pixels(pixels), x(x) {}
	void run () {
		calculPixel(scene, screen, lights, pixels, x);
	}
	~PixelJob(){}
};
}
