#include "connexion.h"

Connexion::Connexion(){}

bool Connexion::createConnection()
{
    bool test=false;
db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("agence");
db.setUserName("alib");//inserer nom de l'utilisateur
db.setPassword("alib");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
    return  test;

}

void Connexion::closeConnection()
{
    db.close();
}
