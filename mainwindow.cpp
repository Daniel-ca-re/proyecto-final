
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bee.h"
#include "angry_bee.h"
#include "frog.h"
#include "tadpole.h"
#include "qiterator.h"
#include "iterator"
#include "iostream"
#include <cstdlib>
#include "math.h"



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
    timer->start(1000/60);
    scores= txtinfo("../proyecto_final/BD/Scores.txt");
    Bees_spawn=10;
    Abees_spawn=13;
    puntajefrontera=150;

    losesound= new QMediaPlayer();
    losesound->setMedia(QUrl("qrc:/sounds/GAME OVER.mp3"));

    theme= new QMediaPlayer();
    theme->setMedia(QUrl("qrc:/sounds/song.mp3"));

    jump= new QMediaPlayer();
    jump->setMedia(QUrl("qrc:/sounds/jump.mp3"));

    Throw= new QMediaPlayer();
    Throw->setMedia(QUrl("qrc:/sounds/lanzamiento.mp3"));

    hit= new QMediaPlayer();
    hit->setMedia(QUrl("qrc:/sounds/hit.mp3"));

    gethit= new QMediaPlayer();
    gethit->setMedia(QUrl("qrc:/sounds/GETHIT.mp3"));




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
    past=0;
    puntaje=0;
    scene->setBackgroundBrush(QPixmap(":/images/background.png"));


}
void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    if(evento->key()==Qt::Key_W)
    {

        if(can_he_move())
        {
            jump->play();
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
    if(evento->key()==Qt::Key_I)
    {
        bala_generator(0,15);
    }
    if(evento->key()==Qt::Key_K)
    {
        bala_generator(0,-15);
    }
    if(evento->key()==Qt::Key_L)
    {
        bala_generator(15,0);
    }
    if(evento->key()==Qt::Key_J)
    {
        bala_generator(-15,0);
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
    for(int i =0;i!=frogs.size();i++)
    {
        if(frogs.at(i)->lengua2->fake_layer->collidesWithItem(players.at(0)))
        {
             return true;
        }
    }
    return false;
}

void MainWindow::Bhit()
{
    for(int i=0;i<balas.size();i++)
    {
        if(balas.at(i)->getpos()[1]>900 || balas.at(i)->getpos()[0]>1200  || balas.at(i)->getpos()[0]<-100 )
        {
            scene->removeItem(balas.at(i));
            balas.removeAt(i);
            i--;
        }
    }
    for(int i=0;i<balas.size();i++)
    {
        for(int ii=0; ii<bees.size();ii++)
        {
            if(balas.at(i)->collidesWithItem(bees.at(ii)))
            {
                hit->stop();
                hit->play();
                scene->removeItem(balas.at(i));
                scene->removeItem(bees.at(ii));
                bees.removeAt(ii);
                balas.removeAt(i);
                i--;
                ii--;
                puntaje+=10;
            }
        }

    }
    for(int i=0;i<balas.size();i++)
    {
        for(int ii=0; ii<Abees.size();ii++)
        {
            if(balas.at(i)->collidesWithItem(Abees.at(ii)))
            {
                hit->stop();
                hit->play();
                scene->removeItem(balas.at(i));
                scene->removeItem(Abees.at(ii));
                Abees.removeAt(ii);
                balas.removeAt(i);
                i--;
                ii--;
                puntaje+=10;
            }
        }

    }
    for(int i=0;i<balas.size();i++)
    {
        for(int ii=0; ii<frogs.size();ii++)
        {
            if(balas.at(i)->collidesWithItem(frogs.at(ii)))
            {
                hit->stop();
                hit->play();
                scene->removeItem(balas.at(i));
                frogs.at(ii)->life--;
                balas.removeAt(i);
                i--;
            }
        }

    }
    for(int i=0;i<balas.size();i++)
    {
        for(int ii=0; ii<frogs.size();ii++)
        {
            if(balas.at(i)->collidesWithItem(frogs.at(ii)->lengua))
            {
                hit->stop();
                hit->play();
                scene->removeItem(balas.at(i));
                balas.removeAt(i);
                i--;
            }
        }

    }
    for(int i=0;i<balas.size();i++)
    {
        for(int ii=0; ii<platforms.size();ii++)
        {
            if(balas.at(i)->collidesWithItem(platforms.at(ii)))
            {
                hit->stop();
                hit->play();
                scene->removeItem(balas.at(i));
                balas.removeAt(i);
                i--;
            }
        }

    }
    for(int i=0;i<balas.size();i++)
    {
        for(int ii=0; ii<floor.size();ii++)
        {
            if(balas.at(i)->collidesWithItem(floor.at(ii)))
            {
                hit->stop();
                hit->play();
                scene->removeItem(balas.at(i));
                balas.removeAt(i);
                i--;
            }
        }

    }

}

void MainWindow::tadpole_generator()
{
    for(int i=0;i<tadpoles.size();i++)
    {
        if(tadpoles.at(i)->getpos()[0] < -100 || tadpoles.at(i)->getpos()[0]>1200)
        {
            scene->removeItem(tadpoles.at(i));
            tadpoles.removeAt(i);
            i--;
        }
    }
    int v[2]={28,40};

    int angle[2]={84,127};
    float pos [2]={-1,-1};
    float randvel=((rand()% (10*(v[1]-v[0])) )/10) +v[0];
    float randang=((rand()% (10*(angle[1]-angle[0])) )/10) + angle[0];
    while (!(0<pos[0] && pos[0]<1150 && 350<pos[1] && pos[1]<630))
    {
        randvel=((rand()% (10*(v[1]-v[0])) )/10) +v[0];
        randang=((rand()% (10*(angle[1]-angle[0])) )/10) + angle[0];
        pos[0]=randvel*(randvel/0.8)*cos(3.1416*randang/180) + 1000;
        pos[1]=randvel*(randvel/0.8)*sin(3.1416*randang/180) - 100 -0.4*pow(randvel/0.8,2);
    }
    tadpoles.push_back(new tadpole(10,-0.8,{1000,-100},{ randvel*float(cos(3.1416*randang/180)) , randvel*float(sin(3.1416*randang/180)) }) );
    scene->addItem(tadpoles.back());
}

void MainWindow::frog_genetarot()
{
    if(frogs.size()==0)
    {
        frogs.push_back(new frog(80,{1151-50,65},-150));
        scene->addItem(frogs.back()->lengua);
        scene->addItem(frogs.back()->lengua2);
        scene->addItem(frogs.back());
    }
}

void MainWindow::bee_genetarot()
{
    bees.push_back(new bee(40,20,{1180,float(rand()%300+100)},-5));
    scene->addItem(bees.back());
}

void MainWindow::Abee_genetarot()
{
    Abees.push_back(new angry_bee(20,{1180,float(rand()%450+100)},5));
    scene->addItem(Abees.back());
}

void MainWindow::platform_generator()
{
    if(platforms.at(0)->getpos()[0]+platforms.at(0)->L < -100)
    {
        scene->removeItem(platforms.at(0));
        platforms.removeAt(0);
    }
    if((rand()%2==0))
    {
        platforms.push_back(new platform(rand()%160+100,10,{1200,float(rand()%280+120)},{-1,0},'g'));
        scene->addItem(platforms.back());
    }
}

void MainWindow::floor_generator()
{
    if(floor.at(0)->getpos()[0]+floor.at(0)->L < -100)
    {
        scene->removeItem(floor.at(0));
        floor.removeAt(0);
    }
    if((floor.back()->getpos()[0]+floor.back()->L) < 1400)
    {
        if (floor.back()->type=='w')
        {
                floor.push_back(new platform(rand()%400+300,15,{floor.back()->getpos()[0]+floor.back()->L,8},{-1,0},'g'));
        }
        else
        {
            if((rand()%3)%2==0)
            {
                floor.push_back(new platform(rand()%400+300,15,{floor.back()->getpos()[0]+floor.back()->L,8},{-1,0},'g'));
            }
            else
            {
                floor.push_back(new platform(rand()%100+300,15,{floor.back()->getpos()[0]+floor.back()->L,8},{-1,0},'w'));
            }
        }
        scene->addItem(floor.back());
    }
}

void MainWindow::collitions()
{
        for(int i =0;i!=floor.size();i++)
        {
            if (floor.at(i)->collidesWithItem(players.at(0)))
            {
                if(floor.at(i)->type=='g' )
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
                    else if(floor.at(i)->collidesWithItem(players.at(0)) && (state=='a'||state=='d') && (players.at(0)->getpos()[1] < floor.at(i)->getpos()[1] + players.at(0)->ry*0.5 ))
                    {
                        auto v = players.at(0)->getvel();
                        players.at(0)->setvel(-v[0],v[1]);
                        players.at(0)->Advance(timestep);
                        break;
                    }
                }
                else
                {
                    players.at(0)->life=0;
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
                     break;
                }
                else if(platforms.at(i)->collidesWithItem(players.at(0)) && state=='s')
                {
                    auto p = players.at(0)->getpos();
                    auto v = players.at(0)->getvel();
                    players.at(0)->setvel(v[0],0);
                    players.at(0)->setpos(p[0],platforms.at(i)->getpos()[1]-players.at(0)->ry-platforms.at(i)->H);
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
        for(int i =0;i!=frogs.size();i++)
        {
            if (frogs.at(i)->lengua2->collidesWithItem(players.at(0)))
            {
                char state=frogs.at(i)->lengua2->where_is_it(players.at(0)->getpos());
                if(frogs.at(i)->lengua2->fake_layer->collidesWithItem(players.at(0)) && frogs.at(i)->lengua2->collidesWithItem(players.at(0)) && state=='w')
                {
                     auto p = players.at(0)->getpos();
                     auto v = players.at(0)->getvel();
                     players.at(0)->setvel(v[0],0);
                     players.at(0)->setpos(p[0],frogs.at(i)->lengua2->getpos()[1]+players.at(0)->ry);
                     break;
                }
                else if(frogs.at(i)->lengua2->collidesWithItem(players.at(0)) && state=='s')
                {
                    auto p = players.at(0)->getpos();
                    auto v = players.at(0)->getvel();
                    players.at(0)->setvel(v[0],0);
                    players.at(0)->setpos(p[0],frogs.at(i)->lengua2->getpos()[1]-players.at(0)->ry-frogs.at(i)->lengua2->H);
                    break;
                }
                else if(frogs.at(i)->lengua2->collidesWithItem(players.at(0)) && (state=='a'||state=='d') && (players.at(0)->getpos()[1] < frogs.at(i)->lengua2->getpos()[1] + players.at(0)->ry*0.5 ))
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
        scene->removeItem(frogs.at(0)->lengua2);
        frogs.removeAt(0);
    }
    while(tadpoles.size()!=0)
    {
        scene->removeItem(tadpoles.at(0));
        tadpoles.removeAt(0);
    }
    while(players.size()!=0)
    {
        scene->removeItem(players.at(0));
        players.removeAt(0);
    }
    ui->lcdNumber_2->display(scores.info[0]);
    ui->lcdNumber_3->display(scores.info[1]);
    ui->lcdNumber_4->display(scores.info[2]);

    std::cout<<"eliminad\n";
}

void MainWindow::start()
{
    players.push_back(new maty(30,60,{40,70},-0.8));
    scene->addItem(players.back());
    bees.push_back(new bee(40,20,{1180,500},-5));
    scene->addItem(bees.back());
    Abees.push_back(new angry_bee(20,{1180,100},5));
    scene->addItem(Abees.back());
    floor.push_back(new platform(1400,15,{0,8},{-1,0},'g'));
    scene->addItem(floor.back());
    platforms.push_back(new platform(230,10,{1200,150},{-1,0},'g'));
    scene->addItem(platforms.back());
    theme->play();
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
    for(int i=0; i!=tadpoles.size();i++)
    {
        for(int ii=0; ii!=floor.size();ii++)
        {
            if(floor.at(ii)->collidesWithItem(tadpoles.at(i)) && floor.at(ii)->type=='g')
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
            gethit->stop();
            gethit->play();
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
            gethit->stop();
            gethit->play();
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
            gethit->stop();
            gethit->play();
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
            gethit->stop();
            gethit->play();
            auto vel=players.at(0)->getvel();
            players.at(0)->life-=5;
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
            started=false;
            theme->stop();
            losesound->play();
            scores.addnew(puntaje);
            scores.saveinfo();
            delete_all();

            ui->progressBar->setValue(0);
            scene->setBackgroundBrush(QPixmap(":/images/game over.png"));

        }
        for(int i =0; i<frogs.size();i++)
        {
            if(frogs.at(i)->life==0)
            {
                scene->removeItem(frogs.at(i)->lengua);
                scene->removeItem(frogs.at(i)->lengua2);
                scene->removeItem(frogs.at(i));
                frogs.removeAt(i);
                i--;
                puntaje+=120;
            }
        }
        if(puntaje>puntajefrontera && Bees_spawn>5)
        {
            puntajefrontera+=150;
            Abees_spawn--;
            Bees_spawn--;
        }
        ui->lcdNumber->display(puntaje);
        scores.addnew(puntaje);
        ui->lcdNumber_2->display(scores.info[0]);
        ui->lcdNumber_3->display(scores.info[1]);
        ui->lcdNumber_4->display(scores.info[2]);
}

void MainWindow::ADVANCE()
{
    if (started)
    {
        started=false;
        float t =2*timestep;

        for(int i =0;i!=players.size();i++)
        {
            players.at(i)->Advance(t);
        }


        Bhit();

        past=(++past)%61;
        if(past==0)
        {
            second();
        }
        collitions();


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
            scene->removeItem(frogs.at(i)->lengua2);
            frogs.at(i)->Advance(t);
            scene->addItem(frogs.at(i)->lengua2);
            scene->removeItem(frogs.at(i)->lengua);
            scene->addItem(frogs.at(i)->lengua);
            scene->removeItem(frogs.at(i));
            scene->addItem(frogs.at(i));
        }
        for(int i =0;i!=tadpoles.size();i++)
        {
            tadpoles.at(i)->Advance(t*0.9);
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
        started=true;
        scene->setBackgroundBrush(QPixmap(":/images/background.png"));
        set_life();




    }
}

void MainWindow::second()
{


        time_passed=(++time_passed)%221;
        if(time_passed%1==0)
        {
            floor_generator();
        }
        if(time_passed%1==0)
        {
            tadpole_generator();
        }
        if(time_passed%10==0)
        {
            platform_generator();
        }
        if((3+time_passed)%Abees_spawn==0)
        {
            Abee_genetarot();
        }
        if((2+time_passed)%Bees_spawn==0)
        {
            bee_genetarot();
        }
        if((7+time_passed)%40==0)
        {
            frog_genetarot();
        }
        if((time_passed)%220==0)
        {
            theme->play();
        }
}

void MainWindow::bala_generator(float vx, float vy)
{
    Throw->stop();
    Throw->play();
    balas.push_back(new bala(10, players.at(0)->getpos() , {vx,vy}));
    scene->addItem(balas.back());
}



