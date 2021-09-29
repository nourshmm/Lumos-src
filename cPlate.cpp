
#include "cPlate.h"
#include <omp.h>

cPlate::cPlate(vector < cv::String> fn, FILE * file) {

    this->fn = fn;
    this->size_i = 0;
    this->file = file;

}


float* cPlate::get_table(Mat channel) {

    float* tab;
    uint j = 0;
    uint s = this->size_i * 2;
    tab = (float*)malloc(this->size_i * sizeof(float));
    if (tab == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }
    else {

        for (int i = 0; i < s; i += 2) {
            // all value take 2 case (1 case <=> 8bit , 1 value <=>16bit)
            float Temp = (float)((channel.data[i + 1] << 8) + channel.data[i]);

            tab[j] = Temp;
            j += 1;
        }
    }

    return tab;
}
string* cPlate::reg(string s) {
    string* ls = new string[10];
    string time, f, l, a, z, c, name;
    //string example_name = " JumpCP AD SED E05 aprés fixation new 20X A549 CellPainting_E08_T0001L0F0023A04Z05C06";
    string delimiter = "\\";
    string column;
    string line, fld;


    ls[0] = s.substr(0, s.find(delimiter));
    string field = s.erase(0, ls[0].length() + delimiter.length());
    size_t pos = std::string::npos;

    while ((pos = field.find(delimiter)) != std::string::npos)
    {
        ls[0] = field.substr(0, field.find(delimiter));
        fld = field.erase(0, ls[0].length() + delimiter.length());
    }
    delimiter = "_";
    ls[0] = fld.substr(0, fld.find(delimiter));
    field = fld.erase(0, ls[0].length() + delimiter.length());


    ls[1] = field[0]; //line
    regex e("[a-zA-Z-_]");
    regex_token_iterator<string::iterator> i(field.begin(), field.end(), e, -1);
    regex_token_iterator<string::iterator> end;
    *i++;


    ls[2] = (*i++); // column

    *i++;
    ls[3] = (*i++); // T
    ls[4] = (*i++);// f
    ls[5] = (*i++); // l 
    ls[6] = (*i++);//a
    ls[7] = (*i++); //z
    ls[8] = (*i++); // c

    return ls;

}

void cPlate::copyto(int pos_x, int pos_y, Mat image, Mat plate) {

    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 200; j++) {
            plate.at<ushort>(pos_y + i, pos_x + j) = image.at<ushort>(i, j);
        }

    }




}
Mat cPlate::my_resize(Mat tab, int scalar) {
    Mat reseized = Mat(200, 200, CV_16UC1, Scalar(65535));
    int l, c;
    int cols = tab.cols / scalar;
    int rows = tab.rows / scalar;


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            l = i * scalar;
            c = j * scalar;
            reseized.at<ushort>(i, j) = tab.at<ushort>(l, c);

            //reseized.at<uchar>(i, j+1) = tab.at<uchar>(l, c+1);


        }
    }

    return reseized;
}
vector< cv::Mat> cPlate::create_plate() {
    int w = 24 * 620; // column * 200 (size image) * 3 (field in the first line for one well)  + 20 (separator of wells)
    int h = 16 * 420; // line * 200 (size image) * 2 (field in the first column for one well)  + 20 (separator of wells)
    int size_p = h * w;
    Mat first = imread(fn[0], IMREAD_ANYDEPTH); // read first image 


    int cols = first.cols;
    int rows = first.rows;
    this->size_i = cols * rows;

    vector <cv::Mat> channels;
    for (int id = 0; id < 8; id++) {
        channels.push_back(cv::Mat(h, w, CV_16UC1, Scalar(65535))); // create matrix 16 bit grayscale for all channels / brightfields 

    }



    size_t size = (fn.size());


    int id = 0;

    //int pos_x = 0, pos_y = 0;

    int z = 0;



    //int c = 0, f = 0, ww = 0, ligne = 0;
   //#pragma omp parallel for
    for (int i = 0; i < size; i++) {
        std::cout << i << "\t" << endl;
        string* s = reg(fn[i]);
        int chan = stoi(s[8]) - 1;
        if (chan > 4) {
            chan += z;
            z++;
        }
        else
            z = 0;
        int pos_f_c = (stoi(s[4]) - 1) % 3;
        int pos_f_l = (stoi(s[4]) - 1) / 3;
        int  pos_y = ((int)(s[1].at(0) - 'A')) * 420; // line
        pos_y += pos_f_l * 200; 

        int pos_x = (stoi(s[2]) - 1) * 620 + (pos_f_c * 200);





        cv::Mat reseized, dst, res;
        float* tab;
        
        dst = imread(fn[i], IMREAD_ANYDEPTH);
        res = Mat(200, 200, CV_16UC1, Scalar(0));
        if ((dst.cols + dst.rows) == 0) {
            fputs(fn[i].c_str(), file);
            fputs("\n", file);
            continue;
        }
        resize(dst, reseized, res.size());
        //cv::Mat to(channels[chan], cv::Range(pos_y, pos_y + 200), cv::Range(pos_x, pos_x + 200));
        //reseized.copyTo(to);
        copyto(pos_x, pos_y, reseized, channels[chan]); 

    }







 
    return channels;
}
