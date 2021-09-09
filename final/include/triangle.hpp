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
		d = Vector3f::dot(normal, a);
        	bound[0] = minE(minE(a, b), c);
        	bound[1] = maxE(maxE(a, b), c);
        	cen = (a + b + c) / 3;
        	nSet = false;
        	tSet = false;
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

	void setVNorm(const Vector3f& anorm, const Vector3f& bnorm,
                  const Vector3f& cnorm) {
        an = anorm;
        bn = bnorm;
        cn = cnorm;
        nSet = true;
    }

    void setVT(const Vector2f& _at, const Vector2f& _bt, const Vector2f& _ct) {
        at = _at;
        bt = _bt;
        ct = _ct;
        tSet = true;
    }

    Vector3f min() const override { return bound[0]; }
    Vector3f max() const override { return bound[1]; }
    Vector3f center() const override { return cen; }
    vector<Object3D*> getFaces() override { return {(Object3D*)this}; }
    Vector3f cen;
    Vector2f at, bt, ct;
    Vector3f an, bn, cn;
    Vector3f bound[2];
    float d;
    bool nSet = false;
    bool tSet = false;

   protected:
    bool inTriangle(const Vector3f& p) {
        float va = Vector3f::dot(Vector3f::cross((b - p), (c - p)), normal),
              vb = Vector3f::dot(Vector3f::cross((c - p), (a - p)), normal),
              vc = Vector3f::dot(Vector3f::cross((a - p), (b - p)), normal);
        return (va >= 0 && vb >= 0 && vc >= 0);
    }

    Vector3f getNorm(const Vector3f& p) {
        if (!nSet) return normal;
        Vector3f va = (a - p), vb = (b - p), vc = (c - p);
        float ra = Vector3f::cross(vb, vc).length(),
              rb = Vector3f::cross(vc, va).length(),
              rc = Vector3f::cross(va, vb).length();
        return (ra * an + rb * bn + rc * cn).normalized();
    }

    void getUV(const Vector3f& p, float& u, float& v) {
        if (!tSet) return;
        Vector3f va = (a - p), vb = (b - p), vc = (c - p);
        float ra = Vector3f::cross(vb, vc).length(),
              rb = Vector3f::cross(vc, va).length(),
              rc = Vector3f::cross(va, vb).length();
        Vector2f uv = (ra * at + rb * bt + rc * ct) / (ra + rb + rc);
        u = uv.x();
        v = uv.y();
    }

    Ray randomRay(int axis= -1, long long int seed=0) const override {
        float r1 = random(axis, seed), r2 = random(axis, seed);
        if (r1 + r2 > 1) {
            r1 = 1 - r1;
            r2 = 1 - r2;
        }
        return Ray(r1 * b + r2 * c + (1 - r1 - r2) * a, diffDir(normal, axis, seed));
    }
};


protected:
    Vector3f a;
    Vector3f b;
    Vector3f c;
    Material* material;
};

#endif //TRIANGLE_H
