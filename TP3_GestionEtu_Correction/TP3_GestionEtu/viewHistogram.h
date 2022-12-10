#pragma once
#include "promotion.h"
#include <QWidget>
#include <QBarSeries>
#include <QChart>
#include <QChartView>
#include <QGridLayout>
#include <QValueAxis>

#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
QT_CHARTS_USE_NAMESPACE
#endif

/**
 * @brief Class to manage the Histogram View
 * @author Adrien Peytavie
*/
class ViewHistogram : public QObject, public Observer
{
	Q_OBJECT

private:
	Promotion* promo;
	QWidget* widget;
	QBarSeries* series;
	QValueAxis* axisY;

public:
	ViewHistogram(Promotion*, QWidget*);

	void update() override;
};

