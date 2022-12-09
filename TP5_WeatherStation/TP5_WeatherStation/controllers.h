#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include "weatherreport.h"
#include "dbmanager.h"
#include <QtNetwork/QNetworkAccessManager>

class AbstractController
{
public:
public:
  virtual ~AbstractController() =default;
  virtual void control() = 0;
};

class Controller_WeatherRequest : public QObject, public AbstractController
{
    Q_OBJECT
private:
  WeatherReport* model;
public:
  Controller_WeatherRequest(WeatherReport *wreport) : model(wreport) {}

  virtual void control() override;

public slots:
    void replyFinished(QNetworkReply* reply);

};

#endif // CONTROLLERS_H
