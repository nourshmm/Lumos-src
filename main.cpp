#include "QtWidgetsApplication2.h"
#include <QtWidgets/QApplication>
#include < QMenu.h>
#include < iostream>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWidgetsApplication2 w;
    w.show();
    cout << "ici" << endl;


    // emplacement "C:\Users\nzi_sur\source\repos\QtWidgetsApplication2\QtWidgetsApplication2"
    return a.exec();
}
