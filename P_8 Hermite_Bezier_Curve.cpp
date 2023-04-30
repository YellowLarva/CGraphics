#include <iostream>
#include <conio.h>
#include <graphics.h>
#include <math.h>
using namespace std;
void bezier_curve(int x[4], int y[4])
{
    double t;
    for (t = 0.0; t < 1.0; t = t + 0.0005)
    {
        double xt = pow(1 - t, 3) * x[0] + 3 * t * pow(1 - t, 2) * x[1] + 3 * pow(t, 2) * (1 - t) * x[2] + pow(t, 3) * x[3];
        double yt = pow(1 - t, 3) * y[0] + 3 * t * pow(1 - t, 2) * y[1] + 3 * pow(t, 2) * (1 - t) * y[2] + pow(t, 3) * y[3];
        putpixel(xt, yt, YELLOW);
    }
    for (int i = 0; i < 3; i++)
    {
        line(x[i], y[i], x[i + 1], y[i + 1]);
    }
}
void hermite_curve(int x1, int y1, int x2, int y2, double t1, double t4)
{
    float x, y, t;
    for (t = 0.0; t <= 1.0; t += 0.001)
    {
        float h1 = 2 * t * t * t - 3 * t * t + 1;
        float h2 = -2 * t * t * t + 3 * t * t;
        float h3 = t * t * t - 2 * t * t + t;
        float h4 = t * t * t - t * t;
        x = (h1 * x1) + (h2 * x2) + (h3 * t1) + (h4 * t4);
        y = (h1 * y1) + (h2 * y2) + (h3 * t1) + (h4 * t4);
        // x=((2*t*t*t-3*t*t+1)*x1)+((-2*t*t*t+3*t*t)*x2)+((t*t*t2*t*t+t)*t1)+((t*t*t-t*t)*t4);
        // y=(2*t*t*t-3*t*t+1)*y1+(-2*t*t*t+3*t*t)*y2+(t*t*t2*t*t+1)*t1+(t*t*t-t*t)*t4;
        putpixel(x, y, YELLOW);
    }
    putpixel(x1, y1, GREEN);
    putpixel(x2, y2, GREEN);
    line(x1, y1, x2, y2);
}
int main()
{
    // clrscr();
    int gdriver = DETECT, gmode, errorcode;
    int x1, y1, x2, y2, n;
    double t1, t4;
    int gd = DETECT, gm;
    char pathtodriver[] = "";
    initgraph(&gd, &gm, pathtodriver);
    int x[4], y[4];
    int i;
    cout << "1.BezierCurve\n2.HermiteCurve\n";
    cout << "Enter your choice:";
    cin >> n;
    if (n == 1)
    {
        cout << "Enter x and ycoordinates\n";
        for (i = 0; i < 4; i++)
        {
            cout << "x" << i + 1 << ":";
            cin >> x[i];
            cout << "y" << i + 1 << ":";
            cin >> y[i];
            cout << endl;
        }
        bezier_curve(x, y);
    }
    else if (n == 2)
    {
        cout << "Enter the xcoordinate of 1st hermite point:";
        cin >> x1;
        cout << "Enter the ycoordinateof 1st hermite point:";
        cin >> y1;
        cout << "Enter the xcoordinate of 4th hermite point:";
        cin >> x2;
        cout << "Enter the ycoordinate of 4th hermite point:";
        cin >> y2;
        cout << "Enter tangent at p1:";
        cin >> t1;
        cout << "Enter tangent at p4:";
        cin >> t4;
        hermite_curve(x1, y1, x2, y2, t1, t4);
    }
    else
    {
        cout << "\nInvalid Choice";
    }
    getch();
    return 0;
}