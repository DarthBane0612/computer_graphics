#pragma once

#include <image.hpp>
#include <algorithm>
#include <queue>
#include <stdbool.h>
#include <cstdio>

class Element {
public:
    virtual void draw(Image &img) = 0;
    virtual ~Element() = default;
};

class Line : public Element {

public:
    int xA, yA;
    int xB, yB;
    Vector3f color;
    void draw(Image &img) override {
        // TODO: Implement Bresenham Algorithm
	int x, y;
	int dx, dy;
	int e;
	dx = xA-xB
	dy = yA-yB;
	e = -dx;
	x = xA;
	y = yA;
	for (int i = 0; i <= dx; i += 1) {
		img.SetPixel(x, y, color);
		x = x + 1;
		e = e + (2 * dy);
		if (e >= 0) {
			y = y + 1;
			e = e - (2 * dx);
		}
	}
        printf("Draw a line from (%d, %d) to (%d, %d) using color (%f, %f, %f)\n", xA, yA, xB, yB,
                color.x(), color.y(), color.z());
    }
};

class Circle : public Element {

public:
    int cx, cy;
    int radius;
    Vector3f color;

    void CirclePoints(Image &img, int x, int y, Vector3f &color) {
	img.SetPixel(x, y, color);
	img.SetPixel(y, x, color);
	img.SetPixel(-x, y, color);
	img.SetPixel(y, -x, color);
	img.SetPixel(x, -y, color);
	img.SetPixel(-y, x, color);
	img.SetPixel(-x, -y, color);
	img.SetPixel(-y, -x, color); 
    }

    void draw(Image &img) override {
        // TODO: Implement Algorithm to draw a Circle
	//int x, y;
	float d;
	cx = 0;
	cy = radius;
	d = 1.25 - float(radius);
	CirclePoints(img, cx, cy, color);
	while (x <= y) {
		if (d < 0) {
			d = d + float((2 * cx) + 3);
		}
		else {
			d = d + float(2 * (cx - cy) + 5);
			cy = cy - 1;
		}
		cx = cx + 1;
		CirclePoints(img, cx, cy, color);
	}	
	
        printf("Draw a circle with center (%d, %d) and radius %d using color (%f, %f, %f)\n", cx, cy, radius,
               color.x(), color.y(), color.z());
    }
};

class Fill : public Element {

public:
    int cx, cy;
    Vector3f color;
    typedef struct Seed {
	int x;
	int y;
    } Seed;
    queue<Seed> q;
    void draw(Image &img) override {
        // TODO: Flood fill
	int xl, xr, i;
	bool spanNeedFill;
	Seed point;
	if (q.empty() != true) {
		for (int i = q.size(); i < q.size(); i += 1) {
			q.pop();
		}
	}
	point.x = cx;
	point.y = cy;
	q.push(point);
	while(q.empty() != true) {
		point = q.pop();
		cy = point.y;
		cx = point.x;
		while (img.GetPixel(cx, cy) != color) {
			img.SetPixel(cx, cy, color);
			cx += 1;
		}
		xr = cx - 1;
		cx = point.x - 1;
		while (img.GetPixel(cx, cy) != color) {
                        img.SetPixel(cx, cy, color);
                        cx -= 1;
                }
                xl = cx + 1;

		cx = xl;
		y = y + 1;
		while (x <= xr) {
			spanNeedfill = false;
			while (img.getPixel(cx, cy) != color) {
				spanNeedFill = true;
				x += 1;
			}
			if (spanNeedFill == true) {
				point.x = cx - 1;
				point.y = cy;
				q.push(point);
				spanNeedFill = false;
			}
			while (img.getPixel(cx, cy) == color && cx <= xr) {
				cx += 1;
			}
		}
		cx = xl;
                y = y - 2;
                while (x <= xr) {
                        spanNeedfill = false;
                        while (img.getPixel(cx, cy) != color) {
                                spanNeedFill = true;
                                x += 1;
                        }
                        if (spanNeedFill == true) {
                                point.x = cx - 1;
                                point.y = cy;
                                q.push(point);
                                spanNeedFill = false;
                        }
                        while (img.getPixel(cx, cy) == color && cx <= xr) {
                                cx += 1;
                        }
                }

	}
        printf("Flood fill source point = (%d, %d) using color (%f, %f, %f)\n", cx, cy,
                color.x(), color.y(), color.z());
    }
}
