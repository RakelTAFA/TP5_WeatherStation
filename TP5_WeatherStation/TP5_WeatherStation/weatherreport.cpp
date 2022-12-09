#include "weatherreport.h"
#include <QDateTime>
#include <QTimeZone>
//#include <unistd.h>

WeatherReport::WeatherReport()
    : temp(0.0),temp_min(0.0),temp_max(0.0),
      lon(0.0),lat(0.0)
{ }
