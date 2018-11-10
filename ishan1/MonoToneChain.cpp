// Implementation of Andrew's monotone chain 2D convex hull algorithm.
// Time  complexity: O(n log n).

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


long long whichDirection(const Point &p0, const Point &p1, const Point &p2)
{
	int x1=p1.x-p0.x;
	int y1=p1.y-p0.y;
	int x2=p2.x-p0.x;
	int y2=p2.y-p0.y;
	int result=x1*y2-y1*x2;
	return result;
	
}


void  convex_hull(vector<Point> vec)
{
	int n = vec.size();
	int  k = 0;
	if (n <= 3) 
		return;

	vector<Point> H(2*n);

	// Sort points lexicographically
	sort(vec.begin(), vec.end());

	// code for lower hull
	for (int i = 0; i < n; ++i) {
		while (k >=2 && whichDirection(H[k-2], H[k-1], vec[i]) <= 0) // does not make a anti-clockwise turn
			{
				k--;
			}

		H[k] = vec[i];
		k++;
	}

	

	// code for upper hull
	for (int i = n-1, t = k+1; i > 0; --i) {
		while (k >= t && whichDirection(H[k-2], H[k-1], vec[i-1]) <= 0) // doesn't make a anti-clockwise turn
		 {
			k--;
		}
		H[k] = vec[i-1];
		k++;
	}

	for(int i=0;i<k-1;i++)
		{
			cout << "("<<H[i].x <<"  "<< H[i].y <<")" <<endl;
		}

	
}



//************************************************** Driver main Function **********************************************************************

int main(){
	clock_t c1,c2;

	ofstream fs;

    string filename = "TimeMono.csv";

    fs.open(filename,std::ios_base::app);

	//Point input[]= {{1,1}, {2,2}, {4,4}, {4,2},{4,-4}, {-2,1}, {-1,-4},{2,-1}}; 
	//Point input[]= {{1,1}, {2,2},{3,1}, {4,4}, {-2,1}, {-1,-4},{2,-5}};
	//Point input[]= {{0, 3}, {2, 2}, {1, 1}, {2, 1},{3, 0}, {0, 0}, {3, 3}};
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






	std::vector<Point> vec;
	for(int i=0;i<n;i++){
		vec.push_back(input[i]);
	}

	c1=clock();
	convex_hull(vec);
	c2=clock();

	double time_taken = ((double)c2-c1)/CLOCKS_PER_SEC; // in seconds 
    printf("Monotone Chain took %f ms to compute Convex HULL \n", time_taken*1000); 

    fs << n/1000 <<","<<time_taken*1000<<endl;
	return 0;
}