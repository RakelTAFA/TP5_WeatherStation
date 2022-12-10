#pragma once
#include "promotion.h"
#include <QListWidget>

/**
 * @brief Class to manage the QListWidget
 * @author Adrien Peytavie
*/
class ViewList : public QObject, public Observer
{
	Q_OBJECT

private:
	Promotion* promo;
	QListWidget* list;

public:
	ViewList(Promotion*, QListWidget*);

	void update() override;

public slots:
	void remove();
};

