#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hashmap.h"
#include"linkNode.h"
#include"user.h"
#include"time.h"

#define N 10
int userNum = 0; // 记录现在银行共有多少个用户
static double BankTotalMoney = 0.0;

HashMap* hashmap;//第一次运行的时候，会从文件中读取所有用户，在注册的时候，不仅会往文件中写入一份，也会往hashmap写入一份
LinkNode* head;//head同hashmap一样，head和hashmap的指针里面存储着同一块地址（即可以获取修改同一块地址里面的内容）
Customer* custCurrent;//存储当前用户的信息，每一次修改用户信息后，都应该重新赋一次值

void initUser(){
	hashmap = createHash(N);
	head = createNode();
	user_fileGet(hashmap,head,userNum);
	Bank_TotalAmount_fileGet(BankTotalMoney);
}

//登录
void login(){
	int accountCard;  // 存储登录用户输入的账号，用于后续做账号比较
	char password[7];  // 存储登录用户输入的密码，用于后续做密码比较
	char *oper = "登录";  // 登录操作，写入日志文件
	printf("欢迎来到登录界面\n");
	while(1){
		printf("请输入您的银行卡号和密码:\n");
		scanf("%d %s",&accountCard,&password);
		//去记录中查找，检查1.是否存在此卡号；2.密码是否正确
		if((Customer*)getData(hashmap,accountCard)!=NULL){
			//接下来检查密码是否输入正确
			custCurrent = (Customer*)getData(hashmap,accountCard); //查找成功，就将查找到的信息赋值一份给custCurrent，便于后面一直拿到用户的信息
			if(strcmp(password,custCurrent->password)==0){
				//将用户信息记录到日志logs记录文件中
				userLogsRecords(custCurrent,oper);
				printf("登录成功，请继续接下来的操作\n");
				return;	
			}else{
				printf("密码输入错误！请重新操作\n");
			}
		}else{
			printf("银行卡号和密码输入错误，请重新输入：\n");
			continue;
		}
	}
}

//注册
void sign(){
	char pw[7];  // 用于确认密码
	char *oper = "注册";
	DataType* data = (DataType*)malloc(sizeof(DataType)); //存储DataType类型的data数据，包括key和value，value就是Customer类型
	Customer* user = (Customer*)malloc(sizeof(Customer)); //存储注册用户的所有信息

	printf("欢迎来到注册界面\n");	
	printf("请依次输入您的名字  手机号码  身份证:\n");
	scanf("%s %s %s",&user->accountName,&user->mobile,&user->sfz);
	user->accountCard = atoi(user->sfz); // 将字符串类型的身份证转化为数字类型的银行账号

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
	user->money = 0.0;  // 注册的时候用户的余额为0
	
	currentTime(user->Time);  // 获取当前时间存入user中，表示创建用户的时间
	data->key = user->accountCard;
	data->value = (Customer *) malloc(sizeof(Customer));//data的value也需要malloc出来
    memcpy(data->value, user, sizeof(Customer));//将注册用户信息内容复制到data->value中

	putData(hashmap,data); // 将刚刚注册的用户信息存储到hashmap中
	addNode(head,data); // 将刚刚注册的用户信息存储到head中
	user_filePut(user);
	userLogsRecords(user,oper);
	printf("两次输入密码正确，银行卡注册成功!\n");
	free(user);  // 为什么可以free掉，也忘记了
	//free(data->value); // 为什么不能free掉，忘记了
	//free(data);
	return;
}

//修改用户信息 
void updateInfo(){
	char *oper = "修改用户信息";
	int i=0;
	int flag = 1;
	Customer *user = (Customer*)getData(hashmap,custCurrent->accountCard);

	printf("欢迎来到修改个人信息界面:\n");
	printf("您的信息为：");
	printf("银行卡号：%d，账户名称：%s，手机号码：%s，身份证：%s，密码：******，余额：%lf\n\n",user->accountCard,user->accountName,user->mobile,user->sfz,user->money);
	
	while(flag){
		printf("请问你要修改什么信息？\n");
		printf("1 修改账户名称\n");  // 有些人改名了
		printf("2 修改电话号码\n");
		printf("3 修改密码\n");  // 认为在修改信息的时候，密码也属于个人信息，应该兼容
		printf("0 退出修改个人信息界面\n");

		scanf("%d",&i);
		switch(i){
		case 1:printf("请输入账户名称:\n");scanf("%s", &user->accountName);break;
		case 2:printf("请输入电话号码:\n");scanf("%s", &user->mobile);break;
		case 3:printf("请输入要修改的密码:\n");scanf("%s", &user->password);break;
		case 0:flag = 0;break;
		default:printf("输入有误，请输入对应的值");
		}
		printf("您的信息为：");
		printf("银行卡号：%d，账户名称：%s，手机号码：%s，身份证：%s，密码：******，余额：%lf\n\n",user->accountCard,user->accountName,user->mobile,user->sfz,user->money);
	}

	custCurrent = user;
	userUpgrade_filePut(head);
	userLogsRecords(user,oper);
	printf("修改用户信息成功！ ");
	system("pause");
	return;
}

//修改密码
void changePW(){
	char *oper = "修改密码";
	char passWord[7],passWord_1[7];
	Customer *user = (Customer*)getData(hashmap,custCurrent->accountCard);

	printf("欢迎来到修改密码界面\n");
	while(1){
		printf("请输入原密码:\n");
		scanf("%s",&passWord);

		if(strcmp(passWord,user->password) == 0){
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
	strcpy(user->password,passWord_1);
	custCurrent = user;
	userUpgrade_filePut(head);
	userLogsRecords(user,oper);
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
			putData(hashmap,custCurrent);
			updateNode(head,custCurrent,user,sizeof(custCurrent));//将更新后的用户信息，也在链表中更新一份
			userUpgrade_filePut(head);
			userLogsRecords(custCurrent,oper);
			Bank_TotalAmountChange(oper,custCurrent,money);
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
		Bank_TotalAmountChange(oper,custCurrent,money);
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

//转账--目前只能本行转账本行
void transferMoney(){
	char oper[10] = "转账";
	char oper1[10] = "转账";
	Customer* custTMP_1;
	int flag,accountCard;
	char accountName[10];
	float money=0;
	Customer *user = (Customer*)getData(hashmap,custCurrent->accountCard);
	user = custCurrent;

	printf("欢迎来到转账界面\n");
	while(1){
		printf("请输入您需要转账的账号 姓名\n");
		scanf("%d %s",&accountCard,&accountName);
		if((custTMP_1 = (Customer*)getData(hashmap,accountCard)) != NULL){
			//账号存在，开始校验姓名,get函数返回对应卡号的用户信息
			if(strcmp(custTMP_1->accountName,accountName) == 0){
				printf("你要转账的用户名为：%s\n",custTMP_1->accountName);
				while(1){
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
									userUpgrade_filePut(head);
									userLogsRecords(custCurrent,oper);
									Bank_TotalAmountChange(strcat(oper,"发起方"),custCurrent,money);
									Bank_TotalAmountChange(strcat(oper1,"接收方"),custCurrent,money);
									printf("转账成功！");
									return;
								}else{
									printf("您的账户上余额不足,请重新输入\n");
									continue;
								}
						}else{
							printf("请输入整百转账金额\n");
						}
					}else{
						printf("取消转账！\n");
						return;
					}
				}
			}else{
				printf("您输入银行账号对应的账号姓名不对，请重新输入\n");
				continue;
			}
		}else{
			printf("您输入的账号不存在！");
			return;
		}
	}
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

// 从文件中获取全部的信息
void user_fileGet(HashMap *hashmap, LinkNode *head, int userNum) {
    FILE *fp;
    Customer custTmp;
    DataType *user;

    fp = fopen("用户源信息文件.txt", "r");
    if (fp == NULL) {
        perror("打开文件失败啦");
        system("pause");
        exit(1);
    }

    while (!feof(fp)) {
        if (fscanf(fp, "%s %d %s %s %s %s %lf\n", &custTmp.Time, &custTmp.accountCard, &custTmp.accountName, &custTmp.mobile, &custTmp.sfz, &custTmp.password, &custTmp.money) == 7) {
            user = (DataType *) malloc(sizeof(DataType));
            user->value = (Customer *) malloc(sizeof(Customer));
            memcpy(user->value, &custTmp, sizeof(Customer));//将custTmp的值复制到user->value中
            user->key = custTmp.accountCard;
            putData(hashmap, user);
            addNode(head, user);
            userNum++;
        } else {
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

// 记录银行总体金额变化
// 这个money是进行金钱操作的金额
void Bank_TotalAmountChange(char *oper,Customer *custTmp,double money){
	FILE *fp;
	char time[30];
	currentTime(time);
	if(strcmp(oper,"存款")){
		BankTotalMoney += money;
	}else if(strcmp(oper,"取款")){
		BankTotalMoney -= money;
	}
	fp = fopen("银行总金额变化文件.txt","a");
	fprintf(fp,"%s %d %s %f %f\n",time,custTmp->accountCard,oper,money,BankTotalMoney);
	fclose(fp);
	return;
}

// 从银行总金额文件中获取全部的信息Bank_TotalAmountChange;
void Bank_TotalAmount_fileGet(double BankTotalMoney) {
    //double BankTotalMoney = 0;
    char line[256];
    char *last_line = NULL;
    FILE *fp = fopen("银行总金额变化文件.txt", "r");
    if (fp == NULL) {
        perror("打开文件失败啦");
        system("pause");
        exit(1);
    }
    while (fgets(line, sizeof(line), fp)) {
        last_line = strdup(line);
    }

    if (last_line != NULL) {
        char *last_num_str = strrchr(last_line, ' ');
        if (last_num_str != NULL) {
            BankTotalMoney = atoi(last_num_str);
        }
        free(last_line);
    }

    printf("The last number in the file is: %lf\n", BankTotalMoney);
    fclose(fp);
    return;
}


// 更新（存款、取款、转账、修改用户信息、修改密码）时用户源信息存入文件
// 暂时没有用到，直接用指针指向那片地址，然后修改了
void userUpgrade_filePut(LinkNode* head){
	FILE *fp;
	Customer *custTmp;
	DataType *user;
	fp = fopen("用户源信息文件.txt","w");
	while(nextNode(head)){
		head = nextNode(head);
		user = ((DataType*)head->data);
		custTmp = (Customer*)user->value;
		fprintf(fp,"%s %d %s %s %s %s %f\n",custTmp->Time,custTmp->accountCard,custTmp->accountName,custTmp->mobile,custTmp->sfz,custTmp->password,custTmp->money);
	}
	fclose(fp);
}