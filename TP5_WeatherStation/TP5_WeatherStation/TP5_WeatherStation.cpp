//#include <unistd.h>
#include <iostream>
#include <QtNetwork/QNetworkAccessManager>
#include <QByteArray>

#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonArray>

#include "TP5_WeatherStation.h"
#include "ui_TP5_WeatherStation.h"

#include "weatherreport.h"
using namespace std;


struct ReportAll {
    qint64 time;
    int aqi;
};


TP5_WeatherStation::TP5_WeatherStation(DbManager *dbm, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::TP5_WeatherStationClass)
    , weatherReport (new WeatherReport) // Weather Data class
    , dbmanager (dbm)                   // DB Manager, for Pollution Data
    , netmanager (nullptr)              // NetWork Manager, for http requests
{
    ui->setupUi(this);
    
    // Weather report View
    reportView = new ViewReport(weatherReport,ui);

    // Pollution Forecast View
    pollutionView = new ViewPollution(dbmanager, ui->groupBox_pollution);

    weatherReport->addObserver(reportView);
    weatherReport->addObserver(pollutionView);

    // netmanager here (or better in initialisation list)  + callback to replyFinished
    netmanager = new QNetworkAccessManager(this);
    pollutionManager = new QNetworkAccessManager(this);

    weatherRequest(); 
    connect(netmanager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(weatherReplyFinished(QNetworkReply*)));
    connect(pollutionManager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(pollutionReplyFinished(QNetworkReply*)));
    // uncomment once observable implemented
    connect(ui->pushButton_weather_request, &QPushButton::pressed, this, &TP5_WeatherStation::weatherRequest);
    connect(ui->pushButton_weather_request, &QPushButton::pressed, this, &TP5_WeatherStation::pollutionRequest);

}


TP5_WeatherStation::~TP5_WeatherStation()
{
    delete ui;
    delete dbmanager;
    if (netmanager != nullptr)
        netmanager->deleteLater();
    if (pollutionManager != nullptr)
        pollutionManager->deleteLater();
}


void TP5_WeatherStation::weatherRequest() {

    // your request here
    QString URL = "https://api.openweathermap.org/data/2.5/weather?q=bourg-en-bresse,fr&units=metric&lang=fr&appid=0d41ac5cb088db1d5301807cbfb18170";
    QUrl url(URL);
    QNetworkRequest* request = new QNetworkRequest(url);
    request->setUrl(url);

    //--header ’Accept: application/json’
    request->setRawHeader("Accept", "application/json");
    qDebug() << Q_FUNC_INFO << request->url();
    netmanager->get(*request);
}


void TP5_WeatherStation::weatherReplyFinished(QNetworkReply* reply)
{
    QByteArray datas = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(datas);
    QJsonObject jsonObj = jsonResponse.object();
    QString infos(datas);
    
    if (reply->error() != QNetworkReply::NoError)
    {
        //Network Error
        qDebug() << reply->error() << "=>" << reply->errorString();
    }
    else if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200)
    {
        // Partie test
        /*
        QJsonObject mainObj = jsonObj["main"].toObject();
        float temp = mainObj["temp"].toDouble();
        
        QJsonArray weatherArray = jsonObj["weather"].toArray();
        QJsonObject weatherArrayZero = weatherArray[0].toObject();
        QString id = weatherArrayZero["main"].toString();
        cout << id.toStdString() << endl;
        */

        QJsonArray weatherArray = jsonObj["weather"].toArray();
        QJsonObject weatherArrayZero = weatherArray[0].toObject();
        QString main, description;
        main = weatherArrayZero["main"].toString();
        description = weatherArrayZero["description"].toString();

        QJsonObject mainObj = jsonObj["main"].toObject();
        double temp, temp_min, temp_max, lon, lat;
        temp = mainObj["temp"].toDouble();
        temp_min = mainObj["temp_min"].toDouble();
        temp_max = mainObj["temp_max"].toDouble();

        QJsonObject coordObj = jsonObj["coord"].toObject();
        lon = coordObj["lin"].toDouble();
        lat = coordObj["lon"].toDouble();

        weatherReport->fetchData(main, description, temp, temp_min, temp_max, lon, lat);
    }
    else {
        cout << "Failed to connect to API !" << endl;
    }

    reply->deleteLater();
}


void TP5_WeatherStation::pollutionRequest()
{
    QString URL = "https://api.openweathermap.org/data/2.5/air_pollution/forecast?lat=46.0398&lon=5.4133&units=metric&lang=fr&appid=0d41ac5cb088db1d5301807cbfb18170";
    QUrl url(URL);
    QNetworkRequest* request = new QNetworkRequest(url);
    request->setUrl(url);

    //--header ’Accept: application/json’
    request->setRawHeader("Accept", "application/json");
    qDebug() << Q_FUNC_INFO << request->url();
    pollutionManager->get(*request);
}


void TP5_WeatherStation::pollutionReplyFinished(QNetworkReply* reply)
{
    QByteArray datas = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(datas);
    QJsonObject jsonObj = jsonResponse.object();
    QString infos(datas);

    if (reply->error() != QNetworkReply::NoError)
    {
        //Network Error
        qDebug() << reply->error() << "=>" << reply->errorString();
    }
    else if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200)
    {
        if (dbmanager->isOpen())
        {
            QJsonArray listArray = jsonObj["list"].toArray();

            for (int i = 0; i < listArray.size(); i++)
            {
                /*
                QJsonArray numberArray = listArray[i].toArray();
                QJsonObject numberArrayTime = listArray[2].toObject();

                int localtimeInt = numberArrayTime["dt"].toInt();
                QDateTime localtime = QDateTime::fromSecsSinceEpoch(localtimeInt);
                qint64 msdt = localtime.toMSecsSinceEpoch();

                QJsonObject mainArray = numberArray[0].toObject();
                int aqi = mainArray["aqi"].toInt();
                */

                ReportAll rp;
               
                rp.time = QDateTime::fromSecsSinceEpoch(jsonObj["list"].toArray()[i].toObject().value("dt").toInt()).toMSecsSinceEpoch();
                rp.aqi = jsonObj["list"].toArray()[i].toObject().value("main").toObject().value("aqi").toInt();

                dbmanager->addData(rp.time, rp.aqi);
            }
            dbmanager->printAllData();
        }
        else 
        {
            qDebug() << "Pas entrer dans la boucle...";
        }
        

    }
    else {
        cout << "Failed to connect to API !" << endl;
    }
    
    reply->deleteLater();
}
