#ifndef STATI_H
#define STATI_H

#include <QDialog>
#include <QtCharts>
#include "employe.h"
#include "ui_stati.h"

namespace Ui {
class stati;
}

class stati : public QDialog
{
    Q_OBJECT
protected:
   void paintEvent(QPaintEvent *);

public:
    explicit stati(QWidget *parent = nullptr);
    ~stati();

private slots:
   void on_pushButton_11_clicked();

private:
    Ui::stati *ui;
    QVector<QPointF> dataPoints;
    QtCharts::QChartView *chartView;
    QtCharts::QLineSeries *series;
    employe e;
};

#endif // STATI_H

