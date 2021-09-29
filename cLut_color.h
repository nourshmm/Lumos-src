#pragma once
#include "cBmp.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
class cLut_color
{
	uint size;

	uchar* channel;


public:
	/// <summary>
	/// Create a color look up table 
	/// </summary>
	/// <param name="channel">grayscale data</param>
	/// <param name="size">size of data</param>
	cLut_color(uchar* channel, uint size);
	/// <summary>
	/// generates a pallet according to the channel  
	/// </summary>
	/// <param name="choice"> channel id</param>
	/// <returns> pallet</returns>
	uchar* lut_color(uint choice);

};

