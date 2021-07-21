#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>
#include <iostream>
using namespace std;

// TODO: implement this class and add more fields as necessary,
class Triangle: public Object3D {

public:
	Triangle() = delete;

    // a b c are three vertex positions of the triangle
	Triangle( const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m) : Object3D(m) {
		this->a = a;
		this->b = b;
		this->c = c;
		this->normal = Vector3f::cross(b - a, c - a).normalized();
		this->material = m;
		vertices[0] = a;
		vertices[1] = b;
		vertices[2] = c;
	}

	bool intersect( const Ray& ray,  Hit& hit , float tmin) override {
		Vector3f E1, E2, S;
		E1 = vertices[0] - vertices[1];
		E2 = vertices[0] - vertices[2];
		S = vertices[0] - ray.getOrigin();
		Matrix3f m2 = Matrix3f(S, E1, E2, false);
		Matrix3f m1 = Matrix3f(ray.getDirection(), E1, E2, false);
		Matrix3f m3 = Matrix3f(ray.getDirection(), S, E2, false);
		Matrix3f m4 = Matrix3f(ray.getDirection(), E1, S, false);
		float t = (m2.determinant()) / (m1.determinant());
		float beta = (m3.determinant()) / (m1.determinant());
		float gama = (m4.determinant()) / (m1.determinant());
		if (t > 0 && beta >= 0 && gama <= 1 && beta + gama <= 1 && t > tmin) {
				if (hit.getT() > t) {
					hit.set(t, material, normal);
				}
			}
			return true;
		}
        	return false;
	}
	Vector3f normal;
	Vector3f vertices[3];
protected:
	Vector3f a;
	Vector3f b;
	Vector3f c;
	Material* material;
};

#endif //TRIANGLE_H
