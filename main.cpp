
#include <iostream>
#include <cmath>
#include <list>
#include <algorithm>
#include <chrono>
#include <thread>
#include "gfx.hpp"
#define BLACK	0.0,0.0,0.0
#define WHITE	1.0,1.0,1.0
#define GRAY    0.75,0.75,0.75
#define RED     1.0,0.0,0.0

using namespace gfx;
using namespace std;

class Point
{
public:
	Point(double x, double y): x1(x), y1(y), thickness(5)
	{

	}
	void draw () const
  	{
	    set_pen (thickness, RED, 1);
	    draw_point(x1,y1);
  	}
	double x1, y1, thickness; // thickness of pen
	/*
	class creates the point using gfx.cpp
	*/
};

static list<Point*> points;

class Edge
{
public:
	Edge(Point  const a, Point  const b): aa(a), bb(b), is_hull(true)
	{}
	void draw (bool is_hull) const
  	{
  		if(this->is_hull)
    		set_pen (aa.thickness, RED, 1);
    	else
    		set_pen (aa.thickness, GRAY, 1);
    	draw_line((aa).x1, (aa).y1, (bb).x1, (bb).y1);
  	}
	Point aa, bb;
	bool is_hull;
	/*

	*/
};

static list<Edge*> edges;
/*
    Using slowconvex hull algorithm.

*/

bool Right(Edge const &e, Edge const &f)
{

	double x, y, r, s, crossProd;

	x=f.bb.x1-f.aa.x1;
	y=f.bb.y1-f.aa.y1;

	r=e.aa.x1-f.aa.x1;
	s=e.aa.y1-f.aa.y1;

	crossProd = r*y - s*x;

	if (crossProd > 0.01)
		return 0;

	r=e.bb.x1-f.aa.x1;
	s=e.bb.y1-f.aa.y1;

	crossProd = r*y - s*x;

	if (crossProd > 0.01)
		return 0;

	return 1;
}

bool Left(Edge const &e, Edge const &f)
{

	double x, y, r, s, crossProd;

	x=f.bb.x1-f.aa.x1;
	y=f.bb.y1-f.aa.y1;

	r=e.aa.x1-f.aa.x1;
	s=e.aa.y1-f.aa.y1;

	crossProd = r*y - s*x;

	if (crossProd < -0.01)
		return 0;

	r=e.bb.x1-f.aa.x1;
	s=e.bb.y1-f.aa.y1;

	crossProd = r*y - s*x;

	if (crossProd < -0.01)
		return 0;

	return 1;
}

static void algorithm1()
{
	auto ie(edges.begin());
	for(;ie!=edges.end();ie++)
	{
		for(auto je(edges.begin());je!=edges.end();je++)
		{
			if (je==ie)
				continue;
			if ( !(Right(**je,**ie)!=Left(**je,**ie)) )
				(**ie).is_hull = false;
		}
	}
/////////// algorithm slow convex hull ends.
};
static void cb_draw()
{
    cout<<edges.size()<<" Edges and "<< points.size()<<" Points in the Convex Hull"<<endl;
	for(auto ip(points.begin()); ip != points.end(); ip++)
	{
		(*ip)->draw();
	}
	for(auto ie(edges.begin()); ie != edges.end(); ie++)
	{
		(*ie)->draw(true);
	}//////////  for printing total number of edges and points in the console.
};


static void cb_mouse(double mx, double my, int flags)
{
	if (flags & MOUSE_RELEASE)
	{
		points.push_back(new Point(mx,my));
		if(points.size() > 1)
		{
			auto ip(points.rbegin());
			auto jp(points.rbegin());
			ip++;
			Point p3 = **jp;
			for(; ip!=points.rend(); ip++)
			{
				Point p4 = **ip;
				edges.push_back(new Edge(p3,p4));
            }
		}
	}
};



int main (int argc, char ** argv)
{

  	add_button("Convex Hull", algorithm1);
  	main ("Convex Hull", cb_draw, cb_mouse);///////// adding buttons to the gui of the program.
}
