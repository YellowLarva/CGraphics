#include<iostream>
#include<graphics.h>
#include<cstdio>
using namespace std;

const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;

template <typename T>
class point{

	public: 
		T x, y;
		point(){
			x = y = 0;
		}
		point(T x, T y){		//constructer
			this->x = x;
			this->y = y;
		}
		void enterPoint(bool print=false){
			cout<<"\nX co-ordinate: ";
			cin>>x;
			cout<<"\nY co-ordinate: ";
			cin>>y;
		}
		void setPoint(T x, T y){
			this->x = x;
			this->y = y;
		}

};
class line_clipping{
	private: 
		point<int> p1, p2;
		int l, t, r, b;
	//function to generate outcodes			
	int generateOutcode(point<int> p){
		int outcode = INSIDE;
		if(p.x < l)
			outcode |= LEFT;
		else if(p.x > r)
			outcode |= RIGHT;
			
		if(p.y < t)
			outcode |= TOP;
		else if(p.y > b)
			outcode |= BOTTOM;
			
		return outcode;
	}
	
	public:
		line_clipping(){
			l = t = 200;
			r = 500;
			b = 400;
		}
		line_clipping(point<int> top, point<int> bottom){
			l = top.x;
			t = top.y;
			r = bottom.x;			
			b = bottom.y;	
		}
		void getCoordinates(){
			cout << "Clip Window lie in range x [200,500] y [200,400] \n";
			cout<<"\nEnter First point";
			p1.enterPoint();
			cout<<"\nEnter Second point";
			p2.enterPoint();	

		}
		
		void plotline(){
			int o1 = generateOutcode(p1);
			int o2 = generateOutcode(p2);
			bool accept = false;
			while(true){
				if(o1 == 0 && o2 == 0){
					//if line is completely inside (Trivially accepted)
					accept = true;
					break;
				}else if(o1 & o2){
				//	( Trivially rejected)
					break;
				}else{
					//clipping is required
					int otemp;
					point<int> temp;
					otemp = o1 != 0? o1 : o2;
					
					if(otemp & TOP){
						temp.x = p1.x + (p2.x - p1.x)*(t - p1.y) / (p2.y - p1.y);
						temp.y = t;
					}else if(otemp & BOTTOM){
						temp.x = p1.x + (p2.x - p1.x)*(b - p1.y) / (p2.y - p1.y);
						temp.y = b;
					}else if(otemp & LEFT){
						temp.y = p1.y + (p2.y - p1.y)*(l - p1.x) / (p2.x - p1.x);
						temp.x = l;
					}else if(otemp & RIGHT){
						temp.y = p1.y + (p2.y - p1.y)*(r - p1.x) / (p2.x - p1.x);
						temp.x = r;
					}


					if(otemp == o1){
						p1.x = temp.x;
						p1.y = temp.y;
						o1 = generateOutcode(p1);
					}else{
						p2.x = temp.x;
						p2.y = temp.y;
						o2 = generateOutcode(p2);
					}
				
				
				}
			}
			setcolor(RED);
			
			if(accept){ 
			   //to display clipped line in green colour.
				setcolor(GREEN);
				line(p1.x, p1.y, p2.x, p2.y);
			}else{
				setcolor(RED); // rejected line in red colour.
				line(p1.x, p1.y, p2.x, p2.y);
			}
		}
		
		void clip(){
			int gd = DETECT, gm;
		    initgraph(&gd, &gm,(char*) "D:\\SW\\Dev-Cpp\\MinGW64\\include");	
		    //clipping rectangle
			rectangle(200, 200, 500, 400);
			setcolor(RED);
			//original line
			line(p1.x,p1.y,p2.x,p2.y);
			plotline();	
			getch();	
			
		}
};
int main(){
	line_clipping ob;
	//to input coordinates of lines
	ob.getCoordinates();
	//line clipping function
	ob.clip();
	return 0;
}

