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
    mNetworkCache = new QNetworkDiskCache(this);
    mNetworkCache-> setCacheDirectory("./.cache");

    mNetworkAccessManager = new QNetworkAccessManager(this);
    mNetworkAccessManager->setCache(mNetworkCache);

    connect(mNetworkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleNetworkData(QNetworkReply*)));

    mScene = new QGraphicsScene(this);
    ui->graphicsView->setScene(mScene);

    mScene->addItem(&mPixmap);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString name = QFileDialog::getOpenFileName(this, "Open GPX File", ".", "GPX (*.gpx)");
    if(!name.isEmpty())
    {
        using namespace godwit;

        FutureFactory<Track, const QString&>::create_async_byFuture(name);

        mTrack = std::unique_ptr<Track>( FutureFactory<Track, const QString&>::create_sync(name) );
        updateTrack();
    }
}

void MainWindow::handleNetworkData(QNetworkReply *reply)
{
    if(!reply)
    {
        qDebug() << "QNetworkReply is NULL";
        return;
    }

    QUrl url = reply->url();
    if(reply->error())
    {
        qDebug() << "Network reply error";
        return;
    }

    QImage img;
    img.load(reply, 0);
    reply->deleteLater();

    mPixmap.setPixmap( QPixmap::fromImage(img) );
}

void MainWindow::on_spinBox_valueChanged(int)
{
    updateTrack();
}

void MainWindow::updateTrack()
{
    using namespace godwit;

    if(mTrack)
    {
        const Point start = mTrack->getStart();
        // const Point end = mTrack.getEnd();

        int zoom = ui->spinBox->value();
        int tilex = long2tilex(start.getLongitude(), zoom);
        int tiley = lat2tiley(start.getLatitude(), zoom);

        QUrl url = QUrl(mPath.arg(zoom).arg(tilex).arg(tiley));
        QNetworkRequest request;
        request.setUrl(url);
        request.setRawHeader("User-Agent", "Godwit 1.0.0");
        mNetworkAccessManager->get(request);
    }
}

void MainWindow::callbackTrackCreated(std::unique_ptr<godwit::Track> ptr)
{
    mTrack = std::unique_ptr<godwit::Track>(std::move(ptr));
    updateTrack();
}
