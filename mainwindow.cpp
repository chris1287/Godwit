#include <QFileDialog>
#include <QImage>
#include <future>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <QFileInfo>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "track.h"
#include "GeoUtils.h"
#include "FutureFactory.h"

QString MainWindow::mPath = "http://tile.openstreetmap.org/%1/%2/%3.png";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mSettings("Godwit", "CrP")
{
    ui->setupUi(this);
    mViewer = new MapViewer();
    mViewer->setMapThemeId("earth/openstreetmap/openstreetmap.dgml");
    setCentralWidget(mViewer);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mViewer;
}

void MainWindow::on_actionOpen_triggered()
{
    QString gpxDirectory = mSettings.value("gpxDirectory").toString();
    gpxDirectory = gpxDirectory.isEmpty() ? "." : gpxDirectory;

    QString name = QFileDialog::getOpenFileName(this, "Open GPX File", gpxDirectory, "GPX (*.gpx)");
    if(!name.isEmpty())
    {
        using namespace godwit;

        QFileInfo f(name);
        mSettings.setValue("gpxDirectory", f.absolutePath());

        mTrack = std::unique_ptr<Track>( FutureFactory<Track, const QString&>::create_sync(name) );
        mViewer->updateTrackPoints(*mTrack);
    }
}
