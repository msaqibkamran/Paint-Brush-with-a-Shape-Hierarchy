
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
	vector <Shape *> allShapes;
	fstream fin;
	fstream fout;
	int window_ID = initwindow(600, 600, "Paint");
	panel();
	points c1;
	points c2;
	points c3;
	points c6;
	int nop = 0, x = 0, y = 0, r = 0, fillc = 0;
	setcolor(7);
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
				while (GetAsyncKeyState(VK_RBUTTON) != 1)
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
					moveto(c1.x, c1.y);
					int i = 7;
					while (cha[0] != 13)
					{
						outtext(cha);
						text.push_back(cha[0]);
						cha[0] = getch();
						c1.x = getx();
						c1.y = gety();
					}
					p[1] = c1;
					Text *t = new Text(p, 2, 7, BLACK, text);
					allShapes.push_back(t);
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

				for (int i = 95; i < 600; i++)
				{
					for (int j = 0; j < 600; j++)
					{
						int a = getpixel(i, j);
						fout << a;
						fout << endl;
					}
				}
			}
			else if (x >= 14 && x <= 45 && y >= 368 && y <= 400)   // LOAD
			{
				while (!ismouseclick(WM_LBUTTONDOWN));
				getmouseclick(WM_LBUTTONDOWN, x, y);
				c1.x = x;
				c1.y = y;
				cout << "yes";
				fin.open("Output.pb");
				int p;
				for (int i = 95; i < 600; i++)
				{
					for (int j = 0; j <600; j++)
					{
						fin >> p;
						putpixel(i, j, p);
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
