#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "graphe.h"
#include "arbre.h"
#include "grapheValue.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pushButton_build_clicked();

    void on_pushButton_parcourir_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_build_arbre_clicked();

private:
    Ui::MainWindow *ui;
    grapheValue* G;
    arbre* A;
};
#endif // MAINWINDOW_H
