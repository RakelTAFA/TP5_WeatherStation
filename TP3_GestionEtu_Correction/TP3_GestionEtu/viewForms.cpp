#include "viewForms.h"
#include "controllers.h"
#include <QStringList>

/**
* @brief Constructor
 * @param promo The current promotion (students list)
 * @param ui Interface
*/
ViewForms::ViewForms(Promotion* promo, Ui::TP3_GestionEtuClass* ui) : ui(ui), promo(promo)
{
	init();
	update();
}

/**
* @brief Initialize the forms UI
*/
void ViewForms::init()
{
	QStringList listBAC;
	listBAC << "S" << "ES" << "L" << "STI";
	ui->lineEdit_add_BAC->addItems(listBAC);

	QStringList listDept;
	for (int i = 1; i < 96; i++)
	{
		listDept.append( QString::number(i).rightJustified(2, '0'));
	}
	ui->lineEdit_add_department->addItems(listDept);
}

/**
* @brief Update the adding form
*/
void ViewForms::update()
{
	ui->lineEdit_add_number->clear();
	ui->lineEdit_add_firstname->clear();
	ui->lineEdit_add_lastname->clear();
	ui->lineEdit_add_BAC->setCurrentIndex(-1);
	ui->lineEdit_add_department->setCurrentIndex(-1);
}

/**
* @brief Add a student to the list
*/
void ViewForms::add()
{
	// Generate the data
	QStringList list;
	list << ui->lineEdit_add_number->text() <<
		ui->lineEdit_add_firstname->text() <<
		ui->lineEdit_add_lastname->text() <<
		ui->lineEdit_add_BAC->itemText(ui->lineEdit_add_BAC->currentIndex()) <<
		ui->lineEdit_add_department->itemText(ui->lineEdit_add_department->currentIndex());

	// Call the controller
	Controller_AddForm control(promo);
	control.control(list);
}

/**
* @brief Remove a student from the list
*/
void ViewForms::remove()
{
	// Generate the data
	QStringList list;
	list << ui->lineEdit_remove_number->text() ;

	// Call the controller
	Controller_DeleteForm control(promo);
	control.control(list);
}
