#include "dialogaffichegraphe.h"
#include "ui_dialogaffichegraphe.h"
#include "mainwindow.h"

DialogAfficheGraphe::DialogAfficheGraphe(QWidget *parent,bool estValue, graphe* G , grapheValue* GV) :
    QDialog(parent),
    ui(new Ui::DialogAfficheGraphe) , Gra{G}, GraVal{GV}
{
    ui->setupUi(this);
    if(estValue){
        dessin = new DessinGrapheWidget(GV,estValue,this);
    }else{
        dessin = new DessinGrapheWidget(G,estValue,this);
    }

    //dessin->resize(this->width(),this->height());
    dessin->resize(this->width(),this->height());
    this->resize(this->width()+200,this->height()+200);
}

DialogAfficheGraphe::~DialogAfficheGraphe()
{
    delete ui;
}
