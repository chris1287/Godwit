#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "track.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
        Track t = Track::createTrackFromGPX(name);
        QString s(QString::number(t.getDistance()));
        ui->textEdit->setText(s);
    }
}
