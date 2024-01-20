#include<stdio.h>
#include<stdlib.h>
#include"menu.h"
#include"user.h"
#include"admin.h"


void sign_loginOperator(){
	int a,flag=1;
	initUser();

	while(flag){
		sign_loginMenu();
		printf("请选择注册登录操作：\n");
		scanf("%d",&a);
		switch(a){
		case 1:sign();system("pause");break;
		case 2:login();system("pause");flag=0;break;
		case 0:flag=0;break;//返回到上一个界面，现在有问题，返回的是下一个界面
		default:printf("输入有误，请重新输入\n");system("pause");
		}
		system("cls");
	}
}

void admin_loginOperator(){
	int a,flag=1;
	initUser(); // 初始化hashmap和head，并且从文件中将用户信息存储到hashmap和head中   user里面的hashmap拿到了数据，admin里面的数据
	while(flag){
		admin_sign_loginMenu();
		printf("请选择操作：\n");
		scanf("%d",&a);
		switch(a){
		case 1:adminLogin();system("pause");flag=0;break;
		case 0:flag=0;break;//返回到上一个界面，现在有问题，返回的是下一个界面
		default:printf("输入有误，请重新输入\n");system("pause");
		}

		system("cls");
	}
}

void userOperator(){
	int flag=1,i;
	while(flag){
		userMenu();
		scanf("%d",&i);
		switch(i){
		case 1:saveMoneyLogical();system("pause");break;
		case 2:drawMoneyLogical();system("pause");break;
		case 3:transferMoney();system("pause");break;
		case 4:showMoney();system("pause");break;
		case 5:changePW();system("pause");break;
		case 6:updateInfo();system("pause");break;
		case 0:flag=0;system("pause");break;
		default:printf("输入有误，请重新输入\n");
		}
		system("cls");
	}
}

void adminOperator(){
	int flag=1,i;
	while(flag){
		adminMenu();
		scanf("%d",&i);
		switch(i){
		case 1:showAllUser();system("pause");break;
		case 2:showSignalUser();system("pause");break;
		case 3:showBankMoney();system("pause");break;
		case 4:assistUserChangePW();system("pause");break;
		case 0:flag=0;system("pause");break;
		default:printf("输入有误，请重新输入\n");
		}
		system("cls");
	}
}

void main(){
	int id,flag=1;
	while(flag){
		menu();
		printf("请选择用户或管理员操作\n");
		scanf("%d",&id);
		switch(id){
		case 1:sign_loginOperator();userOperator();break;
		case 2:admin_loginOperator();adminOperator();break;
		case 0:flag=0;break;
		default:printf("输入有误，请重新输入");break;
		}
		system("cls");
	}
}
