#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include "clustering.h"

#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/io.h>


int user_data;

void
viewerOneOff (pcl::visualization::PCLVisualizer& viewer)
{
    viewer.setBackgroundColor (1.0, 0.5, 1.0);
    pcl::PointXYZ o;
    o.x = 1.0;
    o.y = 0;
    o.z = 0;
  //  viewer.addSphere (o, 0.25, "sphere", 0);
    std::cout << "i only run once" << std::endl;

}

void
viewerPsycho (pcl::visualization::PCLVisualizer& viewer)
{
    static unsigned count = 0;
    std::stringstream ss;
    ss << "Once per viewer loop: " << count++;
    viewer.removeShape ("text", 0);
    viewer.addText (ss.str(), 200, 300, "text", 0);

    //FIXME: possible race condition here:
    user_data++;
}

int
main (int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);

  // Fill in the cloud data
  pcl::PCDReader reader;
  // Replace the path below with the path where you saved your file
  reader.read<pcl::PointXYZ> ("point.pcd", *cloud);

  std::cerr << "Cloud before filtering: " << std::endl;
  std::cerr << *cloud << std::endl;
//-----------------------------------------------

srand (time(NULL));

	int total_points, total_values, K, max_iterations;

	//cin >> total_points >> total_values >> K >> max_iterations;

         total_values=3;
         total_points=cloud->points.size ();
         K=6;
         max_iterations=10;
	vector<Point> points;


	for(int i = 0; i < total_points; i++)
	{
			vector<double> values;
			values.push_back(cloud->points[i].x);
			values.push_back(cloud->points[i].y);
			values.push_back(cloud->points[i].z);

			Point p(i, values);
			points.push_back(p);

	}

	KMeans kmeans(K, total_points, total_values, max_iterations);
	 kmeans.run(points);
   std::vector<Point> points1=points;

pcl::PointCloud<pcl::PointXYZ> cloud1;
    // Fill in the cloud data
    cloud1.width    = points1.size();
    cloud1.height   = 1;
    cloud1.is_dense = false;
  cloud1.points.resize (cloud1.width * cloud1.height);

  for (size_t i = 0; i < cloud1.points.size (); ++i)
  {
    cloud1.points[i].x = points1[i].getValue(0);
    cloud1.points[i].y =points1[i].getValue(1);
    cloud1.points[i].z = points1[i].getValue(2);
  }
    pcl::io::savePCDFileASCII ("test_pcd.pcd", cloud1);



reader.read<pcl::PointXYZ> ("test_pcd.pcd", *cloud_filtered);


/*

//--------------------------------------

  // Create the filtering object
  pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
  sor.setInputCloud (cloud);
  sor.setMeanK (50);
  sor.setStddevMulThresh (1.0);
  sor.filter (*cloud_filtered);

  std::cerr << "Cloud after filtering: " << std::endl;
  std::cerr << *cloud_filtered << std::endl;

  pcl::PCDWriter writer;
  writer.write<pcl::PointXYZ> ("table_scene_lms400_inliers.pcd", *cloud_filtered, false);

  sor.setNegative (true);
  sor.filter (*cloud_filtered);
  writer.write<pcl::PointXYZ> ("table_scene_lms400_outliers.pcd", *cloud_filtered, false);
  */

pcl::visualization::CloudViewer viewer("Cloud Viewer");


    //blocks until the cloud is actually rendered
    viewer.showCloud(cloud_filtered);

    //use the following functions to get access to the underlying more advanced/powerful
    //PCLVisualizer

    //This will only get called once
    viewer.runOnVisualizationThreadOnce (viewerOneOff);


    //This will get called once per visualization iteration
    viewer.runOnVisualizationThread (viewerPsycho);

while(1)
{

}


  return (0);
}
