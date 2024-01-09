#include<stdio.h>
#include<stdlib.h>
#include"user.h"
#include"hashmap.h"

//从文件中取出用户信息
void user_fileGet(){
	FILE *fp;
	Customer custTmp;
	//HashNode* node = &(hashmap->table[0]);
	fp = fopen("用户源信息.txt","r");
	if(fp == NULL){
		perror("打开文件失败啦");
		system("pause");
		exit(1);
	}
	while(!feof(fp)){
		if(fscanf(fp,"%d %s %s %s %s %lf\n",&custTmp.accountCard,&custTmp.accountName,&custTmp.mobile,&custTmp.sfz,&custTmp.password,&custTmp.money)==6){
				putData(hashmap,custTmp.accountCard,&custTmp);
				userNum++;
			}else{
				printf("暂时没有任何学生信息，请先录入！\n");
				system("pause");
			}
		}
	fclose(fp);
}

//将用户的信息存入文件中
void user_filePut(){
	FILE *fp;
	Customer* custTmp;
	LinkNode* node = nextNode(head);

	fp = fopen("用户源信息.txt","w+");
	while(node){
		custTmp = (Customer *)&node->data;
		fprintf(fp,"%d %s %s %s %s %lf\n",custTmp->accountCard,custTmp->accountName,custTmp->mobile,custTmp->sfz,custTmp->password,custTmp->money);
		node = node->next;
	}
	fclose(fp);
	return;
}

//将余额变动的信息、用户登录的信息存入文件中

//从文件中取出余额变动信息



//从文件中取出余额变动信息

//将管理员操作日志文件存入文件中
void admin_filePut(char* ch){
	FILE *fp;

	fp = fopen("管理员操作日志文件.txt","w+");
	fprintf(fp,"%s\n",ch);
	fclose(fp);
	return;
}

//从文件中取出管理员操作日志
void admin_fileGet(){
	FILE *fp;
	char ch[10];
	fp = fopen("管理员操作日志文件.txt","r");
	if(fp == NULL){
		perror("打开文件失败啦");
		system("pause");
		exit(1);
	}
	while(!feof(fp)){
		if(fscanf(fp,"%s\n",&ch)==1){
				printf("管理员的操作为：%s",ch);
			}else{
				printf("管理员暂时没有操作！\n");
				system("pause");
			}
		}
	fclose(fp);
}