#include<stdio.h>
#include<stdlib.h>
#include"linkNode.h"
#include"user.h"
#include"hashmap.h"

HashMap *hashmap;

//查看所有用户
void showAllUser(){
	//直接打印linknode即可
	LinkNode* head,*node;
	Customer* user = (Customer*)malloc(sizeof(Customer));
	node = nextNode(head);
	printf("所有用户信息：\n");
	while(node){
		user = (Customer*)node->data;
		printf("账户卡号：%d，账户名称：%s，手机号码：%s，身份证：%s，密码：%s，账户金额：%f\n",user->accountCard,user->accountName,user->mobile,user->sfz,user->password,user->money);
		node = nextNode(node);
	}
}

//查看单个用户的信息和操作记录
void showSignalUser(int accountCard){
	Customer* user = (Customer*)malloc(sizeof(Customer));
	user = (Customer*)getData(hashmap,accountCard);
	//怎么看操作记录呢？应该将操作记录在文件中，然后输出文件中对应的accountCard
	printf("您需要查看的账户卡号 %d的用户信息是：账户名称：%s，手机号码：%s，身份证：%s，密码：%s，账户金额：%f\n",user->accountCard,user->accountName,user->mobile,user->sfz,user->password,user->money);
}

//查看银行整体金额变化--金额变动记录是记录单个用户每一次操作了金额变化（如存取款、转账操作），读文件展示出来，并在最后添加一个
//变量记录总金额变化即可
void showBankMoney(){
	double BankMoney;//记录银行总金额变化
	Customer* user = (Customer*)malloc(sizeof(Customer));
	printf("账户卡号为 %d操作记录是：存款|取款|转账：%d，账户总金额为：%lf\n",user->accountCard,user->money,BankMoney);
	return;
}

//帮助用户修改密码
void assistUserChangePW(int accountCard){
	char password[7],password_confirm[7];
	Customer* user = (Customer*)malloc(sizeof(Customer));
	user = (Customer*)getData(hashmap,accountCard);
	printf("请输入您需要修改的密码\n");
	scanf("%s",&password);
	printf("请再次输入您需要修改的密码\n");
	scanf("%s",&password_confirm);
	if(strcmp(password_confirm,password) == 0){
		printf("两次输入密码一致\n");
		strcpy(user->password,password);
		putData(hashmap,accountCard,user);
		printf("密码修改成功！\n");
	}
	return;
}