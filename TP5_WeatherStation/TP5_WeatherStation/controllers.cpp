#include "controllers.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

#include <QByteArray>

#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonArray>

void Controller_WeatherRequest::control(){
    QNetworkAccessManager* netmanager = new QNetworkAccessManager(this);
    connect(netmanager, &QNetworkAccessManager::finished, this, &Controller_WeatherRequest::replyFinished);
//    connect(netmanager, SIGNAL(finished(QNetworkReply*)), netmanager, SLOT(deleteLater()));

    QString URL = "https://api.openweathermap.org/data/2.5/weather?q=bourg-en-bresse,fr&units=metric&lang=fr&appid=72fe9074d468b143e4725271e2449cda";
    QUrl url(URL);
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("Accept", "application/json");
    qDebug() << Q_FUNC_INFO << request.url();
    netmanager->get(request);

//    netmanager->deleteLater();

}

void Controller_WeatherRequest::replyFinished(QNetworkReply* reply)
{
    if(reply->error() !=  QNetworkReply::NoError)
    {
         qDebug() << "Failed to connect:" << reply->error() << "=" << reply->errorString();
         qDebug() << reply->readAll();
    }
    else if( reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200)
    {
        qDebug() << reply->request().url().toString();
        QByteArray infos = reply->readAll();
        qDebug() << infos;
        //...
        QJsonDocument jsonResponse = QJsonDocument::fromJson(infos/*.toUtf8()*/);
        QJsonObject jsonObj = jsonResponse.object();
        qDebug() << "cod\t:" << jsonObj["cod"] << jsonObj["cod"].toInt() << jsonObj["cod"].toString().toInt();

        QJsonArray weatherArray = jsonObj["weather"].toArray();
        for (auto w:weatherArray) {
            QJsonValue main = w.toObject()["main"];
            QJsonValue description = w.toObject()["description"];
            qDebug() << "weather\t:" << w << " " << main.toString() << " " << description.toString();
//            model->addPerson(main.toString());
        }

        QJsonObject mainObj = jsonObj["main"].toObject();
        QJsonValue temp = mainObj["temp"];
        QJsonValue temp_min = mainObj["temp_min"];
        QJsonValue temp_max = mainObj["temp_max"];
        qDebug() << "main\t:" << temp.toDouble()<< " " << temp_min.toDouble() << " " << temp_max.toDouble();

        model->notifyObserver();
    }
    else
    {
        qDebug() << "Failed to connect:" << reply->error() << "=" << reply->errorString();
        qDebug() << reply->readAll();
    }

    reply->deleteLater();
}
