#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "mainwindow.h"
#include <QSqlQuery>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
     this->setWindowTitle("connecter");
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    QString UserName = ui->lineEdit->text();
    QString Password = ui->lineEdit_2->text();

    if (UserName == "admin" && Password == "admin")
    {
        // Afficher un message de succès
        QMessageBox::information(this, "agence", "Login Success.");

        // Créer et afficher la fenêtre principale
        MainWindow *mainwindowW = new MainWindow();
        mainwindowW->show();

        // Fermer la fenêtre de login
        this->close();
    }

   else
    {
       QString userName = ui->lineEdit->text();
       QString password = ui->lineEdit_2->text();
       QSqlQuery query;
       query.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE NOM = :nom AND CIN = :cin");
       query.bindValue(":nom", userName);

       query.bindValue(":cin", password);
       if (query.exec())
       {
           query.next();
           int count = query.value(0).toInt();

           if (count == 1)  // If a match is found
           {
               QMessageBox::information(this, "agence", "Login Success.");

               // Create and show the main window
               MainWindow *mainwindowW = new MainWindow();
               mainwindowW->show();

               // Close the login window
               this->close();
           }
           else
           {
               QMessageBox::warning(this, "utilisateur", "Please enter valid username, password");
           }
       }

    }

}

void login::on_pushButton_2_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"AGENCE", "Êtes-vous sûr de fermer l'application?",QMessageBox::Yes |QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {QApplication::quit();
    }
}
