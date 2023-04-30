#include <stdio.h>
#include <graphics.h>
#include<iostream>
#include<cmath>
using namespace std;
int points[80][2] = { { 0 } },news[80][2] = { { 0 } };

int leftClip(int, int);
int topClip(int, int);
int rightClip(int, int);
int bottomClip(int, int);

int main() {
	int gd = DETECT, gm, xmin, ymin, xmax, ymax, n, i;
	cout<<	"Enter the co-ordinates of top left corner of the clipping window: "<<endl;
	cin>> xmin;
	cin>> ymin;
cout<<
			"Enter the co-ordinates of  right bottom corner of the clipping window: "<<endl;
	cin>> xmax;
	cin>>ymax;

	cout<<"Enter the number of co-ordinates of the polygon: "<<endl;
	cin>> n;

	for (i = 0; i < n; i++) {
		cout<<"Enter the co-ordinates of vertex : "<< i + 1<<" ";
		cin>> points[i][0];
		cin>>points[i][1];
	}

	initgraph(&gd, &gm, NULL);

	rectangle(xmin, ymin, xmax, ymax);
	for (i = 0; i < n; i++)
		line(points[i][0], points[i][1], points[(i + 1) % n][0],
				points[(i + 1) % n][1]);

	int result = leftClip(n, xmin);
	for(i=0;i<result;i++)
	{
	cout<<points[i][0];
	cout<<points[i][1];
	cout<<endl;
   }
   cout<<endl;
	result = topClip(result, ymin);
	for(i=0;i<result;i++)
	{
	cout<<points[i][0];
	cout<<points[i][1];
	cout<<endl;
   }
	result = rightClip(result, xmax);
	cout<<endl;
	for(i=0;i<result;i++)
	{
	cout<<points[i][0];
	cout<<points[i][1];
	cout<<endl;
   }
	result = bottomClip(result, ymax);
	cout<<endl;
	for(i=0;i<result;i++)
	{
	cout<<points[i][0];
	cout<<points[i][1];
	cout<<endl;
   }
    setcolor(14);
	for (i = 0; i < result; i++)
		line(points[i][0], points[i][1], points[(i + 1) % result][0],
				points[(i + 1) % result][1]);
	getch();
    closegraph();
	return 0;
}

int leftClip(int limit, int xmin) {
	int i, j = 0, x1, y1, x2, y2;
	float m;
	for (i = 0; i < limit; i++) {
		x1 = points[i][0];
		y1 = points[i][1];
		x2 = points[(i + 1) % limit][0];
		y2 = points[(i + 1) % limit][1];
		if (x2 - x1)
			m = (y2 - y1) * 1.0 / (x2 - x1);

		if (x1 < xmin && x2 < xmin)
			continue;
		if (x1 > xmin && x2 > xmin) {
			news[j][0] = x2;
			news[j++][1] = y2;
			continue;
		}
		if (x1 >= xmin && x2 <= xmin) {
			news[j][0] = xmin;
			news[j++][1] = y1 + m * (xmin - x1);
			continue;
		}
		if (x1 <= xmin && x2 >= xmin) {
			news[j][0] = xmin;
			news[j++][1] = y1 + m * (xmin - x1);
			news[j][0] = x2;
			news[j++][1] = y2;
		}
	}

	for (i = 0; i < j; i++) {
		points[i][0] = news[i][0];
		points[i][1] = news[i][1];
		news[i][0] = news[i][1] = 0;
	}

	if (j < limit)
		for (; i < limit; i++)
			points[i][0] = points[i][1] = 0;

	return j;
}

int topClip(int limit, int ymin) {
	int i, j = 0, x1, y1, x2, y2;
	float m;
	for (i = 0; i < limit; i++) {
		x1 = points[i][0];
		y1 = points[i][1];
		x2 = points[(i + 1) % limit][0];
		y2 = points[(i + 1) % limit][1];
		if (x2 - x1)
			m = (y2 - y1) * 1.0 / (x2 - x1);

		if (y1 < ymin && y2 < ymin)
			continue;
		if (y1 > ymin && y2 > ymin) {
			news[j][0] = x2;
			news[j++][1] = y2;
			continue;
		}
		if (y1 >= ymin && y2 <= ymin) {
			if(x1==x2)
			{
				news[j][0]=x1;
				news[j++][1]=ymin;
			}
			else{
			news[j][0] = x1 + (ymin - y1) / m;
			news[j++][1] = ymin;	
			}
			
			continue;
		}
		if (y1 <= ymin && y2 >= ymin) {
			if(x1==x2){
			news[j][0] = x1;
			news[j++][1] = ymin;
			news[j][0] = x2;
			news[j++][1] = y2;	
			}
			else{
			news[j][0] = x1 + (ymin - y1) / m;
			news[j++][1] = ymin;
			news[j][0] = x2;
			news[j++][1] = y2;	
			}
			
		}
		
	}

	for (i = 0; i < j; i++) {
		points[i][0] = news[i][0];
		points[i][1] = news[i][1];
		news[i][0] = news[i][1] = 0;
	}

	if (j < limit)
		for (; i < limit; i++)
			points[i][0] = points[i][1] = 0;

	return j;
}

int rightClip(int limit, int xmax) {
	int i, j = 0, x1, y1, x2, y2;
	float m;
	for (i = 0; i < limit; i++) {
		x1 = points[i][0];
		y1 = points[i][1];
		x2 = points[(i + 1) % limit][0];
		y2 = points[(i + 1) % limit][1];
		if (x2 - x1)
			m = (y2 - y1) * 1.0 / (x2 - x1);

		if (x1 > xmax && x2 > xmax)
			continue;
		if (x1 < xmax && x2 < xmax) {
			news[j][0] = x2;
			news[j++][1] = y2;
			continue;
		}
		if (x1 <= xmax && x2 >= xmax) {
			/*if(m==0){
			news[j][0] = xmax;
			news[j++][1] = y1;	
			}
			else*/{
			news[j][0] = xmax;
			news[j++][1] = y1 + m * (xmax - x1);	
			}
			
			continue;
		}
		if (x1 >= xmax && x2 <= xmax) {
		/*	if(m==0){
			news[j][0] = xmax;
			news[j++][1] = y1 ;
			news[j][0] = x2;
			news[j++][1] = y2;	
			}
			else*/{
				news[j][0] = xmax;
			news[j++][1] = y1 + m * (xmax - x1);
			news[j][0] = x2;
			news[j++][1] = y2;
			}
			
		}
	}

	for (i = 0; i < j; i++) {
		points[i][0] = news[i][0];
		points[i][1] = news[i][1];
		news[i][0] = news[i][1] = 0;
	}

	if (j < limit)
		for (; i < limit; i++)
			points[i][0] = points[i][1] = 0;

	return j;
}

int bottomClip(int limit, int ymax) {
	int i, j = 0, x1, y1, x2, y2;
	float m;
	for (i = 0; i < limit; i++) {
		x1 = points[i][0];
		y1 = points[i][1];
		x2 = points[(i + 1) % limit][0];
		y2 = points[(i + 1) % limit][1];
		if (x2 - x1)
			m = (y2 - y1) * 1.0 / (x2 - x1);

		if (y1 > ymax && y2 > ymax)
			continue;
		if (y1 < ymax && y2 < ymax) {
			news[j][0] = x2;
			news[j++][1] = y2;
			continue;
		}
		if (y1 <= ymax && y2 >= ymax) {
			if(x1==x2){
			news[j][0] = x1;
			news[j++][1] = ymax;	
			}
			else{
			news[j][0] = x1 + (ymax - y1) / m;
			news[j++][1] = ymax;
			}
			
			continue;
		}
		if (y1 >= ymax && y2 <= ymax) {
			if(x1==x2){
			news[j][0] = x1;
			news[j++][1] = ymax;
			news[j][0] = x2;
			news[j++][1] = y2;	
			}
			else{
			news[j][0] = x1 + (ymax - y1) / m;
			news[j++][1] = ymax;
			news[j][0] = x2;
			news[j++][1] = y2;	
			}
			
		}
		
		
	}

	for (i = 0; i < j; i++) {
		points[i][0] = news[i][0];
		points[i][1] = news[i][1];
		news[i][0] = news[i][1] = 0;
	}

	if (j < limit)
		for (; i < limit; i++)
			points[i][0] = points[i][1] = 0;

	return j;
}

