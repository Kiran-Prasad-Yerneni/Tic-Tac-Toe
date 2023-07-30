#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include<sys/socket.h>
#include <arpa/inet.h>

MainWindow::MainWindow(QWidget *parent, int boardSize)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , boardSize(boardSize)
    , pushButtons(boardSize)
    , N(Network())
{
    ui->setupUi(this);
    this->setWindowTitle("Tic Tac Toe");
    ui->stackedWidget->setCurrentIndex(2);

    pushButtons[0] = ui->pushButton_1;
    pushButtons[1] = ui->pushButton_2;
    pushButtons[2] = ui->pushButton_3;
    pushButtons[3] = ui->pushButton_4;
    pushButtons[4] = ui->pushButton_5;
    pushButtons[5] = ui->pushButton_6;
    pushButtons[6] = ui->pushButton_7;
    pushButtons[7] = ui->pushButton_8;
    pushButtons[8] = ui->pushButton_9;

    for (int i = 0; i < 9; ++i)
    {
        pushButtons[i]->setText(QString(" "));
    }

    xo[0] = 'X';
    xo[1] = 'O';

    turn = 0;

    ui->statusbar->showMessage(QString(" "));
}

void MainWindow::newGame()
{
    for (int i = 0; i < 9; i++)
    {
        pushButtons[i]->setText(QString(" "));
        T.board[(i)/3][(i)%3] = ' ';
    }
    ui->statusbar->showMessage(QString("Player 1's Turn"));
    ui->resetbtn->setText(QString("Reset"));
    turn = 0;
    qApp->processEvents();
}

void MainWindow::userPlay(int ind)
{
    pushButtons[ind-1]->setText(QString(xo[turn]));
    T.board[(ind-1)/3][(ind-1)%3] = xo[turn];
    switch(T.gameStatus())
    {
    case gamestate::COMPLETED:
    {
        std::string ans = "Player";
        ans += '1' + turn;
        ans += " Wins!";
        QMessageBox::information(this, "Tic Tac Toe", QString::fromUtf8(ans));
        ui->resetbtn->setText(QString("New Game"));
        qApp->processEvents();
        return;
    }
    case gamestate::TIE:
    {
        QMessageBox::information(this, "Tic Tac Toe", QString("TIE!"));
        ui->resetbtn->setText(QString("RESET"));
        qApp->processEvents();
        return;
    }
    default:
        break;
    }

    turn = !turn;
    std::string pturn = "Player";
    pturn += '1'+turn;
    pturn += "'s Turn";
    ui->statusbar->showMessage(QString::fromUtf8(pturn));
    qApp->processEvents();
}


void MainWindow::localUserPlay()
{
    int ind = sender()->objectName().split("_")[1].toInt();
    userPlay(ind);
}


void MainWindow::multiUserPlay()
{
    if(turn == player)
    {
        int ind = sender()->objectName().split("_")[1].toInt();
        //send(ind)
        N.sendInd(ind);
        userPlay(ind);
    }
    if(T.gameStatus() != gamestate::ONGOING)
        return;
    int ind;
    //recieve(ind)
    ind = N.recieve();
    switch (ind) {
    case -1:
        QMessageBox::information(this, "Tic Tac Toe", "Connection Lost!");
        on_pushButton_home_clicked();
        break;
    case -2:
        newGame();
        if(player == 1)
            multiUserPlay();
        break;
    default:
        userPlay(ind);
        break;
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_exitbtn_clicked()
{
//    close();
    QApplication::quit();
}


void MainWindow::on_resetbtn_clicked()
{
    newGame();
    if(N.isConnected())
    {
        N.sendInd(-2);
        if(player == 1)
            multiUserPlay();
    }
}


void MainWindow::on_pushButton_local_clicked()
{
    newGame();
    for(int i = 0; i < 9; i++)
    {
        pushButtons[i]->disconnect(SIGNAL(clicked()));
    }
    for (int i = 0; i < 9; i++)
    {
        pushButtons[i]->setText(QString(" "));
        connect(pushButtons[i], SIGNAL(clicked()), this, SLOT(localUserPlay()));
    }
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_multi_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Play Online", "Send request?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        ui->stackedWidget->setCurrentIndex(1);
        player = 0;
        //start client
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(0);
        ui->statusbar->showMessage("Connecting....");
        qApp->processEvents();
        player = 1;
        N.createServer();
        QMessageBox::information(this, "Tic Tac Toe", "Connection Successfull!");
    }
    newGame();
    for(int i = 0; i < 9; i++)
    {
        pushButtons[i]->disconnect(SIGNAL(clicked()));
    }
    for (int i = 0; i < 9; i++)
    {
        pushButtons[i]->setText(QString(" "));
        connect(pushButtons[i], SIGNAL(clicked()), this, SLOT(multiUserPlay()));
    }
    if(player == 1)
        multiUserPlay();
}


void MainWindow::on_pushButton_home_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->statusbar->showMessage(" ");
    qApp->processEvents();
    N.closeConnection();
}


void MainWindow::on_pushButton_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_connect_clicked()
{
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ui->IP_4->displayText().toUtf8());
    serverAddr.sin_port = htons(ui->IP_5->displayText().toInt());
    N.setServerAddress(serverAddr);
    //send request to server
    N.createClient();
    QMessageBox::information(this, "Tic Tac Toe", "Connection Successfull!");
    ui->stackedWidget->setCurrentIndex(0);
}

