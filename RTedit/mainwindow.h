#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void on_actionOpen_triggered();    

    void on_actionExit_triggered();

public slots:
    void addTableValue(QString, QString, int, QString, QString);

private:
    Ui::MainWindow *ui;
    void setupTable();
};

#endif // MAINWINDOW_H
