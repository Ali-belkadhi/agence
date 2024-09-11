#include "formation.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

#include <QMessageBox>
#include <QPainter>
#include <QDebug>
#include <QSqlError>
#include <QDate>
#include <QPdfWriter>
#include <QTextDocument>
#include "formation.h"
formation::formation()
{

}
formation::formation(int id_formation ,QString titre,QDate date_debut,QString duree, QString lieu,QString competence)
{
    this->id_formation=id_formation;
    this->titre=titre;
    this->date_debut=date_debut;
    this->duree=duree;
    this->lieu=lieu;
    this->competence=competence;
}

QString formation::gettitre()
{
    return titre;
}
void formation::settitre(QString titre)
{
    this->titre = titre;
}


QDate formation::getdate_debut()
{
    return date_debut;
}
void formation::setdate_debut(QDate date_debut)
{
    this->date_debut = date_debut;
}


QString formation::getduree()
{
    return duree;
}
void formation::setduree(QString duree)
{
    this->duree = duree;
}



QString formation::getlieu()
{
    return lieu;
}
void formation::setlieu(QString lieu)
{
    this->lieu = lieu;
}



QString formation::getcompetence()
{
    return competence;
}
void formation::setcompetence(QString competence)
{
    this->competence = competence;
}

bool formation::ajouter()
{
    QSqlQuery query;

    // Check if a formation with the same titre and date_debut already exists
    query.prepare("SELECT COUNT(*) FROM FORMATION WHERE TITRE = :titre AND date_debut = :date_debut");

    query.bindValue(":titre", titre);
    query.bindValue(":date_debut", date_debut);

    if (query.exec()) {
        query.next();
        if (query.value(0).toInt() > 0) {
            qDebug() << "A formation with the same titre and date_debut already exists!";
            return false; // Prevent adding duplicate
        }
    } else {
        qDebug() << "Database error during duplicate check: " << query.lastError().text();
        return false;
    }

    // If no duplicate is found, proceed with the insertion
    query.prepare("INSERT INTO FORMATION (ID_FORMATION, TITRE, DATE_DEBUT, DUREE, LIEU, COMPETENCE) "
                  "VALUES (:id_formation, :titre, :date_debut, :duree, :lieu, :competence)");

    query.bindValue(":id_formation", id_formation);
    query.bindValue(":titre", titre);
    query.bindValue(":date_debut", date_debut);
    query.bindValue(":duree", duree);
    query.bindValue(":lieu", lieu);
    query.bindValue(":competence", competence);

    if (!query.exec()) {
        qDebug() << "Failed to add formation:" << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQueryModel *formation::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM FORMATION");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("titre"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_debut"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("duree"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("lieu"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("competence"));


    return model;
}




bool formation::supprimer(int id_formation)
{
    QSqlQuery query;
    QString res = QString::number(id_formation);
    query.prepare("DELETE FROM FORMATION WHERE ID_FORMATION = :ID_FORMATION");
    query.bindValue(":ID_FORMATION", res);

    return query.exec();

}


bool formation::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE FORMATION SET titre = :titre, date_debut = :date_debut, duree = :duree, lieu = :lieu, competence = :competence WHERE ID_FORMATION = :id_formation");
    query.bindValue(":id_formation", id_formation);
    query.bindValue(":titre", titre);
    query.bindValue(":date_debut", date_debut);
    query.bindValue(":duree", duree);
    query.bindValue(":lieu", lieu);
    query.bindValue(":competence", competence);


    if (!query.exec()) {
        qDebug() << "Erreur lors de la modification :" << query.lastError().text();
        return false;
    }
    return true;
}

/*bool employe::modifier() {
    QSqlQuery query;
    query.prepare("UPDATE employé SET nom = :nom, prenom = :prenom, fonction = :fonction, departement = :departement, cin = :cin, tel = :tel, date = :date WHERE id_employe = :id_employe");

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
}*/

QSqlQueryModel* formation::recherche(const QString& searchValue)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    // Préparer la requête SQL avec des paramètres
    QString queryString = "SELECT * FROM FORMATION WHERE "
                          "id_formation LIKE :search "
                          "OR titre LIKE :search "
                          "OR date_debut LIKE :search "
                          "OR duree LIKE :search "
                          "OR lieu LIKE :search "
                          "OR competence LIKE :search "

                          ;

    query.prepare(queryString);

    // Utiliser '%' pour faire la recherche partielle
    QString searchPattern = QString("%%1%").arg(searchValue);
    query.bindValue(":search", searchPattern);

    // Exécuter la requête
    if (!query.exec()) {
        qDebug() << "Erreur lors de la recherche :" << query.lastError().text();
        return nullptr;
    }

    // Définir le modèle de données
    model->setQuery(query);

    // Définir les en-têtes des colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_formation"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("titre"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_debut"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("duree"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("lieu"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("competence"));


    return model;
}


QSqlQueryModel*  formation::trititre()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM FORMATION ORDER BY titre ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_formation"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("titre"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_debut"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("duree"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("lieu"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("competence"));

    return model;
}

QSqlQueryModel*  formation::triduree()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM FORMATION ORDER BY duree ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_formation"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("titre"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_debut"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("duree"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("lieu"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("competence"));
    return model;
}

QSqlQueryModel*  formation::trilieu()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM FORMATION ORDER BY lieu ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_formation"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("titre"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_debut"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("duree"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("lieu"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("competence"));
    return model;
}




void formation::generatePDF(int id_formation, QString titre, QString date_debut, QString duree, QString lieu, QString competence)
{
    // Specify the file name and path where the PDF will be saved
    QString filename = "formation" + QString::number(id_formation) + ".pdf";

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
    QString content = "<h1>Informations sur l'formation</h1>";
    content += "<p><b>ID :</b> " + QString::number(id_formation) + "</p>";
    content += "<p><b>titre:</b> " + titre + "</p>";
    content += "<p><b>date_debut:</b> " + date_debut + "</p>";
    content += "<p><b>duree:</b> " + duree + "</p>";
    content += "<p><b>lieu:</b> " + lieu + "</p>";
    content += "<p><b>competence:</b> " + competence + "</p>";


    // Configuration du contenu du document
    document.setHtml(content);
    document.setDefaultTextOption(option);

    // Dessin du contenu sur le PDF
    document.drawContents(&painter);

    // Fermeture du QPainter
    painter.end();
}

int formation::statistique1() {
    QSqlQuery query;
    int count = 0;

    // Assuming 'duree' is in a format like '2j', '3j', etc.
    QSqlQuery requete("SELECT COUNT(*) FROM FORMATION WHERE duree <= '2j'");
    if (requete.next()) {
        count = requete.value(0).toInt(); // Get the count of formations with 2 days or less
    }
    return count;
}

int formation::statistique2() {
    QSqlQuery query;
    int count = 0;

    QSqlQuery requete("SELECT COUNT(*) FROM FORMATION WHERE duree > '2j'");
    if (requete.next()) {
        count = requete.value(0).toInt(); // Get the count of formations with more than 2 days
    }
    return count;
}
