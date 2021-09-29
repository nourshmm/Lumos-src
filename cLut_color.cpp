#include "cLut_color.h"
#include <ctime>
/// <summary>
/// 
/// </summary>

cLut_color::cLut_color(uchar* channel, uint size) {
	this->channel = channel;
	//this->lut = lut;
	this->size = size;

}

uchar* generate_color(uchar r) {

	int i;
	uchar* c = (uchar*)malloc(256 * sizeof(uchar*));
	if (!c) {
		cout << "can't create lut color" << endl;

	}
	else {

		for (i = 0; i < 256; i++) {
			int a = (int)i;
			float b = (float)(i / 255.0);
			a = r * 256;
			c[i] = (uchar)a;




		}
	}
	return c;

}





/*Mat cLut_color::lut_color(uchar choice) {
	uchar* canal = this->channel;
	cv::Mat ch = cv::Mat(2000, 2000, CV_8UC1, (uchar*)canal);
	cv::Mat color;


	if(choice == 1)
		applyColorMap(ch,color, COLORMAP_HOT);
	if(choice==2)
		applyColorMap(ch, color, COLORMAP_BONE);
	if(choice== 5)
		applyColorMap(ch, color,  COLORMAP_PINK);
	if( (choice ==3)|| (choice ==4))
		applyColorMap(ch, color, COLORMAP_HOT);
	return color;
}
*/
uchar* cLut_color::lut_color(uint choice) {
	uint size = this->size;
	uchar* bmp;
	uchar* lut;


	float cmp;

	uchar indice;
	bmp = (uchar*)malloc(3 * size * sizeof(uchar));

	if (choice == 1) {

		for (uint i = 0; i < 3 * size; i++) {
			indice = (this->channel[i / 3]);



			bmp[i++] = 0;//indice;
			bmp[i++] = 0;
			bmp[i] = 0;



		}
	}
	if (choice == 2) {

		for (uint i = 0; i < 3 * size; i++) {
			indice = (this->channel[i / 3]);
			bmp[i++] = 0;
			bmp[i++] = indice;
			bmp[i] = 0;



		}
	}
	if (choice == 5) {

		for (uint i = 0; i < 3 * size; i++) {
			indice = (this->channel[i / 3]);

			bmp[i++] = 0;
			bmp[i++] = 0;
			bmp[i] = indice;



		}
	}
	if (choice == 6) {

		for (uint i = 0; i < 3 * size; i++) {
			indice = (this->channel[i / 3]);

			bmp[i++] = 255;
			bmp[i++] = 255;
			bmp[i] = 255;



		}

	}
	if ((choice == 3) || (choice == 4)) {


		lut = generate_color(160);
		for (uint i = 0; i < 3 * size; i++) {
			indice = (this->channel[i / 3]);

			bmp[i++] = 0;

			bmp[i++] = lut[(uint)indice];

			bmp[i] = indice;



		}
	}

	free(this->channel);

	return bmp;


}
