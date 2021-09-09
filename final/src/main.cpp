#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <string>

#include "pathtracer.hpp"
#include "scene_parser.hpp"
using namespace std;
int main(int argc, char* argv[]) {
    for (int argNum = 1; argNum < argc; ++argNum) {
        std::cout << "Argument " << argNum << " is: " << argv[argNum]
                  << std::endl;
    }
    if (argc < 5) {
        std::cout << "Usage: ./bin/PA1 <input scene file> <output bmp file> "
                     "<method> [<spp>]/[<numRounds> <numPhotons> <ckpt_interval>]"
                  << endl;
        return 1;
    }

    Scene scene(argv[1]);

    if (!strcmp(argv[3], "rc") || !strcmp(argv[3], "pt")) {
        int samps = atoi(argv[4]);
        PathTracer pt(scene, samps, argv[3], argv[2]);
        pt.render();
    } 
    else {
        cout << "Unknown method: " << argv[4] << endl;
        return 1;
    }
    return 0;
}
