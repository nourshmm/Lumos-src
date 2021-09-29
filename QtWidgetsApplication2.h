#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication2.h"
#include <qlistview.h>
#include < QTreeView.h>
#include < QGraphicsScene.h>
#include <QGraphicsPixmapItem>
class QtWidgetsApplication2 : public QMainWindow
{
    Q_OBJECT
 public slots:
     /// <summary>
     /// show image in UI
     /// </summary>
     void widgetimage();
     /// <summary>
     /// generate all images from a run
     /// </summary>
     void widgetrun();
     /// <summary>
     /// generate one plate 
     /// </summary>
     void widgetplate();

public:
    /// <summary>
    /// connect all widgets in UI
    /// </summary>
    /// <param name="parent"></param>
    QtWidgetsApplication2(QWidget *parent = Q_NULLPTR);
    
private:
    /// <summary>
    /// Create the UI
    /// </summary>
    Ui::QtWidgetsApplication2Class ui;
    


};
