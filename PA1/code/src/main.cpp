#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "scene_parser.hpp"
#include "image.hpp"
#include "camera.hpp"
#include "group.hpp"
#include "light.hpp"

#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    for (int argNum = 1; argNum < argc; ++argNum) {
        std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
    }

    if (argc != 3) {
        cout << "Usage: ./bin/PA1 <input scene file> <output bmp file>" << endl;
        return 1;
    }
    string inputFile = argv[1];
    string outputFile = argv[2];  // only bmp is allowed.

    // TODO: Main RayCasting Logic
    // First, parse the scene using SceneParser.
    // Then loop over each pixel in the image, shooting a ray
    // through that pixel and finding its intersection with
    // the scene.  Write the color at the intersection to that
    // pixel in your output image.
    
    SceneParser sp = SceneParser(inputFile.c_str());
    
    Camera* camera = sp.getCamera();
    Image* img = new Image(camera->getWidth(), camera->getHeight());
    for (int x = 0; x < camera->getWidth(); ++x) {
	for (int y = 0; y < camera->getHeight(); ++y) {
		Ray camRay = sp.getCamera()->generateRay(Vector2f(x, y));
		Group* baseGroup = sp.getGroup();
		Hit hit;
		bool isIntersect = baseGroup->intersect(camRay, hit, 0);
		if (isIntersect) {
			Vector3f finalColor = Vector3f::ZERO;
			for (int li = 0; li < sp.getNumLights(); li += 1) {
				Light* light = sp.getLight(li);
				Vector3f L, lightColor;
				light->getIllumination(camRay.pointAtParameter(hit.getT()), L, lightColor);
				finalColor += hit.getMaterial()->Shade(camRay, hit, L, lightColor);
			}
			img->SetPixel(x, y, finalColor);
		}
		else {
			img->SetPixel(x, y, sp.getBackgroundColor());
		}
	}
    }


    
    cout << "Hello! Computer Graphics!" << endl;
    img->SaveBMP(outputFile.c_str());

    return 0;
}

