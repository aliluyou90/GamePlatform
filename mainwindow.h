#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "gameserver.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_start_pushButton_clicked();

    void on_exit_pushButton_clicked();

    void on_shutDown_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    GameServer *server;
};

#endif // MAINWINDOW_H
