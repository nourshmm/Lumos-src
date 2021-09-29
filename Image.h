#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
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
#include"Lut.h"
using namespace cv;
using namespace std;

#include<list>

using namespace std;
/// <summary>
/// Create an image from a list of channels
/// </summary>
class Image
{
public:

	string channel1, channel2, channel3, channel4;
	string* channels;
	//uint** image; // RGB format image[sizeof_channel][3]
	uint size;
	uint cols;
	uint rows;
	int nb_channels;


	Image();
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="channels">list of channels </param>
	/// <param name="size">size of channel</param>
	/// <returns></returns>
	Image(string* channels, int nb_channels);

	Mat read_image(const String path);


	float* get_table(Mat channel);
	int get_nb_channels();
	/// <summary>
	/// create image from list of channel "channels"
	/// </summary>
	/// <returns>array 2 dim "RGB" format</returns>
	vector<Mat>  create_img();
	/// <summary>
	/// get columns number
	/// </summary>
	/// <returns> columns number</returns>
	uint get_cols();
	/// <summary>
	/// get line number
	/// </summary>
	/// <returns>lines number</returns>
	uint get_rows();

};

