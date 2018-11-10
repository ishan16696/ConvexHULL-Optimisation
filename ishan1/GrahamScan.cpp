// GrahamScan Algorithm
/**
*    Time complexity  -> O(nlogn)
 *    Space complexity -> O(n)
 *    if the input is presorted than time comlexity can be O(n)
**		
**/

#include<bits/stdc++.h>
using namespace std;

struct Point
{
	int x;
	int y;
};

Point p0;

int whichSide(Point,Point,Point);
int whichSide2(Point,Point,Point);
int distance(Point,Point ,Point );

//To sort according to the Counter clock wise  angle w.r.t p0
int compare(Point p1,Point p2){
		int r=whichSide(p0,p1,p2);
		
		if(r >0){
			return 1;
		}
		else if(r==0){
			if(distance(p0,p1,p2)>0){
				return 0;
			}
			else{
				return 1;
			}
		}
		else
		return 0;	

}

void sortingAccordingToPolarAngle_wrtp0(Point input[],int n){
		sort(&input[1],input+1+(n-1),compare);

}	


void swap(Point &p1,Point &p2){
	Point temp=p1;
	p1=p2;
	p2=temp;
}

Point nextToTop(stack<Point> &s){
	Point r=s.top();
	s.pop();
	Point ret=s.top();
	s.push(r);
	return ret;
}


void findConvex_Hull(Point input[],int n){
		
//Find the point with the lowest y coordinate. If there are two points with same value, then the point with smaller x coordinate 
//value is considered. Put the bottom-most point at first position.
	Point start=input[0];
	int min;// to hold the index of min y co-ordinate point
	for (int i = 1; i <n ; ++i)
	{
		if(input[i].y < start.y){
			start=input[i];
			min=i;

		}
		else if(input[i].y==start.y && input[i].x < start.x)
		{
			start=input[i];
			min=i;
		}
		
	} //end of for loop

	
	
	swap(input[min],input[0]);
	
	
	p0=start;		
	sortingAccordingToPolarAngle_wrtp0(input,n);


	
	stack<Point> s;
	s.push(input[0]);
	s.push(input[1]);
	s.push(input[2]);

	int m = 1; // Initialize size of modified array 
   	for (int i=1; i<n; i++) 
   	{ 
       // Keep removing i while angle of i and i+1 is same with respect to p0 
       while (i < n-1 && whichSide(p0, input[i],input[i+1]) == 0) 
          i++; 
  
       input[m] = input[i]; 
       m++;  // Update size of modified array 
   } 	

   	if(m<3)
   	return ;



	for(int i=3;i<m;i++){
		while(whichSide(nextToTop(s),s.top(),input[i])<0)  // if makes a non-left turn then pop
			s.pop();
		s.push(input[i]);
	}


// Now stack has the output points, print contents of stack 
   while (!s.empty()) 
   { 
       Point p = s.top(); 
       cout << "( " << p.x << "," << p.y <<" )" << endl; 
       s.pop(); 
   } 



}


int distance(Point a,Point b,Point c){
//this function is for the collinear points , to calculate the distance which collinear is far or near 
// and according to that we add point or put in collinear array


	double dis1=(double) sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
	double dis2=(double) sqrt(pow(a.x-c.x,2)+pow(a.y-b.y,2));
	return (int)(dis1-dis2);
/*
	if it return >0 means b is more far than c from a

	if it return <0 means c is more far than b from a
	*/

}

int whichSide(Point a,Point b,Point c){

	// to calculate the which side point lie is here we have to the cross product 
	int x1=a.x-b.x;
	int y1=a.y-b.y;
	int x2=a.x-c.x;
	int y2=a.y-c.y;
	int result=y2*x1-x2*y1;
	return result;

	
    /*  Cross product to find where c belongs in reference to vector ab.
     	 If result > 0 it means theta is anti-clockwise ===>> implies  'c' is on left of ab.
         result == 0 it means theta is zero ===>> implies 'a','b' and 'c' are collinear.
         result < 0  it means theta is clockwise ===>> means 'c' is on right of ab.
     
*/
}



//**********************************************  DRIVER MAIN FUNCTION *******************************************************************

int main(){
	clock_t c1,c2;

	ofstream fs;

    string filename = "TimeGraham.csv";

    fs.open(filename,std::ios_base::app);
	//Point input[]= {{0, 3},{1,1} {2, 2},{4,4},{0, 0}};
	//Point input[]={{0,3},{1,1},{2,2},{2,1},{3,0},{0,0},{3,3}};
	//Point input[]= {{1,1}, {2,2},{3,1}, {4,4}, {-2,1}, {-1,-4},{2,-5}};
	//Point input[]= {{1,-1}, {2,2},{2,1}, {4,3}, {-2,1}, {-1,-4},{2,-6}};
	///Point input[]= {{1,1}, {2,2}, {4,4}, {4,2},{4,-4}, {-2,1}, {-1,-4},{2,-1}};
	//Point input[]={{7, 7},{7, -7} ,{-7 ,-7},{-7,7},{9, 0},{-9,0},{0 ,9},{0, -9}};

	//Point input[]={{7,7},{7,-7},{-7 ,-7} ,{-7,7} ,{9, 0},{-9, 0}, {0, 9},{ 0, -9}, {0, 0} ,{1, 2} ,{-2 ,1},{-1,-1},{3,4}, {4,3},{ -5, 4},{6, 5}};

	//int n=sizeof(input)/sizeof(input[0]);


	int n;
	cin >> n; //no of points
	Point input[n];
	int l,k;
	vector<int> v;
	for (int i = 0; i < n; ++i)
	{
		cin >> l >> k;
		v.push_back(l);
		v.push_back(k);
	}
	int q=0;
	for (int i = 0; i <v.size(); i=i+2)
	{
		input[q].x=v[i];
		input[q].y=v[i+1];
		q++;
	}
	
	
	c1=clock();
	findConvex_Hull(input,n);
	c2=clock();

	double time_taken = ((double)c2-c1)/CLOCKS_PER_SEC; // in seconds 
    printf("GrahamScan took %f ms to compute Convex HULL \n", time_taken*1000); 

    fs << n/1000 <<","<<time_taken*1000<<endl;
	return 0;
}