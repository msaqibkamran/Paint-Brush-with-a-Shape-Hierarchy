
#include<iostream>
#include<conio.h>
#include<windows.h>
#include"graphics.h"
#include<vector>
#include<fstream>
using namespace std;

struct  points
{
	double x, y;
};

void FloodFill(int x, int y, int oldColor, int newColor)
{

	if (getpixel(x, y) == oldColor)
	{
		putpixel(x, y, newColor);
		FloodFill(x + 1, y, oldColor, newColor);
		FloodFill(x - 1, y, oldColor, newColor);
		FloodFill(x, y + 1, oldColor, newColor);
		FloodFill(x, y - 1, oldColor, newColor);
	}
}
void myRectangle(int x1, int y1, int x2, int y2)
{
	line(x1, y1, x2, y1);  // top
	line(x1, y1, x1, y2); // right
	line(x1, y2, x2, y2); // bottom
	line(x2, y2, x2, y1); // left
}
void myTri(int x1, int y1, int x2, int y2, int x3, int y3)
{
	line(x1, y1, x2, y2);
	line(x2, y2, x3, y3);
	line(x3, y3, x1, y1);
}
void myTriangle(points p1, points p2, points p3)
{
	line(p1.x, p1.y, p2.x, p2.y);
	line(p2.x, p2.y, p3.x, p3.y);
	line(p3.x, p3.y, p1.x, p1.y);
}
bool PointLiesOnLine(points a, points b, points p)
{
	int ab = sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
	int ap = sqrt((p.x - a.x)*(p.x - a.x) + (p.y - a.y)*(p.y - a.y));
	int pb = sqrt((b.x - p.x)*(b.x - p.x) + (b.y - p.y)*(b.y - p.y));
	if (ab == ap + pb)
		return true;
	return false;
}
double areaOfTriangle(points a, points b, points c)
{
	double ans = ((a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y)) / 2.0);
	if (ans < 0)
		ans = -ans;
	return ans;
}
void panel()
{
	myRectangle(5, 5, 90, 416);     // panel

	outtextxy(7, 7, "Colors");

	myRectangle(10, 25, 25, 40);
	FloodFill(11, 26, BLACK, RED);
	myRectangle(35, 25, 50, 40);
	FloodFill(36, 26, BLACK, GREEN);
	myRectangle(60, 25, 75, 40);
	FloodFill(61, 26, BLACK, BLUE);
	myRectangle(10, 50, 25, 65);
	FloodFill(11, 51, BLACK, YELLOW);
	myRectangle(35, 50, 50, 65);
	FloodFill(36, 51, BLACK, 13); // orange
	myRectangle(60, 50, 75, 65);
	FloodFill(61, 51, BLACK, WHITE);
	myRectangle(10, 75, 25, 90);   // BLACK

	outtextxy(7, 100, "Shapes");

	circle(19, 130, 10);
	myTri(40, 120, 33, 138, 46, 138);
	myRectangle(62, 120, 75, 138);		// RECTANGLE
	myRectangle(10, 150, 25, 165);		// LINE
	line(15, 155, 21, 161);				// LINE
	line(40, 165, 50, 165);			    // POLYGON
	line(50, 165, 54, 156);
	line(40, 165, 35, 156);
	line(35, 156, 38, 150);
	line(38, 150, 50, 150);
	line(51, 150, 53, 155);			   // POLYGON
	myRectangle(61, 150, 75, 165);    // CURVE
	line(61, 165, 65, 154);
	line(65, 154, 75, 157);           // CURVE
	myRectangle(10, 174, 55, 194);    // TEXT
	setcolor(12);
	outtextxy(14, 177, "TEXT");
	setcolor(15);                     // TEXT

	outtextxy(7, 200, "ERASER");
	myRectangle(10, 220, 35, 240);
	myRectangle(35, 240, 45, 220);
	outtextxy(7, 248, "BUCKET");
	myRectangle(17, 268, 35, 275);
	myRectangle(17, 275, 35, 294);
	setcolor(12);
	outtextxy(22, 277, "B");
	setcolor(15);

	outtextxy(7, 300, "SAVE");
	myRectangle(16, 317, 34, 340);
	setcolor(12);
	outtextxy(21, 321, "S");
	setcolor(15);

	outtextxy(7, 350, "LOAD");
	myRectangle(16, 368, 34, 391);
	setcolor(12);
	outtextxy(21, 371, "L");
	setcolor(15);
}

class Shape
{
protected:
	points *arr;
	int color;
    int noOfPoints;
    int type;
public:
	Shape()
	{
		arr = 0;
		color = 0;
		noOfPoints = 0;
	}
	Shape(points *p, int c, int nop)
	{
		arr = new points[nop];
		color = c;
		for (int i = 0; i < nop; i++)
		{
			arr[i] = p[i];
		}
	}
	virtual ~Shape()
	{
		if (arr != nullptr)
			delete[] arr;
	}
	points* getArr()
	{
		return arr;
	}
	int getNoOfPoints()
	{
		return noOfPoints;
	}
	int getType()
	{
		return type;
	}

	virtual void draw() = 0;
	virtual bool contains(points) = 0;
	virtual void fill(int) = 0;
	virtual int getFillColor() = 0;
};
class Circle : public Shape
{
private:
	int fillColor;
	double radius;
public:
	Circle(points *p, int nop, int r, int c, int fc)
	{
		noOfPoints = nop;
		arr = new points[nop];
		for (int i = 0; i < nop; i++)
		{
			arr[i] = p[i];
		}
		radius = r;
		fillColor = fc;
		color = c;
		type = 1;
	}
	void draw()
	{
		setcolor(color);
		circle(arr[0].x, arr[0].y, radius);
		setcolor(7);
	}
	bool contains(points p)
	{
		if ((p.x - arr[0].x) * (p.x - arr[0].x) + (p.y - arr[0].y) * (p.y - arr[0].y) <= radius * radius)
			return true;
		else
			return false;

	}
	void fill(int color)
	{
		int currentColor = getpixel(arr[0].x + 1, arr[0].y + 1);
		fillColor = color;
		if(currentColor != color)
			FloodFill(arr[0].x + 1, arr[0].y + 1, currentColor, color);
	}
	int getFillColor()
	{
		return fillColor;
	}
};
class Text : public Shape
{
	vector <char> text;
	int fillColor;
public:
	Text(points *p, int nop, int c, int fc, vector<char> &t)
	{
		noOfPoints = nop;
		arr = new points[nop];
		for (int i = 0; i < nop; i++)
		{
			arr[i] = p[i];
		}
		text = t;
		fillColor = fc;
		color = c;
		type = 2;
	}
	bool contains(points p)
	{
		if (p.x >= arr[0].x && p.x <= arr[1].x && p.y >= arr[0].y && p.y <= arr[1].y + 20)
			return true;
		return false;
	}
	void draw()
	{
		setcolor(color);
		settextstyle(10, HORIZ_DIR, 4);
		moveto(arr[0].x, arr[0].y);
		for (int i = 0; i < text.size(); i++)
		{
			char c[2] = { '\0','\0' };
			c[0] = text[i];
			outtext(c);
		}
		settextstyle(0, 0, 0);
	}
	void fill(int color)
	{
		setcolor(color);
		fillColor = color;
		settextstyle(10, HORIZ_DIR, 4);
		moveto(arr[0].x, arr[0].y);
		for (int i = 0; i < text.size(); i++)
		{
			char c[2] = { '\0','\0' };
			c[0] = text[i];
			outtext(c);
		}
		settextstyle(0, 0, 0);
	}
	int getFillColor()
	{
		return fillColor;
	}
};
class POLYGON : public Shape
{
protected:
	int fillColor;
public:
	POLYGON()
	{
		arr = 0;
		color = 0;
		noOfPoints = 0;
		fillColor = 0;
	}
	POLYGON(vector<points> p, int nop, int c, int fc)
	{
		noOfPoints = nop;
		arr = new points[nop];
		for (int i = 0; i < nop; i++)
		{
			arr[i] = p[i];
		}
		color = c;
		fillColor = fc;
		type = 3;
	}
	void draw()
	{
		setcolor(color);
		for (int i = 0; i < noOfPoints - 1; i++)
		{
			line(arr[i].x, arr[i].y, arr[i + 1].x, arr[i + 1].y);
		}
		line(arr[noOfPoints - 1].x, arr[noOfPoints - 1].y, arr[0].x, arr[0].y);
		setcolor(7);
	}
	virtual bool contains(points p)  // polygon
	{
		int j = noOfPoints - 1;
		bool  oddCount = false;
		for (int i = 0; i < noOfPoints; i++)
		{
			if ((arr[i].y < p.y && arr[j].y >= p.y) || (arr[j].y < p.y && arr[i].y >= p.y))
			{
				if (arr[i].x + (p.y - arr[i].y) / (arr[j].y - arr[i].y)*(arr[j].x - arr[i].x) < p.x)
				{
					oddCount = !oddCount;
				}
			}
			j = i;
		}
		return oddCount;
	}
	virtual void fill(int color)
	{
		int x = 0, y = 0;
		for (int i = 0; i < noOfPoints - 1; i++)
		{
			x += arr[i].x;
		}
		x = x / (noOfPoints - 1);
		for (int i = 0; i < noOfPoints - 1; i++)
		{
			y += arr[i].y;
		}
		y = y / (noOfPoints - 1);
		int currentColor = getpixel(x, y);
		fillColor = color;
		if (currentColor != color)
			FloodFill(x, y, currentColor, color);
	}
	virtual int getFillColor()
	{
		return fillColor;
	}
};
class myRECTANGLE :public POLYGON
{
public:
	myRECTANGLE(vector<points> p, int nop, int c, int fc)
	{
		noOfPoints = 2;
		arr = new points[2];
		for (int i = 0; i < 2; i++)
		{
			arr[i] = p[i];
		}
		color = c;
		fillColor = fc;
		type = 4;
	}
	void draw()
	{
		setcolor(color);
		setlinestyle(0, 1, 4);
		myRectangle(arr[0].x, arr[0].y, arr[1].x, arr[1].y);
		setcolor(7);
	}
	bool contains(points p)
	{
		if (p.x >= arr[0].x && p.x <= arr[1].x && p.y >= arr[0].y && p.y <= arr[1].y)
			return true;
		return false;
	}
	void fill(int color)
	{
		int x = (arr[0].x + arr[1].x) / 2;
		int y = (arr[0].y + arr[1].y) / 2;
		int currentColor = getpixel(x, y);
		fillColor = color;
		if (currentColor != color)
			FloodFill(x, y, currentColor, color);
	}
	int getFillColor()
	{
		return fillColor;
	}
};
class TRIANGLE : public Shape
{
private:
	int fillColor;
public:
	TRIANGLE(points *p, int nop, int c, int fc)
	{
		noOfPoints = nop;
		arr = new points[nop];
		for (int i = 0; i < nop; i++)
		{
			arr[i] = p[i];
		}
		color = c;
		fillColor = fc;
		type = 5;
	}
	void draw()
	{
		setcolor(color);
		myTriangle(arr[0], arr[1], arr[2]);
		setcolor(7);
	}
	bool contains(points p)
	{
		double A = areaOfTriangle(arr[0], arr[1], arr[2]);
		double A1 = areaOfTriangle(p, arr[1], arr[2]);
		double A2 = areaOfTriangle(arr[0], p, arr[2]);
		double A3 = areaOfTriangle(arr[0], arr[1], p);
		if (A == A1 + A2 + A3)
			return true;
		return false;
	}
	void fill(int color)
	{
		int x = (arr[0].x + arr[1].x + arr[2].x) / 3;
		int y = (arr[0].y + arr[1].y + arr[2].y) / 3;
		int currentColor = getpixel(x, y);
		fillColor = color;
		if (currentColor != color)
			FloodFill(x, y, currentColor, color);
	}
	int getFillColor()
	{
		return fillColor;
	}
};
class OpenShape : public Shape
{
protected:
	bool style;
	int fillColor;
public:
	virtual void fill(int color)
	{
		int currentColor = getpixel(arr[0].x + 1, arr[0].y + 1);
		fillColor = color;
		FloodFill(arr[0].x + 1, arr[0].y + 1, currentColor, color);
	}
};
class Line : public OpenShape
{
public:
	Line(points* p, int nop, int c, int fc, bool s)
	{
		noOfPoints = nop;
		fillColor = fc;
		arr = new points[nop];
		for (int i = 0; i < nop; i++)
		{
			arr[i] = p[i];
		}
		color = c;
		style = s;
		type = 6;
	}
	void draw()
	{
		setcolor(color);
		if (style == true)
			setlinestyle(0, 0, 4);
		else
			setlinestyle(1, 1, 2);
		line(arr[0].x, arr[0].y, arr[1].x, arr[1].y);
		setcolor(7);
		setlinestyle(0, 1, 4);
	}
	bool contains(points p)
	{
		if (PointLiesOnLine(arr[0], arr[1], p) == true)
			return true;
		return false;
	}
	void fill(int color)
	{
		fillColor = color;
		setcolor(color);
		if (style == true)
			setlinestyle(0, 1, THICK_WIDTH);
		else
			setlinestyle(1, 1, 2);
		line(arr[0].x, arr[0].y, arr[1].x, arr[1].y);
		setcolor(7);
		setlinestyle(0, 1, 4);
	}
	int getFillColor()
	{
		return fillColor;
	}
};
class Curve : public OpenShape
{

public:
	Curve(vector<points> p, int nop, int c, int fc, bool s)
	{
		noOfPoints = nop;
		fillColor = fc;
		arr = new points[nop];
		for (int i = 0; i < nop; i++)
		{
			arr[i] = p[i];
		}
		color = c;
		style = s;
		type = 7;
	}
	void draw()
	{
		setcolor(color);
		if (style == true)
			setlinestyle(0, 1, THICK_WIDTH);
		else
			setlinestyle(1, 1, 2);
		for (int i = 0; i < noOfPoints - 1; i++)
		{
			line(arr[i].x, arr[i].y, arr[i + 1].x, arr[i + 1].y);
		}
		setcolor(7);
		setlinestyle(0, 1, 4);
	}
	bool contains(points p)
	{
		bool flag = 0;
		for (int i = 0; i < noOfPoints - 1 && flag == 0; i++)
		{
			if (PointLiesOnLine(arr[i], arr[i + 1], p) == true)
				flag = 1;
		}
		return flag;
	}
	void fill(int color)
	{
		fillColor = color;
		setcolor(color);
		if (style == true)
			setlinestyle(0, 1, THICK_WIDTH);
		else
			setlinestyle(1, 1, 2);
		for (int i = 0; i < noOfPoints - 1; i++)
		{
			line(arr[i].x, arr[i].y, arr[i + 1].x, arr[i + 1].y);
		}
		setcolor(7);
		setlinestyle(0, 1, 4);

	}
	int getFillColor()
	{
		return fillColor;
	}
};

int main()
{
	int window_ID = initwindow(600, 600, "Paint");
	panel();
	vector <Shape *> allShapes;
	fstream fin;
	fstream fin1;
	fstream fout;
	points c1;
	points c2;
	points c3;
	points c6;
	int nop = 0, x = 0, y = 0, r = 0, fillc = 0;
	setcolor(7);
	int size = 0;
	
	int current_W = initwindow(400, 150, "LOAD");
	setcurrentwindow(current_W);
	settextstyle(0, 0, 3);
	outtext("Do You want to ");
	moveto(0, 22);
	outtext("load your Work?");
	bar(50, 70, 125, 115);
	bar(200, 70, 275, 115);
	outtextxy(53,80,"Yes");
	outtextxy(210, 80, "No");
	while (!ismouseclick(WM_LBUTTONDOWN));
	getmouseclick(WM_LBUTTONDOWN, x, y);
	if (x >= 50 && x <= 125 && y >= 70 && y <= 115)  // YES

	{
		closegraph(CURRENT_WINDOW);
		setcurrentwindow(window_ID);
		fin.open("Output.pb");
		setcolor(15);
		setlinestyle(0, 1, 1);
		panel();
		setlinestyle(0, 1, 4);
		setcolor(7);
		fin >> size;
		int npoints;
		for (int i = 0; i < size; i++)
		{
			int t;
			int fc;
			fin >> t;
			fin >> npoints;
			if (t == 1)   // Circle
			{
				points  Points[2];
				int r;
				fin >> Points[0].x;
				fin >> Points[0].y;
				fin >> Points[1].x;
				fin >> Points[1].y;
				fin >> fc;
				r = sqrt(((Points[1].x - Points[0].x)*(Points[1].x - Points[0].x)) + ((Points[1].y - Points[0].y)*(Points[1].y - Points[0].y)));
				Circle *c = new Circle(Points, npoints, r, 7, fc);
				allShapes.push_back(c);
				c->draw();
				c->fill(fc);
			}
			else if (t == 2)  // text
			{
				vector <char> T;
				points  Points[2];
				fin >> Points[0].x;
				fin >> Points[0].y;
				fin >> Points[1].x;
				fin >> Points[1].y;
				fin >> fc;
				int leng = 0;
				fin.close();
				fin.open("text.pb");
				fin >> leng;
				for (int i = 0; i < leng; i++)
				{
					char cha[2] = { '\0','\0' };
					fin >> cha[0];
					T.push_back(cha[0]);
				}
				fin.close();
				Text *t = new Text(Points, npoints, 7, fc, T);
				allShapes.push_back(t);
				moveto(Points[0].x, Points[0].y);
				setcolor(7);
				t->draw();
				t->fill(fc);
				settextstyle(0, 0, 0);
				fin.open("Output.pb");
			}
			else if (t == 3)  // polygon
			{
				vector <points> Points;
				int j = 0;
				while (j < npoints)
				{
					points p;
					fin >> p.x;
					fin >> p.y;
					Points.push_back(p);
					j++;
				}
				fin >> fc;
				POLYGON *p = new POLYGON(Points, npoints, 7, fc);
				allShapes.push_back(p);
				p->draw();
				p->fill(fc);
			}
			else if (t == 4)  // Rectangle
			{
				vector <points> Points;
				int j = 0;
				while (j < npoints)
				{
					points p;
					fin >> p.x;
					fin >> p.y;
					Points.push_back(p);
					j++;
				}
				fin >> fc;
				myRECTANGLE *r = new myRECTANGLE(Points, npoints, 7, fc);
				allShapes.push_back(r);
				r->draw();
				r->fill(fc);
			}
			else if (t == 5)  // Triangle
			{
				points  Points[3];
				fin >> Points[0].x;
				fin >> Points[0].y;
				fin >> Points[1].x;
				fin >> Points[1].y;
				fin >> Points[2].x;
				fin >> Points[2].y;
				fin >> fc;
				TRIANGLE *t = new TRIANGLE(Points, npoints, 7, fc);
				allShapes.push_back(t);
				t->draw();
				t->fill(fc);
			}
			else if (t == 6)  // Line
			{
				points  Points[2];
				fin >> Points[0].x;
				fin >> Points[0].y;
				fin >> Points[1].x;
				fin >> Points[1].y;
				fin >> fc;
				Line *l = new Line(Points, npoints, 7, fc, 1);   // 1 for solid
				allShapes.push_back(l);
				l->draw();
				l->fill(fc);
			}
			else if (t == 7)  // Curve
			{
				vector <points> Points;
				int j = 0;
				while (j < npoints)
				{
					points p;
					fin >> p.x;
					fin >> p.y;
					Points.push_back(p);
					j++;
				}
				fin >> fc;
				Curve *c = new Curve(Points, npoints, 7, fc, 0);
				allShapes.push_back(c);
				c->draw();
				c->fill(fc);
			}
		}
	}
	else if (x >= 200 && x <= 275 && y >= 70 && y <= 115)
	{
		closegraph(CURRENT_WINDOW);
		setcurrentwindow(window_ID);
	}
	setlinestyle(0, 1, 4);
	while (true)
	{
		if (ismouseclick(WM_LBUTTONDOWN) == true)
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);
			cout << x << " " << y << endl;
			if (x >= 10 && x <= 25 && y >= 121 && y <= 135)   // CIRCLE
			{
				while (GetAsyncKeyState(VK_RBUTTON) != 1)
				{
					while (!ismouseclick(WM_LBUTTONDOWN));
					getmouseclick(WM_LBUTTONDOWN, x, y);
					c1.x = x;
					c1.y = y;
					points *p = new points[3];
					p[0] = c1;
					while (!ismouseclick(WM_LBUTTONDOWN));
					getmouseclick(WM_LBUTTONDOWN, x, y);
					c2.x = x;
					c2.y = y;
					p[1] = c2;
					nop = 2;
					r = sqrt(((c2.x - c1.x)*(c2.x - c1.x)) + ((c2.y - c1.y)*(c2.y - c1.y)));
					Circle *c = new Circle(p, nop, r, 7, BLACK);
					allShapes.push_back(c);
					c->draw();
					if (p != nullptr)
						delete[] p;
				}
			}
			else if (x >= 35 && x <= 45 && y >= 121 && y <= 135)   // TRIANGLE
			{
				while (GetAsyncKeyState(VK_RBUTTON) != 1)
				{
					while (!ismouseclick(WM_LBUTTONDOWN));
					getmouseclick(WM_LBUTTONDOWN, x, y);
					c1.x = x;
					c1.y = y;
					while (!ismouseclick(WM_LBUTTONDOWN));
					getmouseclick(WM_LBUTTONDOWN, x, y);
					c2.x = x;
					c2.y = y;
					while (!ismouseclick(WM_LBUTTONDOWN));
					getmouseclick(WM_LBUTTONDOWN, x, y);
					c3.x = x;
					c3.y = y;
					nop = 3;
					points *p = new points[nop];
					p[0] = c1;
					p[1] = c2;
					p[2] = c3;

					TRIANGLE *t = new TRIANGLE(p, nop, 7, BLACK);
					allShapes.push_back(t);
					t->draw();
					if (p != nullptr)
						delete[] p;
				}
			}
			else if (x >= 62 && x <= 75 && y >= 121 && y <= 135)   // RECTANGLE
			{
				while (GetAsyncKeyState(VK_RBUTTON) != 1)
				{
					while (!ismouseclick(WM_LBUTTONDOWN));
					getmouseclick(WM_LBUTTONDOWN, x, y);
					c1.x = x;
					c1.y = y;
					while (!ismouseclick(WM_LBUTTONDOWN));
					getmouseclick(WM_LBUTTONDOWN, x, y);
					c2.x = x;
					c2.y = y;
					vector<points> p;
					points p1;
					points p2;
					p1 = c1;
					p2 = c2;
					nop = 2;
					p.push_back(p1);
					p.push_back(p2);
					myRECTANGLE *r = new myRECTANGLE(p, nop, 7, BLACK);
					allShapes.push_back(r);
					r->draw();
					p.clear();
				}
			}
			else if (x >= 10 && x <= 25 && y >= 150 && y <= 165)   // LINE
			{
				while (GetAsyncKeyState(VK_RBUTTON) != 1)
				{
					points *L = new points[2];
					while (!ismouseclick(WM_LBUTTONDOWN));
					getmouseclick(WM_LBUTTONDOWN, x, y);
					L[0].x = x;
					L[0].y = y;
					while (!ismouseclick(WM_LBUTTONDOWN));
					getmouseclick(WM_LBUTTONDOWN, x, y);
					L[1].x = x;
					L[1].y = y;

					Line *l = new Line(L, 2, 7, BLACK, 1);   // 0 is for dotted
					allShapes.push_back(l);
					l->draw();
					if (L != nullptr)
						delete[] L;
				}
			}
			else if (x >= 38 && x <= 54 && y >= 150 && y <= 165)   // POLYGON
			{
				//while (GetAsyncKeyState(VK_MENU) != 1)
				{
					vector<points> p;
					points p1;
					nop = 0;
					while (GetAsyncKeyState(VK_RBUTTON) != 1)
					{
						while (!ismouseclick(WM_LBUTTONDOWN));
						getmouseclick(WM_LBUTTONDOWN, x, y);
						nop++;
						p1.x = x;
						p1.y = y;
						p.push_back(p1);
					}
					POLYGON *P = new POLYGON(p, nop, 7, BLACK);
					allShapes.push_back(P);
					P->draw();
					p.clear();
				}
			}
			else if (x >= 61 && x <= 75 && y >= 150 && y <= 165)   // CURVE
			{
				//while (GetAsyncKeyState(VK_MENU) != 1)  // ALT key
				{
					vector<points> p;
					points p1;
					nop = 0;
					while (GetAsyncKeyState(VK_RBUTTON) != 1)
					{
						while (!ismouseclick(WM_LBUTTONDOWN));
						getmouseclick(WM_LBUTTONDOWN, x, y);
						nop++;
						p1.x = x;
						p1.y = y;
						p.push_back(p1);
					}
					Curve *c = new Curve(p, nop, 7, BLACK, 0);   // 0 is for dotted
					allShapes.push_back(c);
					c->draw();
					p.clear();
				}
			}
			else if (x >= 10 && x <= 55 && y >= 174 && y <= 194)   // TEXT
			{
			//	while (GetAsyncKeyState(VK_RBUTTON) != 1)
				{
					while (!ismouseclick(WM_LBUTTONDOWN));
					getmouseclick(WM_LBUTTONDOWN, x, y);
					settextstyle(10, HORIZ_DIR, 4);
					c1.x = x;
					c1.y = y;
					vector<char> text;
					points *p = new points[2];
					p[0] = c1;
					char cha[2] = { '\0','\0' };
					cha[0] = getch();
					int len = 1;
					moveto(c1.x, c1.y);
					while (cha[0] != 13)
					{
						outtext(cha);
						text.push_back(cha[0]);
						len++;
						cha[0] = getch();
						c1.x = getx();
						c1.y = gety();
					}
					p[1] = c1;
					Text *t = new Text(p, 2, 7, 7, text);
					allShapes.push_back(t);
					{
					    fout.open("text.pb");
						fout << len << endl;
						for (int i = 0; i < text.size(); i++)
						{
							fout << text[i];
							fout << endl;
						}
						fout.close();
					}
					settextstyle(0, 0, 0);
					text.clear();
				}
			}

			else if (x >= 17 && x <= 35 && y >= 268 && y <= 294)         // BUCKET
			{
				while (!ismouseclick(WM_LBUTTONDOWN));
				getmouseclick(WM_LBUTTONDOWN, x, y);
				if (x >= 10 && x <= 25 && y >= 25 && y <= 40)    // Red color
				{
					while (GetAsyncKeyState(VK_RBUTTON) != 1)
					{
						while (!ismouseclick(WM_LBUTTONDOWN));
						getmouseclick(WM_LBUTTONDOWN, x, y);
						c1.x = x;
						c1.y = y;
						for (int i = 0; i < allShapes.size(); i++)
						{
							if (allShapes[i]->contains(c1) == true)
							{
								int clr = allShapes[i]->getFillColor();
								if (clr != RED)
									allShapes[i]->fill(RED);
							}
						}
					}
				}
				else if (x >= 35 && x <= 50 && y >= 25 && y <= 40)    // GREEN color
				{
					while (GetAsyncKeyState(VK_RBUTTON) != 1)
					{
						while (!ismouseclick(WM_LBUTTONDOWN));
						getmouseclick(WM_LBUTTONDOWN, x, y);
						c1.x = x;
						c1.y = y;
						for (int i = 0; i < allShapes.size(); i++)
						{
							if (allShapes[i]->contains(c1) == true)
							{
								int clr = allShapes[i]->getFillColor();
								if (clr != GREEN)
									allShapes[i]->fill(GREEN);
							}
						}
					}
				}
				else if (x >= 60 && x <= 75 && y >= 25 && y <= 40)    // BLUE color
				{
					while (GetAsyncKeyState(VK_RBUTTON) != 1)
					{
						while (!ismouseclick(WM_LBUTTONDOWN));
						getmouseclick(WM_LBUTTONDOWN, x, y);
						c1.x = x;
						c1.y = y;
						for (int i = 0; i < allShapes.size(); i++)
						{
							if (allShapes[i]->contains(c1) == true)
							{
								int clr = allShapes[i]->getFillColor();
								if (clr != BLUE)
									allShapes[i]->fill(BLUE);
							}
						}
					}
				}
				else if (x >= 10 && x <= 25 && y >= 50 && y <= 65)    // YELLOW color
				{
					while (GetAsyncKeyState(VK_RBUTTON) != 1)
					{
						while (!ismouseclick(WM_LBUTTONDOWN));
						getmouseclick(WM_LBUTTONDOWN, x, y);
						c1.x = x;
						c1.y = y;
						for (int i = 0; i < allShapes.size(); i++)
						{
							if (allShapes[i]->contains(c1) == true)
							{
								int clr = allShapes[i]->getFillColor();
								if (clr != YELLOW)
									allShapes[i]->fill(YELLOW);
							}
						}
					}
				}
				else if (x >= 35 && x <= 50 && y >= 50 && y <= 65)    // PINK color
				{
					while (GetAsyncKeyState(VK_RBUTTON) != 1)
					{
						while (!ismouseclick(WM_LBUTTONDOWN));
						getmouseclick(WM_LBUTTONDOWN, x, y);
						c1.x = x;
						c1.y = y;
						for (int i = 0; i < allShapes.size(); i++)
						{
							if (allShapes[i]->contains(c1) == true)
							{
								int clr = allShapes[i]->getFillColor();
								if (clr != 13)
									allShapes[i]->fill(13);
							}
						}
					}
				}
				else if (x >= 60 && x <= 75 && y >= 50 && y <= 65)    // WHITE color
				{
					while (GetAsyncKeyState(VK_RBUTTON) != 1)
					{
						while (!ismouseclick(WM_LBUTTONDOWN));
						getmouseclick(WM_LBUTTONDOWN, x, y);
						c1.x = x;
						c1.y = y;
						for (int i = 0; i < allShapes.size(); i++)
						{
							if (allShapes[i]->contains(c1) == true)
							{
								int clr = allShapes[i]->getFillColor();
								if (clr != WHITE)
									allShapes[i]->fill(WHITE);
							}
						}
					}
				}
				else if (x >= 10 && x <= 25 && y >= 75 && y <= 90)    // BLACK color
				{
					while (GetAsyncKeyState(VK_RBUTTON) != 1)
					{
						while (!ismouseclick(WM_LBUTTONDOWN));
						getmouseclick(WM_LBUTTONDOWN, x, y);
						c1.x = x;
						c1.y = y;
						for (int i = 0; i < allShapes.size(); i++)
						{
							if (allShapes[i]->contains(c1) == true)
							{
								int clr = allShapes[i]->getFillColor();
								if (clr != BLACK)
									allShapes[i]->fill(BLACK);
							}
						}
					}
				}
			}
			else if (x >= 10 && x <= 45 && y >= 220 && y <= 240)   // ERASOR
			{
				while (GetAsyncKeyState(VK_RBUTTON) != 1)
				{
					while (!ismouseclick(WM_LBUTTONDOWN));
					getmouseclick(WM_LBUTTONDOWN, x, y);
					c1.x = x;
					c1.y = y;
					int index;
					int flag = 0;
					for (int i = allShapes.size() - 1; i >= 0; i--)
					{
						if (allShapes[i]->contains(c1) == true)
						{
							index = i;
							flag = 1;
							cleardevice();
							break;
						}
					}
					vector <Shape *> allShapesNew;
					for (int i = 0; i < allShapes.size(); i++)
					{
						if (i == index && i != allShapes.size() - 1)
							i++;
						if (i == index && i == allShapes.size() - 1)
							break;
						allShapesNew.push_back(allShapes[i]);
					}
					allShapes = allShapesNew;
					if (flag == 1)
					{
						setcolor(15);
						setlinestyle(0, 1, 1);
						panel();
						setlinestyle(0, 1, 4);
						setcolor(7);
						for (int i = 0; i < allShapes.size(); i++)
						{
							allShapes[i]->draw();
							int fillcol = allShapes[i]->getFillColor();
							if (fillcol != 0)
								allShapes[i]->fill(allShapes[i]->getFillColor());
						}
					}
				}
			}
			else if (x >= 14 && x <= 45 && y >= 317 && y <= 340)   // SAVE
			{
				while (!ismouseclick(WM_LBUTTONDOWN));
				getmouseclick(WM_LBUTTONDOWN, x, y);
				c1.x = x;
				c1.y = y;
				cout << "yes";
				fout.open("Output.pb");

				/*for (int i = 95; i < 600; i++)
				{
					for (int j = 0; j < 600; j++)
					{
						int a = getpixel(i, j);
						fout << a;
						fout << endl;
					}
				}*/
				fout << allShapes.size();
				fout << endl;
				int type;
				for (int i = 0; i < allShapes.size(); i++)
				{
					int t;
					t = allShapes[i]->getType();
					fout << t	<<	endl;
					int nop=allShapes[i]->getNoOfPoints();
					fout << nop;
					fout << endl;
					points*  a;
					a = allShapes[i]->getArr();
					for (int i = 0; i < nop; i++)
					{
						fout << a[i].x;
						fout << endl;
						fout << a[i].y;
						fout << endl;
					}
					fout << allShapes[i]->getFillColor();
					fout << endl;
				}
			}
			else if (x >= 14 && x <= 45 && y >= 368 && y <= 400)   // LOAD
			{
				/*while (!ismouseclick(WM_LBUTTONDOWN));
				getmouseclick(WM_LBUTTONDOWN, x, y);
				c1.x = x;
				c1.y = y;*/
				cout << "yes";
				
				cleardevice();
			/*	for (int i = 0; i < allShapes.size(); i++)   // deallocation
				{
					delete allShapes[i];
				}
				allShapes.clear();  */
				fin1.open("Output.pb");
				setcolor(15);
				setlinestyle(0, 1, 1);
				panel();
				setlinestyle(0, 1, 4);
				setcolor(7);
				//int size;
				fin1 >> size;
				int npoints;
				for (int i = 0; i < size; i++)
				{
					int t;
					int fc;
					fin1 >> t;
					fin1 >> npoints;
					if (t == 1)   // Circle
					{
						points  Points[2];
						int r;
						fin1 >> Points[0].x;
						fin1 >> Points[0].y;
						fin1 >> Points[1].x;
						fin1 >> Points[1].y;
						fin1 >> fc;
						r = sqrt(((Points[1].x - Points[0].x)*(Points[1].x - Points[0].x)) + ((Points[1].y - Points[0].y)*(Points[1].y - Points[0].y)));
						Circle *c = new Circle(Points, npoints, r,7, fc);
						allShapes.push_back(c);
						c->draw();
						c->fill(fc);
					}
					else if (t == 2)  // text
					{
						vector <char> T;
						points  Points[2];
						fin1 >> Points[0].x;
						fin1 >> Points[0].y;
						fin1 >> Points[1].x;
						fin1 >> Points[1].y;
						fin1 >> fc;
						int leng=0;
						fin1.close();
						fin1.open("text.pb");
						fin1 >> leng;
						for (int i = 0; i < leng; i++)
						{
							char cha[2] = { '\0','\0' };
							fin1 >> cha[0];
							T.push_back(cha[0]);
						}
						fin1.close();
				    	Text *t = new Text(Points, npoints, 7, fc,T);
						allShapes.push_back(t);
						moveto(Points[0].x, Points[0].y);
						setcolor(7);
						t->draw();
						t->fill(fc);
						settextstyle(0, 0, 0);
					}
					else if (t == 3)  // polygon
					{
						vector <points> Points;
						int j=0;
						while (j < npoints)
						{
							points p;
							fin1 >> p.x;
							fin1 >> p.y;
							Points.push_back(p);
							j++;
						}
						fin1 >> fc;
						POLYGON *p = new POLYGON(Points, npoints, 7, fc);
						allShapes.push_back(p);
						p->draw();
						p->fill(fc);
					}
					else if (t == 4)  // Rectangle
					{
						vector <points> Points;
						int j = 0;
						while (j < npoints)
						{
							points p;
							fin1 >> p.x;
							fin1 >> p.y;
							Points.push_back(p);
							j++;
						}
						fin1 >> fc;
						myRECTANGLE *r = new myRECTANGLE(Points, npoints, 7, fc);
						allShapes.push_back(r);
						r->draw();
						r->fill(fc);
					}
					else if (t == 5)  // Triangle
					{
						points  Points[3];
						fin1 >> Points[0].x;
						fin1 >> Points[0].y;
						fin1 >> Points[1].x;
						fin1 >> Points[1].y;
						fin1 >> Points[2].x;
						fin1 >> Points[2].y;
						fin1 >> fc;
						TRIANGLE *t = new TRIANGLE(Points, npoints,7, fc);
						allShapes.push_back(t);
						t->draw();
						t->fill(fc);
					}
					else if (t == 6)  // Line
					{
						points  Points[2];
						fin1 >> Points[0].x;
						fin1 >> Points[0].y;
						fin1 >> Points[1].x;
						fin1 >> Points[1].y;
						fin1 >> fc;
						Line *l = new Line(Points, npoints, 7, fc,1);   // 1 for solid
						allShapes.push_back(l);
						l->draw();
						l->fill(fc);
					}
					else if (t == 7)  // Curve
					{
						vector <points> Points;
						int j = 0;
						while (j < npoints)
						{
							points p;
							fin1 >> p.x;
							fin1 >> p.y;
							Points.push_back(p);
							j++;
						}
						fin1 >> fc;
						Curve *c = new Curve(Points, npoints, 7, fc,0);
						allShapes.push_back(c);
						c->draw();
						c->fill(fc);
					}
				}
			}
		}
	}
	for (int i = 0; i < allShapes.size(); i++)   // deallocation
	{
		delete allShapes[i];
	}
	allShapes.clear();

	return 0;
}
