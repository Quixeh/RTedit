#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void resizeEvent(QResizeEvent* event);
    void updateViews();


private slots:
    void on_actionOpen_triggered();    
    void on_actionExit_triggered();
    void on_Tabs_currentChanged(int index);
    void on_actionOpen_Folder_triggered();

public slots:
    void addTableValue(QString, QString, int, QString, QString);
    void clearSlot();
    void updateTransverseViewsSlot();
    void updateCoronalViewsSlot();
    void updateSaggitalViewsSlot();

private:
    Ui::MainWindow *ui;
    void setupTable();
    void updateTransverseViews();
    void updateCoronalViews();
    void updateSaggitalViews();

    QGraphicsScene* sceneTl;
    QGraphicsScene* sceneBl;
    QGraphicsScene* sceneTr;
    QGraphicsScene* sceneBr;

    QGraphicsPixmapItem itemBl;
    QGraphicsPixmapItem itemBr;
    QGraphicsPixmapItem itemTl;

};

#endif // MAINWINDOW_H
