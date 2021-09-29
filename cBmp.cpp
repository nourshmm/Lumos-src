#include "cBmp.h"





cBmp::cBmp(uint size) {
    this->size = size;

    this->bmp = generate_bmp();

}
uchar** cBmp::generate_bmp() {

    this->bmp = (uchar**)malloc(3 * sizeof(uchar*));
    if (this->bmp) {
        for (uint i = 0; i < 3; i++)
            this->bmp[i] = (uchar*)malloc(size * sizeof(uchar));

    }


    return bmp;
}
