#include "cCreate_Bmp.h"
#include "cLut_color.h"
#include<omp.h>


cCreate_Bmp::cCreate_Bmp(Image i) {
    this->image = i;
    this->size = 0;
    this->cols = 0;
    this->rows = 0;
    this->nb_channels = 1;

}

uchar* cCreate_Bmp::create_bmp() {
    float* tab;
    uint i = 0, j;
    vector <Mat> b = this->image.create_img(); // all channels
    this->cols = this->image.get_cols(); // w of image
    this->rows = this->image.get_rows(); // h of image
    this->size = this->cols * this->rows; // image size
    uint size = this->size;
    long long int s = this->size;
    s *= 3; // size of the RGB image

    uchar* tmp = nullptr;

    uchar* bmp = (uchar*)malloc(s * sizeof(uchar));


// alocate memory for channel_color
    uchar** channel_color;
    channel_color = (uchar**)malloc(this->nb_channels * sizeof(uchar*));


    for (int id = 0; id < this->nb_channels; id++)
        channel_color[id] = (uchar*)malloc(3 * size * sizeof(uchar));


    i = 0;


    for (auto it = b.begin(); it != b.end(); ++it, i++) {
       // get table from matrix
        tab = image.get_table(*it);

        // create look up table  16 bit -> 8 bit
        Lut l(tab, size);
        
        tmp = l.from_16_to_8();

        // creating and drawing histogramme from the image 16 bit
        //tmp = l.draw_hist();


        // create color look up table
        cLut_color color(tmp, this->size);
      
        channel_color[i] = color.lut_color(i + 1);
     


    }

    //b.clear();
    int div;
    for (j = 0; j < s; j++) {
        div = this->nb_channels;
        if (bmp) {
            float acc = 0;

            //#pragma omp parallel for 
            for (int k = 0; k < this->nb_channels; k++) {
                /*if ((channel_color[k][j]) < 10)
                    div--;*/
                    //acc = (0.4 * channel_color[k][j]) + (0.6 * acc);
                acc += (channel_color[k][j]);

                //cout << "channel_color[k][j] " << (uint)channel_color[k][j] << endl;
            }
            if (acc > 30)
                acc /= div;

            int acm = (int)acc;

            bmp[j] = (uchar)acm;
            //cout << "this is acc" << (uint) acc << endl;
        }
        else
            printf(" result is empty ! \n");
    }
    for (uint id = 0; id < this->nb_channels; id++)
        free(channel_color[id]);
    free(channel_color);

    return bmp;

}
