#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <marble/GeoDataLineString.h>

#include "mapviewer.h"
#include "tracklayer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void centerOnLastLoadedPoint();

private slots:
    void on_actionOpen_triggered();
    void on_actionChange_theme_triggered();

private:
    Ui::MainWindow *ui;
    MapViewer *mViewer;

    static QString mPath;
    QSettings mSettings;
};

#endif // MAINWINDOW_H
