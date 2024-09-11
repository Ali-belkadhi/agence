#include "mainwindow.h"
#include "login.h"


#include "connexion.h"
#include <QApplication>
#include <QMessageBox>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    login w;
    Connexion c;

    bool test = c.createConnection();
    if (test) {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                 QObject::tr("Connection successful.\n"
                                             "Click OK to continue."), QMessageBox::Ok);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

    return a.exec();
}


