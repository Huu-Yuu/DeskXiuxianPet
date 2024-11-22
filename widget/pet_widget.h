#ifndef DESKXIUXIANPET_PET_WIDGET_H
#define DESKXIUXIANPET_PET_WIDGET_H
#include<QWidget>
#include<QMap>
#include<QList>
#include<QUrl>
#include<QTimer>
#include<QEvent>
#include<QMouseEvent>
#include<QContextMenuEvent>
#include<QMenu>
#include<QMetaEnum>
#include<QLabel>
#include "../public/public_enum.h"
using namespace Pet;

class PetWidget : public QWidget
{
Q_OBJECT
public:
    PetWidget(QWidget *parent = nullptr);
    ~PetWidget() override;

public:
    void showActAnimation(Pet::RoleAct k);

public slots:
    void onMenuTriggered(QAction* action);

protected:
    void paintEvent(QPaintEvent* event)override;
    void contextMenuEvent(QContextMenuEvent* event) override;

private:
    void loadRoleActRes();
    void initMenu();

private:
    QMap<Pet::RoleAct, QString> action_map;
    QMap<QString, const char*> act_str_map;    ///< 动作字符串和枚举值映射关系
    Pet::RoleAct cur_role_act;
    QUrl cur_role_pix;
    QMenu* menu;
    QLabel* pet_label;         ///< 宠物窗口
    QMetaEnum mate_enum = QMetaEnum::fromType<Pet::RoleAct>();    ///< 角色动作元对象枚举值
};

class DragFilter_:public QObject{

public:
    bool eventFilter(QObject* obj,QEvent* event)
    {
        auto w=dynamic_cast<QWidget*>(obj);
        if(!w)
            return false;

        if(event->type()==QEvent::MouseButtonPress)
        {
            auto e=dynamic_cast<QMouseEvent*>(event);
            if(e)
            {
                pos=e->pos();
            }
        }
        else if(event->type()==QEvent::MouseMove)
        {
            auto e=dynamic_cast<QMouseEvent*>(event);
            if(e)
            {
                if(e->buttons()&Qt::MouseButton::LeftButton)
                {
                    w->move(e->globalPos() - pos);
                }
            }
        }
        return QObject::eventFilter(obj,event);
    }

private:
    QPoint pos;
};

#endif //DESKXIUXIANPET_PET_WIDGET_H
