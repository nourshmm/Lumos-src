#include "QtWidgetsApplication2.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QPixmap>
#include <iostream>
#include< string.h>
#include < QLabel.h>
#include < QVBoxLayout>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <qprogressdialog.h>
#include <qprogressbar.h>
#include< QSize.h>
#include <cstdio>
#include"Lut.h"
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
#include"Image.h"
#include"cCreate_Bmp.h"
#include<List>
#include<regex>
#include <array>
#include <omp.h>
#include "cPlate.h"
#include <direct.h>
#include  < dirent.h>
using namespace std;
using namespace cv;

volatile DWORD dwStart;


// TODO
//creer une image avec toute une plaque ou je prend que e T+1 Z+1 je reduit chaque image pour quelle puisse rentrer
// definir automatiquement A et B --> Done
// faire un power  point 


const char* path_run;
Mat read_image(const String path, uint* tab) {

    Mat image;
    int j = 0;


    image = imread(path, IMREAD_ANYDEPTH);
    int size = image.cols * image.rows;
    tab = (uint*)malloc(size * sizeof(uint));
    if (tab == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }
    else {
        size *= 2;
        for (int i = 0; i < size; i += 2) {
            tab[j++] = (image.data[i + 1] << 8) + image.data[i];

        }
    }
    return image;

}


string  reg(string s) {
    string* ls = new string[10];
    string time, f, l, a, z, c, name;
    //string s = " JumpCP AD SED E05 aprés fixation new 20X A549 CellPainting_E08_T0001L0F0023A04Z05C06";
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
    /*delimiter = "_";
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
    cout << s << endl;

    cout << "ls[0] =   " << ls[0] << endl;
    cout << "ls[0] = " << (int) (ls[1].at(0) - 'A')   << "ls[2] = " << stoi( ls[2]) << "ls[4] = " << stoi( ls[4] )<< "ls[8] = " << stoi( ls[8]) << endl;*/
    return fld;

}



float* get_table(Mat channel, int size) {

    float* tab;
    uint j = 0;
    uint s = size * 2;
    tab = (float*)malloc(size * sizeof(float));
    if (tab == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }
    else {

        for (int i = 0; i < s; i += 2) {

            float Temp = (float)((channel.data[i + 1] << 8) + channel.data[i]);

            tab[j] = Temp;
            j += 1;
        }
    }

    return tab;
}


void processing(String* ls, int nb_channels) {

    string* channels = new string[nb_channels];

    int k;

    Mat res;
    int p;
    string id_im = "0";
    // #pragma omp parallel for 
    for (p = 0; p < 1; p++) {
        k = p * 54;
        //cout << "id_thread" << p << "\n";
        for (int i = 0; i < nb_channels; i++) {
            string s = ls[k + i];
            channels[i] = s;




        }


        Image  img(channels, nb_channels - 4);

        /*cv::Mat test =img.read_image("CellPainting_E08_T0001F001L01A01Z01C01.tif");
        cv::Mat test2,TempMat;
        cvtColor(houda, nour, COLOR_GRAY2BGR);
        applyColorMap(nour, TempMat, COLORMAP_JET);*/



        //vector<Mat> liste = img.create_img();


        cCreate_Bmp bmp(img);

        uchar* bmp_f = bmp.create_bmp();


        //cv::Mat TempMat = bmp.create_bmp();
        uint h = 2000;
        uint w = 2000;




        //cout << k << endl;


        cv::Mat TempMat = cv::Mat(w, h, CV_8UC3, (uchar*)bmp_f); // image 3 channel 8 bit 
        //Mat new_image = Mat::zeros(TempMat.size(), TempMat.type()); //  all value in matrix  = 0
        //TempMat.convertTo(new_image, -1, 0.5, 10);



        string pi = "C:\\Users\\nzi_sur\\Documents\\bmp_saved\\bmp\\image";

        id_im += "1";

        pi = pi + id_im + ".jpg";
        imwrite(pi, TempMat);
        //imwrite(pi, new_image);



        //free(bmp_f);
    }

    delete[] channels;
}

Mat addToPlate(Mat img1, Mat img2, uint cols, uint rows) {
    // cv::Mat result(image.rows, image.cols);
    // img1.copyTo(result(Rect(0, 0, image.cols, image.rows / 2)));
     //img2.copyTo(result(Rect(0, image.rows / 2, image.cols, image.rows / 2));



    return img2;

}

void add_newI(cv::Mat image) {
}
void create_channels(vector <cv::Mat> channels, string pi, int w, int h) {
    string indice[8];
    indice[0] = "1";
    indice[1] = "5";
    indice[2] = "2";
    indice[3] = "3";
    indice[4] = "4";
    indice[5] = "6";
    indice[6] = "7";
    indice[7] = "8";
    for (int id = 0; id < 8; id++) {

        // pi += indice[id];

        Mat dst = channels[id];
       /// cout << " this id = " << id << endl;
        //channels[id].convertTo(res, CV_8UC1);
        //normalize(channels[id], res, 0, 255, NORM_MINMAX, CV_8UC1);
        //dst.convertTo(res, CV_8UC1, 1 / 256.0);
       // Mat im_color;

       // applyColorMap(dst, im_color, COLORMAP_OCEAN);
        float* tab = get_table(dst, w * h);

        Lut l(tab, w * h);
        uchar* tmp = l.from_16_to_8();
        Mat resized;
        Mat res = Mat(h, w, CV_8UC1, (uchar*)tmp);
        resize(res, resized, cv::Size(res.cols * 0.25, res.rows * 0.25), 0, 0);
        imwrite(pi + indice[id] + ".png", resized);


    }


}
char* strTochar(string s) {
    char* c;
    int i;
    int sz = s.length() + 1;
    c = (char*)malloc(sz * sizeof(char));
    for (i = 0; i < sz; i++)
        c[i] = s[i];
    c[i] = '\0';

    return c;
}
void make_all(int th, vector<string> all_path, int w, int h,FILE* file) {
    vector <cv::Mat> channels;
    string path = all_path[th];
    path = path + "//*T*F*L*A*Z*C*.tif";
    vector < cv::String> fn;
    glob(path, fn, false);
    //sort(fn.begin(), fn.end());

    size_t size = fn.size();
    //string *ls = reg(fn[0]);


    string str;// = "W:\\Yokogawa\\JumpCP_PROD\\QC_visuel_Lumos\\nouveau_dossier\\" + reg(all_path[th]);
    str = std::string(path_run) + "\\" +reg(all_path[th]);
    // string str = "W:\\Yokogawa\\JumpCP_PROD\\QC_visuel_Lumos\\test";

    char* c = strTochar(str);


    _mkdir(c);

    string pi = str + "\\channel";





    cPlate plte(fn,file);
    channels = plte.create_plate();

 create_channels(channels, pi, w, h);

}






QtWidgetsApplication2::QtWidgetsApplication2(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
  
    /*QString file = QFileDialog::getOpenFileName(this, "Open the folder");

    if (file.isEmpty()) return;
    
    if (!QFile::exists(file)) {
        QMessageBox::critical(this, "Error on loading", "File not found!");
        return;
    }
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);*/
    QObject::connect(ui.actionimage, SIGNAL(triggered()), this, SLOT(widgetimage()));
    QObject::connect(ui.actionrun, SIGNAL(triggered()), this, SLOT(widgetrun()));
    QObject::connect(ui.actionplate, SIGNAL(triggered()), this, SLOT(widgetplate()));
}





void QtWidgetsApplication2::widgetimage() {
  //  setStyleSheet("QWidget{ background-color : rgba( 160, 160, 160, 255); border-radius : 7px;  }");
    QLabel* label = new QLabel(this);
 
  


   
    const QString file = QFileDialog::getOpenFileName(this, "Open image file", "", "IMG (*.*)");

    QImage image(file);
    
   
 // QImage newImage = image.scaled(1500, 800, Qt::KeepAspectRatio);
    QHBoxLayout* layout = new QHBoxLayout();
    //layout->setSizeConstraint(QLayout::SetFixedSize);
    QSize s = this->size();
   //layout->setGeometry(QRect(0, 0, 800, 800));
   //label->setGeometry(QRect(s.width, s.width(), s.height() / 3, s.height() / 3));

    //label->setGeometry(QRect(0, 0, 800,800));
    label->setPixmap(QPixmap::fromImage(image));
    //label->show();

    
    setLayout(layout);
    layout->addWidget(label);
    label->show();
    

  
 
}
char* my_strcpy(char* tocpy, int len) {
    char* str;
    str = (char*)malloc(len * sizeof(char));
    int i; 
    for ( i = 0; i < len; i++) {
        str[i] = tocpy[i];

    }
    str[len] = '\0';
        




    return str;
}
void QtWidgetsApplication2::widgetrun() {
    int w = 24 * 620;
    int h = 16 * 420;
    int size_p = h * w;
    DIR* dir, * d;
    struct dirent* entry, * entr;
    vector <string> fss;
    FILE* pFile;

    QString name = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    char* str;
    QByteArray ba = name.toLatin1();
    
     str =my_strcpy(ba.data(), ba.length());
     string ss = std::string(str);
    
     string root = "W:\\Yokogawa\\JumpCP_PROD\\QC_visuel_Lumos\\" + ss.substr(ss.find_last_of("/\\") + 1);
     string nameFileTxt = root + "\\qc.txt";
     path_run = root.c_str();
     pFile = fopen(nameFileTxt.c_str(), "w");


     _mkdir(path_run);
   if (str) {
        //string name = "W:\\Yokogawa\\JumpCP_PROD\\Run9et10_20210628\\";
        if ((dir = opendir(str)) == NULL)
            perror("opendir() error");
        else {
            puts("contents of root:");
            while ((entry = readdir(dir)) != NULL) {
                //printf("  %s\n", entry->d_name);
                std::string  strg = "\\" + std::string(entry->d_name);
                string fold = str + strg;
                const char* cstr = fold.c_str();
                for (int j = 0; j < 2; j++) {
                    if ((d = opendir(cstr)) == NULL)
                        perror("opendir() error");

                    else {
                        for (int i = 0; i < 3; i++)
                            entr = readdir(d);

                        fold += ("\\" + (std::string(entr->d_name)));



                        cstr = fold.c_str();
                    }
                    closedir(d);
                }

                if (d)
                    fss.push_back(fold);

            }
            closedir(dir);
        }
    


        fss.erase(fss.begin());
       fss.erase(fss.begin());
    
       int max = fss.size();
        QProgressDialog progress("Runing please wait...", "Cancel", 0, max , this);

        progress.setWindowModality(Qt::WindowModal);
        //int n_s = 5;
        

        int n_s = fss.size();
        //#pragma omp parallel for 
        for (int th = 0; th < n_s; th++) {
        

            progress.setValue(th);
            if (progress.wasCanceled())
                break;

            make_all(th, fss, w, h,pFile);
            
            //progress.setValue(th);
 
      
            // ... copie un fichier
        }
        progress.setValue(max);
        if (pFile != NULL)
        {
          
            fclose(pFile);
        }
    }
}
void QtWidgetsApplication2::widgetplate() {

    QFileDialog w;
    w.setFileMode(QFileDialog::DirectoryOnly);
    w.setOption(QFileDialog::DontUseNativeDialog, true);
    QListView* l = w.findChild<QListView*>("listView");
    if (l) {
        l->setSelectionMode(QAbstractItemView::MultiSelection);
    }
    QTreeView* t = w.findChild<QTreeView*>();
    if (t) {
        t->setSelectionMode(QAbstractItemView::MultiSelection);
        //QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    }
    w.exec();
}
