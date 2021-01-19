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
    delete_all();
    start();
    started=true;

}
void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    if(can_he_move())
    {

        if(evento->key()==Qt::Key_W)
        {
            players.at(0)->up();
        }

    }

    if(evento->key()==Qt::Key_S)
    {
        players.at(0)->down();
    }
    if(evento->key()==Qt::Key_A)
    {
        players.at(0)->left();
    }
    if(evento->key()==Qt::Key_D)
    {
        players.at(0)->right();
    }

}

bool MainWindow::can_he_move()
{
    for(int i =0;i!=floor.size();i++)
    {
        if(floor.at(i)->fake_layer->collidesWithItem(players.at(0)))
        {
             return true;
        }
    }
    for(int i =0;i!=platforms.size();i++)
    {
        if(platforms.at(i)->fake_layer->collidesWithItem(players.at(0)))
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
            if (floor.at(i)->collidesWithItem(players.at(0)))
            {
                char state=floor.at(i)->where_is_it(players.at(0)->getpos());
                if(floor.at(i)->fake_layer->collidesWithItem(players.at(0)) && floor.at(i)->collidesWithItem(players.at(0)) && state=='w')
                {
                     auto p = players.at(0)->getpos();
                     auto v = players.at(0)->getvel();
                     players.at(0)->setvel(v[0],0);
                     players.at(0)->setpos(p[0],floor.at(i)->getpos()[1]+players.at(0)->ry);
                     break;
                }
                else if(floor.at(i)->collidesWithItem(players.at(0)) && state=='s')
                {
                    auto p = players.at(0)->getpos();
                    auto v = players.at(0)->getvel();
                    players.at(0)->setvel(v[0],0);
                    players.at(0)->setpos(p[0],floor.at(i)->getpos()[1]+players.at(0)->ry);
                    break;
                }
                else if(floor.at(i)->collidesWithItem(players.at(0)) && (state=='a'||state=='d'))
                {
                    auto v = players.at(0)->getvel();
                    players.at(0)->setvel(-v[0],v[1]);
                    players.at(0)->Advance(timestep);
                    break;
                }
            }

        }
        for(int i =0;i!=platforms.size();i++)
        {
            if (platforms.at(i)->collidesWithItem(players.at(0)))
            {
                char state=platforms.at(i)->where_is_it(players.at(0)->getpos());
                if(platforms.at(i)->fake_layer->collidesWithItem(players.at(0)) && platforms.at(i)->collidesWithItem(players.at(0)) && state=='w')
                {
                     auto p = players.at(0)->getpos();
                     auto v = players.at(0)->getvel();
                     players.at(0)->setvel(v[0],0);
                     players.at(0)->setpos(p[0],platforms.at(i)->getpos()[1]+players.at(0)->ry);
                     std::cout<<'w'<<'\n';
                     break;
                }
                else if(platforms.at(i)->collidesWithItem(players.at(0)) && state=='s')
                {
                    auto p = players.at(0)->getpos();
                    auto v = players.at(0)->getvel();
                    players.at(0)->setvel(v[0],0);
                    players.at(0)->setpos(p[0],platforms.at(i)->getpos()[1]-players.at(0)->ry-platforms.at(i)->H);
                    std::cout<<'s'<<'\n';
                    break;
                }
                else if(platforms.at(i)->collidesWithItem(players.at(0)) && (state=='a'||state=='d') && (players.at(0)->getpos()[1] < platforms.at(i)->getpos()[1] + players.at(0)->ry*0.5 ))
                {
                    auto v = players.at(0)->getvel();
                    players.at(0)->setvel(-v[0],v[1]);
                    players.at(0)->Advance(timestep);
                    break;
                }
            }
        }
        npc_collitions();
        player_collitions();
}

void MainWindow::delete_all()
{
    while(platforms.size()!=0)
    {
        scene->removeItem(platforms.at(0));
        platforms.removeAt(0);
    }
    while(floor.size()!=0)
    {
        scene->removeItem(floor.at(0));
        floor.removeAt(0);
    }
    while(bees.size()!=0)
    {
        scene->removeItem(bees.at(0));
        bees.removeAt(0);
    }
    while(Abees.size()!=0)
    {
        scene->removeItem(Abees.at(0));
        Abees.removeAt(0);
    }
    while(balas.size()!=0)
    {
        scene->removeItem(balas.at(0));
        balas.removeAt(0);
    }
    while(frogs.size()!=0)
    {
        scene->removeItem(frogs.at(0));
        scene->removeItem(frogs.at(0)->lengua);
        frogs.removeAt(0);
    }
    while(tadpoles.size()!=0)
    {
        scene->removeItem(tadpoles.at(0));
        platforms.removeAt(0);
    }
    while(players.size()!=0)
    {
        scene->removeItem(players.at(0));
        players.removeAt(0);
    }

}

void MainWindow::start()
{
    players.push_back(new maty(30,60,{40,70},-0.8));
    scene->addItem(players.back());
    bees.push_back(new bee(80,20,{1180,500},-5));
    scene->addItem(bees.back());
    Abees.push_back(new angry_bee(20,{1180,100},5));
    scene->addItem(Abees.back());
    floor.push_back(new platform(1400,10,{0,8},{0,0},'g'));
    scene->addItem(floor.back());
    frogs.push_back(new frog(80,{1150,50},-150));
    scene->addItem(frogs.back()->lengua);
    scene->addItem(frogs.back());
    platforms.push_back(new platform(300,10,{0,150},{1,0},'g'));
    scene->addItem(platforms.back());
}

void MainWindow::npc_collitions()
{
    for(int i=0; i!=Abees.size();i++)
    {
        for(int ii=0; ii!=platforms.size();ii++)
        {
            if(platforms.at(ii)->collidesWithItem(Abees.at(i)))
            {
                scene->removeItem(Abees.at(i));
                Abees.removeAt(i);
                i--;
                break;

            }

        }
    }
    for(int i=0; i!=bees.size();i++)
    {
        for(int ii=0; ii!=platforms.size();ii++)
        {
            if(platforms.at(ii)->collidesWithItem(bees.at(i)))
            {
                scene->removeItem(bees.at(i));
                bees.removeAt(i);
                i--;
                break;

            }

        }
    }
    for(int i=0; i!=tadpoles.size();i++)
    {
        for(int ii=0; ii!=platforms.size();ii++)
        {
            if(platforms.at(ii)->collidesWithItem(tadpoles.at(i)))
            {
                scene->removeItem(tadpoles.at(i));
                tadpoles.removeAt(i);
                i--;
                break;

            }

        }
    }
}

void MainWindow::player_collitions()
{

    for(int i=0; i!=Abees.size();i++)
    {
        if(players.at(0)->collidesWithItem(Abees.at(i)))
        {
            scene->removeItem(Abees.at(i));
            Abees.removeAt(i);
            i--;
            players.at(0)->life-=10;

        }

    }

    for(int i=0; i!=bees.size();i++)
    {
        if(players.at(0)->collidesWithItem(bees.at(i)))
        {
            scene->removeItem(bees.at(i));
            bees.removeAt(i);
            i--;
            players.at(0)->life-=10;

        }
    }

    for(int i=0; i!=tadpoles.size();i++)
    {
        if(players.at(0)->collidesWithItem(tadpoles.at(i)))
        {
            scene->removeItem(tadpoles.at(i));
            tadpoles.removeAt(i);
            i--;
            players.at(0)->life-=10;

        }
    }

    for(int i=0; i!=frogs.size();i++)
    {
        if(players.at(0)->collidesWithItem(frogs.at(i)->lengua))
        {
            auto vel=players.at(0)->getvel();
            players.at(0)->life-=10;
            if('a'==frogs.at(i)->lengua->where_is_it(players.at(0)->getpos()))
            {
                players.at(0)->setvel(vel[0]-5,vel[1]);
                players.at(0)->setvel(vel[0]-5,vel[1]);
                players.at(i)->Advance(timestep);
            }
            else
            {
                players.at(0)->setvel(vel[0]+5,vel[1]);
                players.at(0)->setvel(vel[0]+5,vel[1]);
                players.at(i)->Advance(timestep);
            }

        }
    }
    float pos=players.at(0)->getpos()[0];
    if(pos+players.at(0)->rx>1158)
    {
        auto v = players.at(0)->getvel();
        players.at(0)->setvel(-v[0],v[1]);
        players.at(0)->Advance(timestep);
    }
    else if(pos-players.at(0)->rx<0)
    {
        auto v = players.at(0)->getvel();
        players.at(0)->setvel(-v[0],v[1]);
        players.at(0)->Advance(timestep);
    }
}

void MainWindow::set_life()
{
        ui->progressBar->setValue(players.at(0)->life);
        if (players.at(0)->life<=0)
        {
            delete_all();
            started=false;
        }
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
            Abees.at(i)->Advance(t,players.at(0)->getpos());
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
        for(int i =0;i!=players.size();i++)
        {
            players.at(i)->Advance(t);
        }
        collitions();
        set_life();
    }
}


