#include "promotion.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

/**
 * @brief Constructor of the Promotion Class to manage the List of student
 * @param url the url of the database
*/
Promotion::Promotion(QString url)
{
	QFile file(url);
	if (file.open(QIODevice::ReadOnly | QFile::Text))
	{
			QTextStream in(&file);

			while (!in.atEnd())
			{
				QStringList split = in.readLine().split(';');
				add(Student(split[0], split[1], split[2], split[4], split[3]));
			}

			file.close();
	}
	else
	{
		qDebug() << "Open File Error, URL : " << url << "\n";
	}
}

/**
 * @brief Function to add a student to the promotion list
 * @param etu The current student
*/
void Promotion::add(Student etu)
{
	students.append(etu);
	notifyObserver();
}

/**
 * @brief Function to remove a list of student
 * @param listName The list of the students text in the view list
*/
void Promotion::remove(QString listName)
{
	for (int i = students.size() - 1 ; i >= 0; i--)
	{
		if (students[i].getText() == listName)
		{
			students.remove(i);
		}
	}
	notifyObserver();
}

/**
 * @brief Function to remove a specific student
 * @param etu The student to remove
*/
void Promotion::remove(Student etu)
{
	for (int i=0;i<students.size();i++)
	{
		if (students[i].getCardID() == etu.getCardID())
			students.remove(i);
	}
	notifyObserver();
}

/**
 * @brief Search the student according to his ID Card
 * @param cardID ID card of the student
*/
Student Promotion::find(QString cardID) const
{
	for (Student student: students)
	{
		if (student.getCardID() == cardID) return student;
	}

	return Student("","","","","");
}

/**
 * @brief Get the text list to fill the view list 
 * @return list of student text
*/
QStringList Promotion::getList() const
{
	QStringList list;

	for (const Student& student : students)
	{
		list.append(student.getText());
	}

	list.sort();
	
	return list;
}

/**
 * @brief Get the statistics for all department 
 * @return A map of all department and the associated number of student
*/
QMap<QString, int> Promotion::getListDepartment() const
{
	QMap<QString, int> series;

	for (const Student& student : students)
	{
		QString dept = student.getDepartment();
		if (series.contains(dept)) series.insert(dept, series.value(dept) + 1);
		else series.insert(dept, 1);
	}

	return series;
}

/**
 * @brief Get the statistics for all bacs
 * @return A map of all bacs and the associated number of student
*/
QMap<QString, int> Promotion::getListBacs() const
{
	QMap<QString, int> series;

	series.insert("S", 0);
	series.insert("ES", 0);
	series.insert("L", 0);
	series.insert("STI", 0);
	series.insert("STG", 0);
	series.insert("Etr", 0);
	series.insert("Autre", 0);

	for (const Student& student : students)
	{
		QString bac = student.getBac();
		if (series.contains(bac)) series.insert(bac, series.value(bac) + 1);
		else series.insert(bac, 1);
	}

	return series;
}

/**
 * @brief Print the student information
*/
ostream& operator<<(ostream& os, const Promotion& dt)
{
	for (const Student& student : dt.students)
	{
		os << student << "\n";
	}

	return os;
}
