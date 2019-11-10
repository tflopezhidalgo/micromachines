#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <iostream>
#include <nlohmann/json.hpp>
#include "Proxy.h"
#include "Socket.h"

MainWindow::MainWindow(Proxy* proxy){
    this->proxy = proxy;
    MainWindow();
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    QPixmap img("/home/tomas/micromachines/header.jpg");
    ui->label->setPixmap(img);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_create_match_button_clicked()
{
    std::string hostName = ui->hostNameField->text().toStdString();
    std::string serviceName = ui->serviceNameField->text().toStdString();

    Socket socket(hostName.c_str(), serviceName.c_str());

    proxy = new Proxy(std::move(socket));
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_join_match_button_clicked()
{
    std::string hostName = ui->hostNameField->text().toStdString();
    std::string serviceName = ui->serviceNameField->text().toStdString();

    Socket socket(hostName.c_str(), serviceName.c_str());

    proxy = new Proxy(std::move(socket));

    nlohmann::json msg;
    msg["mode"] = "join";
    std::string msgDump = msg.dump();
    proxy->sendMessage(msgDump);
    ui->stackedWidget->setCurrentIndex(1);

    QStringList columnas;
    columnas << "Nombre partida" << "Cantidad de jugadores" << "Mapa" << "Cantidad de vueltas";
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(columnas);

    nlohmann::json j = nlohmann::json::parse(proxy->receiveMessage());

    std::cout << "Se recibe " << j.dump() << std::endl;

    int row = 0;

    for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
        std::string matchName = it.key();
        std::string mapName = it.value()[0].get<std::string>();
        int playersAmount = it.value()[1].get<int>();
        int laps = it.value()[2].get<int>();

        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        QTableWidgetItem* matchItem = new QTableWidgetItem(QString::fromStdString(matchName));
        matchItem->setFlags(matchItem->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(row, 0, matchItem);

        QTableWidgetItem* playersAmountItem = new QTableWidgetItem(QString::number(playersAmount));
        playersAmountItem->setFlags(playersAmountItem->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(row, 1, playersAmountItem);

        QTableWidgetItem* mapItem = new QTableWidgetItem(QString::fromStdString(mapName));
        mapItem->setFlags(mapItem->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(row, 2, mapItem);

        QTableWidgetItem* lapsItem = new QTableWidgetItem(QString::number(laps));
        lapsItem->setFlags(lapsItem->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(row++, 3, lapsItem);
    }
}


void MainWindow::on_tableWidget_cellClicked(int row, int column)
{

}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    ui->tableWidget->selectRow(row);
    nlohmann::json msg;
    msg["clientId"] = ui->playerNameField->text().toStdString();
    PlayerID = msg["clientId"];
    msg["matchName"] = ui->tableWidget->item(row, 0)->text().toStdString();
    std::string dumped = msg.dump();
    this->proxy->sendMessage(dumped);
    std::cout << "Se envia " << dumped << std::endl;

    close();
}

Proxy* MainWindow::getProxy() {
    return this->proxy;
}

std::string MainWindow::getPlayerID(){
    return this->PlayerID;
}


void MainWindow::on_buttonBox_accepted()
{
    nlohmann::json msg;
    msg["mode"] = "create";
    msg["matchName"] = ui->matchNameField->text().toStdString();
    //msg["map"] = ui->comboBox->currentText().toStdString();
    msg["map"] = "simple";
    msg["clientId"] = ui->playerNameField_2->text().toStdString();
    this->PlayerID = msg["clientId"];
    msg["playersAmount"] = ui->spinBox->text().toInt();
    msg["raceLaps"] = ui->spinBox_2->text().toInt();
    std::string serializedMsg = msg.dump();

    std::cout << "Se envia: " << msg.dump() << std::endl;

    this->proxy->sendMessage(serializedMsg);
    ui->stackedWidget->setCurrentIndex(3);

    this->proxy->receiveMessage();

    close();
}

void MainWindow::on_buttonBox_rejected()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_buttonBox_2_accepted()
{

}

void MainWindow::on_buttonBox_2_rejected()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_okCancelButtons_accepted()
{
    close();
}
