#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include <vecmath.h>

#include "ray.hpp"
#include "hit.hpp"
#include <iostream>

// TODO: Implement Shade function that computes Phong introduced in class.
class Material {
public:

    explicit Material(const Vector3f &d_color, const Vector3f &s_color = Vector3f::ZERO, float s = 0) :
            diffuseColor(d_color), specularColor(s_color), shininess(s) {

    }

    virtual ~Material() = default;

    virtual Vector3f getDiffuseColor() const {
        return diffuseColor;
    }


    Vector3f Shade(const Ray &ray, const Hit &hit,
                   const Vector3f &dirToLight, const Vector3f &lightColor) {
        Vector3f shaded = Vector3f::ZERO;
	diffuseColor = Vector3f::dot(dirToLight, hit.getNormal());
	Vector3f Ri1 = 2 * (Vector3f::dot(hit.getNormal(), dirToLight));
	//Vector3f Ri2 = Vector3f::dot(Ri1, hit.getNormal());
	Vector3f Ri2 = Ri1 * hit.getNormal();
	Vector3f Ri = Ri2 - dirToLight;
	specularColor = Vector3f::dot(-ray.getDirection(), Ri);
	if (diffuseColor < 0) {
		diffuseColor = 0;
	}
	float x = pow(specularColor.x(), shininess);
	float y = pow(specularColor.y(), shininess);
	float z = pow(specularColor.z(), shininess);
	Vector3f newspecular = Vector3f(x, y, z);
	if (specularColor < 0) {
                specularColor = 0;
        }
	shaded = lightColor * (diffuseColor + newspecular);
        // 
        return shaded;
    }

protected:
    Vector3f diffuseColor;
    Vector3f specularColor;
    float shininess;
};


#endif // MATERIAL_H
