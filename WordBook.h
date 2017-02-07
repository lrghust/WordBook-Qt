#ifndef _WORDBOOK_H_
#define _WORDBOOK_H_
#include<iostream>
#include<cstring>
#include<cctype>
#include<cstdlib>
#include<cstdio>
#include<ctime>
const int DEFAULT_LEN=20;
const int LETTERS_PER_LINE=50;
const int LINES_PER_PAGE=50;
const int HASH_LEN=10000;
using namespace std;
//线性表ADT
const int INIT_LEN=100;//线性表初始长度
const int STEP_LEN=10;//线性表动态增加长度
typedef struct WordInfo{
    int pages;
    int lines;
    struct WordInfo *next;
}WordInfo;
typedef struct{//线性表数据元素
    char word[DEFAULT_LEN];
    int count;
    WordInfo info;
}SqElemType;
typedef struct{//线性表结构
    SqElemType *elem;
    int length;
    int listsize;
}SqList;
bool createSqList(SqList &L);
bool createSortedSqList(SqList L, SqList &Ls);
void loadSqList(SqList &L,char *word,int pages,int lines);
int searchUnsortedSqList(SqList &L,char *word);
int searchSortedSqList(SqList &Ls,char *word);
void sortSqList(SqList Ls);
bool destroySqList(SqList &L);
bool destroySortedSqList(SqList &Ls);
void traverseSqList(SqList L,void (* visit)(SqElemType *));
void visitSqList(SqElemType *elem);

//Hash
typedef struct HashElemType{
    char word[DEFAULT_LEN];
    int count;
    WordInfo info;
    struct HashElemType *next;//不同的单词（冲突）
}HashElemType;
typedef struct{
    int length;
    HashElemType *elem;
}HashTable;
bool initHash(HashTable &H);
void insertHash(HashTable &H,char *word, int pages, int lines);
HashElemType *searchHash(HashTable H,char *word);
bool destroyHash(HashTable &H, bool resume);
bool traverseHash(HashTable H, void (* visit)(HashElemType *));
void visitHash(HashElemType *elem);
bool deleteHash(HashTable &H, char *word);
int hashFunction(char *word);

//main
extern SqList L;
extern SqList Ls;
extern HashTable H;
bool init(char *path);
bool loadBook(char *path);
void getWord(char *word);
bool saveData(char *path);
bool loadData(char *path);

#endif
