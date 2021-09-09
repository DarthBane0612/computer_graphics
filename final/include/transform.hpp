#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vecmath.h>
#include "object3d.hpp"

static Vector3f transformPoint(const Matrix4f &mat, const Vector3f &point) {
    return (mat * Vector4f(point, 1)).xyz();
}

// transform a 3D directino using a matrix, returning a direction
// This function *does not* take the inverse tranpose for you.
static Vector3f transformDirection(const Matrix4f &mat, const Vector3f &dir) {
    return (mat * Vector4f(dir, 0)).xyz();
}

class Transform : public Object3D {
public:
    Transform() {}

    Transform(const Matrix4f &m, Object3D *obj) : o(obj) {
        transform = m.inverse();
        bounds[0] = transformPoint(m, o->min());
        bounds[1] = transformPoint(m, o->max());
        bounds[2] = transformPoint(m, o->center());
    }

    ~Transform() {
    }

    virtual bool intersect(const Ray &r, Hit &h, float tmin) {
        Vector3f trSource = transformPoint(transform, r.getOrigin());
        Vector3f trDirection = transformDirection(transform, r.getDirection());
        Ray tr(trSource, trDirection);
        bool inter = o->intersect(tr, h, tmin);
        if (inter) {
            h.set(h.getT(), h.getMaterial(), transformDirection(transform.transposed(), h.getNormal()).normalized());
        }
        return inter;
    }

    Vector3f min() const override { return bounds[0]; }
    Vector3f max() const override { return bounds[1]; }
    Vector3f center() const override { return bounds[2]; }
    vector<Object3D *> getFaces() override { return {(Object3D *)this}; }


protected:
    Object3D *o; //un-transformed object
    Matrix4f transform;
    Vector3f bounds[3];
};

#endif //TRANSFORM_H
