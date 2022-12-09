//#include <unistd.h>
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

TP5_WeatherStation::TP5_WeatherStation(DbManager *dbm, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::TP5_WeatherStationClass)
    , weatherReport (new WeatherReport) // Weather Data class
    , dbmanager (dbm)                   // DB Manager, for Pollution Data
{
    ui->setupUi(this);

    // Weather report View
    reportView = new ViewReport(weatherReport,ui);
    // Pollution Forecast View
    pollutionView = new ViewPollution(dbmanager, ui->groupBox_pollution);

    // comment following line and uncomment next one, once observable implemented
    weatherRequest();
//    connect(ui->pushButton_weather_request, &QPushButton::pressed, this, &TP5_WeatherStation::weatherRequest);
//    connect(ui->pushButton_weather_request, &QPushButton::pressed, this, &TP5_WeatherStation::pollutionRequest);

}

TP5_WeatherStation::~TP5_WeatherStation()
{
    delete ui;
    delete dbmanager;
}

void TP5_WeatherStation::weatherRequest() {

    // your netmanager and request here

}

void TP5_WeatherStation::weatherReplyFinished(QNetworkReply* reply)
{
    // managing response here (with errors handling if possible)

    //don't forget to delete when no more requested
    reply->deleteLater();
    netmanager->deleteLater();
}
