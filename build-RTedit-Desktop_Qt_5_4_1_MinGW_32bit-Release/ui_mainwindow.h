/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "GraphicsSlice.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionOpen_Folder;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *infoBox;
    QTreeWidget *FileTree;
    QTabWidget *Tabs;
    QWidget *Header;
    QHBoxLayout *horizontalLayout_4;
    QTableWidget *tableWidget;
    QWidget *Orthog;
    QGridLayout *gridLayout;
    GraphicsSlice *viewTl;
    QOpenGLWidget *viewTr;
    GraphicsSlice *viewBl;
    GraphicsSlice *viewBr;
    QWidget *Transverse;
    QHBoxLayout *horizontalLayout_2;
    GraphicsSlice *viewAxial;
    QMenuBar *menuBar;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(602, 456);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionOpen_Folder = new QAction(MainWindow);
        actionOpen_Folder->setObjectName(QStringLiteral("actionOpen_Folder"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(1);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(1, 1, 1, 1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        infoBox = new QGroupBox(centralWidget);
        infoBox->setObjectName(QStringLiteral("infoBox"));
        infoBox->setMinimumSize(QSize(0, 75));

        verticalLayout_2->addWidget(infoBox);

        FileTree = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        FileTree->setHeaderItem(__qtreewidgetitem);
        FileTree->setObjectName(QStringLiteral("FileTree"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FileTree->sizePolicy().hasHeightForWidth());
        FileTree->setSizePolicy(sizePolicy);
        FileTree->setMaximumSize(QSize(150, 16777215));
        FileTree->header()->setVisible(false);

        verticalLayout_2->addWidget(FileTree);


        horizontalLayout->addLayout(verticalLayout_2);

        Tabs = new QTabWidget(centralWidget);
        Tabs->setObjectName(QStringLiteral("Tabs"));
        Header = new QWidget();
        Header->setObjectName(QStringLiteral("Header"));
        horizontalLayout_4 = new QHBoxLayout(Header);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(Header);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);
        tableWidget->setMinimumSize(QSize(150, 0));
        tableWidget->setMaximumSize(QSize(16777215, 16777215));
        tableWidget->setBaseSize(QSize(100, 0));
        tableWidget->setSortingEnabled(true);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget->horizontalHeader()->setMinimumSectionSize(5);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setMinimumSectionSize(5);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableWidget->verticalHeader()->setStretchLastSection(false);

        horizontalLayout_4->addWidget(tableWidget);

        Tabs->addTab(Header, QString());
        Orthog = new QWidget();
        Orthog->setObjectName(QStringLiteral("Orthog"));
        gridLayout = new QGridLayout(Orthog);
        gridLayout->setSpacing(1);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        viewTl = new GraphicsSlice(Orthog);
        viewTl->setObjectName(QStringLiteral("viewTl"));
        sizePolicy1.setHeightForWidth(viewTl->sizePolicy().hasHeightForWidth());
        viewTl->setSizePolicy(sizePolicy1);
        viewTl->setAutoFillBackground(true);
        viewTl->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        viewTl->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        viewTl->setBackgroundBrush(brush);

        gridLayout->addWidget(viewTl, 0, 0, 1, 1);

        viewTr = new QOpenGLWidget(Orthog);
        viewTr->setObjectName(QStringLiteral("viewTr"));
        sizePolicy1.setHeightForWidth(viewTr->sizePolicy().hasHeightForWidth());
        viewTr->setSizePolicy(sizePolicy1);
        viewTr->setAutoFillBackground(true);

        gridLayout->addWidget(viewTr, 0, 1, 1, 1);

        viewBl = new GraphicsSlice(Orthog);
        viewBl->setObjectName(QStringLiteral("viewBl"));
        viewBl->setAutoFillBackground(true);
        viewBl->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        viewBl->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        viewBl->setBackgroundBrush(brush);

        gridLayout->addWidget(viewBl, 1, 0, 1, 1);

        viewBr = new GraphicsSlice(Orthog);
        viewBr->setObjectName(QStringLiteral("viewBr"));
        viewBr->setAutoFillBackground(true);
        viewBr->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        viewBr->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        viewBr->setBackgroundBrush(brush);

        gridLayout->addWidget(viewBr, 1, 1, 1, 1);

        Tabs->addTab(Orthog, QString());
        Transverse = new QWidget();
        Transverse->setObjectName(QStringLiteral("Transverse"));
        horizontalLayout_2 = new QHBoxLayout(Transverse);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        viewAxial = new GraphicsSlice(Transverse);
        viewAxial->setObjectName(QStringLiteral("viewAxial"));
        viewAxial->setAutoFillBackground(true);
        viewAxial->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        viewAxial->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        viewAxial->setBackgroundBrush(brush);

        horizontalLayout_2->addWidget(viewAxial);

        Tabs->addTab(Transverse, QString());

        horizontalLayout->addWidget(Tabs);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 602, 18));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionOpen_Folder);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);

        Tabs->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "RTedit", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open Single", 0));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindow", "Open a Single File", 0));
#endif // QT_NO_TOOLTIP
        actionExit->setText(QApplication::translate("MainWindow", "Quit", 0));
        actionOpen_Folder->setText(QApplication::translate("MainWindow", "Open Folder", 0));
#ifndef QT_NO_TOOLTIP
        actionOpen_Folder->setToolTip(QApplication::translate("MainWindow", "Open a Folder of DICOM Files", 0));
#endif // QT_NO_TOOLTIP
        infoBox->setTitle(QApplication::translate("MainWindow", "Selected Item", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Tag", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "VR", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "VL", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Decription", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Value", 0));
        Tabs->setTabText(Tabs->indexOf(Header), QApplication::translate("MainWindow", "DICOM Header", 0));
        Tabs->setTabText(Tabs->indexOf(Orthog), QApplication::translate("MainWindow", "Orthogonal Views", 0));
        Tabs->setTabText(Tabs->indexOf(Transverse), QApplication::translate("MainWindow", "Transverse View", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
