#include <QMessageBox>
#include "Constants.h"
#include "mainwindow.h"
#include <QDialog>
#include "ui_mainwindow.h"
#include <QPixmap>
#include <iostream>
#include <nlohmann/json.hpp>
#include "Proxy.h"
#include "Socket.h"
#include <thread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(this, &MainWindow::waitStatus, this, &MainWindow::handleResponseStatus);

    this->proxy = NULL;
    this->luaPlayer = false;
    this->screen_h = 0;
    this->screen_w = 0;
    this->full_screen = false;
    this->valid_data = false;

    ui->stackedWidget->setCurrentIndex(0);
    QPixmap img("../src/client/qt/header.jpg");
    ui->label->setPixmap(img);
}

std::string& MainWindow::getLuaPath(){
    return this->lua_path;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_create_match_button_clicked() // Crear partida
{
    std::string hostName = ui->hostNameField->text().toStdString();
    std::string serviceName = ui->serviceNameField->text().toStdString();

    try {
        if (ui->screen_mode_combo_box->currentIndex() == 1)
            if (ui->width_line->text().isEmpty() || ui->height_line->text().isEmpty())
                throw std::runtime_error("No puede estar vacio alguno de los tamaños de pantalla");
            else{
                this->screen_h = this->ui->height_line->text().toInt(NULL, 10);
                this->screen_w = this->ui->width_line->text().toInt(NULL, 10);
                this->lua_path = this->ui->lineEdit->text().toStdString();
                full_screen = false;
                std::cout << "LOG - Seleccionada configuracion " << screen_h << " por " << screen_w << std::endl;
            }
        else
            full_screen = true;

        Socket socket(hostName.c_str(), serviceName.c_str());
        proxy = new Proxy(std::move(socket));
        ui->stackedWidget->setCurrentIndex(2);

    } catch (std::runtime_error &e){
        QMessageBox msg(this);
        msg.setText(e.what());
        std::cout << "ERROR - Se produjo error en linea " << __LINE__ << std::endl;
        msg.exec();
    }
}

void MainWindow::on_join_match_button_clicked() // Unirse a partida
{
    std::string hostName = ui->hostNameField->text().toStdString();
    std::string serviceName = ui->serviceNameField->text().toStdString();

    try {
        if (ui->screen_mode_combo_box->currentIndex() == 1)
            if (ui->width_line->text().isEmpty() || ui->height_line->text().isEmpty())
                throw std::runtime_error("No puede estar vacio alguno de los tamaños de pantalla");
            else{
                this->screen_h = this->ui->height_line->text().toInt(NULL, 10);
                this->screen_w = this->ui->width_line->text().toInt(NULL, 10);
                this->lua_path = this->ui->lineEdit->text().toStdString();
                full_screen = false;
                std::cout << "LOG - Seleccionada configuracion " << screen_h << " por " << screen_w << std::endl;
            }
        else
            full_screen = true;

        Socket socket(hostName.c_str(), serviceName.c_str());

        proxy = new Proxy(std::move(socket));

        nlohmann::json msg;
        msg["mode"] = "join";
        std::string msgDump = msg.dump();
        proxy->sendMessage(msgDump);            // Envio mensaje de join
        ui->stackedWidget->setCurrentIndex(1);

        nlohmann::json j = nlohmann::json::parse(proxy->receiveMessage());  // Recibo información de partidas

        int row = 0;

        if (j.empty()){
            QMessageBox m;
            m.setText("No hay partidas disponibles para unirse");
            m.exec();
            ui->stackedWidget->setCurrentIndex(0);
            return;
        }

        for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
            std::string matchName = it.key();
            std::string mapName = it.value()[0].get<std::string>();
            int laps = it.value()[1].get<int>();
            int playersAmount = it.value()[2].get<int>();

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
    } catch (std::runtime_error &e) {
        QMessageBox m(this);
        m.setText(e.what());
        std::cout << "ERROR - Se produjo " << e.what() << " en " << __LINE__ << std::endl;
        m.exec();
    }

}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    try {
        ui->tableWidget->selectRow(row);
        nlohmann::json msg;
        msg["clientId"] = ui->playerNameField->text().toStdString();
        if (ui->playerNameField->text().isEmpty())
            throw std::runtime_error("Campo nombre está vacío");
        PlayerID = msg["clientId"];
        msg["matchName"] = ui->tableWidget->item(row, 0)->text().toStdString();
        std::string dumped = msg.dump();
        this->proxy->sendMessage(dumped);
        std::cout << "LOG - Se envia " << dumped << std::endl;
        emit waitStatus();

    } catch(std::runtime_error &e) {
        QMessageBox m(this);
        m.setText(e.what());
        std::cout << "ERROR - Se produjo " << e.what() << " en " << __LINE__ << std::endl;
        m.exec();
    }

}

Proxy* MainWindow::getProxy() {
    return this->proxy;
}

std::string& MainWindow::getPlayerID(){
    return this->PlayerID;
}

bool MainWindow::isLuaPlayer() {
    return luaPlayer;
}

int MainWindow::getWidthSelected() {
    return this->screen_w;
}

int MainWindow::getHeightSelected() {
    return this->screen_h;
}

bool MainWindow::isFullScreen(){
    return this->full_screen;
}

bool MainWindow::isValidUser() {
    return valid_data;
}

void MainWindow::on_buttonBox_accepted() // Accept en crear partida
{
    try {
        nlohmann::json msg;
        msg["mode"] = "create";
        msg["matchName"] = ui->matchNameField->text().toStdString();
        msg["map"] = ui->comboBox->currentText().toStdString();
        msg["clientId"] = ui->playerNameField_2->text().toStdString();
        this->PlayerID = msg["clientId"];
        msg["playersAmount"] = ui->spinBox->text().toInt();
        msg["raceLaps"] = ui->spinBox_2->text().toInt();
        std::string serializedMsg = msg.dump();

        this->proxy->sendMessage(serializedMsg);
        std::cout << "LOG - Se envia: " << msg.dump() << std::endl;
        emit waitStatus();

    } catch (std::runtime_error &e) {
        QMessageBox m;
        m.setText(e.what());
        std::cout << "ERROR - Se produjo " << e.what() << " en " << __LINE__ << std::endl;
        m.exec();
    }
}

void MainWindow::on_buttonBox_rejected() // Cancel en crear partida
{
    ui->stackedWidget->setCurrentIndex(0);
    proxy->stop();
}

void MainWindow::on_okCancelButtons_accepted() // Accept en partidas disponibles
{
    if (this->ui->tableWidget->selectedRanges().empty()){
        QMessageBox m;
        m.setText("Debe seleccionar alguna fila");
        m.exec();
        return;
    }
    try {
        nlohmann::json msg;
        int row = this->ui->tableWidget->currentRow();
        ui->tableWidget->selectRow(row);
        msg["clientId"] = ui->playerNameField->text().toStdString();
        if (ui->playerNameField->text().isEmpty())
            throw std::runtime_error("Campo nombre está vacío");
        PlayerID = msg["clientId"];
        msg["matchName"] = ui->tableWidget->item(row, 0)->text().toStdString();
        std::string dumped = msg.dump();
        this->proxy->sendMessage(dumped);
        std::cout << "LOG - Se envia " << dumped << std::endl;
        emit waitStatus();

    } catch(std::runtime_error &e){
        QMessageBox q;
        q.setText(e.what());
        std::cout << "ERROR - Se produjo error en " << __LINE__ << std::endl;
        q.exec();
    }

}

void MainWindow::handleResponseStatus(){
    nlohmann::json j = nlohmann::json::parse(proxy->receiveMessage());
    std::cout << "LOG - " << j.dump() << std::endl;
    QMessageBox m;
    switch(j["status"].get<int>()) {
        case VALID:
            this->close();
            valid_data = true;
            break;
        case MATCH_HAS_STARTED:
            m.setText("La partida está en progreso");
            m.exec();
            break;
        case MATCH_EQUAL_NAMED:
            m.setText("Ya existe una partida con ese nombre");
            m.exec();
            break;
        case CLIENT_EQUAL_NAMED:
            m.setText("Ya existe un cliente con ese nombre");
            m.exec();
            this->ui->stackedWidget->setCurrentWidget(this->ui->createScreen);
            break;
    }
}

nlohmann::json& MainWindow::getInitialData(){
    return this->initialData;
}

void MainWindow::on_okCancelButtons_rejected() // Cancel en partidas disponibles
{
    ui->stackedWidget->setCurrentIndex(0);
    proxy->stop();
}

void MainWindow::on_playerSelectComboBox_currentIndexChanged(int index) // Selecciona jugador inicial
{
    if (index == 0)
        this->luaPlayer = false;
    else
        this->luaPlayer = true;
}

void MainWindow::on_screen_mode_combo_box_highlighted(int index)
{
    if (index == 0){
        this->ui->height_line->setEnabled(false);
        this->ui->width_line->setEnabled(false);
    } else if (index == 1){
        this->ui->height_line->setEnabled(true);
        this->ui->width_line->setEnabled(true);
    }
}

void MainWindow::on_screen_mode_combo_box_currentIndexChanged(int index)
{
    if (index == 0){
        this->ui->height_line->setEnabled(false);
        this->ui->width_line->setEnabled(false);
    } else if (index == 1){
        this->ui->height_line->setEnabled(true);
        this->ui->width_line->setEnabled(true);
    }
}
