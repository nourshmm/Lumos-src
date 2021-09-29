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

/// <sumary>
/// create loot up table 16bit => 8bit
/// create a new channel 8 bit using the look up table 
/// </summary>
using namespace cv;
using namespace std;
class Lut
{
	uint size; // size of channel
	float* channel; // tha channel
	float a, b;
	int* hist;// lower & upper bound
public:

	/// <summary>
	/// constructor (initialise channel & size)
	/// </summary>
	/// <param name="channel">float array channel</param>
	/// <param name="size">size of channel</param>
	/// <returns>channel 8 bit</returns>

	Lut(float* channel, uint size);
	int* nb_occurence(float* channel, uint size);
	void define_B(float percentage);
	void define_A(float percentage);
	uchar* draw_hist();

	void define_bounds(float percentage);

	/// <summary>
	/// apply a look up table on my channel 16bit in order to create a new channel 8bit 
	/// </summary>
	/// <returns>channel 8 bit</returns>
	uchar* from_16_to_8();
	int* get_hist();
	/// <summary>
	/// create an array of value between a and b
	/// </summary>
	/// <param name="a">lower bound</param>
	/// <param name="b">upper bound</param>
	///	<param name="size">size of this array (16bit/32bit ..)</param>
	/// <returns></returns>
	uchar* create_lut_8bit(float a, float b, float gamma, uint size);
};


