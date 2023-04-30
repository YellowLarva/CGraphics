#include <stdio.h>
#include <iostream>
#include <graphics.h>
#include <math.h>

using namespace std;

void bresenhams(int x,int y,int x2,int y2,int shade){    
    int dx,dy;
    int d;
    dx=(x2-x);
    dy=(y2-y);
    d=2*dy-dx;
    if(dx>=0 & dy>=0){			
        if(dy>dx){          
            if(dx==0){
                while(y<=y2){
                    putpixel(x,y,shade);
                    y++;
                    if(d<0){
                        d=d+2*dy;
                    }
                    else{
                    d=d+2*dy-2*dx;
                    }
        
                }
            }
            else{
                while(x<=x2){
                    putpixel(x,y,shade);
                    x++;
                    if(d<0){
                    d=d+2*dy;
                    }
                    else{
                    d=d+2*dy-2*dx;
                    y++;
                    }
                }
            }
	}
	else if(dx>dy){	

	    while(x<=x2){
     		putpixel(x,y,shade);
     		x++;
     		if(d<0){
     		d=d+2*dy;
		 	}
		 	else{
		 	d=d+2*dy-2*dx;
		 		y++;
		 	}
		 
	 	}
	 }
	 }
	 
	else if(dy<0 || dx<0){	
			swap(x,x2);
			swap(y,y2);
            while(x>x2){
     			putpixel(x,y,shade);
     			x--;
     			if(d<0){
     			d=d-2*dy;
		 		}
		 		else{
		 		d=d-2*dy-2*dx;
		 		y++;
		 		}
	 		}
	
	}
}

int main()
{
    int gd = DETECT, gm;
    char pathtodriver[] = "";
    initgraph(&gd, &gm, pathtodriver);
    int x1,y1,x2,y2;
    cout<<"enter x1 y1 x2 y2 respectively "<<endl;
    cin>>x1>>y1>>x2>>y2;
    bresenhams(x1,y1,x2,y2,WHITE);
    getch();
    closegraph();
    return 0;
}