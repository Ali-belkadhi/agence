#include "gestion_employe.h"
#include "ui_gestion_employe.h"
#include "employe.h"
#include <QDebug>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QSqlQuery>
#include <QDesktopServices>
#include <QUrl>
#include <QPieSlice>
#include <QChartView>
#include <QChart>

#include <QPdfWriter>
#include <QPainter>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QVBoxLayout>
#include <QSqlRecord>
#include "stati.h"

gestion_employe::gestion_employe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestion_employe)
{
    ui->setupUi(this);
    this->setWindowTitle("gestion de la employe");
}

gestion_employe::~gestion_employe()
{
    delete ui;

}



void gestion_employe::on_pushButton_5_clicked()
{
    QString nom = ui->lineEdit->text();
    QString prenom = ui->lineEdit_2->text();
    QString fonction = ui->lineEdit_3->text();
    QString departement = ui->lineEdit_4->text();
    QString cin = ui->lineEdit_5->text();
    QString tel = ui->lineEdit_6->text();
    QDate date = ui->dateEdit->date();

    // Input validation for CIN
    bool cinOk;
    int cinInt = cin.toInt(&cinOk);
    if (!cinOk || cinInt <= 0) {
        qDebug() << "CIN must be a valid positive number!";
        QMessageBox::warning(this, "Input Error", "CIN must be a valid positive number.");
        return;
    }

    // Create an instance of the employe object
    employe e;
    e.setnom(nom);
    e.setprenom(prenom);
    e.setfonction(fonction);
    e.setdepartement(departement);
    e.setcin(cinInt);  // Use the validated integer value
    e.settel(tel.toInt());  // Assuming tel is also an integer
    e.setdate(date);

    // Try to add the employee
    if (e.ajouter()) {
        QMessageBox::information(this, "Success", "Employe added successfully!");

        // Clear the QLineEdit and QDateEdit fields
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->dateEdit->setDate(QDate::currentDate());
    } else {
        QMessageBox::warning(this, "Failure", "Failed!!!!!!!!!!!!!!!!!.");
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->dateEdit->setDate(QDate::currentDate());
    }
}

void gestion_employe::on_pushButton_3_clicked()
{
    employe e;
   ui->tableView->setModel(e.afficher());
}

void gestion_employe::on_pushButton_2_clicked()
{
    int idDel = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0)).toInt();
          employe e;
            bool test = e.supprimer(idDel);
            if (test)
            {
                QMessageBox::information(this, "Suppression réussie", "Le employe a été supprimé avec succès.");
 ui->tableView->setModel(e.afficher());
            }
            else
            {
                QMessageBox::critical(this, "Erreur de suppression", "Une erreur est survenue lors de la suppression du employé.");
            }
}

void gestion_employe::on_pushButton_4_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Sélection invalide", "Veuillez sélectionner un employé dans la table.");
        return;
    }

    int row = index.row();

    // Retrieve the 'id_employe' from the selected row (assuming it's in the first column, index 0)
    int id_employe = ui->tableView->model()->index(row, 0).data().toInt(); // Adjust index as needed

    // Get the updated attribute values from the input fields
    QString nom = ui->lineEdit->text();
    QString prenom = ui->lineEdit_2->text();
    QString fonction = ui->lineEdit_3->text();
    QString departement = ui->lineEdit_4->text();
    int cin = ui->lineEdit_5->text().toInt();
    int tel = ui->lineEdit_6->text().toInt();
    QDate date = ui->dateEdit->date();

    // Create an employee object with the selected 'id_employe' and updated values
    employe e(id_employe, nom, prenom, fonction, departement, cin, tel, date);

    // Call the modify function to update the employee record
    bool test = e.modifier();


    if (test) {
        QMessageBox::information(this, "Modification réussie", "Les informations de l'employé ont été modifiées avec succès.");
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->dateEdit->setDate(QDate::currentDate());
        // Refresh the table view to display updated data
        ui->tableView->setModel(e.afficher());
    } else {
        QMessageBox::critical(this, "Erreur de modification", "Une erreur est survenue lors de la modification de l'employé.");
    }
}


void gestion_employe::on_pushButton_9_clicked()
{
    employe e;
    QString searchValue = ui->lineEdit_8->text().trimmed();
      ui->tableView->setModel(e.recherche(searchValue));
}

void gestion_employe::on_pushButton_10_clicked()
{
    employe e;

     ui->tableView->setModel(e.tricin());
}

void gestion_employe::on_pushButton_8_clicked()
{
    employe e;

     ui->tableView->setModel(e.trinom());
}

void gestion_employe::on_pushButton_11_clicked()
{
      employe e;
    ui->tableView->setModel(e.trifonction());
}


void gestion_employe::on_pushButton_clicked()
{
    this->close(); // Ferme la fenêtre actuelle
    QWidget *parentWidget = qobject_cast<QWidget *>(this->parent()); // Récupère le widget parent

    if (parentWidget != nullptr) {
        parentWidget->show(); // Affiche la fenêtre principale existante
    }
}

void gestion_employe::on_pushButton_7_clicked()
{
    QPdfWriter pdf("employés.pdf");
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setPageMargins(QMarginsF(30, 30, 30, 30));

    QPainter painter(&pdf);
    int i = 4000; // Position verticale initiale

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(2000, 2000, "Liste Des employés");

    // Ajout de la date et de l'heure actuelles en haut à droite
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString dateTimeString = currentDateTime.toString("dd/MM/yyyy hh:mm:ss");
    painter.setFont(QFont("Arial", 10));
    painter.drawText(7000, 800, dateTimeString);  // Ajuster la position si nécessaire

    // Dessin de la boîte principale pour le titre
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 50));
    painter.drawRect(1000, 400, 7300, 2600);

    // Dessin de la boîte des en-têtes
    painter.drawRect(0, 3000, 9600, 500);
    painter.setFont(QFont("Arial", 9));

    // Positionnement des en-têtes
    painter.drawText(200, 3300, "id_employe");
    painter.drawText(1500, 3300, "nom");
    painter.drawText(2500, 3300, "prenom");
    painter.drawText(3500, 3300, "fonction");
    painter.drawText(4500, 3300, "departement");
    painter.drawText(5500, 3300, "cin");
    painter.drawText(6500, 3300, "tel");
    painter.drawText(7500, 3300, "date");

    QSqlQuery query;
    query.prepare("SELECT ID_EMPLOYE, NOM, PRENOM, FONCTION, DEPARTEMENT, CIN, TEL, DATE_EMPLOYE FROM EMPLOYE");
    query.exec();

    while (query.next())
    {
        // Dessin de la ligne de tableau pour chaque employé
        painter.drawRect(0, i - 300, 9600, 500); // Dessiner la ligne du tableau

        // Affichage des données dans les colonnes respectives
        painter.drawText(200, i, query.value("id_employe").toString());
        painter.drawText(1500, i, query.value("nom").toString());
        painter.drawText(2500, i, query.value("prenom").toString());
        painter.drawText(3500, i, query.value("fonction").toString());
        painter.drawText(4500, i, query.value("departement").toString());
        painter.drawText(5500, i, query.value("cin").toString());
        painter.drawText(6500, i, query.value("tel").toString());
        painter.drawText(7500, i, query.value("date_employe").toString());

        // Dessiner les lignes de séparation pour le tableau
        painter.drawLine(0, i + 200, 9600, i + 200); // Ligne horizontale inférieure
        painter.drawLine(1200, i - 500, 1200, i + 200); // Séparation entre id_employe et nom
        painter.drawLine(2200, i - 500, 2200, i + 200); // Séparation entre nom et prenom
        painter.drawLine(3200, i - 500, 3200, i + 200); // Séparation entre prenom et fonction
        painter.drawLine(4200, i - 500, 4200, i + 200); // Séparation entre fonction et departement
        painter.drawLine(5200, i - 500, 5200, i + 200); // Séparation entre departement et cin
        painter.drawLine(6200, i - 500, 6200, i + 200); // Séparation entre cin et tel
        painter.drawLine(7200, i - 500, 7200, i + 200); // Séparation entre tel et date

        i = i + 500; // Incrémentation de la position verticale pour passer à la ligne suivante
    }

    int reponse = QMessageBox::question(this, "Générer PDF", "PDF enregistré. Voulez-vous l'afficher ?", QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("employés.pdf"));
    }

    painter.end();
}







void gestion_employe::on_pushButton_6_clicked()
{
    stati stg;
    stg.exec();
}
