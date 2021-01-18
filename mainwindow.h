#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "angry_bee.h"
#include "bee.h"
#include "frog.h"
#include "platform.h"
#include "tadpole.h"
#include "maty.h"
#include "bala.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <vector>
#include <iostream>
#include <QTimer>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void ADVANCE();


private:
    void keyPressEvent(QKeyEvent *evento);
    QGraphicsScene *scene;
    Ui::MainWindow *ui;
    QList <platform*> platforms;
    QList <platform*> floor;
    QList <bee*> bees;
    QList <angry_bee*> Abees;
    QList <frog*> frogs;
    QList <tadpole*> tadpoles;
    QList <bala*> balas;
    QTimer * timer;
    maty *player;
    bool can_he_move();
    void collitions();
    void get_started();
    float timestep=0.4;
    bool started;

private slots:
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
