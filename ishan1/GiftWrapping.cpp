// JARVIS MARCH CONVEX HULL ALGORITHM

/**
**    Time complexity O(nh)
 *    n is the number of points
 *    h is the  number of points on the boundary.
 *    Worst case O(n^2).
**		If no of points a few then it is linear time algo, but if no of points a very large then it is worst
**    it is like graphs algo , We don't know which one is btter  O(ElogV) or O(V2) , it depends on input.
**/

#include<bits/stdc++.h>
using namespace std;

struct Point
{
	int x;
	int y;
};

	// to store the co-ordinates of  boundries which will formed convex HULL
	std::vector<Point> final; 
int whichSide(Point,Point,Point);
int distance(Point ,Point ,Point );

void findConvex_Hull(Point input[],int n){
	
	Point start=input[0];

	// to find the left most x and from this x we have to start
	for(int i=1;i<n;i++){
		if(start.x > input[i].x){
			start=input[i];
		}
	}



	final.push_back(start);
	Point atThis_pt=start;

	// for special treatment of collinear points (to store them)
	vector<Point> coll;

	while(1){

		Point Next_target=input[0];
		for(int i=1;i<n;i++){

			if(input[i].x==atThis_pt.x && input[i].y==atThis_pt.y)
				continue;
		

		int value=whichSide(atThis_pt,Next_target,input[i]);
		if(value>0){
			Next_target=input[i];

			//reset collinear points because we now have a new Next_target.
			coll.clear();
		}
		else if(value==0)
		{
			//for collinear
 		if(distance(atThis_pt,Next_target,input[i])<0){
 			//then calulate the distance  and  then pick the further one but add closer one to list of collinear points.
 		coll.push_back(Next_target);
 		Next_target=input[i];

		}
		else{
			coll.push_back(input[i]);
		}
 	}

}  // end of the for loop

/*for(Point P:coll){
	final.push_back(P);
}*/

if(Next_target.x==start.x && Next_target.y==start.y) 
{
	break; // we got in an loop
}


final.push_back(Next_target);
atThis_pt = Next_target;  

}// end of the while loop



cout<<endl;

//sort(final.begin(),final.end(),mycomp);

//final.erase(std::unique(final.begin(), final.end(),mycomp));  // ---> to remove the duplicates
for(int i=0;i<final.size();i++)
	{
		cout <<"("<< final[i].x << " , " <<final[i].y << ")"<<endl;
}

}


int distance(Point a,Point b,Point c){
//this function is for the collinear points , to calculate the distance which collinear is far or near 
// and according to that we add point or put in collinear array


	double dis1=(double) sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
	double dis2=(double) sqrt(pow(a.x-c.x,2)+pow(a.y-b.y,2));
	return (int)(dis1-dis2);
	/*
	if it ret >0 means b is more far than c from a

	if it ret <0 means c is more far than b from a
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
	ofstream out;
    string filename = "TimeGift.csv";
    string output = "output.csv";
    out.open(output); 
    fs.open(filename,std::ios_base::app);
	//Point input[]= {{0, 3}, {2, 2}, {1, 1}, {2, 1},{3, 0}, {0, 0}, {3, 3}};
	//Point input[]= {{1,1}, {2,2}, {4,4}, {4,2},{4,-4}, {-2,1}, {-1,-4},{2,-1}};  
	//Point input[]= {{1,1}, {2,2},{3,1}, {4,4}, {-2,1}, {-1,-4},{2,-5}};
	//Point input[]={{7, 7},{7, -7} ,{-7 ,-7},{-7,7},{9, 0},{-9,0},{0 ,9},{0, -9}};
	//Point input[]={{7,7},{7,-7},{-7 ,-7} ,{-7,7} ,{9, 0},{-9, 0}, {0, 9},{ 0, -9}, {0, 0} ,{1, 2} ,{-2 ,1},{-1,-1},{3,4}, {4,3},{ -5, 4},{6, 5}};

	/*Point input[]={{4.4, 14}, {6.7, 15.25}, {6.9, 12.8}, {2.1, 11.1}, {9.5, 14.9}, 
 					{13.2, 11.9}, {10.3, 12.3}, {6.8, 9.5}, {3.3, 7.7}, {0.6, 5.1}, {5.3, 2.4}, 
 						{8.45, 4.7}, {11.5, 9.6}, {13.8, 7.3}, {12.9, 3.1}, {11, 1.1}};*/

//	int n=sizeof(input)/sizeof(input[0]);
	





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
    printf("JARVIS MARCH took %f ms to compute Convex HULL \n", time_taken*1000); 

    fs << n/1000 <<","<<time_taken*1000<<endl;

    for(int i=0;i<final.size();i++)
	{
		out << final[i].x << " , " <<final[i].y <<endl;
}
	return 0;
}