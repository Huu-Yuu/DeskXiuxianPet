//
// Created by patient on 2024/11/19.
//

#include"pet_widget.h"
#include<QPaintEvent>
#include<QPainter>//绘图
#include<QPixmap>//图片
#include<QCursor>
#include<QMetaEnum>
#include<QTimer>

PetWidget::PetWidget(QWidget *parent)
        : QWidget(parent),
          timer(new QTimer(this)),
          menu(new QMenu(this))
{
    this->setWindowFlag(Qt::FramelessWindowHint);//去除窗口边框
    this->setAttribute(Qt::WA_TranslucentBackground);//背景透明

    this->installEventFilter(new DragFilter_);

    connect(timer,&QTimer::timeout,[this](){
        static int index=0;//记录显示动作的当前图片索引
        auto paths = this->action_map.value(this->cur_role_act);
        this->cur_role_pix=paths[index++ % paths.size()];
        //paintEvent() 不允许的
        this->update();

    });

    initMenu();

    loadRoleActRes();

    showActAnimation(RoleAct::Free);
}

PetWidget::~PetWidget() {}

void PetWidget::showActAnimation(RoleAct k)
{
    timer->stop();

    this->cur_role_act=k;

    timer->start(60);
}

void PetWidget::onMenuTriggered(QAction *action)
{
    QMetaEnum me=QMetaEnum::fromType<RoleAct>();

    bool ok;
    int k =  me.keyToValue(action->text().toStdString().c_str(),&ok);
    if(!ok)
        return;

    showActAnimation(static_cast<RoleAct>(k));
}

void PetWidget::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);

    QPixmap pix;
    pix.load(this->cur_role_pix.toLocalFile());

    painter.drawPixmap(0,0,pix);

}

void PetWidget::contextMenuEvent(QContextMenuEvent *event)
{
    this->menu->popup(QCursor::pos());
}

void PetWidget::loadRoleActRes()
{
    auto addRes=[this](RoleAct k,QString path,int count)
    {
        QList<QUrl> paths;
        char buf[260];
        for (int i = 0; i < count; ++i) {
            memset(buf, 0,sizeof(buf));
            sprintf_s(buf,path.toStdString().c_str(),i);
            paths.append(QUrl::fromLocalFile(buf));
        }
        action_map.insert(k,paths);
    };

//    addRes(RoleAct::SayHello,":/sayHello/img/sayHello/sayHello_%d.png",28);
//    addRes(RoleAct::Swing,":/swing/img/swing/swing_%d.png",32);
//    addRes(RoleAct::Sleep,":/sleep/img/sleep/sleep_%d.png",25);
}

void PetWidget::initMenu()
{
    menu->addAction("SayHello");
    menu->addAction("Sleep");
    menu->addAction("Swing");

    auto* act = new QAction("Hide");
    connect(act,&QAction::triggered,[this](){
        this->setVisible(false);
    });

    menu->addAction(act);

    connect(this->menu,&QMenu::triggered,this,&PetWidget::onMenuTriggered);
}
