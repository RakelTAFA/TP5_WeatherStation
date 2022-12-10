#include "viewList.h"
#include "controllers.h"

/**
 * @brief Constructor
 * @param promo The current promotion (students list)
 * @param list  The QT widget list
*/
ViewList::ViewList(Promotion* promo, QListWidget* list):promo(promo), list(list)
{
	update();
}

/**
 * @brief Update the items list according to the students
*/
void ViewList::update()
{
	list->clear();

	list->addItems(promo->getList());
}

/**
 * @brief Remove the selected items of the list
*/
void ViewList::remove()
{
	QList<QListWidgetItem*> items = list->selectedItems();
	QStringList listStringSelected;
	for (QListWidgetItem*  item : items)
	{
		listStringSelected.append(item->text());
	}

	Controller_DeleteList controller(promo);
	controller.control(listStringSelected);
}
