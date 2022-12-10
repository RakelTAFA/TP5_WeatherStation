
#include "student.h"

/**
 * @brief Constructor of the Sudent class
*/
Student::Student(QString cardID, QString firstname, QString lastname, QString bac, QString department):
	cardID(cardID), firstname(firstname), lastname(lastname), bac(bac), department(department)
{
}

/**
 * @brief Print the student information
*/
ostream& operator<<(ostream& os, const Student& dt)
{
	os << dt.cardID.toStdString() << " " << dt.firstname.toStdString() << " " << dt.lastname.toStdString() << " " << dt.bac.toStdString() << " " << dt.department.toStdString();

	return os;
}
