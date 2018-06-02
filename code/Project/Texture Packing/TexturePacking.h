#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TexturePacking.h"
#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QBrush>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <qwindowdefs.h>
#include <ctime>
#include <cstdlib>
#define LOWEST 1
#define HIGHEST 0
#define CANDIDATE_WIDTH 0
#define CANDIDATE_HEIGHT 1000
#define HEIGHT_WEIGHT 2
#define EPS 1e-8
#define maxsize 5000

using namespace std;

class TexturePacking : public QMainWindow
{
	Q_OBJECT

public:
	TexturePacking(QWidget *parent = Q_NULLPTR);

public slots:
	void ClickButtom();

private:
	Ui::TexturePackingClass ui;

protected:
	void paintEvent(QPaintEvent *event);
};

class Rectangle
{
public:
	Rectangle() : bl_x(-1), bl_y(-1) {};
	Rectangle(int w, int h) : width(w), height(h), bl_x(-1), bl_y(-1) {};			 //overload ctor with two parameters
	Rectangle(int w, int h, int x, int y) : width(w), height(h), bl_x(x), bl_y(y) {}; //overload ctor with four parameters
	~Rectangle() {};
	int get_width() const { return width; }	//get width of rectangle
	int get_height() const { return height; }  //get height of rectangle
	int get_x() const { return bl_x; }		   //get cordinate x of rectangle
	int get_y() const { return bl_y; }		   //get cordinate y of rectangle
	bool get_placed() const { return placed; } //get if the rectangle is placed
	bool operator==(const Rectangle &n);	   //overload == to judge wheter two instances are the same
	void rotate();
	void set_bl_x(int x) { bl_x = x; }
	void set_bl_y(int y) { bl_y = y; }
	void place() { placed = true; }
	void reset() { placed = false; }

private:
	int bl_x, bl_y;
	int width, height;
	bool placed = false; //initialized not placed
};

class Segment
{ //horizontal segment class
public:
	Segment() {};
	Segment(int x1, int x2, int y_h) : xl(x1), xr(x2), y(y_h) {}; //overload ctor with given parameters
	~Segment() {};
	int get_xl() const { return xl; } //get left end point
	int get_xr() const { return xr; } //get right end point
	int get_y() const { return y; }   //get y
	void set_xl(int x) { xl = x; }	//set left end point
	void set_xr(int x) { xr = x; }	//set right end point
	void set_y(int y_h) { y = y_h; }  //set y
private:
	int xl, xr; //left end point and right end point
	int y;		//unique y because the segment is horizontal
};


class Layer   // a class for FFDH algorithm to describe its layer
{
public:
	Layer() {};
	Layer(int width, int height, int floorh) :width(width), height(height), floorh(floorh) {};
	~Layer() {};
	int get_width() const { return width; } //get the current width
	int get_height() const { return height; } //get the layer's height:the highest rectangle's y value
	int get_floorh() const { return floorh; } //get the start height of this layer
	void set_width(int w) { width = w; }	  //set the width
	void set_height(int h) { height = h; }	  //set the height
	void set_floorh(int fh) { floorh = fh; }  //set the floor_height
private:
	int width;
	int height;
	int floorh;
};

class Area    //a class for the SAS algorithm to store the boundary values of an area to place the rectangles
{
public:
	Area() {};
	Area(int xl, int xr, int yb, int ya) : xl(xl), xr(xr), yb(yb), ya(ya){};
	~Area() {};
	int get_xl() const { return xl; }   //get the left x value
	int get_xr() const { return xr; }   //get the right x value
	int get_yb() const { return yb; }   //get the below y value
	int get_ya() const { return ya; }   //get the above y value
	void set_xl(int x) { xl = x; }      //set the x_left
	void set_xr(int x) { xr = x; }      //set the x_right
	void set_yb(int y) { yb = y; }      //set the y_below
	void set_ya(int y) { ya = y; }      //set the y_above
private:
	int xl, xr;
	int yb, ya;
};



vector<Rectangle> GetRectangle(int &strip_width); //read all required data from input
vector<Rectangle> GetOptimalSolution(int &strip_width);
bool LengthCheck(vector<Rectangle> &rec_set, int width);											//check if there exists a solution
void PrintRectangles(vector<Rectangle> rec_set);													//print all rectangle attributes in rectangle set
void PrintContour(vector<Segment> Contour);															//print all segment attributes in contour
void PrintSegment(Segment seg);																		//print attributes of a single segment
bool SegmentLRSort(Segment a, Segment b);															//sort segments from left to right
vector<Segment>::iterator FindSegment(vector<Segment> &Contour, int flag);							//find segment with minimum y or maximum y
void ConstructRCL(vector<Rectangle> &rec_set, vector<Rectangle> &RCL, int length, int delta_y);		//construct a candidate list
vector<Rectangle>::iterator FindRectangle(vector<Rectangle> &rec_set, Rectangle &rec);				//find if a rectangle is in rectangle set
void CombineSegment(vector<Segment> &Contour);														//combine neighbour segments which have the same height
void LevelUpdate(vector<Segment> &Contour);															//when no rectangle can be placed, then implement level update
bool BestFit(vector<Rectangle> &unplaced, vector<Segment> &Contour, Rectangle &best_fit_rectangle); //seak for the best fit unplaced rectangle
void FillRectangle(vector<Rectangle> &rec_set, vector<Segment> &Contour);							//fill rectangles in the strip
int IterativeFindSolution(vector<Rectangle> &rec_set, int strip_width, int k);
void VariableNeighbourSearch(vector<Rectangle> &rec_set, vector<Segment> &Contour, int width);
void RandomRectangles(int width, int height, int recnum);                                           //randomly generate the rectangles
void placeFirstRec(vector<Rectangle>& rec, vector<Rectangle>& curRec, int& curX, int& curY, int& height);  //place a layer's first rectangle in the SAS algorithm
int FFDH(vector<Rectangle> &rec, int strip_width);                    //the core of the FFDH algorithm
int SAS(vector<Rectangle> &rec, int strip_width);                     //the core of the SAS algorithm 
void placeNarrowRec(vector<Rectangle> &rec, vector<Rectangle> &narrowRec, vector<Rectangle> &wideRec, Area& curArea, int& way);
void placeWideRec(vector<Rectangle> &rec, vector<Rectangle> &narrowRec, vector<Rectangle> &wideRec, Area& curArea, int& way); // the procedure of placing wideRec rectangles
int SumArea(vector<Rectangle> &rec_set);                              //to calculate the total area of all the rectangla
void setRecPosition(vector<Rectangle>& rec, vector<Rectangle>& curRec, Area& curArea, int index);   //set the position for the rectangle
void defineArea(Area& curArea, int xl, int xr, int yb, int ya);      //set the x&y values for the area
bool sortFFDH(Rectangle& rec1, Rectangle& rec2);             //define the sort order of the FFDH algorithm
bool sortNarrow(Rectangle& rec1, Rectangle& rec2);           //define the sort order of narrow rectangles in the SAS algorithm
bool sortWide(Rectangle& rec1, Rectangle& rec2);             //define the sort order of wide rectangles in the SAS algorithm 