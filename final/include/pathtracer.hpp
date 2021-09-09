#ifndef PATH_TRACER_H
#define PATH_TRACER_H

#include <cmath>
#include <cstring>
#include <iostream>
#include <string>

#include "camera.hpp"
#include "group.hpp"
#include "hit.hpp"
#include "image.hpp"
#include "light.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "utils.hpp"
using namespace std;
static Vector3f ptColor(Ray ray, const Scene& scene) {
    Group* group = scene.getGroup();
    int depth = 0;
    Vector3f color(0, 0, 0), cf(1, 1, 1);
    while (true) {
        if (++depth > 20 || cf.max() < 1e-3) return color;
        Hit hit;
        if (!group->intersect(ray, hit)) {
            color += scene.getBackgroundColor();
            return color;
        }

        // Path Tracing
        ray.origin += ray.direction * hit.t;
        Material* material = hit.material;
        Vector3f refColor(hit.color), N(hit.normal);

        // Emission
        color += material->emission * cf;
        cf = cf * refColor;
        float type = RND2;
        if (type <= material->type.x()) {  // diffuse
            ray.direction = diffDir(N);
        } else if (type <=
                   material->type.x() + material->type.y()) {  // specular
            float cost = Vector3f::dot(ray.direction, N);
            ray.direction = (ray.direction - N * (cost * 2)).normalized();
        } else {  // refraction
            float n = material->refr;
            float R0 = ((1.0 - n) * (1.0 - n)) / ((1.0 + n) * (1.0 + n));
            if (Vector3f::dot(N, ray.direction) > 0) {  // inside the medium
                N.negate();
                n = 1 / n;
            }
            n = 1 / n;
            float cost1 = -Vector3f::dot(N, ray.direction);  // cosine theta_1
            float cost2 =
                1.0 - n * n * (1.0 - cost1 * cost1);  // cosine theta_2
            float Rprob = R0 + (1.0 - R0) * pow(1.0 - cost1,
                                                5.0);  // Schlick-approximation
            if (cost2 > 0 && RND2 > Rprob) {           // refraction direction
                ray.direction =
                    ((ray.direction * n) + (N * (n * cost1 - sqrt(cost2))))
                        .normalized();
            } else {  // reflection direction
                ray.direction = (ray.direction + N * (cost1 * 2));
            }
        }
    }
}

static Vector3f rcColor(Ray ray, const Scene& scene) {
    Group* group = scene.getGroup();
    int depth = 0;
    Vector3f color(0, 0, 0);
    Hit hit;
    if (!group->intersect(ray, hit)) {
        color += scene.getBackgroundColor();
        return color;
    }
    for (int li = 0; li < scene.getNumLights(); ++li) {
        Light* light = scene.getLight(li);
        Vector3f L, lightColor;
        light->getIllumination(ray.pointAtParameter(hit.getT()), L, lightColor);
        color += hit.getMaterial()->phongShade(ray, hit, L, lightColor);
    }
}

class PathTracer {
   public:
    const Scene& scene;
    int samps;
    const char* fout;
    Vector3f (*radiance)(Ray ray, const Scene& scene);
    PathTracer(const Scene& scene, int samps, const char* method,
               const char* fout)
        : scene(scene), samps(samps), fout(fout) {
        if (!strcmp(method, "rc"))
            radiance = rcColor;
        else if (!strcmp(method, "pt"))
            radiance = ptColor;
        else {
            cout << "Unknown method: " << method << endl;
            exit(1);
        }
    }

    void render() {
        Camera* camera = scene.getCamera();
        int w = camera->getWidth(), h = camera->getHeight();
        cout << "Width: " << w << " Height: " << h << endl;
        Image outImg(w, h);
        time_t start = time(NULL);
#pragma omp parallel for schedule(dynamic, 1)  // OpenMP
        for (int y = 0; y < h; ++y) {
            float elapsed = (time(NULL) - start), progress = (1. + y) / h;
            fprintf(stderr, "\rRendering (%d spp) %5.2f%% Time: %.2f/%.2f sec",
                    samps, progress * 100., elapsed, elapsed / progress);
            for (int x = 0; x < w; ++x) {
                Vector3f color = Vector3f::ZERO;
                for (int s = 0; s < samps; ++s) {
                    Ray camRay =
                        camera->generateRay(Vector2f(x + RND, y + RND));
                    color += radiance(camRay, scene);
                }
                outImg.SetPixel(x, y, color / samps);
            }
        }
        outImg.SaveBMP(fout);
    }
};
