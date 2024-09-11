#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>

class employe
{
public:
    employe();
    employe(int id_employe, QString nom, QString prenom, QString fonction, QString departement, int cin, int tel, QDate date);

    QString getnom();
    QString getprenom();
    QString getfonction();
    QString getdepartement();
    int getcin();
    int gettel();
    QDate getdate();
    int getIdEmploye(); // Getter for id_employe

    void setnom(QString nom);
    void setprenom(QString prenom);
    void setfonction(QString fonction);
    void setdepartement(QString departement);
    void setcin(int cin);
    void settel(int tel);
    void setdate(QDate date);
    void setIdEmploye(int id_employe); // Setter for id_employe

    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int id_employe);
    bool modifier();
    QSqlQueryModel*recherche(const QString& searchValue);
    QSqlQueryModel*tricin();
    QSqlQueryModel*trinom();
    QSqlQueryModel*trifonction();
    void generatePDF(int id_employe, QString nom, QString prenom, QString fonction, QString departement, int cin, int tel, QDate date);
    QSqlQueryModel*statistiquesFonction() ;
int statistique1();
int statistique2();
        // Création du document PDF
private:
    int id_employe; // Added id_employe
    QString nom;
    QString prenom;
    QString fonction;
    QString departement;
    int cin;
    int tel;
    QDate date;
};

#endif // EMPLOYE_H
