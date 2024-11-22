#include "widget.h"

#include <QApplication>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QLabel>
#include <QMovie>
#include "widget/pet_widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
    PetWidget w;

    // 托盘图标
    QSystemTrayIcon sysTray(QIcon("://img/icon.png"),&w);

    QMenu menu;
    auto showAct=new QAction("显示", &sysTray);
    auto exitAct=new QAction("隐退", &sysTray);

    QObject::connect(showAct,&QAction::triggered,[&](){
        w.setVisible(true);
    });
    QObject::connect(exitAct,&QAction::triggered,[&](){
        QApplication::quit();
    });

    menu.addAction(showAct);
    menu.addAction(exitAct);

    // 绑定托盘菜单
    sysTray.setContextMenu(&menu);

    sysTray.show();
    w.show();

    return a.exec();
}
