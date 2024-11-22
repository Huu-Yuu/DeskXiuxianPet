#ifndef DESKXIUXIANPET_PUBLIC_ENUM_H
#define DESKXIUXIANPET_PUBLIC_ENUM_H
#include <QObject>
namespace Pet{
    Q_NAMESPACE
    enum RoleAct
    {
        kFree,       ///< 空闲
        kPractice    ///< 修行
    };
    Q_ENUM_NS(RoleAct);
}




#endif //DESKXIUXIANPET_PUBLIC_ENUM_H
