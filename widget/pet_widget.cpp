//
// Created by patient on 2024/11/19.
//

#include"pet_widget.h"
#include<QPaintEvent>
#include<QCursor>
#include<QDebug>
#include<QMovie>
#include<QFileInfo>

PetWidget::PetWidget(QWidget *parent)
        : QWidget(parent),
          menu(new QMenu(this)),
          pet_label(new QLabel(this))
{
    this->setWindowFlag(Qt::FramelessWindowHint);//去除窗口边框
    this->setAttribute(Qt::WA_TranslucentBackground);//背景透明

    this->installEventFilter(new DragFilter_);

    initMenu();

    loadRoleActRes();

    showActAnimation(RoleAct::kFree);
}

PetWidget::~PetWidget() {}

void PetWidget::showActAnimation(RoleAct k)
{
    QString path = action_map.value(k);
    QString format = QFileInfo(path).suffix();
//    qDebug() << "文件格式为：" << format;
    if(format == "gif")
    {
        QMovie *movie = new QMovie(":/res/xiuxian.gif");
        pet_label->setMovie(movie); // 1. 设置要显示的 GIF 动画图片
        movie->start();         // 2. 启动动画
        pet_label->show();
    }
    else if(format == "png")
    {
        pet_label->setPixmap(QPixmap(path));
        pet_label->show();
    }
}

void PetWidget::onMenuTriggered(QAction *action)
{
    bool ok;
    int k =  mate_enum.keyToValue(act_str_map.value(action->text()) ,&ok);
    if(!ok)
        return;
    showActAnimation(static_cast<RoleAct>(k));
}

void PetWidget::paintEvent(QPaintEvent *event)
{

}

void PetWidget::contextMenuEvent(QContextMenuEvent *event)
{
    this->menu->popup(QCursor::pos());
}

void PetWidget::loadRoleActRes()
{
    auto addRes=[this](RoleAct k,QString path)
    {
        action_map.insert(k, path);
        qDebug() << "读取动作资源文件：" << path;
    };
    addRes(RoleAct::kFree, ":/res/xiuxian.png");
    addRes(RoleAct::kPractice, ":/res/xiuxian.gif");
}

void PetWidget::initMenu()
{
    // 主要是为了显示中文菜单，这里将中文和枚举值建立映射关系
    act_str_map.insert("空闲", mate_enum.valueToKey(RoleAct::kFree));
    act_str_map.insert("修行", mate_enum.valueToKey(RoleAct::kPractice));
    menu->addAction("空闲");
    menu->addAction("修行");

    auto* act = new QAction("隐藏");
    connect(act,&QAction::triggered,[this](){
        this->setVisible(false);
    });

    menu->addAction(act);

    connect(this->menu,&QMenu::triggered,this,&PetWidget::onMenuTriggered);
}
