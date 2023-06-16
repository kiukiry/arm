#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
{
setupUi();
}

void MainWindow::setupUi()
{
// Создание кнопок и других элементов интерфейса
m_createButton = new QPushButton("Создать заявку", this);
m_createButton->setGeometry(10, 10, 150, 40);
m_nextDayButton = new QPushButton("Следующий день", this);
m_nextDayButton->setGeometry(170, 10, 150, 40);
m_calendarLabel = new QLabel(this);
m_calendarLabel->setText("Выберите день:");
m_calendarLabel->setGeometry(10, 70, 120, 30);

m_calendar = new QCalendarWidget(this);
m_calendar->setGeometry(10, 100, 310, 200);

m_fioLabel = new QLabel(this);
m_fioLabel->setText("ФИО:");
m_fioLabel->setGeometry(530, 100, 120, 30);

m_fioEdit = new QLineEdit(this);
m_fioEdit->setGeometry(700, 100, 250, 30);

m_phoneLabel = new QLabel(this);
m_phoneLabel->setText("Номер телефона:");
m_phoneLabel->setGeometry(530, 140, 120, 30);

m_phoneEdit = new QLineEdit(this);
m_phoneEdit->setGeometry(700, 140, 250, 30);

m_addressLabel = new QLabel(this);
m_addressLabel->setText("Адрес проживания:");
m_addressLabel->setGeometry(530, 180, 120, 30);

m_addressEdit = new QLineEdit(this);
m_addressEdit->setGeometry(700, 180, 250, 30);

m_visitLabel = new QLabel(this);
m_visitLabel->setText("Приезд мастера:");
m_visitLabel->setGeometry(530, 220, 120, 30);

m_visitEdit = new QLineEdit(this);
m_visitEdit->setGeometry(700, 220, 250, 30);

m_occupyButton = new QPushButton("Занять день", this);
m_occupyButton->setGeometry(330, 260, 150, 40);




// Создание таблицы для отображения заявок
m_tableView = new QTableView(this);
m_tableView->setGeometry(10, 350, 1000, 350);

// Создание модели данных для таблицы
m_model = new QStandardItemModel(0, 4, this);
m_model->setHeaderData(0, Qt::Horizontal, "Дата");
m_model->setHeaderData(1, Qt::Horizontal, "ФИО");
m_model->setHeaderData(2, Qt::Horizontal, "Номер телефона");
m_model->setHeaderData(3, Qt::Horizontal, "Адрес");

m_tableView->setModel(m_model);

// Подключение обработчиков событий
connect(m_createButton, &QPushButton::clicked, this, &MainWindow::createRequest);
connect(m_nextDayButton, &QPushButton::clicked, this, &MainWindow::switchToNextDay);
connect(m_occupyButton, &QPushButton::clicked, this, &MainWindow::occupyDay);


// Начальная настройка интерфейса
setFixedSize(1080, 720);
setWindowTitle("Заявки на ремонт");
}

void MainWindow::createRequest()
{
// Проверка на пустоту полей ввода
if (m_fioEdit->text().isEmpty() || m_phoneEdit->text().isEmpty() || m_addressEdit->text().isEmpty() || m_visitEdit->text().isEmpty()) {
QMessageBox::warning(this, "Ошибка", "Не все поля заполнены");
return;
}

// Добавление данных в таблицу
int row = m_model->rowCount();
m_model->insertRow(row);
m_model->setData(m_model->index(row, 0), m_calendar->selectedDate().toString("dd.MM.yyyy"));
m_model->setData(m_model->index(row, 1), m_fioEdit->text());
m_model->setData(m_model->index(row, 2), m_phoneEdit->text());
m_model->setData(m_model->index(row, 3), m_addressEdit->text());

// Очистка полей ввода
m_fioEdit->clear();
m_phoneEdit->clear();
m_addressEdit->clear();
m_visitEdit->clear();

// Сообщение об успешном добавлении заявки
QMessageBox::information(this, "Успех", "Заявка успешно создана");
}

void MainWindow::switchToNextDay()
{
// Переход на следующий день в календаре
QDate date = m_calendar->selectedDate().addDays(1);
m_calendar->setSelectedDate(date);
}

void MainWindow::occupyDay()
{
// Проверка на пустоту поля календаря
if (!m_calendar->selectedDate().isValid()) {
QMessageBox::warning(this, "Ошибка", "Не выбран день");
return;
}
// Генерация случайной даты приезда мастера
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0,0);
int days = dis(gen);
QDate visitDate = m_calendar->selectedDate().addDays(days);
m_visitEdit->setText(visitDate.toString("dd.MM.yyyy"));
}

void MainWindow::switchToRequestsTable()
{
// Переключение на вкладку с таблицей заявок
setCentralWidget(m_tableView);
}
