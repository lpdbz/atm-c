#include<stdio.h>
#include<stdlib.h>

typedef struct Customer{
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

//用户登录记录
void userLoginRecords();

void filePut();

void fileGet();
