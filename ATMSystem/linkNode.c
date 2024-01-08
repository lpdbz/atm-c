#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "linkNode.h"

LinkNode* createNode(){
	LinkNode* head;
	head = (LinkNode*)malloc(sizeof(LinkNode));
	head->next = NULL;
	return head;
}

void addNode(LinkNode* head,void* data){
	while(head->next){
		head = head->next;
	}
	head->next = (LinkNode*)malloc(sizeof(LinkNode));
	head = head->next;
	head->data = data;
	head->next = NULL;
}

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

int checkDataNode(void* origin,void* now,int size){
	return memcmp(origin,now,size)==0 ? 1:0;
}

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