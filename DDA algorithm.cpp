#include <stdio.h>
#include <iostream>
#include <graphics.h>
#include <math.h>

using namespace std;


class dda{
private:
    int x1, y1, x2, y2, shade;
public:
    dda(int x1, int y1, int x2, int y2, int shade) : x1(x1), y1(y1), x2(x2), y2(y2), shade(shade) {}
    void getLine(){
        
        int window = initwindow(500,500,"");
  
        setbkcolor(BLACK);
//        cleardevice();
        

        double dx = x2 - x1;
        double dy = y2 - y1;
        cout << "dx" << dx << "\n"; 
        cout << "dy" << dy << "\n"; 
		 
        double steps = max(abs(dx),abs(dy));
        cout << "steps " << steps << "\n"; 
        

        double X_shift = dx / steps;
        double Y_shift = dy / steps;
        
        cout << "steps x  " << X_shift << "\n"; 
        cout << "steps y  " << Y_shift << "\n"; 

        double x = x1;
        double y = y1;
        for (int i = 0; i <= steps; i++){
            putpixel(round(x), round(y), shade);
            x += X_shift;
            y += Y_shift;
        }
        
    }

};

int main(){
    dda l1(300,200,200,300,WHITE);
//    dda l2(300,300,200,100,WHITE);
//    dda l3(100,200,200,100,WHITE);
    l1.getLine();
//    l2.getLine();
//    l3.getLine();
    getch();
    closegraph();
    return 0;
}

