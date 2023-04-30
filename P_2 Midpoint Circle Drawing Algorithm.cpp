#include<stdio.h>
#include<graphics.h>
#include<cmath>
#include <iostream>
using namespace std;

void drawCircle(int x, int y, int xc, int yc){
	putpixel(x+xc,y+yc,WHITE);
	putpixel(-x+xc,y+yc,WHITE);
	putpixel(x+xc, -y+yc,WHITE);
	putpixel(-x+xc, -y+yc, WHITE);
	putpixel(y+xc, x+yc, WHITE);
	putpixel(y+xc, -x+yc, WHITE);
	putpixel(-y+xc, x+yc, WHITE);
	putpixel(-y+xc, -x+yc, WHITE);
}

int main(){
	int gd = DETECT, gm;
	int r, xc, yc, h, x, y;
	char pathtodriver[] = "";
   	initgraph(&gd, &gm, pathtodriver);  
	cout<<"Enter the center co-ordinates\n";
	cin>>xc>>yc;
	cout<<"Enter the radius of circle\n";
	cin>>r;
	h = 1 - r;
	x = 0;
	y = r;
	while(x < y)
	{
		drawCircle(x,y,xc,yc);
		++x;
		if(h < 0)
		{
			h = h + (2*x) + 1;
		}
		else
		{
			--y;
			h = h + (2*x) + 1 - (2*y);
		}
	}
	getch();
	closegraph();
	return 0;
}
