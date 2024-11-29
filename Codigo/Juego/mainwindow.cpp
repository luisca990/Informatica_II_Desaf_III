#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Bart.h"
#include "marge.h"
#include "telefono.h"
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
    Bart *bart = new Bart(ui->graphicsView);
    escena -> addItem(bart);
    bart->setPos(2,476);
    /*QGraphicsRectItem *rect1 = new QGraphicsRectItem(0, 0, 50, 50);
    rect1->setBrush(Qt::blue);
    escena->addItem(rect1);

    QGraphicsRectItem *rect2 = new QGraphicsRectItem(ancho - 50, 0, 50, 50);
    rect2->setBrush(Qt::red);
    escena->addItem(rect2);*/

    // Inicializa el temporizador para generar objetos
    // Posición inicial del teléfono

    spawnTimer = new QTimer(this);
    connect(spawnTimer, &QTimer::timeout, this, &MainWindow::spawnObject);
    spawnTimer->start(1000); // Genera un objeto cada segundo


    connect(bart, &Bart::llegarBorde, this, &MainWindow::nuevaEscena);
    connect(bart, &Bart::gameOver, this, &MainWindow::mostrarGameOver);

    setupTelefono();
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


void MainWindow::setupTelefono() {
    // Posición inicial del teléfono
    QPointF posicionTelefono(800, 450); // Cambia la posición según tu escena
    Telefono* telefono = new Telefono(posicionTelefono);
    ui->graphicsView->scene()->addItem(telefono);
}

void MainWindow::mostrarGameOver() {
    // Cambiar a una nueva escena de Game Over
    QGraphicsScene* gameOverScene = new QGraphicsScene(this);
    gameOverScene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
    QGraphicsTextItem* texto = new QGraphicsTextItem("¡Game Over!");
    texto->setDefaultTextColor(Qt::red);
    texto->setFont(QFont("Arial", 30));
    texto->setPos(ui->graphicsView->width() / 2 - 100, ui->graphicsView->height() / 2 - 50);
    gameOverScene->addItem(texto);
    ui->graphicsView->setScene(gameOverScene);
}

MainWindow::~MainWindow()
{
    delete ui;
}
