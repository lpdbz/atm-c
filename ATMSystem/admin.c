#include<stdio.h>
#include<stdlib.h>
#include"linkNode.h"
#include"user.h"
#include"hashmap.h"
#include"time.h"

HashMap* hashmap;//第一次运行的时候，会从文件中读取所有用户，在注册的时候，不仅会往文件中写入一份，也会往hashmap写入一份
LinkNode* head;//head同hashmap一样，head和hashmap的指针里面存储着同一块地址（即可以获取修改同一块地址里面的内容）
char adminName[5] = "root";
char adminPW[5] = "root";

static void adminLogsRecords(char *adminName,char *adminPW,char *oper);

//管理员的登录
void adminLogin(){
	char adminName_login[5];
	char adminPW_login[5];
	while(1){
		printf("请输入管理员账号：\n");
		scanf("%s",adminName_login);
		printf("请输入管理员密码：\n");
		scanf("%s",adminPW_login);
		if(strcmp(adminName,adminName_login)==0 && strcmp(adminPW,adminPW_login)==0){
			printf("管理员登录成功\n");
			break;
		}else{
			printf("账号或密码错误\n");
		}
	}

}

//查看所有用户
void showAllUser(){
	//直接打印linknode即可
	LinkNode *node;
	char *oper = "查看所有用户信息";  // 登录操作，写入日志文件
	Customer* user;
	node = nextNode(head);
	printf("所有用户信息：\n");
	while(node){
		user = (Customer*)malloc(sizeof(Customer));
		user = ((Customer*)((DataType*)node->data)->value);
		printf("账号开户时间：%s,账户卡号：%d，账户名称：%s，手机号码：%s，身份证：%s，密码：%s，账户金额：%f\n",user->Time,user->accountCard,user->accountName,user->mobile,user->sfz,user->password,user->money);
		node = nextNode(node);
	}
	adminLogsRecords(adminName,adminPW,oper);
}

//查看单个用户的信息和操作记录
void showSignalUser(){
	int accountCard; // 账户卡号
	char *oper = "查看单个用户信息";
	Customer* user = (Customer*)malloc(sizeof(Customer));
	printf("请输入您要查看用户信息的银行账号：\n");
	scanf("%d",&accountCard);

	while(1){
		if((Customer*)getData(hashmap,accountCard) != NULL){
			user = (Customer*)getData(hashmap,accountCard);
			printf("您需要查看的账户卡号 %d的用户信息是：账户名称：%s，手机号码：%s，身份证：%s，密码：%s，账户金额：%f\n",user->accountCard,user->accountName,user->mobile,user->sfz,user->password,user->money);
			break;
		}else{
			printf("抱歉，你查找的用户不存在。请继续操作\n");
			continue;
		}
	}
	adminLogsRecords(adminName,adminPW,oper);
}

//查看银行整体金额变化--金额变动记录是记录单个用户每一次操作了金额变化（如存取款操作），读文件展示出来，并在最后添加一个
//变量记录总金额变化即可
void showBankMoney(){
	char *oper = "查看银行整体金额变化";
	double BankMoney;//记录银行总金额变化
	Customer* user = (Customer*)malloc(sizeof(Customer));
	printf("账户卡号为 %d操作记录是：存款|取款|转账：%d，账户总金额为：%lf\n",user->accountCard,user->money,BankMoney);
	adminLogsRecords(adminName,adminPW,oper);
	return;
}

// 帮助用户修改密码
void assistUserChangePW(){
	int accountCard; // 账户卡号
	char originPW[7]; // 账号原密码
	char password[7],password_confirm[7]; // 修改密码和修改密码的确认密码
	char *oper = "帮助用户修改密码";
	Customer* user = (Customer*)malloc(sizeof(Customer));
	while(1){
		printf("请输入您要修改密码的银行账号：\n");
		scanf("%d",&accountCard);
		printf("请输入您要修改密码的原密码：\n");
		scanf("%s",&originPW);
		user = (Customer*)getData(hashmap,accountCard);
		if(user != NULL){
			if(strcmp(user->password,originPW) == 0){
				printf("账号密码匹配成功！\n");
				printf("请输入您需要修改的密码\n");
				scanf("%s",&password);
				printf("请再次输入您需要修改的密码\n");
				scanf("%s",&password_confirm);
				if(strcmp(user->password,password_confirm) != 0){
					if(strcmp(password_confirm,password) == 0){
						printf("两次输入密码一致\n");
						break;
					}else{
						printf("两次输入的密码不一致，请继续操作");
						continue;
					}
				}else{
					printf("修改密码不能与原密码一致！\n");
					continue;
				}
			}else{
				printf("该用户密码输入错误！\n");
				continue;
			}
		}else{
			printf("抱歉，你查找的用户不存在。请继续操作\n");
			continue;
			}
	}
	strcpy(user->password,password_confirm); // user已经指向了hashmap，为什么不能直接修改
	printf("密码修改成功！\n");
	userUpgrade_filePut(head);
	adminLogsRecords(adminName,adminPW,oper);
	return;
}

//从文件中取出管理员操作日志
void admin_fileGet(){
	FILE *fp;
	char ch[10],time[30];
	fp = fopen("管理员操作日志文件.txt","r");
	if(fp == NULL){
		perror("打开文件失败啦");
		system("pause");
		exit(1);
	}
	while(!feof(fp)){
		if(fscanf(fp,"%s\n",&ch)==1){
				printf("管理员的操作为：%s %s",time,ch);
			}else{
				printf("管理员暂时没有操作！\n");
				system("pause");
			}
		}
	fclose(fp);
}

//将管理员操作日志文件存入文件中
static void adminLogsRecords(char *adminName,char *adminPW,char *oper){
	FILE *fp;
	char time[30];
	fp = fopen("管理员操作日志文件.txt","a");
	currentTime(time);
	fprintf(fp,"%s %s %s %s\n",time,adminName,adminPW,oper);
	fclose(fp);
	return;
}