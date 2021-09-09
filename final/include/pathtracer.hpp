#ifndef PATH_TRACER_H
#define PATH_TRACER_H

#include <cmath>
#include <cstring>
#include <string>

#include "camera.hpp"
#include "group.hpp"
#include "hit.hpp"
#include <iostream>
#include "image.hpp"
#include "light.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "utils.hpp"

using namespace std;

static Vector3f pathColor(Ray r, const Scene& scene) {
	Group* group = scene.getGroup();
	int depth = 0;
	Vector3f color(0, 0, 0), cf(1, 1, 1);
	while (true) {
		if (++depth > 20 || cf.max() < 1e - 3) {
			return color;
		}
		Hit hit;
		if (!group->intersect(r, hit)) {
			color += scene.getBackgroundColor();
			return color;
		}
		
		r.origin() += r.getDirection() * hit.getT();
		Material* material = hit.getMaterial();
		Vector3f refColor(hit.color), N(hit.getNormal());
		
		color += material->emission * cf;
		cf = cf * refColor;
		float type = RND2;
		if (type <= material->type.x()) {
			r.getDirection() = diffDir
		}
	}
}


#endif
	
