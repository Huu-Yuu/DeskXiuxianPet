#ifndef DESKXIUXIANPET_PUBLIC_ENUM_H
#define DESKXIUXIANPET_PUBLIC_ENUM_H
#include <QObject>
namespace Pet{
    Q_NAMESPACE
    enum RoleAct
    {
        Free,       ///< 空闲
        practice    ///< 修行
    };
    Q_ENUM_NS(RoleAct);
}




#endif //DESKXIUXIANPET_PUBLIC_ENUM_H
