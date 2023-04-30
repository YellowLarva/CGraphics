#include<iostream>
#include<vector>
#include<graphics.h>
#include<math.h>
using namespace std;

class Matrix{
	public:
		int rows,columns;
		float **arr;
		Matrix(){}
		Matrix(int r,int c){
			rows=r;
			columns=c;
			arr=new float* [r];
			for(int i=0;i<r;i++){
				arr[i]=new float[c];
				for(int j=0;j<c;j++)
					arr[i][j]=0;
			}
		}
		void print(){
			for(int i=0;i<rows;i++){
				cout<<"[ ";
				for(int j=0;j<columns;j++)
					cout<<arr[i][j]<<" ";
				cout<<"]\n";
			}
		}
		static Matrix multiply(Matrix m1, Matrix m2){
			Matrix m(m1.rows,m2.columns);
			for(int i=0;i<m.rows;i++){
				for(int j=0;j<m.columns;j++){
					for(int k=0;k<m1.columns;k++)
						m.arr[i][j]+=m1.arr[i][k]*m2.arr[k][j];
				}
			}
			return m;
		}
};

void plot(vector<int> arr1,vector<int> arr2){
	arr1.push_back(arr1[0]);
	arr1.push_back(arr1[1]);
	arr2.push_back(arr2[0]);
	arr2.push_back(arr2[1]);    // to make close polygon.
	
	setcolor(RED);
	drawpoly(arr1.size()/2,arr1.data());

	setcolor(GREEN);
	drawpoly(arr2.size()/2,arr2.data());
	getch();
	closegraph();
}

Matrix getTransformationMatrix(){
	
	
	Matrix t(3,3);
	float arr[][3]={
		{1,0,0},
		{0,1,0},
		{0,0,1}
	};
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			t.arr[i][j]=arr[i][j];
	return t;
}

void translate(Matrix m[],int n,vector<int> p){
	int xmid , ymid;
	xmid = getmaxx()/2;
	ymid = getmaxy()/2;
	Matrix t=getTransformationMatrix();
	vector<int> points;
	cout<<"\nEnter translation for x-coordinates: ";
	cin>>t.arr[2][0];
	
	cout<<"Enter translation for y-coordinates: ";
	cin>>t.arr[2][1];
	cout<<"Transformation Matrix:\n";
	t.print();
	cout<<"RESULT:\n";
	for(int i=0;i<n;i++){
		m[i]=Matrix::multiply(m[i],t);
		int a=m[i].arr[0][0];
		a=a+xmid;
		int b=m[i].arr[0][1];
		b=ymid-b;
		points.push_back(a); points.push_back(b);
		cout<<"Vertex "<<i+1<<": ";
		m[i].print();
	}
	plot(p,points);
}

void rotate(Matrix m[],int n,vector<int> p){
	int xmid , ymid;
	xmid = getmaxx()/2;
	ymid = getmaxy()/2;
	Matrix t=getTransformationMatrix();
	vector<int> points;
	int z;
	cout<<"\nEnter angle of rotation: ";
	cin>>z;
	int r=z*(3.14/180);
	// 90 degree = 1.571, 60 degree = 1.047 radians,30 degree = 0.523599 .
	t.arr[0][0]=cos(r); t.arr[0][1]=sin(r);
	t.arr[1][0]=-1*sin(r); t.arr[1][1]=cos(r);
		
	cout<<"Transformation Matrix:\n";
	t.print();
	cout<<"RESULT:\n";
	for(int i=0;i<n;i++){
		m[i]=Matrix::multiply(m[i],t);
		int a=m[i].arr[0][0];
		a=a+xmid;
		int b=m[i].arr[0][1];
		b=ymid-b;
		points.push_back(a); points.push_back(b);
		cout<<"Vertex "<<i+1<<": ";
		m[i].print();
	}
	plot(p,points);
}

void scale(Matrix m[],int n,vector<int> p){
	int xmid , ymid;
	xmid = getmaxx()/2;
	ymid = getmaxy()/2;
	Matrix t=getTransformationMatrix();
	vector<int> points;
	float sx,sy;
	cout<<"\nEnter scaling factors sx,sy: ";
	cin>>sx>>sy;
	t.arr[0][0]=sx; t.arr[1][1]=sy;
	cout<<"Transformation Matrix:\n";
	t.print();
	cout<<"RESULT:\n";
	for(int i=0;i<n;i++){
		m[i]=Matrix::multiply(m[i],t);
		int a=m[i].arr[0][0];
		a=a+xmid;
		int b=m[i].arr[0][1];
		b=ymid-b;
		points.push_back(a); 
		points.push_back(b);
		cout<<"Vertex "<<i+1<<": ";
		m[i].print();
	}
	plot(p,points);
}

void reflect(Matrix m[],int n,vector<int> p){
	int xmid , ymid;
	xmid = getmaxx()/2;
	ymid = getmaxy()/2;
	Matrix t=getTransformationMatrix();
	Again:	// switch case default
	cout<<"\n\nReflect About:\n\n1. X-Axis\n2. Y-Axis\n3. Line Y=X\n4. Origin\n\nEnter Choice: ";
	int choice; cin>>choice;
	vector <int> points;
	switch(choice){
		case 1:
			t.arr[1][1]=-1; break;
		case 2:
			t.arr[0][0]=-1; break;
		case 3:
			t.arr[0][0]=0; t.arr[0][1]=1; t.arr[1][0]=1; t.arr[1][1]=0; break;
		case 4:
			t.arr[0][0]=-1; t.arr[1][1]=-1; break;
		default:
			goto Again; break;
	}
	cout<<"Transformation Matrix:\n";
	t.print();
	cout<<"RESULT:\n";
	for(int i=0;i<n;i++){
		m[i]=Matrix::multiply(m[i],t);
		int a=m[i].arr[0][0];
		a=a+xmid;
		int b=m[i].arr[0][1];
		b=ymid-b;
		points.push_back(a); points.push_back(b);
		cout<<"Vertex "<<i+1<<": ";
		m[i].print();
	}
	plot(p,points);	
}
 
int main(){
	int gd=DETECT,gm;
	initgraph(&gd,&gm,(char *)"D:\\SW\\Dev-Cpp\\MinGW64\\include");
	int xmid , ymid;
	xmid = getmaxx()/2;
	ymid = getmaxy()/2;
	setcolor(YELLOW);
line(xmid , 0 , xmid , getmaxy());
line(0 , ymid , getmaxx() , ymid);
	int n;
	cout<<"Enter number of vertices: ";
	cin>>n;
	Matrix m[n];
	vector<int> points;
	for(int i=0;i<n;i++){
		m[i]=Matrix(1,3);
		
		cout<<"\nEnter x-coordinate of vertex "<<i+1<<": ";
		cin>>m[i].arr[0][0];
		int a=m[i].arr[0][0];
		a=a+xmid;
		points.push_back(a);
		
		cout<<"Enter y-coordinate of vertex "<<i+1<<": ";
		cin>>m[i].arr[0][1];
		int b=m[i].arr[0][1];
		b=ymid-b;
		points.push_back(b);
		m[i].arr[0][2]=1;
	}
	int choice;
	cout<<"\nPoints are:\n";
	for(int i=0;i<n;i++){
		cout<<"Vertex "<<i+1<<": ";
		m[i].print();
	}
	
	// Menu
	cout<<"\n1. Translate\n2. Rotate\n3. Scale\n4. Reflection\n\nEnter Choice: ";
	cin>>choice;
	switch(choice){
		case 1:
			translate(m,n,points);
			break;
		case 2:
			rotate(m,n,points);
			break;
		case 3:
			scale(m,n,points); 
			break;
		case 4:
			reflect(m,n,points); 
			break;
		default:
			break;
	}
	return 0;
}


