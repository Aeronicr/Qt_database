#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSqlQuery"
#include "QtSql/QSqlDatabase"
#include <QSqlTableModel>
#include <QDebug>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\Goncharenko.db");
    db.open();
    QSqlQuery query(db);
    db.setDatabaseName("goncharenko_db");
    ui->user->setVisible(false);
    ui->admin->setVisible(false);
    ui->tableView->setSortingEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QSqlDatabase db;
    QSqlQuery query(db);
    QSqlQueryModel * model = new QSqlQueryModel();
        query.exec("SELECT id_order, title, producer, price FROM orders");
        model->setQuery(query);
        ui->tableView->setModel(model);
        ui->tableView->setSortingEnabled(true);
            query.exec("SELECT sum(price),max(price),min(price),avg(price) FROM orders;");
            query.next();
            QString sum;
            QString avg;
            QString min;
            QString max;
            sum = query.value(0).toString();
            max = query.value(1).toString();
            min = query.value(2).toString();
            avg = query.value(3).toString();
            ui->textEdit->clear();
            ui->textEdit->append("sum: " + sum);
            ui->textEdit->append("max: " + max);
            ui->textEdit->append("min: " + min);
            ui->textEdit->append("avg: " + avg);
}

void MainWindow::on_pushButton_2_clicked()
{
    QSqlDatabase db;
    QSqlQuery query(db);
    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    query.prepare(QString("SELECT priority FROM info where login = %1 and password = %2").arg(login).arg(password));
    query.exec();
    while (query.next()) {
        if(query.value(0).toString() == "2"){
            ui->user->setVisible(true);
            ui->admin->setVisible(false);
            ui->groupBox_3->setVisible(false);
            ui->pushButton_3->setVisible(false);
            ui->groupBox_2->setVisible(false);
            ui->groupBox_4->setVisible(false);
        }else if (query.value(0).toString() == "3") {
            ui->user->setVisible(true);
            ui->admin->setVisible(false);
            ui->groupBox_3->setVisible(false);
            ui->pushButton_3->setVisible(false);
            ui->groupBox_2->setVisible(false);
            ui->groupBox_4->setVisible(false);
        }else if (query.value(0).toString() == "1") {
            ui->user->setVisible(true);
            ui->admin->setVisible(true);
            ui->groupBox_3->setVisible(false);
            ui->pushButton_3->setVisible(false);
            ui->groupBox_2->setVisible(false);
            ui->groupBox_4->setVisible(false);
    }

    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QSqlDatabase db;
    QSqlQuery qry;
    QString id_order = ui->lineEdit_3->text();
    QString title = ui->lineEdit_4->text();
    QString producer =ui->lineEdit_5->text();
    QString price = ui->lineEdit_6->text();
    qry.exec("INSERT INTO orders (id_order, title, producer, price)VALUES('"+id_order+"','"+title+"','"+producer+"','"+price+"')");
    qry.exec();
    qDebug()<<qry.exec()<<endl;
}


void MainWindow::on_pushButton_4_clicked()
{
    QSqlDatabase db;
    QSqlQuery qry;
    qry.prepare(QString("DELETE FROM orders WHERE id_order = %1").arg(ui->lineEdit_7->text()));
    qry.exec();
    qDebug()<<qry.exec()<<endl;
}


void MainWindow::on_radioButton_clicked()
{
    ui->groupBox_2->setVisible(true);
    ui->groupBox_3->setVisible(false);
    ui->lineEdit_3->setVisible(true);
    ui->pushButton_3->setVisible(true);
    ui->pushButton_5->setVisible(false);
    ui->groupBox_4->setVisible(false);
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->groupBox_2->setVisible(true);
    ui->groupBox_3->setVisible(false);
    ui->lineEdit_3->setVisible(true);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_5->setVisible(true);
    ui->groupBox_4->setVisible(false);
}

void MainWindow::on_radioButton_3_clicked()
{
    ui->groupBox_2->setVisible(false);
    ui->groupBox_3->setVisible(true);
    ui->groupBox_4->setVisible(false);
}

void MainWindow::on_radioButton_4_clicked()
{
    ui->groupBox_2->setVisible(false);
    ui->groupBox_3->setVisible(false);
    ui->groupBox_4->setVisible(true);
}

void MainWindow::on_pushButton_5_clicked()
{

    QSqlDatabase db;
    QSqlQuery qry;
    QString id_order = ui->lineEdit_3->text();
    QString title = ui->lineEdit_4->text();
    QString producer =ui->lineEdit_5->text();
    QString price = ui->lineEdit_6->text();
    qry.prepare(QString("UPDATE orders SET title = '"+title+"', producer='"+producer+"', price ='"+price+"' where id_order='"+id_order+"'"));
    qry.exec();
    qDebug()<<qry.exec()<<endl;
}



void MainWindow::on_radioButton_5_clicked()
{
    QSqlDatabase db;
    QSqlQuery query(db);
    QSqlQueryModel * model = new QSqlQueryModel();
    query.exec("SELECT * FROM orders ORDER BY id_order DESC");
    model->setQuery(query);
    ui->tableView->setModel(model);
}

void MainWindow::on_radioButton_6_clicked()
{
    QSqlDatabase db;
    QSqlQuery query(db);
    QSqlQueryModel * model = new QSqlQueryModel();
    query.exec("SELECT * FROM orders ORDER BY title");
    model->setQuery(query);
    ui->tableView->setModel(model);
}

void MainWindow::on_radioButton_7_clicked()
{
    QSqlDatabase db;
    QSqlQuery query(db);
    QSqlQueryModel * model = new QSqlQueryModel();
    query.exec("SELECT * FROM orders ORDER BY producer");
    model->setQuery(query);
    ui->tableView->setModel(model);
}

void MainWindow::on_radioButton_8_clicked()
{
    QSqlDatabase db;
    QSqlQuery query(db);
    QSqlQueryModel * model = new QSqlQueryModel();
    query.exec("SELECT * FROM orders ORDER BY price DESC");
    model->setQuery(query);
    ui->tableView->setModel(model);
}

void MainWindow::on_radioButton_9_clicked()
{
    QSqlDatabase db;
    QSqlQuery query(db);
    QSqlQueryModel * model = new QSqlQueryModel();
    query.exec("SELECT * FROM orders ORDER BY price");
    model->setQuery(query);
    ui->tableView->setModel(model);
}

void MainWindow::on_pushButton_8_clicked()
{
    QSqlDatabase db;
    QSqlQuery query(db);
    QSqlQueryModel * model = new QSqlQueryModel();
    query.exec("select * from sqlite_master where type = 'table'");
    model->setQuery(query);
    ui->tableView_2->setModel(model);
}

void MainWindow::on_pushButton_6_clicked()
{
    QSqlDatabase db;
    QSqlQuery query(db);
    query.exec(QString("DROP TABLE IF EXISTS %1").arg(ui->lineEdit_8->text()));
    qDebug()<<query.exec()<<endl;
}

void MainWindow::on_pushButton_7_clicked()
{
    QSqlDatabase db;
    QSqlQuery query(db);
    query.exec(QString("CREATE TABLE %1 (test_id INTEGER PRIMARY KEY NOT NULL UNIQUE)").arg(ui->lineEdit_8->text()));
    qDebug()<<query.exec()<<endl;
}
