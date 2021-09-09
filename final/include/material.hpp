#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include <vecmath.h>

#include "ray.hpp"
#include "hit.hpp"
#include <iostream>
#include "texture.h"

// TODO (PA2): Copy from PA1.
class Material {
public:

    explicit Material(const Vector3f &d_color, const Vector3f &s_color = Vector3f::ZERO, float s = 0, const Vector3f &e_color = vector3f::ZERO, float r = 1, Vector3f t = Vector3f(1, 0, 0), const char *textureFile = "", const char *bumpFile = "") :
            diffuseColor(d_color), specularColor(s_color), shininess(s), emission(e_color), refractiveIndex(r), type(t), texture(textureFile), bump(bumpFile) {

    }

    virtual ~Material() = default;
    
    virtual Vector3f getColor(float u, float v) const {
    	if (!texture.picture) {
    		return color;
    	}
    	else {
    		return texture.getColor(u, v);
    	}
    }

    virtual Vector3f getDiffuseColor() const {
        return diffuseColor;
    }


    Vector3f Shade(const Ray &ray, const Hit &hit,
                   const Vector3f &dirToLight, const Vector3f &lightColor) {
        Vector3f shaded = Vector3f::ZERO;
        diffuseColor = Vector3f::dot(dirToLight.normalized(), hit.getNormal());
        Vector3f Ri1 = 2 * (Vector3f::dot(hit.getNormal(), dirToLight.normalized()));
        Vector3f Ri2 = Ri1 * hit.getNormal();
        Vector3f Ri = Ri2 - dirToLight.normalized();
        specularColor = Vector3f::dot(-ray.getDirection().normalized(), Ri);
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
        return shaded;
    }

 
protected:
    Vector3f diffuseColor;
    Vector3f color;
    Vector3f specularColor;
    Vector3f emission;
    Vector3f surfaceType;
    float refractiveIndex;
    float shininess;
    Texture texture;
};


#endif // MATERIAL_H
