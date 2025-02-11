// Implementation of the KMeans Algorithm

#include<bits/stdc++.h>

using namespace std;

class Point
{
private:
	int id_point, id_cluster;
	vector<double> values;
	int total_values;

public:
	Point(int id_point, vector<double>& values)
	{
		this->id_point = id_point;
		total_values = values.size();

		for(int i = 0; i < total_values; i++)
			this->values.push_back(values[i]);

		id_cluster = -1;
	}

	int getID()
	{
		return id_point;
	}

	void setCluster(int id_cluster)
	{
		this->id_cluster = id_cluster;
	}

	int getCluster()
	{
		return id_cluster;
	}

	double getValue(int index)
	{
		return values[index];
	}

	int getTotalValues()
	{
		return total_values;
	}

	void addValue(double value)
	{
		values.push_back(value);
	}


};

class Cluster
{
private:
	int id_cluster;
	vector<double> central_values;
	vector<Point> points;

public:
	Cluster(int id_cluster, Point point)
	{
		this->id_cluster = id_cluster;

		int total_values = point.getTotalValues();

		for(int i = 0; i < total_values; i++)
			central_values.push_back(point.getValue(i));

		points.push_back(point);
	}

	void addPoint(Point point)
	{
		points.push_back(point);
	}

	bool removePoint(int id_point)
	{
		int total_points = points.size();

		for(int i = 0; i < total_points; i++)
		{
			if(points[i].getID() == id_point)
			{
				points.erase(points.begin() + i);
				return true;
			}
		}
		return false;
	}

	double getCentralValue(int index)
	{
		return central_values[index];
	}

	void setCentralValue(int index, double value)
	{
		central_values[index] = value;
	}

	Point getPoint(int index)
	{
		return points[index];
	}

	int getTotalPoints()
	{
		return points.size();
	}

	int getID()
	{
		return id_cluster;
	}
};

class KMeans
{
private:
	int K; // number of clusters
	int total_values, total_points, max_iterations;
	vector<Cluster> clusters;

	// return ID of nearest center (uses euclidean distance)
	int getIDNearestCenter(Point point)
	{
		double sum = 0.0, min_dist;
		int id_cluster_center = 0;

		for(int i = 0; i < total_values; i++)
		{
			sum += pow(clusters[0].getCentralValue(i) -
					   point.getValue(i), 2.0);
		}

		min_dist = sqrt(sum);

		for(int i = 1; i < K; i++)
		{
			double dist;
			sum = 0.0;

			for(int j = 0; j < total_values; j++)
			{
				sum += pow(clusters[i].getCentralValue(j) -
						   point.getValue(j), 2.0);
			}

			dist = sqrt(sum);

			if(dist < min_dist)
			{
				min_dist = dist;
				id_cluster_center = i;
			}
		}

		return id_cluster_center;
	}

public:
	KMeans(int K, int total_points, int total_values, int max_iterations)
	{
		this->K = K;
		this->total_points = total_points;
		this->total_values = total_values;
		this->max_iterations = max_iterations;
	}

	void  run(vector<Point> & points)
	{

		if(K > total_points)
			return;

		// vector<int> prohibited_indexes;


/*
		// choose K distinct values for the centers of the clusters

		for(int i = 0; i < K; i++)
		{
			while(true)
			{
				int index_point = rand() % total_points;

				if(find(prohibited_indexes.begin(), prohibited_indexes.end(),
						index_point) == prohibited_indexes.end())
				{
					prohibited_indexes.push_back(index_point);
					points[index_point].setCluster(i);
					Cluster cluster(i, points[index_point]);
					clusters.push_back(cluster);
					break;
				}
			}
		}
*/
//------------------------------------------------->>>>>>



map<int,int>mp;
//map<pair<int,int>,int>sumvalue;

int first,second,third;
double s,minm,counter,limit,xcor,ycor,zcor;
/*
for(int j=0;j<total_points;j++)
{
	for(int p=j+1;p<total_points;p++)
	{
		s=sqrt((points[j].getValue(0)-points[p].getValue(0))*(points[j].getValue(0)-points[p].getValue(0))
+((points[j].getValue(1)-points[p].getValue(1))*(points[j].getValue(1)-points[p].getValue(1)))
+((points[j].getValue(2)-points[p].getValue(2))*(points[j].getValue(2)-points[p].getValue(2))));
pair<int,int> pr;
pr.first=j;
pr.second=p;
sumvalue[pr]=s;
	}
}
*/
for(int i=0;i<K;i++)
{
	minm=10000000000;

	for(int j = 0; j < total_points; j++)
	{
		if(mp[j]==0)
		{
		for(int p=j+1;p<total_points;p++)
		{
			if((mp[p]==0)&&(p!=j))
			{
				s=sqrt((points[j].getValue(0)-points[p].getValue(0))*(points[j].getValue(0)-points[p].getValue(0))
+((points[j].getValue(1)-points[p].getValue(1))*(points[j].getValue(1)-points[p].getValue(1)))
+((points[j].getValue(2)-points[p].getValue(2))*(points[j].getValue(2)-points[p].getValue(2))));
				if(s<minm)
				{
					minm=s;
					first=j;
					second=p;

				}
			}
	}
}
}
/*
for (auto const& xt : sumvalue)
{
	pair<int,int> rp;
	rp=xt.first;
	s=xt.second;
	if(((mp[rp.first]==0)||(mp[rp.second]==0))&&(rp.first!=rp.second))
	{
		if(s<minm)
		{
			minm=s;
			first=rp.first;
			second=rp.second;
		}
	}
}
*/

xcor=(points[first].getValue(0)+points[second].getValue(0))/2;
ycor=(points[first].getValue(1)+points[second].getValue(1))/2;
zcor=(points[first].getValue(2)+points[second].getValue(2))/2;
mp[first]=1;
mp[second]=1;
points[first].setCluster(i);
points[second].setCluster(i);
counter=2;
limit=total_points/K;
limit*=0.15;
while(counter<limit)
{
	minm=10000000000;
for(int j = 0; j < total_points; j++)
{
	if(mp[j]==0)
	{
		s=sqrt((points[j].getValue(0)-xcor)*(points[j].getValue(0)-xcor)
+((points[j].getValue(1)-ycor)*(points[j].getValue(1)-ycor))
+((points[j].getValue(2)-zcor)*(points[j].getValue(2)-zcor)));

	 if(s<minm)
	 {
		 minm=s;
		 third = j;
	 }
  }
}
mp[third]=1;
points[third].setCluster(i);
counter++;
xcor=(points[third].getValue(0)+xcor)/2;
ycor=(points[third].getValue(1)+ycor)/2;
zcor=(points[third].getValue(2)+zcor)/2;
}
/*
vector<double> values1;
values1.push_back(xcor);
values1.push_back(ycor);
values1.push_back(zcor);
Point pt(first, values1);
Cluster cluster(i, pt);
clusters.push_back(cluster);
*/
Cluster cluster(i, points[first]);
clusters.push_back(cluster);

}


//------------------------------------------->>>>>
		int iter = 1;

		while(true)
		{
			bool done = true;

			// associates each point to the nearest center
			for(int i = 0; i < total_points; i++)
			{
				int id_old_cluster = points[i].getCluster();
				int id_nearest_center = getIDNearestCenter(points[i]);

				if(id_old_cluster != id_nearest_center)
				{
					if(id_old_cluster != -1)
						clusters[id_old_cluster].removePoint(points[i].getID());

					points[i].setCluster(id_nearest_center);
					clusters[id_nearest_center].addPoint(points[i]);
					done = false;
				}
			}

			// recalculating the center of each cluster
			for(int i = 0; i < K; i++)
			{
				for(int j = 0; j < total_values; j++)
				{
					int total_points_cluster = clusters[i].getTotalPoints();
					double sum = 0.0;

					if(total_points_cluster > 0)
					{
						for(int p = 0; p < total_points_cluster; p++)
							sum += clusters[i].getPoint(p).getValue(j);
						clusters[i].setCentralValue(j, sum / total_points_cluster);
					}
				}
			}

			if(done == true || iter >= max_iterations)
			{
				cout << "Break in iteration " << iter << "\n\n";
				break;
			}

			iter++;
		}

		// shows elements of clusters
		for(int i = 0; i < K; i++)
		{
			int total_points_cluster =  clusters[i].getTotalPoints();

			cout << "Cluster " << clusters[i].getID() + 1 << endl;
                         cout<<total_points_cluster<<endl;

/*
			for(int j = 0; j < total_points_cluster; j++)
			{
				cout << "Point " << clusters[i].getPoint(j).getID() + 1 << ": ";
				for(int p = 0; p < total_values; p++)
					cout << clusters[i].getPoint(j).getValue(p) << " ";


				cout << endl;
			}
*/

			cout << "Cluster values: ";

			for(int j = 0; j < total_values; j++)
				cout << clusters[i].getCentralValue(j) << " ";

			cout << "\n\n";
		}




    //----------------------------------------------------------------------

/*
                    for(int i = 0; i < K; i++)
			{
				for(int j = 0; j < total_values; j++)
				{
					int total_points_cluster = clusters[i].getTotalPoints();
					double sum = 0.0;

					if(total_points_cluster > 0)
					{
						for(int p = 0; p < total_points_cluster; p++)
							sum += clusters[i].getPoint(p).getValue(j);
						clusters[i].setCentralValue(j, sum / total_points_cluster);
					}
				}
			}
*/
                vector<int> threshold;
               for(int i = 0; i < K; i++)
			{

                      int total_points_cluster = clusters[i].getTotalPoints();
					double sum = 0.0;
               double maxm,minm;
              double x,y,z;
x=clusters[i].getCentralValue(0);
y=clusters[i].getCentralValue(0);
z=clusters[i].getCentralValue(0);

     minm=1000000000;
     maxm=0;
                        for(int p = 0; p < total_points_cluster; p++)
			 {
                         sum+=pow(clusters[i].getPoint(p).getValue(0)-x,2);
                         sum+=pow(clusters[i].getPoint(p).getValue(1)-y,2);
                         sum+=pow(clusters[i].getPoint(p).getValue(2)-z,2);
                         sum=sqrt(sum);
                         if(sum<minm)
                        minm=sum;
                        if(sum>maxm)
                         maxm=sum;
                         sum=0;
                         }
// 2 from here
                double ans=abs(maxm-minm);
								ans=ans*1.05;

                        for(int p = 0; p < total_points_cluster; p++)
			          {
                         sum+=pow(clusters[i].getPoint(p).getValue(0)-x,2);
                         sum+=pow(clusters[i].getPoint(p).getValue(1)-y,2);
                         sum+=pow(clusters[i].getPoint(p).getValue(2)-z,2);
                         sum=sqrt(sum);
                          if(sum>ans)
                        {
													/*
vector<double> val;
val.push_back( clusters[i].getPoint(p).getValue(0));
val.push_back( clusters[i].getPoint(p).getValue(1));
val.push_back( clusters[i].getPoint(p).getValue(2));
Point a=Point(clusters[i].getPoint(p).getID(),val);
*/

											 double x1=clusters[i].getPoint(p).getValue(0);
											  double y1=clusters[i].getPoint(p).getValue(1);
												 double z1=clusters[i].getPoint(p).getValue(2);

                       //  std::remove(points.begin(), points.end(), a);
           for(int it=0;it<points.size();it++)
{
if((points[it].getValue(0)==x1)&&(points[it].getValue(1)==y1)&&(points[it].getValue(2)==z1))
{
	points.erase(points.begin() + it);
	break;
}

}}
}
}

cout<<points.size();


return;


// -------------------------------------------------------
	}
};
