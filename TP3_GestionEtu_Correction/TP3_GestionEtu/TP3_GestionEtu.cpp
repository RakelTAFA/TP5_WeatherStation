#include "TP3_GestionEtu.h"

TP3_GestionEtu::TP3_GestionEtu(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

TP3_GestionEtu::TP3_GestionEtu(Promotion* promo, QWidget* parent): QMainWindow(parent),promo(promo)
{
  ui.setupUi(this);

  listView = new ViewList(promo, ui.listWidget);
  connect(ui.pushButton_delete_list, &QPushButton::pressed, listView, &ViewList::remove);

  listForm = new ViewForms(promo, &ui);
  connect(ui.pushButton_addStudent, &QPushButton::pressed, listForm, &ViewForms::add);
  connect(ui.pushButton_delete_number, &QPushButton::pressed, listForm, &ViewForms::remove);

  pieChartView=new ViewPieChart(promo, ui.groupBox_department);
  histogramView = new ViewHistogram(promo, ui.groupBox_bacs);

  promo->addObserver(listView);
  promo->addObserver(pieChartView);
  promo->addObserver(histogramView);
}

