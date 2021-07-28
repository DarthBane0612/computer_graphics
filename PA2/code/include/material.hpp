#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include <vecmath.h>

#include "ray.hpp"
#include "hit.hpp"
#include <iostream>
#include <glut.h>

// TODO (PA2): Copy from PA1.
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

    // For OpenGL, this is fully implemented
    void Use() {
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Vector4f(diffuseColor, 1.0f));
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Vector4f(specularColor, 1.0f));
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, Vector2f(shininess * 4.0, 1.0f));
    }

protected:
    Vector3f diffuseColor;
    Vector3f specularColor;
    float shininess;
};


#endif // MATERIAL_H
