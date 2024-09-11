#ifndef STATI2_H
#define STATI2_H

#include <QDialog>
#include <QtCharts>
#include <formation.h>
namespace Ui {
class stati2;
}

class stati2 : public QDialog
{
    Q_OBJECT
protected:
   void paintEvent(QPaintEvent *);
public:
    explicit stati2(QWidget *parent = nullptr);
    ~stati2();


private slots:
   void on_pushButton_11_clicked();

private:
    Ui::stati2 *ui;
    QVector<QPointF> dataPoints;
    QtCharts::QChartView *chartView;
    QtCharts::QLineSeries *series;
   formation f;
};

#endif // STATI2_H
