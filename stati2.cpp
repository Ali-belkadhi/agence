#include "stati2.h"
#include "ui_stati2.h"

stati2::stati2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stati2)
{
    ui->setupUi(this);
}
void stati2::paintEvent(QPaintEvent *) {
    int A = f.statistique1();  // Formations with 2 days or less
    int B = f.statistique2();  // Formations with more than 2 days

    float total = A + B;
    if (total == 0) return; // Prevent division by zero

    float q1 = (A * 100) / total;
    float q2 = (B * 100) / total;

    QPieSeries *series = new QPieSeries();
    series->append("2 days or less", q1);
    series->append("More than 2 days", q2);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Distribution of Formations by Duration");

    QChartView *chartView = new QChartView(chart, ui->label);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(850, 600);
    chartView->show();
}

stati2::~stati2()
{
    delete ui;
}

void stati2::on_pushButton_11_clicked()
{
    close();
}
