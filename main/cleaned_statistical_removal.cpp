#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include "clustering.h"
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/io.h>


int user_data;

void viewerOneOff (pcl::visualization::PCLVisualizer& viewer)
{
    viewer.setBackgroundColor (1.0, 0.5, 1.0);
    pcl::PointXYZ o;
    o.x = 1.0;
    o.y = 0;
    o.z = 0;
    std::cout << "i only run once" << std::endl;

}

void viewerPsycho (pcl::visualization::PCLVisualizer& viewer)
{
    static unsigned count = 0;
    std::stringstream ss;
    ss << "Once per viewer loop: " << count++;
    viewer.removeShape ("text", 0);
    viewer.addText (ss.str(), 200, 300, "text", 0);

    //FIXME: possible race condition here:
    user_data++;
}

int main (int argc, char** argv)
{

  int i;
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);

  // Fill in the cloud data
  pcl::PCDReader reader;
  reader.read<pcl::PointXYZ> ("point.pcd", *cloud);

  std::cerr << "Cloud before filtering: " << std::endl;
  std::cerr << *cloud << std::endl;

//-----------------------------------------------

// providing seed for random number genrator
srand (time(NULL));

	int total_points, total_attributes, K, max_iterations;

         total_attributes=3;
         total_points=cloud->points.size ();
         K=6;
         max_iterations=10;
	       vector<Point> pointcollection;

  for( i = 0; i < total_points; i++)
	{
			vector<double> values;
			values.push_back(cloud->points[i].x);
			values.push_back(cloud->points[i].y);
			values.push_back(cloud->points[i].z);

			Point p(i, values);
			pointcollection.push_back(p);

	}

	KMeans kmeans(K, total_points, total_attributes, max_iterations);
	kmeans.run(pointcollection);
  std::vector<Point> updatedpoints = pointcollection;

pcl::PointCloud<pcl::PointXYZ> updatedcloud;

    // Fill in the cloud data
    updatedcloud.width    = updatedpoints.size();
    updatedcloud.height   = 1;
    updatedcloud.is_dense = false;
    updatedcloud.points.resize (updatedcloud.width * updatedcloud.height);

  for (size_t j = 0; j < updatedcloud.points.size (); ++j)
  {
    updatedcloud.points[j].x = updatedpoints[j].getValue(0);
    updatedcloud.points[j].y = updatedpoints[j].getValue(1);
    updatedcloud.points[j].z = updatedpoints[j].getValue(2);
  }
    pcl::io::savePCDFileASCII ("test_pcd.pcd", updatedcloud);



reader.read<pcl::PointXYZ> ("test_pcd.pcd", *cloud_filtered);


/*
"""""""""""""""""function by pcl""""""""""""""""""
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

// for infinite loop
while(1)
{

}


  return (0);
}
