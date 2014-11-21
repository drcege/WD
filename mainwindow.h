#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMap>
#include <QTreeWidgetItem>
#include "user.h"
#include "goods.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int USERID;
    int GOODSID;
    User* curUser;
    QVector<Buyer> vecBuyer;
    QVector<Member> vecMember;
    QVector<Seller> vecSeller;
    QVector<Food> vecFood;
    QVector<Electronics> vecElectronics;
    QVector<DailyNecessities> vecDailyNecessities;

    bool loadData();
    int checkUser(QString userName, QString password = "");
    void addTreeNode(QTreeWidgetItem* parent, Food *food);
    void addTreeNode(QTreeWidgetItem* parent, Electronics *elect);
    void addTreeNode(QTreeWidgetItem* parent, DailyNecessities *daily);

private slots:
    void on_action_logout_triggered();

    void on_action_exit_triggered();

    void on_action_about_triggered();

    void on_action_Qt_triggered();

    void on_lineEdit_user_login_textChanged(const QString &arg1);

    void on_lineEdit_pwd_login_textChanged(const QString &arg1);

    void on_lineEdit_user_register_textChanged(const QString &arg1);

    void on_lineEdit_pwd_register_textChanged(const QString &arg1);

    void on_lineEdit_pwd_repeat_textChanged(const QString &arg1);

    void on_pushButton_login_clicked();

    void on_pushButton_quit_clicked();

    void on_pushButton_now_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_register_clicked();

};

#endif // MAINWINDOW_H
