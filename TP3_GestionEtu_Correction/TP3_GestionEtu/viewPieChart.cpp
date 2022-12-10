#include "viewPieChart.h"

ViewPieChart::ViewPieChart(Promotion* promo, QWidget* widget):promo(promo), widget(widget)
{
  series = new QPieSeries();

  QChart* chart = new QChart();
  chart->addSeries(series);
  chart->setTitle(QString("Répartition géographique"));
  chart->setAnimationOptions(QChart::SeriesAnimations);

  QChartView* chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  QGridLayout *chartLayout = new QGridLayout;
  chartLayout->addWidget(chartView, 0, 0);
  chartLayout->setContentsMargins(0, 0, 0, 0);
  
	// update chart
	widget->setLayout(chartLayout);

	update();
}


void ViewPieChart::update()
{
  series->clear();
  
  QMap<QString, int> arraySeries = promo->getListDepartment();
  for (auto serie : arraySeries.keys())
  {
     series->append(serie, arraySeries.value(serie));
  }

  widget->repaint();
}
