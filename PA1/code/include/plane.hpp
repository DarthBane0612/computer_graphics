#ifndef PLANE_H
#define PLANE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>

// TODO: Implement Plane representing an infinite plane
// function: ax+by+cz=d
// choose your representation , add more fields and fill in the functions

class Plane : public Object3D {
public:
    Plane() {
    }

    Plane(const Vector3f &normal, float d, Material *m) : Object3D(m) {
		this->n = normal;
		this->d = d;
		this->material = m;
    }

    ~Plane() override = default;

    bool intersect(const Ray &r, Hit &h, float tmin) override {
	if (Vector3f::dot(n, r.getDirection()) == 0) {
		return false;
	}
	float t = -(-d + Vector3f::dot(n, r.getOrigin()))/(Vector3f::dot(n, r.getDirection()));
	if (t > 0 && t >= tmin) {
		if (h.getT() > t) {
			h.set(t, material, n);
			return true;
		}
	}
        return false;
	
    }

protected:
	Vector3f n;
	float d;
	Material* material;
};

#endif //PLANE_H
		

