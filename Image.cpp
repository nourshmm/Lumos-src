#include "Image.h"
#include<omp.h>
///<TODO>
////done ///
///mettre en paramettre le path d'une image et creer une img a partir d'un tableau
///laisser le channel comme il est 
///creer une class bmp (bitmap) qui s'occupe de creer une image avec plusieurs  channel
///</TODO>









Image::Image() {
    this->channels = NULL;
    this->nb_channels = 0;
    this->cols = 0;
    this->rows = 0;
    this->size = 0;




}
Image::Image(string* channels, int nb_channels) {

    this->channels = channels;
    this->nb_channels = nb_channels;

    this->cols = 0;
    this->rows = 0;
    this->size = 0;



}


Mat Image::read_image(const String path) {

    Mat image;
    uint j = 0;




    image = imread(path, IMREAD_ANYDEPTH);
    if (image.empty())
    {
        cout << "Could not read the image: " << endl;

    }
    this->cols = image.cols;
    this->rows = image.rows;
    this->size = image.cols * image.rows;
 

    return image;

}

float* Image::get_table(Mat channel) {

    float* tab;
    uint j = 0;
    uint s = this->size * 2;
    tab = (float*)malloc(this->size * sizeof(float));
    if (tab == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }
    else {

        for (int i = 0; i < s; i += 2) {

            float Temp = (float)(channel.data[i + 1] << 8) + channel.data[i];

            tab[j] = Temp;
            j += 1;
        }
    }

    return tab;
}
int Image::get_nb_channels() {
    return this->nb_channels;
}
vector<Mat>  Image::create_img() {


    vector<Mat> ch;
    int i;

    for (i = 0; i < this->nb_channels; i++) {
        ch.push_back(read_image(this->channels[i]));

    }


    return ch;

}
uint Image::get_cols() {
    //cout << "ici get" << this->cols << endl;
    return this->cols;

}
uint Image::get_rows() {
    //cout << "ici get" << this->rows << endl;
    return this->rows;

}

