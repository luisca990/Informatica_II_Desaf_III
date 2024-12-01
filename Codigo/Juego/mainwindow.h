#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qgraphicsitem.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QPixmap imgFondo;
    MainWindow(QWidget *parent = nullptr);
    void mostrarGameOver();
    void mostrarVictoria();
    ~MainWindow();


public slots:
    void nuevaEscena();
    void spawnObject();

private:
    Ui::MainWindow *ui;
    int alto;
    int ancho;
    QList<QGraphicsRectItem*> itemsBorrar;
    QTimer* spawnTimer;

private:
    void setupTelefono(); // Declaración de setupJuego

};

#endif // MAINWINDOW_H
