﻿#ifndef DESKXIUXINA_ROLE_DB_H
#define DESKXIUXINA_ROLE_DB_H
#include <QtSql/QSqlDatabase>
#include "../common/singleton.h"
#include <QJsonObject>

class RoleInfoTable
{
public:
    RoleInfoTable();
    RoleInfoTable(const RoleInfoTable& other);
    ~RoleInfoTable();

    void FromJson(const QJsonObject& task_obj);  // 解析任务object
    QJsonObject ToJson() const;

    QString role_name;
    QString role_life;
    QString role_prestige;
    QString role_exp;
    QString role_cur_exp;
    QString role_agg;
    QString role_def;
    QString role_hp;
    QString role_lv;
};




#endif //DESKXIUXINA_ROLE_DB_H
