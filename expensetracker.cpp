// expensetracker.cpp

#include "expensetracker.h"
#include <QInputDialog>

ExpenseTracker::ExpenseTracker(QWidget *parent)
    : QWidget(parent)
{
    expenseList = new QListWidget(this);
    expenseList->setStyleSheet("QListWidget {"
                               "    background-color: #ECEFF1;"
                               "    border: 1px solid #B0BEC5;"
                               "    border-radius: 5px;"
                               "}"
                               "QListWidget::item {"
                               "    background-color: #FFFFFF;"
                               "    padding: 10px;"
                               "    margin-bottom: 5px;"
                               "    border: 1px solid #B0BEC5;"
                               "    border-radius: 5px;"
                               "}"
                               "QListWidget::item:hover {"
                               "    background-color: #E0E0E0;"
                               "}"
                               "QListWidget::item:selected {"
                               "    background-color: #B0BEC5;"
                               "    color: white;"
                               "}");

    QLabel *expenseNameLabel = new QLabel("Expense Name:", this);
    expenseNameInput = new QLineEdit(this);

    QLabel *costLabel = new QLabel("Cost ($):", this);
    costInput = new QLineEdit(this);

    QLabel *categoryLabel = new QLabel("Category:", this);
    categoryComboBox = new QComboBox(this);

    QLabel *dateTimeLabel = new QLabel("Date and Time:", this);
    dateTimeEdit = new QDateTimeEdit(this);

    addButton = new QPushButton("Add Expense", this);
    editButton = new QPushButton("Edit Expense", this);
    deleteButton = new QPushButton("Delete Expense", this);
    sortButton = new QPushButton("Sort Expenses", this);

    totalLabel = new QLabel("Total: ₹0.00", this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *inputLayout = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    inputLayout->addWidget(expenseNameLabel);
    inputLayout->addWidget(expenseNameInput);
    inputLayout->addWidget(costLabel);
    inputLayout->addWidget(costInput);
    inputLayout->addWidget(categoryLabel);
    inputLayout->addWidget(categoryComboBox);
    inputLayout->addWidget(dateTimeLabel);
    inputLayout->addWidget(dateTimeEdit);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(sortButton);

    mainLayout->addWidget(expenseList);
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(totalLabel);

    populateCategories();

    addButton->setStyleSheet("QPushButton {"
                             "    background-color: #90A4AE;"
                             "    color: white;"
                             "    border: none;"
                             "    padding: 10px 20px;"
                             "    border-radius: 5px;"
                             "}"
                             "QPushButton:hover {"
                             "    background-color: #AEBFC7;"
                             "}"
                             "QPushButton:focus {"
                             "    outline: none;"
                             "    border: 2px solid #607D8B;"
                             "}");

    editButton->setStyleSheet("QPushButton {"
                              "    background-color: #90A4AE;"
                              "    color: white;"
                              "    border: none;"
                              "    padding: 10px 20px;"
                              "    border-radius: 5px;"
                              "}"
                              "QPushButton:hover {"
                              "    background-color: #AEBFC7;"
                              "}"
                              "QPushButton:focus {"
                              "    outline: none;"
                              "    border: 2px solid #607D8B;"
                              "}");

    deleteButton->setStyleSheet("QPushButton {"
                                "    background-color: #90A4AE;"
                                "    color: white;"
                                "    border: none;"
                                "    padding: 10px 20px;"
                                "    border-radius: 5px;"
                                "}"
                                "QPushButton:hover {"
                                "    background-color: #7899A2;"
                                "}"
                                "QPushButton:focus {"
                                "    outline: none;"
                                "    border: 2px solid #90A4AE;"
                                "}");

    sortButton->setStyleSheet("QPushButton {"
                              "    background-color: #90A4AE;"
                              "    color: white;"
                              "    border: none;"
                              "    padding: 10px 20px;"
                              "    border-radius: 5px;"
                              "}"
                              "QPushButton:hover {"
                              "    background-color: #AEBFC7;"
                              "}"
                              "QPushButton:focus {"
                              "    outline: none;"
                              "    border: 2px solid #607D8B;"
                              "}");

    connect(addButton, &QPushButton::clicked, this, &ExpenseTracker::addExpense);
    connect(editButton, &QPushButton::clicked, this, &ExpenseTracker::editExpense);
    connect(deleteButton, &QPushButton::clicked, this, &ExpenseTracker::deleteExpense);
    connect(sortButton, &QPushButton::clicked, this, &ExpenseTracker::sortExpenses);
}
void ExpenseTracker::populateCategories()
{
    categoryComboBox->addItem("Food");
    categoryComboBox->addItem("Transportation");
    categoryComboBox->addItem("Utilities");
    // Add more categories as needed.
}

void ExpenseTracker::addExpense()
{
    QString expenseName = expenseNameInput->text();
    QString costText = costInput->text();
    QString category = categoryComboBox->currentText();
    QDateTime dateTime = dateTimeEdit->dateTime();

    if (!expenseName.isEmpty() && !costText.isEmpty()) {
        double cost = costText.toDouble();
        expenseList->addItem(dateTime.toString("yyyy-MM-dd hh:mm") + " - " +
                             expenseName + " - ₹" + QString::number(cost) + " (" + category + ")");
        expenseNameInput->clear();
        costInput->clear();
        updateTotal();
    }
}

void ExpenseTracker::editExpense()
{
    QListWidgetItem *selectedItem = expenseList->currentItem();
    if (selectedItem) {
        QString editedText = QInputDialog::getText(this, "Edit Expense", "Enter the edited expense:", QLineEdit::Normal, selectedItem->text());
        if (!editedText.isEmpty()) {
            selectedItem->setText(editedText);
            updateTotal();
        }
    }
}

void ExpenseTracker::deleteExpense()
{
    QListWidgetItem *selectedItem = expenseList->currentItem();
    if (selectedItem) {
        delete selectedItem;
        updateTotal();
    }
}

void ExpenseTracker::sortExpenses()
{
    expenseList->sortItems(Qt::AscendingOrder);
}

void ExpenseTracker::updateTotal()
{
    double total = 0.0;
    for (int i = 0; i < expenseList->count(); ++i) {
        QString itemText = expenseList->item(i)->text();
        QStringList parts = itemText.split(" - $");
        if (parts.size() == 2) {
            total += parts[1].section(" ", 0, 0).toDouble();
        }
    }

    totalLabel->setText("Total: ₹" + QString::number(total, 'f', 2));
}
