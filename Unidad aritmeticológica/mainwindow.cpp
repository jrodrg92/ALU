#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_ejecutar_clicked()
{

    QString nuevo=ui->txt_num1->text();
    num1=nuevo.toFloat();

    string num_fin1=getBinary32(num1);
    numero1=new numero(num_fin1);
    ui->num1->setEnabled(true);
    ui->num1->setText(QString::fromStdString(num_fin1));

    QString nuevo1=ui->txt_num2->text();
    num2=nuevo1.toFloat();
    string num_fin2=getBinary32(num2);
    numero2=new numero(num_fin2);
    ui->num2->setEnabled(true);
    ui->num2->setText(QString::fromStdString(num_fin2));

    if(ui->rbt_suma->isChecked()==true){
        operacion="Suma";
    }
    else if(ui->rbr_multiplicacion->isChecked()==true){
        operacion="Multiplicacion";
    }
    else if(ui->rbt_division->isChecked()==true){
        operacion="Division";
    }

    alu *nueva=new alu(numero1, numero2, operacion);
    nueva->operar();

}

string MainWindow::getBinary32( float value )
{
    union
    {
         float input;   // assumes sizeof(float) == sizeof(int)
         int   output;
    }    data;

    data.input = value;

    std::bitset<sizeof(33) * CHAR_BIT>   bits(data.output);

    std::string mystring = bits.to_string<char, std::char_traits<char>, std::allocator<char> >();

    return mystring;
}
