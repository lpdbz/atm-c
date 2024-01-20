#ifndef __ADMIN_H_
#define __ADMIN_H_

#pragma once

typedef struct Admin{
	char time[30];  // 管理员开户时间
	char adminName[10];  // 管理员姓名
	char passWord[7];  // 管理员密码
}Admin;
// 管理员不允许注册，暂时只有已经规定好的管理员账号
void showAllUser();

void showSignalUser();

void showBankMoney();

void assistUserChangePW();

//管理员的登录
void adminLogin();

#endif