#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>
#include <iostream>

using namespace std;

// TODO (PA2): Copy from PA1
class Triangle: public Object3D
{

public:
	Triangle() = delete;
        ///@param a b c are three vertex positions of the triangle

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
                Matrix3f m4 = Matrix3f(ray.getDirection(), E1, S, false);;
                float x = m1.determinant();
                float y = m2.determinant();
                float z = m3.determinant();
                float v = m4.determinant();
                Vector3f temp = Vector3f(y, z, v);
                temp = temp / x;
                float t = temp.x();
                if (t >= tmin && t <= hit.getT()) {
                        Vector3f p = ray.pointAtParameter(t);
                        if (Vector3f::dot(Vector3f::cross((vertices[1]-p), (vertices[2]-p)), normal) >= 0 && Vector3f::dot(Vector3f::cross((vertices[2]-p), (vertices[0]-p)), normal) >= 0 && Vector3f::dot(Vector3f::cross((vertices[0]-p), (vertices[1]-p)), normal) >= 0) {
                                hit.set(t, material, normal);
                                return true;
                        }
		}
        	return false;
	}
	Vector3f normal;
	Vector3f vertices[3];

    void drawGL() override {
        Object3D::drawGL();
        glBegin(GL_TRIANGLES);
        glNormal3fv(normal);
        glVertex3fv(vertices[0]); glVertex3fv(vertices[1]); glVertex3fv(vertices[2]);
        glEnd();
    }

protected:
    Vector3f a;
    Vector3f b;
    Vector3f c;
    Material* material;
};

#endif //TRIANGLE_H
