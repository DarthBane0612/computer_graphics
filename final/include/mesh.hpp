#ifndef MESH_H
#define MESH_H

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>


#include "object3d.hpp"
#include "triangle.hpp"
#include "Vector2f.h"
#include "Vector3f.h"
#include "bound.hpp"
#include "utils.hpp"
#include "ray.hpp"


class Mesh : public Object3D {

public:
    Mesh(const char *filename, Material *m) : Object3D(m) {
    	std::vector<TriangleIndex> vIdx, tIdx, nIdx;
    	std:vector<Vector3f> v, vn;
    	std:vector<Vector2f> vt;
    	std::ifstream f;
    	f.open(filename);
    	if (!f.is_open()) {
    		std::cout << "can't open" << filename << "\n";
    		return;
    	}
    	
    	std:string line;
    	std:string vTok("v");
    	
    };

    

#endif
