#ifndef GESTION_FORMATION_H
#define GESTION_FORMATION_H

#include <QDialog>

namespace Ui {
class gestion_formation;
}

class gestion_formation : public QDialog
{
    Q_OBJECT

public:
    explicit gestion_formation(QWidget *parent = nullptr);
    ~gestion_formation();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_13_clicked();

private:
    Ui::gestion_formation *ui;
};

#endif // GESTION_FORMATION_H
