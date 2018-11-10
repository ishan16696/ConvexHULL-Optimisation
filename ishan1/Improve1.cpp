#include<bits/stdc++.h>
using namespace std;

struct Point {
  long long  x, y;

  //sort them in inc order of x , inc order of y (in case of tie)
  bool operator <(const Point &p) const {
    if(x < p.x){
      return true;
    }
  
  else if(x == p.x && y < p.y)
  {
    return true;
  }
  else
    return false;

}
};


inline
float isLeft( Point a, Point b, Point c )
{
    return (b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y);
}




int chainHull( Point* P, int n, Point* H )
{
    // the output array H[] will be used as the stack
    int  bottom=0, top=-1;   // indices for bottom and top of the stack
    int  i;                 // array scan index

   
    int minmin = 0, minmax;
    float xmin = P[0].x;
    for (i=1; i<n; i++)
        if (P[i].x != xmin) 
        	break;
    minmax = i-1;
    if (minmax == n-1) {       
        H[++top] = P[minmin];
        if (P[minmax].y != P[minmin].y) 
            H[++top] =  P[minmax];
        H[++top] = P[minmin];            
        return top+1;
    }

   
    int maxmin, maxmax = n-1;
    float xmax = P[n-1].x;
    for (i=n-2; i>=0; i--)
        if (P[i].x != xmax) break;
    maxmin = i+1;

    // Compute the lower hull on the stack H
    H[++top] = P[minmin];     
    i = minmax;
    while (++i <= maxmin)
    {
        
        if (isLeft( P[minmin], P[maxmin], P[i])  >= 0 && i < maxmin)
            continue;          

        while (top > 0)         
        {
            
            if (isLeft(  H[top-1], H[top], P[i]) > 0)
                 break;         
            else
                 top--;         
        }
        H[++top] = P[i];        
    }

    
    if (maxmax != maxmin)      
         H[++top] = P[maxmax];  
    bottom = top;                  
    i = maxmin;
    while (--i >= minmax)
    {
        // the upper line joins P[maxmax]  with P[minmax]
        if (isLeft( P[maxmax], P[minmax], P[i])  >= 0 && i > minmax)
            continue;           // ignore P[i] below or on the upper line

        while (top > bottom)     
        {
            if (isLeft(  H[top-1], H[top], P[i]) > 0)
                 break;         
            else
                 top--;         
        }
        H[++top] = P[i];        
    }
    if (minmax != minmin)
        H[++top] = P[minmin];  

    return top+1;
}



int main(){
    clock_t c1,c2;

    ofstream fs;

    string filename = "TimeImproveMono.csv";

    fs.open(filename,std::ios_base::app);

 	/* Point input[]={ {0,0}, {1,2} ,{-2,1},{-1,-1}, {3,4} ,{4,3} ,{-5,4} ,{6,5},{7 ,7} ,{7,-7} ,{-7,-7}, {-7,7} ,{9,0} ,{-9, 0}
    ,{0 ,9}, {0,-9} ,{-8,0}, {8,0} ,{-7,0},{7, 0} ,{-6,0} ,{6, 0} ,{-5,0}, {5, 0},{-4,0},{4,0}, {-3,0}, {3, 0},{-2, 0}
    ,{2, 0},{-1, 0}, {1,0},{0,-8}, {0,8} ,{0 ,-7} ,{0,7} ,{0,-6} ,{0,6},{0 ,-5}, {0 ,5} ,{0 ,-4} ,{0,4}, {0, -3} ,{0, 3}
    ,{ 0 ,-2},{0, 2},{ 0,-1}, {0, 1},{1, 1}, {2, 2}, {3, 3}, {4,4}, {5,5} ,{6,6} ,{1,-1}, {2 ,-2}, {3, -3},{4,-4},{5,-5} ,{6, -6},
     {-1, 1}, {-2, 2}, {-3, 3}, {-4, 4}, {-5, 5} ,{-6, 6}, {-1,-1}, {-2 ,-2}, {-3,-3} ,{-4, -4}, {-5 ,-5}, {-6 ,-6}};
*/
 // int n=sizeof(input)/sizeof(input[0]);


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



  Point input2[n];
   c1=clock();
  sort(input,input+n);

   
  int x= chainHull(input,n,input2);
   

  for(int i=0;i<x;i++){
    cout << "(" << input2[i].x <<"   "<<input2[i].y <<")";
    cout <<endl;
  }
   c2=clock();
    double time_taken = ((double)c2-c1)/CLOCKS_PER_SEC; // in seconds 
    printf("Improved Monotone Chain took %f ms to compute Convex HULL \n", time_taken*1000); 

     fs << n/1000 <<","<<time_taken*1000<<endl;
  return 0;
}