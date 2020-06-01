#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QMap>
#include <QTableWidget>
#include <QDebug>
#include <QMessageBox>
#include <QMultiMap>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Route{
private:
    int id;
    int cost;
    bool isAvaliable;
    QVector <int> connectedRouters;
public:
    Route(int id):id(id){cost = rand();};
    int getID(){return this->id;}
    int getCost(){return this->cost;}
    bool connectToRouter(int routerID);
    int getNeighbour(int);
    QVector <int> getConnectedRouters(){return this->connectedRouters;}
};

class Router{
private:
    int id;
    QVector <Route *> routes;
    QVector <int> neighbours;
    QVector <QVector <int>> table;

public:
    QMap<int, QString> optimalRoutes;
    Router(int id):id(id){};
    int getID(){return id;}
    void sendHello();
    bool connectToRoute(Route * r);
    QVector <int> getNeighbours(){return this->neighbours;};
    int getCostTo(int routerID);
    void getOptimalRoutes();
    void setTable(QVector <QVector <int>> table);
    QString getRoutingTable();
};

class Network{
private:
    QVector <Route *> routes;
    QVector <Router *> routers;
    QVector <QVector <int>> table;
public:
    void setRouters(QVector <Router *> routers);
    void setRoutes(QVector <Route *> routes);
    void getTable();
    void sendTable();
};

class MainWindow : public QMainWindow{
    Q_OBJECT
private:
    Network * n;
    int routersCount = 0;
    int routesCount = 0;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_addRouter_clicked();
    void on_addRoute_clicked();
    void on_pushButton_clicked();
private:
    QVector<Route *> routes;
    QVector<Router *> routers;
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
