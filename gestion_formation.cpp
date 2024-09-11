#include "gestion_formation.h"
#include "ui_gestion_formation.h"
#include "formation.h"
#include <QDebug>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QSqlQuery>
#include <QDesktopServices>
#include <QUrl>
#include "stati2.h"
#include "calculator.h"
gestion_formation::gestion_formation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestion_formation)
{
    ui->setupUi(this);
     this->setWindowTitle("gestion de la formation");
}

gestion_formation::~gestion_formation()
{
    delete ui;

}

void gestion_formation::on_pushButton_clicked()
{
    this->close(); // Ferme la fenêtre actuelle
    QWidget *parentWidget = qobject_cast<QWidget *>(this->parent()); // Récupère le widget parent

    if (parentWidget != nullptr) {
        parentWidget->show(); // Affiche la fenêtre principale existante
    }
}

void gestion_formation::on_pushButton_5_clicked()
{
    QString titre = ui->lineEdit->text();
    QDate date_debut = ui->dateEdit->date().QDate::currentDate();
    QString duree = ui->lineEdit_3->text();
    QString lieu = ui->lineEdit_4->text();
    QString competence = ui->lineEdit_5->text();

    // Input validation for titre
    if (titre.isEmpty()) {
        qDebug() << "Titre must not be empty!";
        QMessageBox::warning(this, "Input Error", "Titre must not be empty.");
        return;
    }

    // Create an instance of the formation object
    formation f;
    f.settitre(titre);
    f.setdate_debut(date_debut);
    f.setduree(duree);
    f.setlieu(lieu);
    f.setcompetence(competence);

    // Try to add the formation
    if (f.ajouter()) {
        QMessageBox::information(this, "Success", "Formation added successfully!");

        // Clear the QLineEdit and QDateEdit fields
        ui->lineEdit->clear();
        ui->dateEdit->setDate(QDate::currentDate());  // Reset to current date
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
    } else {
        QMessageBox::warning(this, "Failure", "Failed to add the formation.");
        ui->lineEdit->clear();
        ui->dateEdit->setDate(QDate::currentDate());  // Reset to current date
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
    }
}

void gestion_formation::on_pushButton_3_clicked()
{
    formation f;
   ui->tableView->setModel(f.afficher());
}

void gestion_formation::on_pushButton_2_clicked()
{
    int idDel = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0)).toInt();
          formation f;
            bool test = f.supprimer(idDel);
            if (test)
            {
                QMessageBox::information(this, "Suppression réussie", "La formation a été supprimé avec succès.");
 ui->tableView->setModel(f.afficher());
            }
            else
            {
                QMessageBox::critical(this, "Erreur de suppression", "Une erreur est survenue lors de la suppression du formation.");
            }
}

void gestion_formation::on_pushButton_9_clicked()
{
    formation f;
    QString searchValue = ui->lineEdit_8->text().trimmed();
      ui->tableView->setModel(f.recherche(searchValue));
}

void gestion_formation::on_pushButton_4_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Sélection invalide", "Veuillez sélectionner une formation dans la table.");
        return;
    }

    int row = index.row();

    // Retrieve the 'id_formation' from the selected row (assuming it's in the first column, index 0)
    int id_formation = ui->tableView->model()->index(row, 0).data().toInt();

    // Get the updated attribute values from the input fields
    QString titre = ui->lineEdit->text();
    QDate date_debut = ui->dateEdit->date();
    QString duree = ui->lineEdit_3->text();
    QString lieu = ui->lineEdit_4->text();
    QString competence = ui->lineEdit_5->text();

    // Create a formation object with the selected 'id_formation' and updated values
    formation f(id_formation, titre, date_debut, duree, lieu, competence);

    // Call the modify function to update the formation record
    bool test = f.modifier();

    if (test) {
        QMessageBox::information(this, "Modification réussie", "Les informations de la formation ont été modifiées avec succès.");
        ui->lineEdit->clear();
        ui->dateEdit->setDate(QDate::currentDate());
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();

        // Refresh the table view to display updated data
        ui->tableView->setModel(f.afficher());
    } else {
        QMessageBox::critical(this, "Erreur de modification", "Une erreur est survenue lors de la modification de la formation.");
    }
}

void gestion_formation::on_pushButton_8_clicked()
{
    formation f;

     ui->tableView->setModel(f.trititre());
}

void gestion_formation::on_pushButton_10_clicked()
{
    formation f;

     ui->tableView->setModel(f.triduree());
}

void gestion_formation::on_pushButton_11_clicked()
{
    formation f;

     ui->tableView->setModel(f.trilieu());
}

void gestion_formation::on_pushButton_7_clicked()
{
    QPdfWriter pdf("formation.pdf");
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
    painter.drawText(200, 3300, "id_formation");
    painter.drawText(1500, 3300, "titre");
    painter.drawText(2500, 3300, "date_debut");
    painter.drawText(3500, 3300, "duree");
    painter.drawText(4500, 3300, "lieu");
    painter.drawText(5500, 3300, "competence");


    QSqlQuery query;
    query.prepare("SELECT ID_FORMATION, TITRE, DATE_DEBUT, DUREE, LIEU, COMPETENCE FROM FORMATION");
    query.exec();

    while (query.next())
    {
        // Dessin de la ligne de tableau pour chaque employé
        painter.drawRect(0, i - 300, 9600, 500); // Dessiner la ligne du tableau

        // Affichage des données dans les colonnes respectives
        painter.drawText(200, i, query.value("id_formation").toString());
        painter.drawText(1500, i, query.value("titre").toString());
        painter.drawText(2500, i, query.value("date_debut").toString());
        painter.drawText(3500, i, query.value("duree").toString());
        painter.drawText(4500, i, query.value("lieu").toString());
        painter.drawText(5500, i, query.value("competence").toString());


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
        QDesktopServices::openUrl(QUrl::fromLocalFile("formation.pdf"));
    }

    painter.end();
}

void gestion_formation::on_pushButton_6_clicked()
{
    stati2 stg;
    stg.exec();
}

void gestion_formation::on_pushButton_13_clicked()
{
    calculator c;
    c.exec();
}
