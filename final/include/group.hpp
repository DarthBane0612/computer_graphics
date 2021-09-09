#ifndef GROUP_H
#define GROUP_H


#include "object3d.hpp"
#include "ray.hpp"
#include "hit.hpp"
#include <iostream>
#include <vector>


// TODO (PA2): Implement Group - copy from PA1
class Group : public Object3D {

public:

    Group() {

    }
  
    explicit Group (int num_objects) {
        group.resize(num_objects);
    }

    ~Group() override {
        int len = group.size();
        for (int i = 0; i < len; i += 1) {
              delete group[i];
        }
    }

    void drawGL() override {
	    int len = group.size();
	    for (int i = 0; i < len; i += 1) {
		    group[i]->drawGL();
	    }
    }

    bool intersect(const Ray &r, Hit &h, float tmin) override {
        int len = group.size();
        bool result = false;
        for (int i = 0; i < len; i += 1) {
                bool temp = group[i]->intersect(r, h, tmin);
                result = result | temp;
        }
        return result;
    }

    void addObject(int index, Object3D *obj) {
        group[index] = obj;
    }

    int getGroupSize() {
        return group.size();
    }

private:
        std::vector<Object3D*> group;

};

#endif
	
