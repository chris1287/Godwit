#include <QFileDialog>
#include <QImage>
#include <future>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <QFileInfo>
#include <marble/GeoDataCoordinates.h>

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
    centerOnLastLoadedPoint();
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
        using namespace Marble;

        QFileInfo f(name);
        mSettings.setValue("gpxDirectory", f.absolutePath());

        mTrack = std::unique_ptr<Track>( FutureFactory<Track, const QString&>::create_sync(name) );
        mViewer->updateTrackPoints(*mTrack);

        GeoDataCoordinates p = mViewer->getLastPointLoaded();
        mSettings.setValue("lastLoadedPoint", p.toString());
        mSettings.setValue("lastLoadedZoom", mViewer->zoom());
    }
}

void MainWindow::on_actionChange_theme_triggered()
{
    QString themeDirectory = mSettings.value("themeDirectory").toString();
    themeDirectory = themeDirectory.isEmpty() ? "." : themeDirectory;

    QString name = QFileDialog::getOpenFileName(this, "Open Theme File", themeDirectory, "Theme (*.dgml)");
    if(!name.isEmpty())
    {
        QFileInfo f(name);
        mSettings.setValue("themeDirectory", f.absolutePath());

        QString basePath("marble/data/maps/"); // TODO check if a better way to get the path is available
        int i = 0;
        if((i = name.lastIndexOf(basePath)) >= 0)
        {
            i += basePath.length();
            name = name.remove(0, i);
            mViewer->setMapThemeId(name);
        }
    }
}

void MainWindow::centerOnLastLoadedPoint()
{
    QString lastLoadedPoint = mSettings.value("lastLoadedPoint").toString();
    int lastLoadedZoom = mSettings.value("lastLoadedZoom").toInt();

    bool res;
    Marble::GeoDataCoordinates p = Marble::GeoDataCoordinates::fromString(lastLoadedPoint, res);
    if(res)
    {
        mViewer->centerOn(p);
    }

    if(lastLoadedZoom > 0)
    {
        mViewer->zoomView(lastLoadedZoom);
    }
}
