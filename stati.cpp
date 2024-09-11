#include "stati.h"
#include "ui_stati.h"

stati::stati(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stati)
{
    ui->setupUi(this);
}
void stati::paintEvent(QPaintEvent *) {
    int A = e.statistique1();  // Count for first function (e.g., Manager)
    int B = e.statistique2();  // Count for second function (e.g., Engineer)

    float s1 = A * 100;
    float s2 = B * 100;
    float total = A + B;
    float q1 = s1 / total;
    float q2 = s2 / total;

    float angle1 = (q1 * 360) / 100;
    float angle2 = (q2 * 360) / 100;

    QChartView *chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);

    QPieSeries *series = new QPieSeries();
    series->append("Manager", angle1);   // Use the actual function name here
    series->append("Engineer", angle2);  // Use the actual function name here

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Employee Distribution by Function");

    chartView = new QChartView(chart, ui->label);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(850, 600);
    chartView->show();
}

stati::~stati()
{
    delete ui;
}

void stati::on_pushButton_11_clicked()
{
    close();
}
