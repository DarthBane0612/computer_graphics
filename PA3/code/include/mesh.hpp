#ifndef MESH_H
#define MESH_H

#include <vector>
#include "object3d.hpp"
#include "triangle.hpp"
#include "Vector2f.h"
#include "Vector3f.h"


class Mesh : public Object3D {

public:
    Mesh(const char *filename, Material *m);

    struct TriangleIndex {
        TriangleIndex() {
            x[0] = 0; x[1] = 0; x[2] = 0;
        }
        int &operator[](const int i) { return x[i]; }
        // By Computer Graphics convention, counterclockwise winding is front face
        int x[3]{};
    };

    std::vector<Vector3f> v;
    std::vector<TriangleIndex> t;
    std::vector<Vector3f> n;
    bool intersect(const Ray &r, Hit &h, float tmin) override;

    void drawGL() override {
        // TODO (PA2): Call drawGL for each individual triangle.
	for (int index = 0; index < t.size(); index += 1) {
                TriangleIndex &triindex = t[index];
                Triangle triangle(v[triindex[0]], v[triindex[1]], triindex[2]], material);
                triangle.normal = n[index];
                triangle.drawGL();
        }
    }

private:

    // Normal can be used for light estimation
    void computeNormal();
};

#endif
