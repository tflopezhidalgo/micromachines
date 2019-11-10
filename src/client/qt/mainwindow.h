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
    explicit MainWindow(Proxy* proxy);
    explicit MainWindow(QWidget *parent = 0);
    Proxy* getProxy();
    std::string getPlayerID();
    ~MainWindow();

private slots:
    void on_create_match_button_clicked();

    void on_join_match_button_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_buttonBox_2_accepted();

    void on_buttonBox_2_rejected();

    void on_okCancelButtons_accepted();

private:
    Ui::MainWindow *ui;
    Proxy* proxy;
    std::string PlayerID;
};

#endif // MAINWINDOW_H
