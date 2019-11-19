#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <json.hpp>
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
    std::string& getPlayerID();
    nlohmann::json& getInitialData();
    void waitForInitialPosition();
    int getWidthSelected();
    int getHeightSelected();
    bool isFullScreen();
    bool isLuaPlayer();
    ~MainWindow();

private slots:
    void on_screen_mode_combo_box_currentIndexChanged(int index);

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

    void on_screen_mode_combo_box_highlighted(int index);

signals:

    void waitStatus();


private:
    Ui::MainWindow *ui;
    Proxy* proxy;
    std::string PlayerID;
    bool luaPlayer;
    nlohmann::json initialData;
    int screen_w;
    int screen_h;
    bool full_screen;
};

#endif // MAINWINDOW_H
