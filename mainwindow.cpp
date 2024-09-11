#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gestion_formation.h"
#include "gestion_employe.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("menu");
}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_gestion_commande_clicked()
{
    gestion_employe *gestion_employeWindow = new gestion_employe(this);
        gestion_employeWindow->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    gestion_formation *gestion_formationWindow = new gestion_formation(this);
        gestion_formationWindow->show();
}
