#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector> 
#include <algorithm>
#include <typeinfo>
# include <optional>
#include <Windows.h>
#include <filesystem> 
#include <iostream>
#include <iomanip>
#include <fstream>
#include<stdlib.h>
#include <math.h>
#include <array>
#include <algorithm>
#include "Lut.h"
#include<regex>


using namespace cv;
using namespace std;
class cPlate
{

	vector < cv::String> fn;
	FILE* file;
	int size_i;
public:
	/// <summary>
	/// Generate an image with all the images of a plate and a text file indicating the paths of all corrupted images
	/// </summary>
	/// <param name="f"> All path of images</param>
	/// <param name="file">the paths of all corrupted images </param>
	cPlate(vector < cv::String> f, FILE * file);
	/// <summary>
	/// Extract information from name of image 
	/// </summary>
	/// <param name="s">Image name</param>
	/// <returns>Vector with all information</returns>
	string* reg(string s);
	/// <summary>
	/// Get data from matrix
	/// </summary>
	/// <param name="channel">Image matrix</param>
	/// <returns> float table with all value</returns>
	float* get_table(Mat channel);
	/// <summary>
	/// Quick zoom
	/// </summary>
	/// <param name="tab">image </param>
	/// <param name="scalar">the scalar of zoom</param>
	/// <returns>image resized</returns>
	Mat my_resize(Mat tab, int scalar);
	/// <summary>
	/// Copy the resized image into the image of plate at emplacement (pos_x, pos_y)
	/// </summary>
	/// <param name="pos_x">Line position</param>
	/// <param name="pos_y">Column position</param>
	/// <param name="image">Resized image</param>
	/// <param name="playe">Plate </param>
	void copyto(int pos_x, int pos_y, Mat image, Mat plate);
	/// <summary>
	/// Create plate with 384 field
	/// </summary>
	/// <returns>return vector with all images of plate</returns>
	vector <cv::Mat> create_plate();
};

