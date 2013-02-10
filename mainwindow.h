#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <future>

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
    void handleNetworkData(QNetworkReply *);
    void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QNetworkDiskCache *mNetworkCache;
    QNetworkAccessManager *mNetworkAccessManager;
    QGraphicsScene *mScene;
    QGraphicsPixmapItem mPixmap;
    static QString mPath;
    std::unique_ptr<godwit::Track> mTrack;
    std::future<godwit::Track> mHandleTrack;

private:
    void updateTrack();
    void callbackTrackCreated(std::unique_ptr<godwit::Track> ptr);
};

#endif // MAINWINDOW_H
