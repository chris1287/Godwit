#include <QFileDialog>
#include <QImage>
#include <future>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "track.h"
#include "GeoUtils.h"
#include "FutureFactory.h"

QString MainWindow::mPath = "http://tile.openstreetmap.org/%1/%2/%3.png";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    viewer = new MapViewer();
    viewer->setMapThemeId("earth/openstreetmap/openstreetmap.dgml");
    setCentralWidget(viewer);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete viewer;
}

void MainWindow::on_actionOpen_triggered()
{
    QString name = QFileDialog::getOpenFileName(this, "Open GPX File", ".", "GPX (*.gpx)");
    if(!name.isEmpty())
    {
        using namespace godwit;

        mTrack = std::unique_ptr<Track>( FutureFactory<Track, const QString&>::create_sync(name) );
        viewer->updateTrackPoints(*mTrack);
    }
}
