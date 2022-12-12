#ifndef WEATHERREPORT_H
#define WEATHERREPORT_H

#include <QDebug>
#include <qvector.h>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonArray>
#include <QString>

#include "observer.h"

/**
 * @brief The WeatherReport class
 * @author FJa
 */
class WeatherReport : public Observable
{
private:
    QString main,description; //> text report
    double temp,temp_min,temp_max; //> temperatures
    double lon,lat; //> localisation

    QVector<Observer*> observers;

public:
    WeatherReport();

    void addObserver(Observer* observer) { observers.append(observer); }
    void removeObserver(Observer* observer) { return; }
    void notifyObserver() const { for (Observer* o : observers) o->update(); }

    // getters
    const QString& getDescription() const {return description;}
    double getTemp() const {return temp;}
    double getTempMin() const {return temp_min;}
    double getTempMax() const {return temp_max;}
    double getLon() const {return lon;}
    double getLat() const {return lat;}
    
    void fetchData(QString _main, QString _description, double _temp, double _temp_min, double _temp_max, double _lon, double _lat) {
        main = _main;
        description = _description;
        temp = _temp;
        temp_min = _temp_min;
        temp_max = _temp_max;
        lon = _lon;
        lat = _lat;
    }
};

#endif // WEATHERREPORT_H
