#include<iostream>
#include<vector>
#include<graphics.h>
#include<utility>
#include<cmath>
#include<algorithm>
using namespace std;

class EdgeBucket{
	public:
		int y_max;
		float slope_inverse,x_of_y_min;
		EdgeBucket(int y,float x,float m){
			y_max=y;
			x_of_y_min=x;
			slope_inverse=m;		
		}
};

bool accordingToX(EdgeBucket e1, EdgeBucket e2){
	return (e1.x_of_y_min<e2.x_of_y_min);
}

int main(){
	
	int n, y_min, y_max, x_of_y_min;
	int m=0;	
	
	cout<<"Enter number of vertices: ";
	cin>>n;
	
	pair<int,int> vertices[n+1];
	for(int i=0;i<n;i++){
		cout<<"\nEnter x-coordinate of vertex "<<i+1<<": ";
		cin>>vertices[i].first;
		cout<<"Enter y-coordinate of vertex "<<i+1<<": ";
		cin>>vertices[i].second;
		m=max(m,vertices[i].second);
	}
	
	
	vertices[n]=vertices[0];
	
	// global edge table
	vector<EdgeBucket> get[m+1];
	
	// filling global edge table
	for(int i=1;i<n+1;i++){
		if(vertices[i].second>vertices[i-1].second){
			y_min=vertices[i-1].second;
			y_max=vertices[i].second;
			x_of_y_min=vertices[i-1].first;
		}
		else{
			y_min=vertices[i].second;
			y_max=vertices[i-1].second;
			x_of_y_min=vertices[i].first;
		}
		//(x2-x1)/(y2-y1)
		float slopeInverse=(float)(vertices[i].first-vertices[i-1].first)/(float)(vertices[i].second-vertices[i-1].second);	
	    // if not checked then there will be same two points and result will be incorrect.
		if(!isinf(slopeInverse))
			get[y_min].push_back(EdgeBucket(y_max,(float)x_of_y_min,slopeInverse));
	}
	
	int gd=DETECT,gm;
	initgraph(&gd,&gm,(char*)"D:\\SW\\Dev-Cpp\\MinGW64\\include");
	
	//active edge table
	vector<EdgeBucket> active_table;
	
	for(int i=0;i<m+1;i++){
		//remove finished edges
		for(int j=0;j<active_table.size();j++)
		
			if(active_table[j].y_max<=i){
				active_table.erase(active_table.begin()+j);
				j--;
			}
		//add EdgeBuckets
		
		for(int j=0;j<get[i].size();j++){
			active_table.push_back(get[i][j]);
		}
		//sort according to x_of_y_min
		sort(active_table.begin(),active_table.end(),accordingToX);		
		
		setcolor(WHITE);
		// line can't be formed by single point
		for(int j=0;j<active_table.size();j+=2){
			delay(10);
			line((int)active_table[j].x_of_y_min,i,(int)active_table[j+1].x_of_y_min,i);
			active_table[j].x_of_y_min += active_table[j].slope_inverse;
			active_table[j+1].x_of_y_min += active_table[j+1].slope_inverse;
		}
	}
	getch();
	closegraph();
	return 0;
}

