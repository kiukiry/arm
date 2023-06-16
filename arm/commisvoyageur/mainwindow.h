// mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QCalendarWidget>
#include <QDate>
#include <QTableView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <random>

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
MainWindow(QWidget *parent = nullptr);

private slots:
void createRequest();
void switchToNextDay();
void occupyDay();
void switchToRequestsTable();

private:
QPushButton *m_createButton;
QPushButton *m_nextDayButton;
QLabel *m_calendarLabel;
QCalendarWidget *m_calendar;
QLabel *m_fioLabel;
QLineEdit *m_fioEdit;
QLabel *m_phoneLabel;
QLineEdit *m_phoneEdit;
QLabel *m_addressLabel;
QLineEdit *m_addressEdit;
QLabel *m_visitLabel;
QLineEdit *m_visitEdit;
QPushButton *m_occupyButton;
QTableView *m_tableView;
QStandardItemModel *m_model;

void setupUi();
};

#endif // MAINWINDOW_H
