#pragma once

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

int hash(HashMap* hashmap,int k);

HashMap* createHash(int size);

void* getData(HashMap* hashmap,int key);

void putData(HashMap* hashmap,void* value);

void destoryHashMap(HashMap* hashmap);

int constainsKey(HashMap* hashmap,int key);