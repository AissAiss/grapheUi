#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grapheValue.h"

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

bool MainWindow::getEstValue() const
{
    return d_estValue;
}

graphe *MainWindow::getG()
{
    return G;
}

grapheValue* MainWindow::getGV()
{
    return GV;
}


void MainWindow::on_pushButton_build_clicked()
{
    QString str = ui->lineEdit_nomDuFichier->text();
    d_estValue = ui->checkBox_value->isChecked();

    if(d_estValue){
        GV = new grapheValue(str.toStdString());


        GV->rang();
        GV->tarjan();
        GV->dijkstra(1);

        ui->label_aps_vector->setText(QString::fromStdString(GV->getAps()));
        ui->label_fs_vector->setText(QString::fromStdString(GV->getFs()));

        ui->label_prem_vector->setText(QString::fromStdString(GV->getTarjanPrem()));
        ui->label_pilch_vector->setText(QString::fromStdString(GV->getTarjanPilch()));
        ui->label_cfc_vector->setText(QString::fromStdString(GV->getTarjanCfc()));
        ui->label_num_vector->setText(QString::fromStdString(GV->getTarjanNum()));
        ui->label_adjacence_vector->setText(QString::fromStdString(GV->getAdjacence()));

        GV->distance(1);
        ui->label_dist_vector->setText(QString::fromStdString(GV->getDist()));
        ui->label_rang_vector->setText(QString::fromStdString(GV->getRangddi()));
        ui->label_Matrice_arrete_vector->setText(QString::fromStdString(GV->getMatricePoids()));
        ui->label_Value->setText(QString::fromStdString("Valeur des aretes"));

        ui->label_titre_dijkstra->setText(QString::fromStdString("Dijkstra"));
        ui->label_dijkstra_dist->setText(QString::fromStdString("Distance"));
        ui->label_dijkstra_pred->setText(QString::fromStdString("Predecesseur"));
        ui->label_dijkstra_dist_vector->setText(QString::fromStdString(GV->getDijkstraDist()));
        ui->label_dijkstra_pred_vector->setText(QString::fromStdString(GV->getDijkstraPred()));

        ui->pushButton_save->setEnabled(true);

        //limitation spinBox
        ui->spinBox_distance->setRange(1,GV->getNbSommet());
        ui->spinBox_dijkstra->setRange(1,GV->getNbSommet());
        ui->spinBox_dijkstra->show();
        ui->pushButton_parcourir_dijkstra->show();

    }else{
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

        //clear des chose sur graphe value
        ui->label_Matrice_arrete_vector->clear();
        ui->label_Value->clear();
        ui->label_titre_dijkstra->clear();
        ui->label_dijkstra_dist->clear();
        ui->label_dijkstra_pred->clear();
        ui->label_dijkstra_dist_vector->clear();
        ui->label_dijkstra_pred_vector->clear();
        ui->spinBox_dijkstra->hide();
        ui->pushButton_parcourir_dijkstra->hide();

        ui->pushButton_save->setEnabled(true);

        //limitation spinBox
        ui->spinBox_distance->setRange(1,G->getNbSommet());

    }



}

void MainWindow::on_pushButton_parcourir_clicked()
{
    int nb = ui->spinBox_distance->value();

    if(d_estValue)
    {
        GV->distance(nb);
        ui->label_dist_vector->setText(QString::fromStdString(GV->getDist()));
    }else{
        G->distance(nb);
        ui->label_dist_vector->setText(QString::fromStdString(G->getDist()));
    }

    ui->spinBox_distance->cleanText();

}

void MainWindow::on_pushButton_save_clicked()
{
    QMessageBox msgBox;
    if(d_estValue){
        GV->sauvgarde();
    }else{
        G->sauvgarde();
    }

    msgBox.setText("Votre document à été sauvgardé !");
    msgBox.exec();

}

void MainWindow::on_pushButton_build_arbre_clicked()
{
    QString str = ui->lineEdit_nomDuFichier_arbre->text();

    A = new arbre(str.toStdString());

    A->codage();

    ui->label_codage_vector->setText(QString::fromStdString(A->getCodage()));

}


void MainWindow::on_pushButton_parcourir_dijkstra_clicked()
{
    int nb = ui->spinBox_dijkstra->value();

    if(d_estValue)
    {
        GV->dijkstra(nb);

        ui->label_dijkstra_dist_vector->setText(QString::fromStdString(GV->getDijkstraDist()));
        ui->label_dijkstra_pred_vector->setText(QString::fromStdString(GV->getDijkstraPred()));
    }

    ui->spinBox_dijkstra->cleanText();
}

void MainWindow::on_pushButton_dessiner_clicked()
{
    if(d_estValue)
    {
        graph = new DialogAfficheGraphe(this,d_estValue,nullptr,getGV());
    }else{
        graph = new DialogAfficheGraphe(this,d_estValue,getG());
    }


    graph->show();
}
