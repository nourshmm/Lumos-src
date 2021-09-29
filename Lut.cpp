#include "Lut.h"



Lut::Lut(float* channel, uint size) {

    this->size = size;
    this->channel = channel;

    this->a = 0;
    this->b = 65535;
    this->hist = nb_occurence(this->channel, this->size);

    
    //free(val);
}
int* Lut::nb_occurence(float* channel, uint size) {
    int* occ = NULL; // histogram data
    occ = (int*)malloc(65536 * sizeof(int));

    for (int i = 0; i < 65536; i++) {

        occ[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        int indice = (int)channel[i];
        occ[indice] += 1;
      
    }
    return occ;
}

int maximum(float* tab, int size) {


    int max = 0;
    for (int i = 0; i < size; i++) {
        if (tab[i] > max)
            max = tab[i];
    }
    return max;
}
int minimum(float* tab, int size) {


    int min = 0;
    for (int i = 0; i < size; i++) {
        if (tab[i] < min)
            min = tab[i];
    }
    return min;
}
int maxm(int* tab) {

    int indice;
    int max = 0;
    for (int i = 0; i < 65536; i++) {
        if (tab[i] > max) {
            max = tab[i];
            indice = i;
        }
    }
    return max;
}
int minm(int* tab) {


    int min = 65535;
    for (int i = 0; i < 65536; i++) {
        if ((tab[i] < min))
            min = tab[i];
    }
    return min;
}


uchar* Lut::from_16_to_8() {
    uchar* val = NULL;
    uint i;
    uint indice;
    uint size = this->size;

    //define_bounds(50);

     //this->hist = nb_occurence(this->channel, this->size);
     //
     //int max = maximum(this->channel, size);
    // cout << "max " << this->hist[max] << endl; 

     //int m = maxm(occ);
     //this->a = minimum(this->channel, size);
    //
     //this->b = max;
    define_A(1);
    define_B(5);
    this->a = 200;
    this->b = 4000;
    uchar* vec = NULL;
    vec = (uchar*)malloc(this->size * sizeof(uchar));
    val = create_lut_8bit(this->a, this->b, 1, 65536);
    if (vec == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }
    else {
        for (i = 0; i < this->size; i++) {

            indice = (uint)(this->channel[i]);

            vec[i] = val[indice];

        }
    }
    return vec;

}

void Lut::define_B(float percentage) {

    int max = maximum(this->channel, this->size);
    //cout << "max = " << max << endl;
    percentage = (percentage * this->size);
    percentage /= 100.0;
    if (percentage == 0)
        this->b = max;
    else {
        int acc1 = 0;
        for (int j = max; j > 0; j--) {
            acc1 += this->hist[j];
            if (acc1 >= percentage) {
                this->b = j;
                break;

            }
        }

    }
}
void Lut::define_A(float percentage) {

    int max = maximum(this->channel, this->size);
    //cout << "max = " << max << endl;
    percentage = (percentage * this->size);
    percentage /= 100.0;
    if (percentage == 0) {
        this->a = 0;
    }
    else {
        int acc2 = 0;
        for (int i = 0; i < max; i++) {
            acc2 += this->hist[i];

            if (acc2 >= percentage) {
                this->a = i;
                break;
            }
        }
    }
}
uchar* Lut::draw_hist() {
    int* hist_pix = NULL;

    hist_pix = (int*)malloc(2048 * sizeof(int));
    int acc;
    int indice;
    int maxi = maxm(this->hist);

    int s = 2048 * 2048;
    uchar** image = NULL;
    uchar* img = NULL;
    img = (uchar*)malloc(s * sizeof(uchar));
    image = (uchar**)malloc(2048 * sizeof(uchar*));
    for (int i = 0; i < 2048; i++) {
        image[i] = NULL;
        image[i] = (uchar*)malloc(2048 * sizeof(uchar));
    }


    /*for (int i = 0; i < 2048; i++) {
        acc = 0;
        indice = i * 32;
        for (int j = 0; j < 32; j++) {
            indice += j;
            if ((this->hist[indice]) > acc) {
                acc = this->hist[indice];

            }
        }

        hist_pix[i] = (int)(acc / 2);
    }
    */
    int* imge = (int*)malloc(2048 * sizeof(int));
    for (int i = 0; i < 2048; i++) {
        float f = (float)this->hist[i];
        f = f / (float)maxi;

        f = f * 2000;
        imge[i] = (int)f;

    }
    for (int i = 0; i < 2048; i++) {
        for (int j = 0; j < 2048; j++) {
            if (j <= imge[i])
                image[2047 - j][i] = 255;
            else
                image[2047 - j][i] = 0;


        }
    }






    int k = 0;
    for (int i = 0; i < 2048; i++) {
        for (int j = 0; j < 2048; j++) {
            img[k++] = image[i][j];


        }
    }
    return img;
}
void Lut::define_bounds(float percentage) {
    //int* hist = nb_occurence(this->channel, this->size);
    int max = maximum(this->channel, this->size);
    cout << "max = " << max << endl;
    percentage = (percentage * this->size);
    percentage /= 100.0;

    int acc1 = 0;
    int acc2 = 0;

    /*for (int i = 0; i < max; i++) {
        acc1 += hist[i];

        if (acc1 >= percentage) {
            this->a = i;
            break;
        }

    }*/
    this->a = 0;
    for (int j = max; j > 0; j--) {
        acc2 += hist[j];
        if (acc2 >= percentage) {
            this->b = j;
            break;

        }
    }
    cout << this->a << " this->b " << this->b << endl;


}
int* Lut::get_hist() {
    return this->hist;
}

uchar* Lut::create_lut_8bit(float a, float b, float gamma, uint size) {

    uchar* new_val;
    float cmp;
    int res;
    new_val = (uchar*)malloc(65535 * sizeof(uchar));
    size = b - a;

    if (new_val == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }

    else {
        //new_val = '\0';

        for (uint i = 0; i < size; i++) {


            if (i < a)

                new_val[i] = 0;
            else if (i > b)
                new_val[i] = 255;

            else {

                // formule : 255( val/65535) ^ gamma

                cmp = (float)i / size;
                cmp = pow(cmp, gamma);
                res = (255.0 * cmp);
                new_val[i] = (uchar)res;

            }
        }
    }

    return  new_val;
}


