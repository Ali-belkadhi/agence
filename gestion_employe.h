#ifndef GESTION_EMPLOYE_H
#define GESTION_EMPLOYE_H

#include <QDialog>
#include <QSqlQueryModel>
namespace Ui {
class gestion_employe;
}

class gestion_employe : public QDialog
{
    Q_OBJECT

public:
    explicit gestion_employe(QWidget *parent = nullptr);
    QSqlQueryModel* statistiquesFonction();
    ~gestion_employe();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::gestion_employe *ui;
};

#endif // GESTION_EMPLOYE_H
