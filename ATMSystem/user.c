#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hashmap.h"
#include"linkNode.h"
#include"user.h"
#include"time.h"

#define N 10
int userNum = 0;

HashMap* hashmap;
LinkNode* head;
Customer* custCurrent;//存储当前用户的信息，每一次修改用户信息后，都应该重新赋一次值

//每次相关操作，都需要打印凭条，也没有写

void initUser(){
	hashmap = createHash(N);
	head = createNode();
	user_fileGet(hashmap,head,userNum);
}

//登录
void login(){
	int accountCard;
	char password[7];
	Customer* user;
	char *oper = "登录";

	printf("欢迎来到登录界面\n");
	printf("请输入您的银行卡号和密码:\n");

	while(1){
		scanf("%d %s",&accountCard,&password);
		//为什么hashmap返回的出错了，明明getData没有问题！！！
		user = (Customer*)getData(hashmap,accountCard);
		printf("登录时获取hashmap的打印：银行卡号：%d，账户名称：%s，手机号码：%s，身份证：%s，密码：******，余额：%lf\n\n",user->accountCard,user->accountName,user->mobile,user->sfz,user->money);
		//去记录中查找，检查1.是否存在此卡号；2.密码是否正确
		if(user!=NULL){
			//接下来检查密码是否输入正确
			custCurrent = user; //查找成功，就将查找到的信息赋值一份给custCurrent，便于后面一直拿到用户的信息
			if(strcmp(password,user->password)==0){
				//将用户信息记录到日志logs记录文件中
				userLogsRecords(custCurrent,oper);
				printf("登录成功，请继续接下来的操作\n");
				return;	
			}
		}else{
			printf("银行卡号和密码输入错误，请重新输入：\n");
		}
	}
}

//注册
void sign(){
	char pw[7];
	char *oper = "注册";
	Customer* user = (Customer*)malloc(sizeof(Customer));

	printf("欢迎来到注册界面\n");	
	printf("请依次输入您的名字  手机号码  身份证:\n");
	scanf("%s %s %s",&user->accountName,&user->mobile,&user->sfz);
	user->accountCard = atoi(user->sfz);

	if(constainsKey(hashmap,user->accountCard)){
		printf("用户已存在，请去登录\n");
		return;
	}

	printf("注册成功，您的银行卡号为：%d\n",user->accountCard);
	while(1){
		printf("请输入您的银行卡密码(6位数):\n");
		scanf("%s",&user->password);
		printf("请再次输入你的银行卡密码:\n");
		scanf("%s",&pw);
		if(strcmp(user->password,pw) != 0){
			printf("两次输入密码不一致，请重新输入\n");
			continue;
		}else{
			break;
		}
	}
	user->money = 0.0;//注册的时候用户的余额为0
	
	// 获取当前时间存入文件中
	currentTime(user->Time);
	putData(hashmap,user->accountCard,user);
	addNode(head,user);
	user_filePut(user);
	userLogsRecords(user,oper);
	printf("两次输入密码正确，银行卡注册成功!\n");
	return;
}

//修改用户信息
void updateInfo(){
	char *oper = "修改用户信息";
	int i=0;
	int flag = 1;
	Customer *user = (Customer*)getData(hashmap,custCurrent->accountCard);
	Customer *user_1 = (Customer*)getData(hashmap,custCurrent->accountCard);
	user_1 = custCurrent;

	printf("欢迎来到修改个人信息界面:\n");
	printf("您的信息为：");
	printf("银行卡号：%d，账户名称：%s，手机号码：%s，身份证：%s，密码：******，余额：%lf\n\n",user->accountCard,user->accountName,user->mobile,user->sfz,user->money);
	
	while(flag){
		printf("请问你要修改什么信息？\n");
		printf("1 修改账户名称\n");//有些人改名了
		printf("2 修改电话号码\n");
		printf("3 修改密码\n");//认为在修改信息的时候，密码也属于个人信息，应该兼容
		printf("0 退出修改个人信息界面\n");

		scanf("%d",&i);
		switch(i){
		case 1:printf("请输入账户名称:\n");scanf("%s",&user->accountName);break;
		case 2:printf("请输入电话号码:\n");scanf("%s",&user->mobile);break;
		case 3:printf("请输入要修改的密码:\n");scanf("%s",&user->password);break;
		case 0:flag = 0;break;//怎么退出呢，并执行后续代码
		default:printf("输入有误，请输入对应的值");
		}
		printf("您的信息为：");
		printf("银行卡号：%d，账户名称：%s，手机号码：%s，身份证：%s，密码：******，余额：%lf\n\n",user->accountCard,user->accountName,user->mobile,user->sfz,user->money);
	}
	custCurrent = user;
	//printf("银行卡号：%d，账户名称：%s，手机号码：%s，身份证：%s，密码：%s，余额：%lf\n\n",custCurrent->accountCard,custCurrent->accountName,custCurrent->mobile,custCurrent->sfz,custCurrent->password,custCurrent->money);
	
	putData(hashmap,user->accountCard,user);
	updateNode(head,custCurrent,user_1,sizeof(user_1));//将更新后的用户信息，也在链表中更新一份
	userUpgrade_filePut(head);
	userLogsRecords(user,oper);
	printf("修改用户信息成功！ ");
	system("pause");
	//将修改后的信息记录到用户源信息中。
	return;
}

//修改密码
void changePW(){
	char *oper = "修改密码";
	char passWord[7],passWord_1[7];
	Customer *user = (Customer*)getData(hashmap,custCurrent->accountCard);
	user = custCurrent;
	printf("欢迎来到修改密码界面\n");
	while(1){
		printf("请输入原密码:\n");
		scanf("%s",&passWord);

		if(strcmp(passWord,custCurrent->password) == 0){
			printf("请输入你想要修改的密码:\n");
			scanf("%s",&passWord_1);
			if(strcmp(passWord,passWord_1)==0){
				printf("不能修改为原密码！请重新操作\n");
				continue;
			}else{
				break;
			}
		}else{
			printf("原密码输入错误！请重新操作\n");
			continue;
		}
	}
	strcpy(custCurrent->password,passWord_1);
	putData(hashmap,custCurrent->accountCard,custCurrent);
	updateNode(head,custCurrent,user,sizeof(custCurrent));//将更新后的用户信息，也在链表中更新一份
	userUpgrade_filePut(head);
	userLogsRecords(custCurrent,oper);
	printf("密码修改成功！\n");
}

//取款
void drawMoney(){
	char *oper = "取款";
	int money;
	Customer *user = (Customer*)getData(hashmap,custCurrent->accountCard);
	user = custCurrent;
	printf("请输入您需要取款的金额(只能取款整百元)\n");

	scanf("%d",&money);
	if(((int)money)/100 != 0 && ((int)money)%100 == 0){
		if(money <= custCurrent->money){
			printf("您的余额足够，可以为您取出\n");
			custCurrent->money -= money;
			putData(hashmap,custCurrent->accountCard,custCurrent);
			updateNode(head,custCurrent,user,sizeof(custCurrent));//将更新后的用户信息，也在链表中更新一份
			userUpgrade_filePut(head);
			userLogsRecords(custCurrent,oper);
			printf("取款成功！\n");
			printf("您的银行卡号为：%d,现在的余额为:%f\n",custCurrent->accountCard,custCurrent->money);
		}else{
			printf("您的余额不足，无法取出您需要的钱，请重新操作\n");
		}
	}else{
		printf("您取出的钱不是整百，请重新输入\n");
	}
}

// 取款逻辑业务
void drawMoneyLogical(){
	int i=0,flag=1;
	printf("欢迎来到取款界面\n");
	while(flag){
		printf("1 取款\n");
		printf("2 退出\n");
		scanf("%d",&i);
		switch(i){
		case 1:drawMoney();break;
		case 2:flag=0;break;
		default:printf("输入有误，请重新输入！\n");break;
		}
	}
	return;
}

//存款
void saveMoney(){
	char *oper = "存款";
	float money;
	Customer *user = (Customer*)getData(hashmap,custCurrent->accountCard);
	user = custCurrent;
	printf("欢迎来到存款界面\n");
	printf("请输入您要存储的钱(只存储整百元)\n");
	scanf("%f",&money);

	if(((int)money)/100 != 0 && ((int)money)%100 == 0){
		custCurrent->money += money;
		//printf("put进hashmap前的打印：银行卡号：%d，账户名称：%s，手机号码：%s，身份证：%s，密码：******，余额：%lf\n\n",custCurrent->accountCard,custCurrent->accountName,custCurrent->mobile,custCurrent->sfz,custCurrent->money);
		//putData(hashmap,custCurrent->accountCard,custCurrent);
		updateNode(head,custCurrent,user,sizeof(custCurrent));//将更新后的用户信息，也在链表中更新一份
		// 修改的信息存入源信息文件时，需要原来的时间，从链表中取出的时间有问题
		userUpgrade_filePut(head);
		userLogsRecords(custCurrent,oper);
		//修改的信息应该存入日志文件中
		printf("存储成功！\n");
		printf("您的银行卡号为：%d,现在的余额为:%f\n",custCurrent->accountCard,custCurrent->money);
	}else{
		printf("您存储的钱不是整百数，请重新存储整百的钱\n");
	}
	return;
}

//存款逻辑业务
void saveMoneyLogical(){
	int i=0,flag=1;
	printf("欢迎来到存款界面\n");
	while(flag){
		printf("1 存款\n");
		printf("2 退出\n");
		scanf("%d",&i);
		switch(i){
		case 1:saveMoney();break;
		case 2:flag=0;break;
		default:printf("输入有误，请重新输入！\n");break;
		}
	}
	return;
}

//查询余额
void showMoney(){
	char *oper = "查询余额";
	printf("欢迎来到查询余额界面\n");

	printf("您的银行卡号为:%d\n",custCurrent->accountCard);
	printf("您的余额为:%lf\n",custCurrent->money);
	userLogsRecords(custCurrent,oper);
	return;
}

//转账
void transferMoney(){
	char *oper = "转账";
	Customer* custTMP_1;
	int flag,accountCard;
	char accountName[10];
	float money=0;
	Customer *user = (Customer*)getData(hashmap,custCurrent->accountCard);
	user = custCurrent;

	printf("欢迎来到转账界面\n");
	printf("请输入您需要转账的账号 姓名\n");
	scanf("%d %s",&accountCard,&accountName);

	if((custTMP_1 = (Customer*)getData(hashmap,accountCard)) != NULL){
		//账号存在，开始校验姓名,get函数返回对应卡号的用户信息
		if(strcmp(accountName,accountName) == 0){
			printf("你要转账的用户名为：%s\n",custTMP_1->accountName);

			printf("请输入转账金额:\n");
			scanf("%f",&money);
			//在这里确认转账其实也可以做一个界面（优化）
			printf("确认转账请输入1，输入其他取消转账\n");
			scanf("%d",&flag);
			if(flag==1){
				//继续校验自己的账户是否有足够转账的金额
				if(((int)money)/100 != 0 && ((int)money)%100 == 0){
						if((custCurrent->money - money) >= 0){
							custCurrent->money -= money;
							custTMP_1->money += money;
							putData(hashmap,custCurrent->accountCard,custCurrent);
							putData(hashmap,custTMP_1->accountCard,custTMP_1);
							updateNode(head,custCurrent,user,sizeof(custCurrent));//将更新后的用户信息，也在链表中更新一份
							userUpgrade_filePut(head);
							userLogsRecords(custCurrent,oper);
							printf("转账成功！");
					}else{
						printf("您的账户上余额不足\n");
						return;
					}
				}
			}else{
				printf("取消转账！\n");
				return;
			}
		}
	}else{
		printf("您输入的账号不存在！");
		return;
	}
}

//这两个是不能写单独的函数的，应该嵌入到转账、存取功能函数中。
//余额变动记录--
void balanceChange(){
	
}

//用户的日志logs记录
void userLogsRecords(Customer *custTmp,char *oper){
	FILE *fp;
	char time[30];
	fp = fopen("用户logs日志文件.txt","a");
	currentTime(time);
	fprintf(fp,"%s %d %s %s\n",time,custTmp->accountCard,custTmp->accountName,oper);
	fclose(fp);
	return;
}

void user_fileGet(HashMap *hashmap,LinkNode *head,int userNum){
	FILE *fp;
	Customer custTmp,*user;
	userNum = 0;

	fp = fopen("用户源信息文件.txt","r");
	if(fp == NULL){
		perror("打开文件失败啦");
		system("pause");
		exit(1);
	}

	while(!feof(fp)){
		user = (Customer*)malloc(sizeof(Customer));
		if(fscanf(fp,"%s %d %s %s %s %s %lf\n",&custTmp.Time,&custTmp.accountCard,&custTmp.accountName,&custTmp.mobile,&custTmp.sfz,&custTmp.password,&custTmp.money)==7){
				*user = custTmp;
				putData(hashmap,custTmp.accountCard,user);
				addNode(head,user);
				userNum++;
			}else{
				printf("暂时没有任何学生信息，请先录入！\n");
				system("pause");
			}
		}
	fclose(fp);
}

//注册：将用户的信息存入文件中
void user_filePut(Customer *custTmp){
	FILE *fp;
	
	fp = fopen("用户源信息文件.txt","a");
	fprintf(fp,"%s %d %s %s %s %s %f\n",custTmp->Time,custTmp->accountCard,custTmp->accountName,custTmp->mobile,custTmp->sfz,custTmp->password,custTmp->money);
	fclose(fp);
	return;
}

//更新（存款、取款、转账、修改用户信息、修改密码）时用户源信息存入文件
void userUpgrade_filePut(LinkNode* head){
	FILE *fp;
	Customer *custTmp;
	fp = fopen("用户源信息文件.txt","w");
	while(nextNode(head)){
		head = nextNode(head);
		custTmp = (Customer*)head->data;
		fprintf(fp,"%s %d %s %s %s %s %f\n",custTmp->Time,custTmp->accountCard,custTmp->accountName,custTmp->mobile,custTmp->sfz,custTmp->password,custTmp->money);
	}
	fclose(fp);
}