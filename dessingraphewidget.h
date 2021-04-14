#ifndef DESSINGRAPHEWIDGET_H
#define DESSINGRAPHEWIDGET_H

#include <QObject>
#include <QWidget>
#include "graphe.h"
#include "grapheValue.h"
#include <time.h>
#include <random>

class DessinGrapheWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DessinGrapheWidget(QWidget *parent = nullptr);
    DessinGrapheWidget(graphe* G,bool estValue, QWidget *parent = nullptr);
    DessinGrapheWidget(grapheValue* GV,bool estValue, QWidget *parent = nullptr);
    ~DessinGrapheWidget();

    QPoint creePointEntre(int xg,int yh,int xd,int yd) const;



protected :
    void paintEvent(QPaintEvent *event) override;

private :
    bool d_estValuee;
    graphe* Gra;
    grapheValue* GraVal;

signals:

};

#endif // DESSINGRAPHEWIDGET_H
