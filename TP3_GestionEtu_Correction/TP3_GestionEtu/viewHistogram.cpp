#include "viewHistogram.h"
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QBarSet>

ViewHistogram::ViewHistogram(Promotion* promo, QWidget* widget) :promo(promo), widget(widget)
{
  // Define Series empty
  series = new QBarSeries();


  QChart* chart = new QChart();
  chart->addSeries(series);
  chart->setTitle("Series de bac");
  chart->setAnimationOptions(QChart::SeriesAnimations);

  QStringList categories;
  categories << "Bacs";
  QBarCategoryAxis* axisX = new QBarCategoryAxis();
  axisX->append(categories);
  chart->addAxis(axisX, Qt::AlignBottom);
  series->attachAxis(axisX);

  axisY = new QValueAxis();
  axisY->setLabelFormat("%d");
  chart->addAxis(axisY, Qt::AlignLeft);
  series->attachAxis(axisY);

  chart->legend()->setVisible(true);
  chart->legend()->setAlignment(Qt::AlignBottom);

  QChartView* chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  QGridLayout* chartLayout = new QGridLayout;
  chartLayout->addWidget(chartView, 0, 0);
  chartLayout->setContentsMargins(0, 0, 0, 0);
  
  // update chart
  widget->setLayout(chartLayout);

  update();
}


void ViewHistogram::update()
{
  int maxY = 0;
  series->clear();

  QMap<QString, int> arraySeries = promo->getListBacs();
  for (auto bac : arraySeries.keys())
  {
    int value = arraySeries.value(bac);
    QBarSet* set0 = new QBarSet(bac);
    *set0 << value;
    series->append(set0);
    if (value > maxY) maxY = value;
  }

  axisY->setRange(0, maxY);
  widget->repaint();
}
