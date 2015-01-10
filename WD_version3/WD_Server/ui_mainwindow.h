/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_exit;
    QAction *action_help;
    QAction *action_about;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_response;
    QListWidget *listWidget_response;
    QVBoxLayout *verticalLayout;
    QLabel *label_request;
    QListWidget *listWidget_request;
    QSpacerItem *horizontalSpacer_3;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *help;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(881, 477);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(638, 440));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        MainWindow->setFont(font);
        MainWindow->setFocusPolicy(Qt::StrongFocus);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/images/blink.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        action_exit = new QAction(MainWindow);
        action_exit->setObjectName(QStringLiteral("action_exit"));
        action_help = new QAction(MainWindow);
        action_help->setObjectName(QStringLiteral("action_help"));
        action_about = new QAction(MainWindow);
        action_about->setObjectName(QStringLiteral("action_about"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMinimumSize(QSize(553, 378));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_response = new QLabel(centralWidget);
        label_response->setObjectName(QStringLiteral("label_response"));
        QFont font1;
        font1.setPointSize(20);
        label_response->setFont(font1);
        label_response->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_response);

        listWidget_response = new QListWidget(centralWidget);
        listWidget_response->setObjectName(QStringLiteral("listWidget_response"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(11);
        listWidget_response->setFont(font2);

        verticalLayout_2->addWidget(listWidget_response);


        gridLayout->addLayout(verticalLayout_2, 0, 3, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_request = new QLabel(centralWidget);
        label_request->setObjectName(QStringLiteral("label_request"));
        label_request->setFont(font1);
        label_request->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_request);

        listWidget_request = new QListWidget(centralWidget);
        listWidget_request->setObjectName(QStringLiteral("listWidget_request"));
        listWidget_request->setFont(font2);

        verticalLayout->addWidget(listWidget_request);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 4, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 12);
        gridLayout->setColumnStretch(2, 1);
        gridLayout->setColumnStretch(3, 12);
        gridLayout->setColumnStretch(4, 1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 881, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        help = new QMenu(menuBar);
        help->setObjectName(QStringLiteral("help"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(help->menuAction());
        menu->addAction(action_exit);
        help->addAction(action_help);
        help->addAction(action_about);

        retranslateUi(MainWindow);
        QObject::connect(action_exit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Server", 0));
        action_exit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272\347\263\273\347\273\237(&Q)", 0));
        action_help->setText(QApplication::translate("MainWindow", "\345\270\256\345\212\251(&H)", 0));
        action_about->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216(&A)", 0));
        label_response->setText(QApplication::translate("MainWindow", "Response", 0));
        label_request->setText(QApplication::translate("MainWindow", "Request", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\350\217\234\345\215\225(&M)", 0));
        help->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251(&H)", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
