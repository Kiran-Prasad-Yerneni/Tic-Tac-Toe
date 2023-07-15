#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QMainWindow>
#include "tictactoe.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    tictactoe T;
    int turn;
    char xo[2];

private slots:
    void newGame();
    void userPlayed();

private:
    Ui::MainWindow *ui;
    QPushButton *pushButtons[9];
};
#endif // MAINWINDOW_H
