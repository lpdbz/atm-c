#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hashmap.h"
#include"linkNode.h"

int hash(HashMap* hashmap,int k){
	k = abs(k) % hashmap->size;
	return k;
}

HashMap* createHash(int size){
	int i;
	HashMap *hashmap;
	hashmap = (HashMap*)malloc(sizeof(HashMap));

	hashmap->size = size;
	hashmap->table = (LinkNode*)malloc(size*sizeof(LinkNode));
	
	for(i=0;i<hashmap->size;i++){
		hashmap->table[i].data = NULL;
		hashmap->table[i].next = NULL;
	}
	return hashmap;
}


void* getData(HashMap* hashmap,int key){
	int pos;
	DataType* data;
	LinkNode* head,*node;

	//得到hash散列值
	pos = hash(hashmap,key);

	//拿到要找的数据的头结点
	head = &(hashmap->table[pos]);
	node = nextNode(head);
	//在这个链表中遍历找到key的值
	while(node){
		data = (DataType *)(node->data);
		if(data->key == key){
			return data->value;
		}
		node = nextNode(node);
	}
	return NULL;	
}

void putData(HashMap* hashmap,int key,void* value){
	int pos;
	DataType* data;
	LinkNode* head;

	data = (DataType*)malloc(sizeof(DataType));
	data->key = key;
	data->value = value;
	//得到hash散列值
	pos = hash(hashmap,key);
	head = &(hashmap->table[pos]);
	
	//向找到的头结点中插入数据
	addNode(head,data);
}


/*void printHashMap(HashMap* hashmap){
	int i;
	DataType* tmp;
	LinkNode* node = &(hashmap->table[0]);
	tmp = (DataType *)(hashmap->table[0].data);
	for(i=0;i<hashmap->size;i++){
		printf("hashmap的值为：[%d,%s]->",tmp->key,tmp->value);
		node = &(hashmap->table[i]);
		while(node->next){
			node = node->next;
			printf("[%d,%s]->",tmp->key,tmp->value);
		}
		printf("null\n\n");
	}
}*/

void destoryHashMap(HashMap* hashmap){
	LinkNode* head;
	int i;
	for(i=0;i<hashmap->size;i++){
		head = &(hashmap->table[i]);
		destoryLinkNode(head);
	}
	free(hashmap->table);
	free(hashmap);
}

int constainsKey(HashMap* hashmap,int key){
	return getData(hashmap,key) == NULL ? 0:1;
}

/*void main1111(){	
	int key,fkey;
	char value[10];
	HashMap *hashmap = createHash(10);
	while(1){
		printf("请输入需要存储的key和value(输入'q'退出插入)\n");
		if(scanf("%d",&key)==1 && key >= 0 ){
			scanf("%s",&value);
			putData(hashmap,key,value);
		}else{
			printf("输入异常值，结束插入！\n");
			break;
		}
	}
	printHashMap(hashmap);

	printf("请输入你需要得到的key:\n");
	fflush(stdin);
	scanf("%d",&fkey);
	printf("fkey=%d\n",fkey);
	getData(hashmap,fkey);
	destoryHashMap(hashmap);
}*/