#pragma once
#include "promotion.h"
#include <QWidget>
#include <QPieSeries>
#include <QChart>
#include <QChartView>
#include <QGridLayout>
#include <QChartGlobal>
#include "qchartglobal.h"

#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
QT_CHARTS_USE_NAMESPACE
#endif

//using namespace QtCharts;
QT_USE_NAMESPACE

/**
 * @brief Class to manage the PieChart View
 * @author Adrien Peytavie
*/
class ViewPieChart : public QObject, public Observer
{
	Q_OBJECT

private:
	Promotion* promo;
	QWidget* widget;
	QPieSeries* series;

public:
	ViewPieChart(Promotion*, QWidget*);

	void update() override;
};

