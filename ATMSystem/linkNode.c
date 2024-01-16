#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "linkNode.h"

// 初始化一个节点
LinkNode* createNode(){
	LinkNode* head;
	head = (LinkNode*)malloc(sizeof(LinkNode));
	head->next = NULL;
	return head;
}

// 添加节点
void addNode(LinkNode* head,void* data){
	while(head->next){
		head = nextNode(head);
	}
	head->next = (LinkNode*)malloc(sizeof(LinkNode));
	head = nextNode(head);
	head->data = data;
 	head->next = NULL;
}

// 删除节点
void deleted(LinkNode* head,void* data,int size){
	LinkNode* temp;
	while(head->next){
		temp = head->next;
		if(checkDataNode(temp->data,data,size)){
			head->next=temp->next;
			free(temp);
		}else{
			head=head->next;
		}
	}
}

//更新链表：根据旧数据进行查找，如果存在旧数据则修改为新数据
void updateNode(LinkNode* head,void* newData,void* oldData,int size){
	while(head->next){
		head = head->next;
		if(checkDataNode(head->data,oldData,size)){
			head->data = newData;
		}
	}
}

// 检查是否存在某节点，传入地址，地址可以变化
int checkDataNode(void* origin,void* now,int size){
	return memcmp(origin,now,size)==0 ? 1:0;
}

// 返回当前节点的下一个节点
LinkNode* nextNode(LinkNode* node){
	return node->next;
}

//从前往后一个个节点删除
void destoryLinkNode(LinkNode* head){
	LinkNode* node;
	while(head->next){
		node = nextNode(head);
		head->next = nextNode(node);
		free(node->data);
		free(node);
	}
	free(head);
}