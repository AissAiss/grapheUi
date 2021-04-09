#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_build_clicked()
{
    QString str = ui->lineEdit_nomDuFichier->text();

    G = new graphe(str.toStdString());

    G->rang();
    G->tarjan();
    G->adjacence();

    ui->label_aps_vector->setText(QString::fromStdString(G->getAps()));
    ui->label_fs_vector->setText(QString::fromStdString(G->getFs()));

    ui->label_prem_vector->setText(QString::fromStdString(G->getTarjanPrem()));
    ui->label_pilch_vector->setText(QString::fromStdString(G->getTarjanPilch()));
    ui->label_cfc_vector->setText(QString::fromStdString(G->getTarjanCfc()));
    ui->label_num_vector->setText(QString::fromStdString(G->getTarjanNum()));
    ui->label_adjacence_vector->setText(QString::fromStdString(G->getAdjacence()));

    G->distance(1);
    ui->label_dist_vector->setText(QString::fromStdString(G->getDist()));
    ui->label_rang_vector->setText(QString::fromStdString(G->getRangddi()));

    ui->pushButton_save->setEnabled(true);


}

void MainWindow::on_pushButton_parcourir_clicked()
{
    int nb = ui->spinBox_distance->value();

    G->distance(nb);

    ui->label_dist_vector->setText(QString::fromStdString(G->getDist()));

    ui->spinBox_distance->cleanText();

}

void MainWindow::on_pushButton_save_clicked()
{
    QMessageBox msgBox;

    G->sauvgarde();
    msgBox.setText("Votre document à été sauvgardé !");
    msgBox.exec();
}
