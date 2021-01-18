#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bee.h"
#include "angry_bee.h"
#include "frog.h"
#include "tadpole.h"
#include "qiterator.h"
#include "iterator"
#include "iostream"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene= new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0,0,1151,-691);
    started=false;

    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(ADVANCE()));
    timer->start(1000/120);




}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    player= new maty(30,60,{40,70},-0.9);
    scene->addItem(player);
    bees.push_back(new bee(80,20,{300,500},5));
    scene->addItem(bees.back());
    Abees.push_back(new angry_bee(20,{100,100},5));
    scene->addItem(Abees.back());
    floor.push_back(new platform(1400,10,{0,8},{0,0},'g'));
    scene->addItem(floor.back());
    frogs.push_back(new frog(80,{1100,50},-200));
    scene->addItem(frogs.back());
    scene->addItem(frogs.back()->lengua);
    platforms.push_back(new platform(300,10,{0,150},{0,0},'g'));
    scene->addItem(platforms.back());
    started=true;

}
void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    if(can_he_move())
    {
        if(evento->key()==Qt::Key_D)
        {
            player->right();
        }
        else if(evento->key()==Qt::Key_W)
        {
            player->up();
        }
        if(evento->key()==Qt::Key_A)
        {
            player->left();
        }
    }

    if(evento->key()==Qt::Key_S)
    {
        player->down();
    }

}

bool MainWindow::can_he_move()
{
    for(int i =0;i!=floor.size();i++)
    {
        if(floor.at(i)->fake_layer->collidesWithItem(player))
        {
             return true;
        }
    }
    for(int i =0;i!=platforms.size();i++)
    {
        if(platforms.at(i)->fake_layer->collidesWithItem(player))
        {
             return true;
        }
    }
    return false;
}

void MainWindow::collitions()
{
        for(int i =0;i!=floor.size();i++)
        {
            if (floor.at(i)->collidesWithItem(player))
            {
                char state=floor.at(i)->where_is_it(player->getpos());
                if(floor.at(i)->fake_layer->collidesWithItem(player) && floor.at(i)->collidesWithItem(player) && state=='w')
                {
                     auto p = player->getpos();
                     auto v = player->getvel();
                     player->setvel(v[0],0);
                     player->setpos(p[0],floor.at(i)->getpos()[1]+player->ry);
                     break;
                }
                else if(floor.at(i)->collidesWithItem(player) && state=='s')
                {
                    auto p = player->getpos();
                    auto v = player->getvel();
                    player->setvel(v[0],0);
                    player->setpos(p[0],floor.at(i)->getpos()[1]+player->ry);
                }
                else if(floor.at(i)->collidesWithItem(player) && (state=='a'||state=='d'))
                {
                    auto v = player->getvel();
                    player->setvel(-v[0],v[1]);
                    player->Advance(timestep);
                }
            }

        }
        for(int i =0;i!=platforms.size();i++)
        {
            if (platforms.at(i)->collidesWithItem(player))
            {
                char state=platforms.at(i)->where_is_it(player->getpos());
                if(platforms.at(i)->fake_layer->collidesWithItem(player) && platforms.at(i)->collidesWithItem(player) && state=='w')
                {
                     auto p = player->getpos();
                     auto v = player->getvel();
                     player->setvel(v[0],0);
                     player->setpos(p[0],platforms.at(i)->getpos()[1]+player->ry);
                     std::cout<<'w'<<'\n';
                     break;
                }
                else if(platforms.at(i)->collidesWithItem(player) && state=='s')
                {
                    auto p = player->getpos();
                    auto v = player->getvel();
                    player->setvel(v[0],0);
                    player->setpos(p[0],platforms.at(i)->getpos()[1]-player->ry-platforms.at(i)->H);
                    std::cout<<'s'<<'\n';
                }
                else if(platforms.at(i)->collidesWithItem(player) && (state=='a'||state=='d') && (player->getpos()[1] < platforms.at(i)->getpos()[1] + player->ry*0.5 ))
                {
                    auto v = player->getvel();
                    player->setvel(-v[0],v[1]);
                    player->Advance(timestep);
                }
            }
        }
        return;
}

void MainWindow::ADVANCE()
{
    if (started)
    {

        float t =timestep;
        for(int i =0;i!=bees.size();i++)
        {
            bees.at(i)->Advance(t);
        }
        for(int i =0;i!=Abees.size();i++)
        {
            Abees.at(i)->Advance(t,player->getpos());
        }
        for(int i =0;i!=frogs.size();i++)
        {
            frogs.at(i)->Advance(t);
        }
        for(int i =0;i!=tadpoles.size();i++)
        {
            tadpoles.at(i)->Advance(t);
        }
        for(int i =0;i!=balas.size();i++)
        {
            balas.at(i)->Advance(t);
        }
        for(int i =0;i!=floor.size();i++)
        {
            floor.at(i)->Advance(t);
        }
        for(int i =0;i!=platforms.size();i++)
        {
            platforms.at(i)->Advance(t);
        }
        player->Advance(t);
        collitions();
        ui->lcdNumber->display(player->getpos()[1]);
        ui->lcdNumber_2->display(platforms.back()->getpos()[1]);
        ui->lcdNumber_3->display(Abees.back()->getpos()[1]);
    }
}
