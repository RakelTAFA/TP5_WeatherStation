#pragma once
#include "promotion.h"
#include <QGroupBox>
#include "ui_TP3_GestionEtu.h"

class ViewForms : public QObject
{
	Q_OBJECT

private:
	Ui::TP3_GestionEtuClass* ui;
	Promotion* promo;

public:
	ViewForms(Promotion*, Ui::TP3_GestionEtuClass*);

	void init();
	void update();

public slots:
	void add();
	void remove();
};

