#include "connexion.h"
#include <QSqlRecord>
#include <QTextCodec>
#include <QDebug>
#include <QSqlQuery>
#include <iostream>

using namespace std;

connexion::connexion()
{

    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");

    maBase=new QSqlDatabase(db);

    maBase->setHostName("localhost");
    maBase->setDatabaseName("nw");
    maBase->setUserName("troux");
    maBase->setPassword("tyk2irty");
    bool ok = maBase->open();
    if(!ok)
    {
        cout<<"Connection impossible"<<endl;
    }
    else
    {
        cout<<"Connection réussie"<<endl;
    }
}
