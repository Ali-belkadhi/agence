#ifndef FORMATION_H
#define FORMATION_H
#include <QDate>
#include <QString>
#include <QSqlQueryModel>
class formation
{
public:
    formation();
    formation(int id_formation , QString titre ,QDate date_debut, QString duree ,QString lieu ,QString competence);
    QString gettitre();
    QDate getdate_debut();
    QString getduree();
    QString getlieu();
    QString getcompetence();
    void settitre(QString titre);
    void setdate_debut(QDate date_debut );
    void setduree (QString duree);
    void setlieu (QString lieu);
    void setcompetence (QString competence);
    bool ajouter();
    QSqlQueryModel *afficher();
   bool supprimer(int id_formation);
   bool modifier();
   QSqlQueryModel*recherche(const QString& searchValue);
   QSqlQueryModel*trititre();
   QSqlQueryModel*triduree();
   QSqlQueryModel*trilieu();
   void generatePDF(int id_formation, QString titre, QString date_debut, QString duree, QString lieu, QString competence);
   int statistique1();

   int statistique2();
private:
    int id_formation;
    QString titre;
    QDate date_debut;
    QString duree;
    QString lieu;
    QString competence;

};


#endif // FORMATION_H
