#pragma once
#include"Image.h"
#include "Lut.h"
/// <summary>
/// create a bmp from channels  
/// </summary>
class cBmp
{
	uchar** bmp;
	uint size;
public:
	cBmp(uint size);
	uchar** generate_bmp();

};
