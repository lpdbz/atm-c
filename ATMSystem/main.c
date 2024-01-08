#include<stdio.h>
#include<stdlib.h>
#include"menu.h"
#include"user.h"
#include"hashmap.h"
#define N 100

void sign_loginOperator(){
	int a,flag=1;
	initUser();
	fileGet();
	while(flag){
		sign_loginMenu();
		printf("请选择注册登录操作：\n");
		scanf("%d",&a);
		switch(a){
		case 1:sign();system("pause");break;
		case 2:login();system("pause");flag=0;break;
		case 0:flag=0;break;
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
	adminMenu();
}

void main(){
	int id,flag=1;
	while(flag){
		menu();
		printf("请选择用户或管理员操作\n");
		scanf("%d",&id);
		switch(id){
		case 1:sign_loginOperator();userOperator();break;
		case 2:adminOperator();break;
		case 0:flag=0;break;
		default:printf("输入有误，请重新输入");break;
		}
		system("cls");
	}
}
