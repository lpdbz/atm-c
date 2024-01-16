#pragma once

typedef struct LinkNode{
	void* data;
	struct LinkNode* next;
}LinkNode;

LinkNode* createNode();

void addNode(LinkNode* head,void* data);

void deletedNode(LinkNode* head,void* data);

void updateNode(LinkNode* head,void* newData,void* oldData,int size);

int checkDataNode(void* origin,void* now,int size);

LinkNode* nextNode(LinkNode* node);

void destoryLinkNode(LinkNode* head);

void printLink(LinkNode* head);