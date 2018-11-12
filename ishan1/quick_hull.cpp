#include<bits/stdc++.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

using namespace std; 
#define iPair pair<int, int> 
#define tup tuple<float, int  , int>

set<iPair> ghull ; 

using namespace std ; 



struct Point 
{ 
    int x, y; 
}; 
  
// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(Point p, Point q, Point r) 
{ 
    int val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y); 
  
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 
  
// Prints convex hull of a set of n points. 
void convexHull(Point points[], int n) 
{ 
    // There must be at least 3 points 
 //    if (n < 3) 
	// {
	// 	for (int i = 0 ; i < n ;i++)
	// 	{
	// 		iPair p ; 
	// 		p.first = points[i].x ;
	// 		p.second = points[i].y ;
	// 		ghull.insert(p) ;
	// 	}
	// }
  
    // Initialize Result 
    vector<Point> hull; 
  
    // Find the leftmost point 
    int l = 0; 
    for (int i = 1; i < n; i++) 
        if (points[i].x < points[l].x) 
            l = i; 
  
    // Start from leftmost point, keep moving counterclockwise 
    // until reach the start point again.  This loop runs O(h) 
    // times where h is number of points in result or output. 
    int p = l, q; 
    do
    { 
        // Add current point to result 


        hull.push_back(points[p]); 
  //========================================      
        iPair tmp ; 
        tmp.first = points[p].x; 
        tmp.second = points[p].y ;
        ghull.insert(tmp);   
 //=========================================

        // Search for a point 'q' such that orientation(p, x, 
        // q) is counterclockwise for all points 'x'. The idea 
        // is to keep track of last visited most counterclock- 
        // wise point in q. If any point 'i' is more counterclock- 
        // wise than q, then update q. 
        q = (p+1)%n; 
        for (int i = 0; i < n; i++) 
        { 
           // If i is more counterclockwise than current q, then 
           // update q 
           if (orientation(points[p], points[i], points[q]) == 2) 
               q = i; 
        } 
  
        // Now q is the most counterclockwise with respect to p 
        // Set p as q for next iteration, so that q is added to 
        // result 'hull' 
        p = q; 
  
    } while (p != l);  // While we don't come to first point 
  
    // Print Result 
    // for (int i = 0; i < hull.size(); i++) 
    //     cout << "(" << hull[i].x << ", "
    //           << hull[i].y << ")\n"; 
} 






void to_c_hull(vector<iPair>arr,iPair a , iPair z)
{
	if (arr.size() < 1 ) 
	{
		ghull.insert(a);
        ghull.insert(z) ; 
		return ;
	}

	Point points[arr.size() + 2] ; 
	int i = 0;
	
    for (auto ele : arr)
	{
		points[i].x = ele.first; 
		points[i++].y = ele.second;
	}
    points[i].x = a.first ;
    points[i++].y = a.second ; 
    points[i].x = z.first ;
    points[i++].y = z.second ;

	convexHull(points , i) ;		
}















float slope(iPair a , iPair b)
{

	float s = (b.second  - a.second)/(b.first - a.first) ; 
	return s ;
}


bool comp(tup a , tup b)
{
	return get<0>(a) < get<0>(b)  ;
}


int findSide(iPair p1, iPair p2, iPair p) 
{ 
    int val = (p.second - p1.second) * (p2.first - p1.first) - 
              (p2.second - p1.second) * (p.first - p1.first); 
  
    if (val > 0) 
        return 1; 
    if (val < 0) 
        return -1; 
    return 0; 
} 


iPair median_base(vector<iPair> arr , iPair a ,iPair z )
{

	vector<tup> t_arr;  
	int n = arr.size() ;

	int i = 0 , j = n-1 ; 
	for(i = 0 ; i < n/2 ; i++ , j--)
	{
		float s = slope(arr[i] , arr[j]);
		t_arr.push_back(make_tuple(s, i, j)); 
	}
	sort(t_arr.begin() , t_arr.end() , comp);
	tup m_tuple = t_arr[t_arr.size()/2];
	return {get<1>(m_tuple) , get<2>(m_tuple)};
}



int dist(iPair p, iPair q) 
{ 
    return (p.second - q.second) * (p.second - q.second) + 
           (p.first - q.first) * (p.first - q.first); 
} 


int lineDist(iPair p1, iPair p2, iPair p) 
{ 

    return abs ((p.second - p1.second) * (p2.first - p1.first) - 
               (p2.second - p1.second) * (p.first - p1.first)); 
    // return   (p.second - p1.second) * (p2.first - p1.first) - 
    //            (p2.second - p1.second) * (p.first - p1.first); 
} 


void pq_hull(vector<iPair> arr , iPair a , iPair z)
{

    ghull.insert(a) ; 
    ghull.insert(z) ;

	if(arr.size() <= 5) 
	{

		cout << "thats it for "<<a.first << " "<<a.second << " "<<z.first << " " << z.second << endl;
		for(auto x : arr) cout << x.first <<" " <<x.second <<endl;
		cout << "================"<<endl;
		to_c_hull(arr,a,z) ;
		return ;  
	} 

	// vector<iPair> temp ;  
	// for(int i = 0 ; i < arr.size() ; i++)
	// {
	// 	if(arr[i] == a || arr[i] == z) continue ; 
	// 	temp.push_back(arr[i]) ; 
	// }
    iPair qr = median_base(arr, a  , z) ;
    iPair q = arr[qr.first] ;
    iPair r = arr[qr.second] ; 
    if(q.first > r.first) swap(q,r) ;        
    cout << "Q IS " << q.first << " " <<q.second << endl; 
    cout << "R is "<<r.first << " "<< r.second<<endl;

    int max_dist = INT_MIN; 
    int p_ind = -1; 
    for (int i=0; i<arr.size(); i++) 
    { 
    	if(i == qr.first || i == qr.second) continue ;
        int temp = lineDist(q, r, arr[i]); 
        if (findSide(q, r, arr[i]) >= 0 && temp > max_dist) 
        { 
            p_ind = i; 
            max_dist = temp; 
        } 
    } 


    if(p_ind == -1)
    { 
  		return  ; 	
    }


    iPair p = arr[p_ind] ; 
	ghull.insert(arr[p_ind]) ;     
	arr.erase(arr.begin() + p_ind) ; 
    
cout << a.first << " "<<a.second << "==="<<p.first <<" "<<p.second << "==="<<z.first <<" "<<z.second<<endl; 

    iPair p1 = a ; 
    iPair p2 = p; 

    //left to ap
    vector<iPair> L ; 
    for(auto ele : arr)
    {
    	if(findSide(p1,p2,ele) == 1 || findSide(p1,p2,ele) == 0)
    	{
    		L.push_back(ele) ; 
    	}
    }
 

    //right to zp
    vector<iPair> R ; 
    p1 = z ;
    p2 = p ; 
    for(auto ele : arr)
    {
    	if(findSide(p1,p2,ele) == -1 || findSide(p1,p2,ele) == 0)
    	{
    		R.push_back(ele) ; 
    	}
    }


pq_hull(L, a, p) ; 
pq_hull(R, p ,z) ;

}

void p_hull(vector<iPair> a ,int n)
{

   // if(n < 3) cout << "not possible " ; 
	int min_x = 0  , max_x = 0 ; 
    for (int i=1; i<n; i++) 
    { 
        if (a[i].first < a[min_x].first) 
            min_x = i;  
    } 
    iPair a1 = a[min_x] ;     
    a.erase(a.begin() + min_x) ;
    
    for(int i = 1 ; i<a.size(); i++)
    {
    if(a[i].first > a[max_x].first) 
       max_x = i;
    }
    iPair z = a[max_x]; 
    a.erase(a.begin() + max_x) ;
	
    cout << "================"<<endl;

	pq_hull(a,  a1 ,z); 

	for(auto x : ghull)
	{
		cout << x.first << " "<< x.second << endl;
	}

}

int main()
{
	int n ; 
	cin >> n ; 
	vector<iPair>v;
	int a , b ; 
    srand (time(NULL));
	for (int i = 0; i < n; i++)
	{
		cin >> a >> b  ;
		v.push_back({a,b}) ;  
	}




	p_hull(v ,n) ; 

	return 0 ; 
}





