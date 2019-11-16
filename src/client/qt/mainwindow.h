#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Proxy.h"
#include "Socket.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    Proxy* getProxy();
    std::string getPlayerID();
    bool isLuaPlayer();
    ~MainWindow();

private slots:
    void on_create_match_button_clicked();

    void on_join_match_button_clicked();

    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_okCancelButtons_accepted();

    void on_playerSelectComboBox_currentIndexChanged(int index);

    void on_okCancelButtons_rejected();

    void handleResponseStatus();

signals:

    void waitStatus();


private:
    Ui::MainWindow *ui;
    Proxy* proxy;
    std::string PlayerID;
    bool luaPlayer;
};

#endif // MAINWINDOW_H
