#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Jugador.h"
#include <QDebug>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *escena = new QGraphicsScene(this);
    int ancho = ui->graphicsView->width();
    int alto = ui->graphicsView->height();
    qDebug() << "Dimensiones iniciales" <<alto << ancho;
    escena->setSceneRect(0,0,ancho,alto);
    ui->graphicsView->setScene(escena);
    Jugador *jug1 = new Jugador(ui->graphicsView);
    escena -> addItem(jug1);
    jug1->setPos(200,200);
    QGraphicsRectItem *rect1 = new QGraphicsRectItem(0, 0, 50, 50);
    rect1->setBrush(Qt::blue);
    escena->addItem(rect1);

    QGraphicsRectItem *rect2 = new QGraphicsRectItem(ancho - 50, 0, 50, 50);
    rect2->setBrush(Qt::red);
    escena->addItem(rect2);


    connect(jug1, &Jugador::llegarBorde, this, &MainWindow::nuevaEscena);

}

void MainWindow::nuevaEscena(){

    ancho = ui->graphicsView->width();
    alto = ui->graphicsView->height();


    for (QGraphicsItem *item : this->ui->graphicsView->scene()->items()) {
        if (QGraphicsRectItem *rect = dynamic_cast<QGraphicsRectItem*>(item)) {
            this->ui->graphicsView->scene()->removeItem(rect);
            //qDebug()<< "Dimensiones escena" << alto << ancho;
            //delete rect;
        }

    }

    for (int i = 0; i < 2; ++i) {
        int x = QRandomGenerator::global()->bounded(ancho - 50);
        int y = QRandomGenerator::global()->bounded(alto + 50);
        //qDebug() << "Las coordenadas del nuevo rect"<< x << y;
        QGraphicsRectItem *randomRect = new QGraphicsRectItem(x, y, 50, 50);
        randomRect->setBrush(Qt::green);
        this->ui->graphicsView->scene()->addItem(randomRect);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
