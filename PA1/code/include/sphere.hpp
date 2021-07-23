#ifndef SPHERE_H
#define SPHERE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>

// TODO: Implement functions and add more fields as necessary

class Sphere : public Object3D {
public:
    Sphere() {
        // unit ball at the center
    }

    Sphere(const Vector3f &center, float radius, Material *material) : Object3D(material) {
	this->center = center;
	this->radius = radius;
	this->material = material;
    }

    ~Sphere() override = default;

    bool intersect(const Ray &r, Hit &h, float tmin) override {
        //
	Vector3f l = center - r.getOrigin();
	float tp = Vector3f::dot(l, r.getDirection());
	float dsquare = l.squaredLength() - tp * tp;
	if (dsquare < 0) {
		return false;
	}
	float d = sqrt(dsquare);
	if (d > radius) {
		return false;
	}
	float squaret = radius * radius - dsquare;
	if (squaret < 0) {
		return false;
	}
	float tprime = sqrt(squaret);
	float t;
	if (l.squaredLength() < radius * radius) {
		t = tp + tprime;
		Vector3f point = r.pointAtParameter(t);
		Vector3f normal = (point - center).normalized();
		if (t >= tmin) {
			if (h.getT() > t) {
				h.set(t, material, normal);
				return true;
			}
		}
	}
	else if (l.squaredLength() > radius * radius) {
		if (tp < 0) {
			return false; 
		}
		t = tp - tprime;
		Vector3f point = r.pointAtParameter(t);
                Vector3f normal = (point - center).normalized();
		if (t >= tmin) {
			if (h.getT() > t) {
				h.set(t, material, normal);
				return true;
			}
		}
	}
	else {
		t = 0;
		Vector3f point = r.pointAtParameter(t);
                Vector3f normal = (point - center).normalized();
		if (tmin <= 0) {
			if (h.getT() > 0) {
				h.set(t, material, normal);
				return true;
			}
		}
	}
        return false;
    }

protected:
	Vector3f center;
	float radius;
	Material* material;
};


#endif
