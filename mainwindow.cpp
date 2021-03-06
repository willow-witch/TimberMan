#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QPainter>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(650, 950);     // фиксируем окно, чтобы было проще с координатами
    timerPaint=new QTimer;
    connect(timerPaint,SIGNAL(timeout()),this,SLOT(Update()));
    timerPaint->setInterval(20);
    timerPaint->start();
    timberman = new Timberman(980);
    tree=new Tree(650,980);
    repaint();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!tree->getRybTree())
    {
        switch(event->key()){
            case (Qt::Key_Left):{
                LeftORRight=true;
                ProvGameOver();
                tree->deleteTrunk(LeftORRight);
                ProvGameOver();
                break;
            }
            case (Qt::Key_Right):{
                LeftORRight=false;
                ProvGameOver();
                tree->deleteTrunk(LeftORRight);
                ProvGameOver();
                break;
            }
        }
        repaint();
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
     QPainter p(this);
     p.drawPixmap(QRect(0,0,650,950),QPixmap(":/fon/Images/fon.png"));
     tree->picture(&p);
     timberman->draw(&p);
}

void MainWindow::ProvGameOver()
{
    switch(tree->getTypeTree(0))
    {
        case 1:
        {
            if (LeftORRight)
            {
                qDebug("game over  %d",++gameOver);
                timberman->setIm(QPixmap(":Rip/Images/rip_lev.png"));
                timerPaint->stop();
            }
            break;
        }
        case 2:
        {
            if (!LeftORRight)
            {
                qDebug("game over  %d",++gameOver);
                timberman->setIm(QPixmap(":Rip/Images/rip_prav.png"));
                timerPaint->stop();
            }
            break;
        }
    }
}

void MainWindow::Update()
{
    if (tree->getRybTree())
    {
        if (LeftORRight)
        {
            switch(timberman->getSost())
            {
                //    перемещаемся влево
                case 0:
                {
                    timberman->setIm(QPixmap(":/images/drovosek1_lev.png"));
                    timberman->setX(timberman->getIm().width()-indentTree);
                    repaint();
                    break;
                }
                //    замахиваемся
                case 1:
                {
                    timberman->setIm(QPixmap(":/images/drovosek2_lev.png"));
                    repaint();
                    break;
                }
                //    рубим
                case 2:
                {
                    timberman->setIm(QPixmap(":/images/drovosek3_lev.png"));
                    repaint();
                    break;
                }
                //    исходное положение
                case 3:
                {
                    timberman->setIm(QPixmap(":/images/drovosek1_lev.png"));
                    repaint();
                    break;
                }
            }
        }
        else
        {
            switch(timberman->getSost())
            {
                //    перемещаемся вправо
                case 0:
                {
                    timberman->setIm(QPixmap(":/images/drovosek1_prav.png"));
                    timberman->setX(650 - 3*timberman->getIm().width()+indentTree);
                    repaint();
                    break;
                }
                 //    замахиваемся
                case 1:
                {
                    timberman->setIm(QPixmap(":/images/drovosek2_prav.png"));
                    repaint();
                    break;
                }
                //    рубим
                case 2:
                {
                    timberman->setIm(QPixmap(":/images/drovosek3_prav.png"));
                    repaint();
                    break;
                }
                //    исходное положение
                case 3:
                {
                    timberman->setIm(QPixmap(":/images/drovosek1_prav.png"));
                    repaint();
                    break;
                }
            }
        }
        timberman->UPsost();
    }
    tree->DownTree();
    repaint();
}

