// expensetracker.h

#ifndef EXPENSETRACKER_H
#define EXPENSETRACKER_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class ExpenseTracker : public QWidget
{
    Q_OBJECT

public:
    ExpenseTracker(QWidget *parent = nullptr);

private slots:
    void addExpense();
    void editExpense();
    void deleteExpense();
    void sortExpenses();
    void updateTotal();

private:
    QListWidget *expenseList;
    QLineEdit *expenseNameInput;
    QLineEdit *costInput;
    QComboBox *categoryComboBox;
    QDateTimeEdit *dateTimeEdit;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *sortButton;
    QLabel *totalLabel;

    void populateCategories();
};

#endif // EXPENSETRACKER_H
