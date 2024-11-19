#include "widget.h"

#include <QApplication>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QLabel>
#include <QMovie>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    QSystemTrayIcon sysTray(QIcon("://img/icon.png"),&w);

    QMenu menu;
    auto showAct=new QAction("show",&sysTray);
    auto exitAct=new QAction("exit",&sysTray);

    QObject::connect(showAct,&QAction::triggered,[&](){
        w.setVisible(true);
    });
    QObject::connect(exitAct,&QAction::triggered,[&](){
        QApplication::quit();
    });

    menu.addAction(showAct);
    menu.addAction(exitAct);

    sysTray.setContextMenu(&menu);

    sysTray.show();
    w.show();

    QLabel *label = new QLabel();
       QMovie *movie = new QMovie(":/res/xiuxian.gif");
       label->setMovie(movie); // 1. 设置要显示的 GIF 动画图片
       movie->start();         // 2. 启动动画
       label->show();


    return a.exec();
}
