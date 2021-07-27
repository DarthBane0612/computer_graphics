#ifndef GROUP_H
#define GROUP_H


#include "object3d.hpp"
#include "ray.hpp"
#include "hit.hpp"
#include <iostream>
#include <vector>



// TODO: Implement Group - add data structure to store a list of Object*
class Group : public Object3D {

public:

    Group() = delete;

    explicit Group (int num_objects) {
	group.resize(num_objects);
    }

    ~Group() override {
	int len = group.size();
	for (int i = 0; i < len; i += 1) {
		delete group[i];
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
	//group.insert(group.begin() + index, obj);
	group[index] = obj;
    }

    int getGroupSize() {
	return group.size();
    }

private:
	std::vector<Object3D*> group;
};

#endif
	
