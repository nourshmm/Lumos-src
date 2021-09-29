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
using namespace cv;
using namespace std;
#include <iostream> 
#include <vector> 
#include <stdio.h>
#include <stdlib.h>
#include<regex>

#include "Lut.h"

/// <summary>
/// create an object channel from an array (Uint16 *)
/// </summary>
class cChannel
{
public:
	//Lut l;
	uint* val, * channel;

	uint a, b;
	int size, size_l;
	cChannel();
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="channel"></param>
	/// <param name="a">lower born of lut</param>
	/// <param name="b">upper born of lut</param>
	/// <param name="size">size of channel</param>
	/// <returns></returns>
	cChannel(uint* channel, uint a, uint b, int size, int size_l);
	/// <summary>
	/// set the bounds of the look up table
	/// </summary>
	/// <param name="a">lower bound</param>
	/// <param name="b">upper bound</param>
	void set_bound(uint a, uint b);
	/// <summary>
	/// get the array before lut
	/// </summary>
	/// <returns>channel</returns>
	uint* get_channel();
	/// <summary>
	/// get array after tyhe application of lut on this channel
	/// </summary>
	/// <returns></returns>
	//uint* get_newChannel();

};
