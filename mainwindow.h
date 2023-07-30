#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QMainWindow>
#include "tictactoe.h"
#include "multiplayer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, int boardSize = 9);
    ~MainWindow();

private slots:
    void newGame();

    void multiUserPlay();

    void userPlay(int ind);

    void localUserPlay();

    void on_exitbtn_clicked();

    void on_resetbtn_clicked();

    void on_pushButton_local_clicked();

    void on_pushButton_multi_clicked();

    void on_pushButton_home_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_connect_clicked();

    void on_actionChange_my_Port_number_triggered();

    void on_actionShow_my_IP_address_triggered();

private:
    Ui::MainWindow *ui;
    int boardSize;
    std::vector<QPushButton *> pushButtons;
    tictactoe T;
    Multiplayer N;
    int turn;
    int player;
    char xo[2];
};
#endif // MAINWINDOW_H
