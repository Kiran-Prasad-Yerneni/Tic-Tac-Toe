#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Tic Tac Toe");

    pushButtons[0] = ui->pushButton_1;
    pushButtons[1] = ui->pushButton_2;
    pushButtons[2] = ui->pushButton_3;
    pushButtons[3] = ui->pushButton_4;
    pushButtons[4] = ui->pushButton_5;
    pushButtons[5] = ui->pushButton_6;
    pushButtons[6] = ui->pushButton_7;
    pushButtons[7] = ui->pushButton_8;
    pushButtons[8] = ui->pushButton_9;

    xo[0] = 'X';
    xo[1] = 'O';

    turn = 0;

    for (int i = 0; i < 9; ++i)
    {
        pushButtons[i]->setText(QString(" "));
        connect(pushButtons[i], SIGNAL(clicked()), this, SLOT(userPlayed()));
    }
    ui->result->setText(QString("Player1's Turn"));
}

void MainWindow::updateGUI()
{
    int i = sender()->objectName().split("_")[1].toInt();
    pushButtons[i-1]->setText(QString("O"));
//    button->setText(QString(T.board[i][j]));

}

void MainWindow::userPlayed()
{
    int i = sender()->objectName().split("_")[1].toInt();
    pushButtons[i-1]->setText(QString(xo[turn]));
    T.board[(i-1)/3][(i-1)%3] = xo[turn];

    switch(T.gameStatus())
    {
    case gamestate::COMPLETED:
    {
        std::string ans = "Player";
        ans += '1' + turn;
        ans += " Wins!";
        ui->result->setText(QString::fromUtf8(ans));
        return;
    }
    case gamestate::TIE:
    {
        ui->result->setText(QString("TIE!"));
        return;
    }
    default:
        break;
    }

    turn = !turn;
    std::string pturn = "Player";
    pturn += '1'+turn;
    pturn += "'s Turn";
    ui->result->setText(QString::fromUtf8(pturn));
}

MainWindow::~MainWindow()
{
    delete ui;
}



