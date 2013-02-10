#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <future>
#include <QSettings>
#include "mapviewer.h"

#include "track.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    MapViewer *mViewer;
    static QString mPath;
    std::unique_ptr<godwit::Track> mTrack;
    QSettings mSettings;
};

#endif // MAINWINDOW_H
