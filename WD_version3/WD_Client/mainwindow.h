#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtNetwork>

#include "buyer.h"
#include "member.h"
#include "seller.h"
#include "food.h"
#include "electronics.h"
#include "dailynecessities.h"

namespace Ui
{
class MainWindow;
}

typedef enum {
    RegisterRequest, RegisterResponse,
    LoginRequest, LoginResponse,
    BuyRequest, BuyResponse,
    StockRequest, StockResponse,
    RechargeRequest, RechargeResponse,
    UpgradeRequest, UpgradeResponse,
    ExchangeRequest, ExchangeResponse,
    LogoutRequest
}UdpType;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void sendRequest(UdpType type);
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QUdpSocket* udpSocket;
    QHostAddress serverAddr;
    qint16 clientPort, serverPort;
    QDateTime TIMESTAMP;

    /*********************  Custom Functions *****************************/

    void addTreeNode(int index, QStringList newGoods);
    void addTreeRecord(QStringList rec);
    void listAllGoods(QString key="");
    void listMyGoods(QString key="");
    void setManagePage(QString newUser, UserClass userClass, double balance, int level, int token, QVector<QStringList> vecRecord);
    void setMainPage(QVector<QVector<QStringList> > vec2Goods, UserClass userClass, int level);

    /***********************  reset  ************************************/
    void resetLoginPage();
    void resetRegisterPage();
    void resetMainPage();
    void resetManagePage();

private slots:

    /**********************  loginPage  *******************************/
    void loginPage_textChanged();

    void on_pushButton_login_clicked();

    void on_pushButton_now_clicked();

    /**********************  registerPage  ******************************/
    void registerPage_textChanged();

    void on_pushButton_register_clicked();

    void on_pushButton_back_clicked();

    /************************  mainPage  ********************************/

    void on_pushButton_search_clicked();

    void on_pushButton_clear_clicked();

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    //!pageBuyer

    void on_spinBox_buyer_valueChanged(int arg1);

    void on_pushButton_buy_clicked();

    //!pageSeller

    void on_radioButton_all_clicked();

    void on_radioButton_mine_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_lineEdit_name_textChanged(const QString &arg1);

    void on_spinBox_seller_valueChanged(int arg1);

    void on_pushButton_in_clicked();

    /************************  managePage  *******************************/
    void on_pushButton_Recharge_clicked();

    void on_pushButton_Upgrade_clicked();

    void on_pushButton_Exchange_clicked();

    void on_pushButton_record_clicked();

    void on_pushButton_back_record_clicked();

    void on_lineEdit_Token_textChanged(const QString &arg1);

    /**********************  action  ***********************************/
    void on_action_deal_triggered();

    void on_action_manage_triggered();

    void on_action_logout_triggered();

    void on_action_about_triggered();

    void on_action_help_triggered();

    /**********************  UDP  ******************/
    void processPendingDatagrams();
};

#endif // MAINWINDOW_H
