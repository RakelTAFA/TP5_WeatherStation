#pragma once
#include <QStringList>
#include <QMessageBox>
#include "promotion.h"

/**
 * @brief AbstractController manage the list of students
 * @author Adrien Peytavie
*/
class AbstractController
{
public:
  virtual ~AbstractController() {}
  virtual void control(const QStringList& list) = 0;
};

/**
 * @brief Controller to delete student from the View List
 * @author Adrien Peytavie
*/
class Controller_DeleteList : public AbstractController
{
private:
  Promotion* promo;
public:
    /**
    * @brief Constructor
    */
  Controller_DeleteList(Promotion* promo) : promo(promo) {}

  /**
  * @brief Control the removing process of students
  */
  virtual void control(const QStringList& list) override
  {
        // Check the number of parameters
        //if (list.size() != 1) return;
    for (QString student: list)
    {
        promo->remove(student);
    }
  }
};

/**
 * @brief ControlLer to add student to the Promotion
 * @author Adrien Peytavie
*/
class Controller_AddForm : public AbstractController
{
private:
    Promotion* promo;
public:
    /**
    * @brief Constructor
    */
    Controller_AddForm(Promotion* promo) : promo(promo) {}

    /**
    * @brief Control the adding process of a student
    */
    virtual void control(const QStringList& list) override
    {
        // Check the number of parameters
        if (list.size() != 5) return;

        // Check if the ID already exist
        Student studentOld = promo->find(list[0]);
        if (studentOld.getCardID() != "")
        {
            // Create an error
            QMessageBox::warning(nullptr,"Add Student","The student already exist.");
            return;
        }

        // Check the others parameters not NULL
        if (list[0] == "")
        {
            QMessageBox::warning(nullptr, "Add Student", "The card ID is empty."); return;
        }
        if (list[1] == "")
        {
            QMessageBox::warning(nullptr, "Add Student", "The firstname is empty."); return;
        }
        if (list[2] == "")
        {
            QMessageBox::warning(nullptr, "Add Student", "The lastname is empty."); return;
        }
        if (list[3] == "")
        {
            QMessageBox::warning(nullptr, "Add Student", "The bac is empty."); return;
        }
        if (list[4] == "")
        {
            QMessageBox::warning(nullptr, "Add Student", "The department is empty."); return;
        }

        // Create and add the new student
        Student studentNew(list[0], list[1], list[2], list[3], list[4]);
        promo->add(studentNew);
    }
};

/**
 * @brief ControlLer to remove a student
 * @author Adrien Peytavie
*/
class Controller_DeleteForm : public AbstractController
{
private:
    Promotion* promo;
public:
    /**
    * @brief Constructor
    */
    Controller_DeleteForm(Promotion* promo) : promo(promo) {}

    /**
    * @brief Control the removing process from a student ID
    */
    virtual void control(const QStringList& list) override
    {
        // Check the number of parameters
        if (list.size() != 1) return;

        // Search the student
        Student student = promo->find(list[0]);

        // Check if the student has been found
        if (student.getCardID()!="")
            promo->remove(student);
    }
};
