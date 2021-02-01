#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "angry_bee.h"
#include "bee.h"
#include "frog.h"
#include "platform.h"
#include "tadpole.h"
#include "maty.h"
#include "bala.h"
#include "txtinfo.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <vector>
#include <iostream>
#include <QTimer>
#include <QGraphicsView>
#include <QRectF>

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
    QList <maty *> players;
    int puntaje;
    txtinfo scores;


    void get_started();
    float timestep=0.4;   
    bool started;
    void delete_all();
    void start();
    void set_life();
    long int time_passed;


    void collitions();
    void npc_collitions();
    void player_collitions();
    bool can_he_move();
    int past;
    void Bhit();


    void tadpole_generator();
    void frog_genetarot();
    void bee_genetarot();
    void Abee_genetarot();
    void platform_generator();
    void floor_generator();
    void second();
    void bala_generator(float vx, float vy);

    int Abees_spawn, Bees_spawn;

    int puntajefrontera;



private slots:
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
