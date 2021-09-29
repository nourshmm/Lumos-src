#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include"Image.h"
#include "Lut.h"
/// <summary>
/// create a bmp from channels  
/// </summary>

using namespace cv;
class cCreate_Bmp
{

	Image image;
	uint size;
	int nb_channels;
	uint cols;
	uint rows;


public:
	/// <summary>
	/// Create bmp from image with N channel (N > = 1)
	/// </summary>
	/// <param name="i">Image</param>
	cCreate_Bmp(Image i);

	/// <summary>
	/// create a bmp from channels  
	/// </summary>
	uchar* create_bmp();

};
