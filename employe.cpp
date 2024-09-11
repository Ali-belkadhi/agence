#include "employe.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QPainter>
#include <QDebug>
#include <QSqlError>
#include <QDate>
#include <QPdfWriter>
#include <QTextDocument>
#include <QSqlRecord>
#include <QVariant>
employe::employe()
{

}


employe::employe(int id_employe, QString nom, QString prenom,  QString fonction, QString departement ,int cin ,int tel, QDate date  )
{
    this->id_employe=id_employe;
    this->nom=nom;
    this->prenom=prenom;
    this->fonction=fonction;
    this->departement=departement;
    this->cin=cin;
    this->tel=tel;
    this->date=date;
}


QString employe::getnom()
{
    return nom;
}

void employe::setnom(QString nom)
{
    this->nom = nom;
}

QString employe::getprenom()
{
    return prenom;
}

void employe::setprenom(QString prenom)
{
    this->prenom = prenom;
}



QString employe::getfonction()  // Correct return type
{
    return fonction;
}

void employe::setfonction(QString fonction)
{
    this->fonction = fonction;
}

QString employe::getdepartement()
{
    return departement;
}

void employe::setdepartement(QString departement)
{
    this->departement = departement;
}
int employe::getcin()
{
    return cin;
}

void employe::setcin(int cin)
{
    this->cin = cin;
}



int employe::gettel()
{
    return tel;
}

void employe::settel(int tel)
{
    this->tel = tel;
}


QDate employe::getdate()
{
    return date;
}

void employe::setdate(QDate date)
{
    this->date = date;
}



bool employe::ajouter()
{
    QSqlQuery query;

    // Check if an employee with the same CIN already exists
    query.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE CIN = :cin");
    query.bindValue(":cin", cin);  // Use the same placeholder consistently

    if (query.exec()) {
        query.next();
        if (query.value(0).toInt() > 0) {
            qDebug() << "An employee with the same CIN already exists!";
            return false;  // Prevent adding duplicate
        }
    } else {
        qDebug() << "Database error during duplicate check: " << query.lastError().text();
        return false;
    }

    // Generate or assign a unique ID for the employee (you might need to handle this if auto-increment is not used)
    int id_employe = /* Generate or get new employee ID here, e.g., from a sequence or auto-increment */

    // Proceed with the insertion
    query.prepare("INSERT INTO EMPLOYE (ID_EMPLOYE, NOM, PRENOM, FONCTION, DEPARTEMENT, CIN, TEL, DATE_EMPLOYE) "
                  "VALUES (:id_employe, :nom, :prenom, :fonction, :departement, :cin, :tel, :date)");

    query.bindValue(":id_employe", id_employe);  // You need to provide or generate this value
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":fonction", fonction);
    query.bindValue(":departement", departement);
    query.bindValue(":cin", cin);
    query.bindValue(":tel", tel);
    query.bindValue(":date", date);

    if (!query.exec()) {
        qDebug() << "Failed to add employee:" << query.lastError().text();
        return false;
    }

    return true;
}


QSqlQueryModel *employe::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("fonction"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("departement"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("cin"));
      model->setHeaderData(6, Qt::Horizontal, QObject::tr("tel"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("date"));

    return model;
}

bool employe::supprimer(int id_employe)
{
    QSqlQuery query;
    QString res = QString::number(id_employe);
    query.prepare("DELETE FROM EMPLOYE WHERE ID_EMPLOYE = :ID_EMPLOYE");
    query.bindValue(":ID_EMPLOYE", res);

    return query.exec();

}

bool employe::modifier() {
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET nom = :nom, prenom = :prenom, fonction = :fonction, departement = :departement, cin = :cin, tel = :tel, date_employe = :date WHERE ID_EMPLOYE = :id_employe");

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":fonction", fonction);
    query.bindValue(":departement", departement);
    query.bindValue(":cin", cin);
    query.bindValue(":tel", tel);
    query.bindValue(":date", date);
    query.bindValue(":id_employe", id_employe); // Bind the id_employe value

    if (!query.exec()) {
        qDebug() << "Erreur lors de la modification :" << query.lastError().text();
        return false;
    }
    return true;
}


QSqlQueryModel* employe::recherche(const QString& searchValue)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    // Préparer la requête SQL avec des paramètres
    QString queryString = "SELECT * FROM EMPLOYE WHERE "
                          "ID_EMPLOYE LIKE '%' || :search || '%' "
                          "OR nom LIKE '%' || :search || '%' "
                          "OR prenom LIKE '%' || :search || '%' "
                          "OR cin LIKE '%' || :search || '%' "
                          "OR fonction LIKE '%' || :search || '%' "
                          "OR departement LIKE '%' || :search || '%' "
                          "OR tel LIKE '%' || :search || '%' "
                          "OR TO_CHAR(date_employe, 'YYYY-MM-DD') LIKE '%' || :search || '%'";

    query.prepare(queryString);

    // Binding the search value without wildcards
    query.bindValue(":search", searchValue);

    // Exécuter la requête
    if (!query.exec()) {
        qDebug() << "Erreur lors de la recherche :" << query.lastError().text();
        return nullptr;
    }

    // Définir le modèle de données
    model->setQuery(query);

    // Définir les en-têtes des colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("fonction"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("departement"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("tel"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("date_employe"));

    return model;
}

QSqlQueryModel*  employe::tricin()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYE ORDER BY cin ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("fonction"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("departement"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("cin"));
      model->setHeaderData(6, Qt::Horizontal, QObject::tr("tel"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("date"));
    return model;
}

QSqlQueryModel*  employe::trinom()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYE ORDER BY nom ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("fonction"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("departement"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("cin"));
      model->setHeaderData(6, Qt::Horizontal, QObject::tr("tel"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("date"));
    return model;
}

QSqlQueryModel*  employe::trifonction()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYE ORDER BY fonction ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("fonction"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("departement"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("cin"));
      model->setHeaderData(6, Qt::Horizontal, QObject::tr("tel"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("date"));
    return model;
}

void employe::generatePDF(int id_employe, QString nom, QString prenom, QString fonction, QString departement, int cin, int tel, QDate date)
{
    // Specify the file name and path where the PDF will be saved
    QString filename = "employe_" + QString::number(id_employe) + ".pdf";

    // Création du document PDF
    QPdfWriter writer(filename);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageMargins(QMarginsF(30, 30, 30, 30));

    // Création du QPainter pour dessiner sur le PDF
    QPainter painter(&writer);

    // Création du document texte pour le contenu du PDF
    QTextDocument document;
    QTextOption option;
    option.setAlignment(Qt::AlignLeft);

    // Construction du contenu du document
    QString content = "<h1>Informations sur l'employé</h1>";
    content += "<p><b>ID_EMPLOYE :</b> " + QString::number(id_employe) + "</p>";
    content += "<p><b>Nom:</b> " + nom + "</p>";
    content += "<p><b>Prénom:</b> " + prenom + "</p>";
    content += "<p><b>Fonction:</b> " + fonction + "</p>";
    content += "<p><b>Département:</b> " + departement + "</p>";
    content += "<p><b>CIN:</b> " + QString::number(cin) + "</p>";
    content += "<p><b>Tel :</b> " + QString::number(tel) + "</p>";
    content += "<p><b>Date :</b> " + date.toString("dd/MM/yyyy") + "</p>";

    // Configuration du contenu du document
    document.setHtml(content);
    document.setDefaultTextOption(option);

    // Dessin du contenu sur le PDF
    document.drawContents(&painter);

    // Fermeture du QPainter
    painter.end();
}
// employe.cpp



int employe::statistique1(){
    QSqlQuery query;
    int count = 0;
    QSqlQuery requete("SELECT * FROM EMPLOYE WHERE fonction = 'Manager'"); // Adjust to the desired function
    while(requete.next()) {
        count++;
    }
    return count;
}

int employe::statistique2(){
    QSqlQuery query;
       int count = 0;
       QSqlQuery requete("SELECT * FROM EMPLOYE WHERE fonction = 'Engineer'"); // Adjust to the desired function
       while(requete.next()) {
           count++;
       }
       return count;
}
