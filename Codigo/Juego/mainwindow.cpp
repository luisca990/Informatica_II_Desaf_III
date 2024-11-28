#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Bart.h"
#include "marge.h"
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
    imgFondo.load(":/Fondo2.jpg");
    QBrush fondoImagen(imgFondo);
    ui->graphicsView->setBackgroundBrush(fondoImagen);
    Bart *jug1 = new Bart(ui->graphicsView);
    escena -> addItem(jug1);
    jug1->setPos(2,476);
    /*QGraphicsRectItem *rect1 = new QGraphicsRectItem(0, 0, 50, 50);
    rect1->setBrush(Qt::blue);
    escena->addItem(rect1);

    QGraphicsRectItem *rect2 = new QGraphicsRectItem(ancho - 50, 0, 50, 50);
    rect2->setBrush(Qt::red);
    escena->addItem(rect2);*/

    // Inicializa el temporizador para generar objetos
    spawnTimer = new QTimer(this);
    connect(spawnTimer, &QTimer::timeout, this, &MainWindow::spawnObject);
    spawnTimer->start(1000); // Genera un objeto cada segundo


    connect(jug1, &Bart::llegarBorde, this, &MainWindow::nuevaEscena);

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

void MainWindow::spawnObject() {
    // Crea un nuevo objeto en movimiento
                  // Hace visible el objeto

    auto* marge = new Marge(this);

    // Generar posición inicial (x = 802, y entre 335 y 526)
    int yPos = QRandomGenerator::global()->bounded(325, 526);
    int xPos = 802;
    marge->setPos(xPos, yPos); // Posición inicial

    // Agregar Marge a la escena
    ui->graphicsView->scene()->addItem(marge);

}

MainWindow::~MainWindow()
{
    delete ui;
}
