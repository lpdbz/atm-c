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

//hashmap的添加数据是新增和更新操作的合并
void putData(HashMap* hashmap,void* data){
	int pos;
	DataType *data1;
	LinkNode* head;

	//得到hash散列值
	pos = hash(hashmap,((DataType*)data)->key);
	head = &(hashmap->table[pos]);

	//如果hashmap中存在，则更新节点；如果不存在，则添加节点
	if((DataType*)getData(hashmap,((DataType*)data)->key)){
		data1 = (DataType*)getData(hashmap,((DataType*)data)->key);
		updateNode(head,data,data1,sizeof(DataType));
	}else{
		//向找到的链表的头结点中插入数据
		addNode(head,data);
	}
}


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