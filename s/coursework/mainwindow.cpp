#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    n = new Network();
    ui->routersTable->setColumnCount(1);
    ui->routersTable->setRowCount(0);
    ui->routersTable->setHorizontalHeaderItem(0, new QTableWidgetItem(""));
    ui->routesTable->setColumnCount(1);
    ui->routesTable->setHorizontalHeaderItem(0, new QTableWidgetItem(""));
    ui->routersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->routesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow(){
    delete n;
    delete ui;
}

bool Route::connectToRouter(int routerID){
    if (connectedRouters.size() > 2) return false;
    connectedRouters.append(routerID);
    return true;
}

int Route::getNeighbour(int currentRouter){
    for (int i = 0; i < connectedRouters.size(); i++){
        if (currentRouter != connectedRouters[i]) return connectedRouters[i];
    }
    return -1;
}

bool Router::connectToRoute(Route * r){
    if (routes.contains(r)) return false;
    routes.append(r);
    r->connectToRouter(this->id);
    return true;
}

void Router::sendHello(){
    for (int i = 0; i < routes.size(); i++){
        neighbours.append(routes[i]->getNeighbour(this->id));
    }
}

int Router::getCostTo(int routerID){
    for (int i = 0; i < routes.size(); i++){
        QVector <int> tmp = routes[i]->getConnectedRouters();
        if (tmp.contains(routerID) && tmp.contains(this->id))
            return routes[i]->getCost();
    }
    return -1;
}

void Router::setTable(QVector<QVector<int> > table){
    this->table = table;
}

void Router::getOptimalRoutes(){
    int st = this->id;
    QVector <int> D;            D.resize(table[0].size());
    QVector <bool> visited;     visited.resize(table[0].size());
    for(int i = 0; i < table[0].size(); i++){
        D[i] = table[st][i];
        visited[i] = false;
    }
    D[st] = 0;
    int index = 0, u = 0;
    for (int i = 0; i < table[0].size(); i++){
        int min = INT_MAX;
        for (int j = 0; j < table[0].size(); j++){
            if (!visited[j] && D[j] < min){
                min = D[j];
                index = j;
            }
        }
        u = index;
        visited[u] = true;
        for(int j = 0; j < table[0].size(); j++){
            if (!visited[j] && table[u][j] != INT_MAX && D[u] != INT_MAX && (D[u] + table[u][j] < D[j])){
                D[j] = D[u] + table[u][j];
            }
        }
    }

    QString vis = "";
    for (int pos = 0; pos < table[0].size(); pos++){
        qDebug() << this->id;
        if (D[pos] != 0 && D[pos] != INT_MAX || pos != this->id){

            int end = pos;
            vis += QString::number(pos);
            int k = 1;
            int weight = D[end];
            while (end != st){
                for (int i = 0; i<table[0].size(); i++)
                    if (table[i][end] != 0){
                        int temp = weight - table[i][end];
                        if (temp == D[i]){
                            weight = temp;
                            end = i;
                            vis = vis + " " + QString::number(i);
                            k++;
                        }
                    }
            }
            //qDebug() << vis;
            std::reverse(vis.begin(), vis.end());
            optimalRoutes[D[pos]] = vis;
            vis.clear();
        }
    }
    qDebug() << optimalRoutes;
}

QString Router::getRoutingTable(){
    qDebug() << "!";
    QString result = "";
    QMutableMapIterator<int, QString> i(this->optimalRoutes);
    while (i.hasNext()){
        i.next();
        int cost = i.key();
        QString route = i.value();
        QStringList tmp = route.split(" ");
        QString with = tmp[tmp.size() - 1];
        result += QString("Маршрут с " + with + " маршрутизатором ценой %1 единиц: " + route + "\n").arg(cost);
    }
    qDebug() << result;
    return result;
}

void Network::setRoutes(QVector<Route *> routes){
    this->routes = routes;
}

void Network::setRouters(QVector<Router *> routers){
    this->routers = routers;
}

void Network::getTable(){
    table.resize(routers.size());
    for (int i = 0; i < routers.size(); i++){
        table[i].resize(routers.size());
        table[i].fill(INT_MAX);
        QVector <int> tmp = routers[i]->getNeighbours();
        for (int j = 0; j < tmp.size(); j++){
            table[i][tmp[j]] = routers[i]->getCostTo(tmp[j]);
        }
    }
    //qDebug() << table;
}

void Network::sendTable(){
    for (int i = 0; i < routers.size(); i++){
        routers[i]->setTable(this->table);
    }
}

void MainWindow::on_addRouter_clicked(){
    routers.append(new Router(routersCount));
    ui->routersTable->setRowCount(routersCount + 1);
    ui->routersTable->setItem(routersCount, 0,
                              new QTableWidgetItem("Маршрутизатор c ID: " + QString::number(routersCount)));

    routersCount += 1;
}

void MainWindow::on_addRoute_clicked(){
    if (ui->router1id->text() == "" || ui->router2id->text() == ""){
        QMessageBox::warning(this, "Ну вот опять!", "Вы не ввели ID маршрутизаторов!");
        return;
    }
    routes.append(new Route(routesCount));
    int a = ui->router1id->text().toInt();
    int b = ui->router2id->text().toInt();
    routes[routesCount]->connectToRouter(a);
    routes[routesCount]->connectToRouter(b);
    ui->routesTable->setRowCount(routesCount + 1);
    ui->routesTable->setItem(routesCount, 0,
                             new QTableWidgetItem(
                             QString("Канал связи между %1 и %2 маршрутизаторами стоимостью %3")
                                 .arg(a).arg(b).arg(routes[routesCount]->getCost())));
    routers[a]->connectToRoute(routes[routesCount]);
    routers[b]->connectToRoute(routes[routesCount]);
    routesCount++;
}

void MainWindow::on_pushButton_clicked(){
    for (int i = 0; i < routers.size(); i++){
        routers[i]->sendHello();
    }
    n->setRoutes(routes);
    n->setRouters(routers);

    n->getTable();
    n->sendTable();
    //ui->routingTable->setRowCount(routersCount);
    for (int i = 0; i < routers.size(); i++){
        routers[i]->getOptimalRoutes();
        QString newRouterString = QString("Таблица маршрутизации для %1 роутера\n").arg(i);
        newRouterString += routers[i]->getRoutingTable();
        ui->routingTable->append(newRouterString);

        qDebug() << newRouterString;
    }
}
