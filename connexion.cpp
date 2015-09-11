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

            maBase->setHostName("172.16.63.111");
            maBase->setDatabaseName("dbtrouxNewWorld");
            maBase->setUserName("troux");
            maBase->setPassword("PscX57Q16");
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
