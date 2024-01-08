#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"linkNode.h"

typedef struct DataType{
	int key;
	void* value;
}DataType;

typedef struct HashMap{
	int size;
	LinkNode* table;
}HashMap;

//int hash(HashMap* hashmap,int k);

// 创建一个hash表，并指定它的大小
HashMap* createHash(int size);

//从hash表中获取数据
void* getData(HashMap* hashmap,int key);

//往hash表中放入数据
void putData(HashMap* hashmap,int key,void* value);

//销毁hash表
void destoryHashMap(HashMap* hashmap);

int constainsKey(HashMap* hashmap,int key);