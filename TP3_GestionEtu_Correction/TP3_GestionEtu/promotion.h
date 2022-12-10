#pragma once
#include <QVector>
#include <iostream>
#include "student.h"
#include "observer.h"

using namespace std;

/**
 * @brief Promotion manage the list of students
 * @author Adrien Peytavie
*/
class Promotion : private Observable
{
private:
	QVector<Student> students;
	QVector<Observer*> observers;

public:
	Promotion() : Observable() {}
	Promotion(QString);

	void add(Student);
	void remove(Student);
	void remove(QString);

	Student find(QString) const;

	QStringList getList() const;
	QMap<QString, int> getListDepartment() const;
	QMap<QString, int> getListBacs() const;

	friend ostream& operator<<(ostream& os, const Promotion& dt);

	// Observer
	virtual void addObserver(Observer* observer) override { observers.append(observer); }
	virtual void removeObserver(Observer* observer) override { observers.removeAll(observer); }
	virtual void notifyObserver() const override {for (Observer* observer : observers) observer->update();}

};

