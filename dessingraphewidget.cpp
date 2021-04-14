#include "dessingraphewidget.h"
#include <QPainter>
#include <QMessageBox>
DessinGrapheWidget::DessinGrapheWidget(QWidget *parent) : QWidget(parent)
{

}

DessinGrapheWidget::DessinGrapheWidget(graphe *G,bool estValue, QWidget *parent) :  QWidget(parent), d_estValuee{estValue}, Gra{G}
{

}

DessinGrapheWidget::DessinGrapheWidget(grapheValue *GV, bool estValue, QWidget *parent) : QWidget(parent), d_estValuee{estValue}, GraVal{GV}
{

}

DessinGrapheWidget::~DessinGrapheWidget()
{
    delete Gra;
    delete GraVal;
}

QPoint DessinGrapheWidget::creePointEntre(int xg, int yh, int xd, int yb) const
{
    /*std::random_device rd;
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distrX(xg, xd);
    std::uniform_int_distribution<> distrY(yh, yb);
    int x = distrX(gen);
    int y = distrY(gen);*/


    int x = xg + (int) ((float)rand() * (xd - xg+1) / (RAND_MAX-1));
    int y = yh + (int) ((float)rand() * (yb - yh+1) / (RAND_MAX-1));


    return QPoint(x,y);
}



void DessinGrapheWidget::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    QPen pen{Qt::darkBlue,3,Qt::SolidLine};
    QPen ecrire{Qt::black,10,Qt::SolidLine};
    paint.setRenderHints(QPainter::Antialiasing);
    paint.setWindow(0,0,1054,623);
    paint.setPen(pen);
    paint.setBrush(Qt::blue);
    paint.setBrushOrigin(0,0);
    vector<QPoint> tabSommet{};

    int nbSommet = d_estValuee ? GraVal->getNbSommet() : Gra->getNbSommet();
    int xDepart = 15, yDepart = 15;
    int xfin =paint.window().width(), yfin = 623;
    int incrementationX = xfin / nbSommet * 2;
    int incrementationY = (yfin / nbSommet) * 1.5;

    tabSommet.resize(nbSommet+1);
    tabSommet[0] = QPoint(nbSommet,0);
    for(int i =1; i <= nbSommet ;++i)
    {
        QPoint p = creePointEntre(xDepart,yDepart,xDepart+incrementationX, yDepart+incrementationY);
        paint.drawEllipse(p,15,15);
        paint.setPen(ecrire);
        paint.drawText(p.x()+15,p.y()-15,QString::number(i));
        paint.setPen(pen);
        xDepart+=incrementationX;
        xDepart = (xDepart + incrementationX > xfin) ? 0 : xDepart;
        if(i % 2 == 0){
            yDepart+=incrementationY;
        }
        tabSommet[i] = p;
    }

    if(d_estValuee){

        for(unsigned int i = 1; i < GraVal->d_matrice_adjacence.size(); ++i)
        {
            for(unsigned int j = 1; j < GraVal->d_matrice_adjacence[i].size() ; ++j)
            {
                if(GraVal->d_matrice_adjacence[i][j] == 1)
                {
                    paint.drawLine(tabSommet[i],tabSommet[j]);
                }
            }
        }
    }else{
        for(unsigned int i = 1; i < Gra->d_matrice_adjacence.size(); ++i)
        {
            for(unsigned int j = 1; j < Gra->d_matrice_adjacence[i].size() ; ++j)
            {
                if(Gra->d_matrice_adjacence[i][j] == 1)
                {
                    paint.drawLine(tabSommet[i],tabSommet[j]);
                }
            }
        }
    }
}
