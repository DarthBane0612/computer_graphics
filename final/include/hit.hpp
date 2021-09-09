#ifndef HIT_H
#define HIT_H

#include <vecmath.h>
#include "ray.hpp"

class Material;

class Hit {
public:

    // constructors
    Hit() {
        material = nullptr;
        t = 1e38;
        r = 0.0001;
        through = Vector3f(1);
        normal = emissionflux = flux = color = Vector3f::Zero;
        n1 = 0;
    }

    Hit(float _t, Material *m, const Vector3f &n) {
        t = _t;
        material = m;
        normal = n;
        r = 0.0001;
        through = Vector3f(1);
        normal = emissionflux = flux = color = Vector3f::Zero;
        n1 = 0;
    }

    Hit(const Hit &h) {
        t = h.t;
        material = h.material;
        normal = h.normal;
        r = 0.0001;
        through = Vector3f(1);
        normal = emissionflux = flux = color = Vector3f::Zero;
        n1 = 0;
    }

    // destructor
    ~Hit() = default;

    float getT() const {
        return t;
    }

    Material *getMaterial() const {
        return material;
    }

    const Vector3f &getNormal() const {
        return normal;
    }
    void reset(const Vector3f &_d) {
    	t = 1e38;
    }
    void set(float _t, Material *m, const Vector3f &n, const Vector3f &c, const Vector3f &_p) {
        t = _t;
        material = m;
        normal = n;
        color = c;
        point = _p;
    }

private:
    float t;
    float r;
    int n1;
    Vector3f color, flux, emissionflux, through;
    Vector3f dir;
    Vector3f, point;
    Material *material;
    Vector3f normal;
    

};

inline std::ostream &operator<<(std::ostream &os, const Hit &h) {
    os << "Hit <" << h.getT() << ", " << h.getNormal() << ">";
    return os;
}

#endif // HIT_H
