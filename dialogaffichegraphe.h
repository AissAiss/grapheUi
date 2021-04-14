#ifndef DIALOGAFFICHEGRAPHE_H
#define DIALOGAFFICHEGRAPHE_H

#include "dessingraphewidget.h"
#include <QDialog>

namespace Ui {
class DialogAfficheGraphe;
}

class DialogAfficheGraphe : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAfficheGraphe(QWidget *parent = nullptr,bool estValue = false, graphe* G = nullptr, grapheValue* GV= nullptr);
    ~DialogAfficheGraphe();

private:
    Ui::DialogAfficheGraphe *ui;
    DessinGrapheWidget* dessin;
    graphe* Gra;
    grapheValue* GraVal;
};

#endif // DIALOGAFFICHEGRAPHE_H
