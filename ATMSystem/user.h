#pragma once

#include<stdio.h>
#include<stdlib.h>
#include"linkNode.h"
#include"hashmap.h"


typedef struct Customer{
	char Time[30];//开户时间用户时间
	int accountCard;//账户卡号
	char accountName[10];//账户名称
	char mobile[12];//手机号码
	char sfz[19];//身份证
	char password[7];//密码  密码输入，在控制台上显示“*”号
	double money;//账户余额
}Customer;


//初始化user
void initUser();

//登录
void login();

//注册
void sign();

//修改用户信息
void updateInfo();
//修改密码
void changePW();

// 取款业务
void drawMoneyLogical();

//存款业务
void saveMoneyLogical();

//查询余额
void showMoney();

//转账
void transferMoney();
//余额变动记录
void balanceChange();

//用户日志logs记录
void userLogsRecords(Customer *custTmp,char *oper);

//注册时用户源信息存入文件
void user_filePut(Customer *custTmp);

//更新时用户源信息存入文件
void userUpgrade_filePut(LinkNode* head);

void user_fileGet(HashMap *hashmap,LinkNode *head,int userNum);

// 记录银行总体金额变化
void Bank_TotalAmountChange(char *oper,Customer *custTmp,double money);

// 从银行总金额文件中获取全部的信息Bank_TotalAmountChange;
void Bank_TotalAmount_fileGet(double BankTotalMoney);