#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <bitset>
#include "numero.h"
#include "alu.h"

#include <QMainWindow>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    string getBinary32(float value);


private slots:
    void on_btn_ejecutar_clicked();

private:
    Ui::MainWindow *ui;
    float num1;
    float num2;

    string operacion;
    numero *numero1;
    numero *numero2;



};

#endif // MAINWINDOW_H
