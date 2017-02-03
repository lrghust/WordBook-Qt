#include<iostream>
#include<cstring>
#include<cctype>
#include<cstdlib>
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
bool createSqList(void);
bool createSortedSqList(void);
void loadSqList(char *word,int pages,int lines);
int searchUnsortedSqList(char *word);
int searchSortedSqList(char *word);
int biSearch(char *word,int begin,int end);
void SortSqList(SqElemType *elem,int num);
void QuickSort(SqElemType *elem,int low,int high);
int Partition(SqElemType *elem,int low,int high);

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
bool initHash(void);
void insertHash(char *word, int pages, int lines);
int hashFunction(char *word);
HashElemType *searchHash(char *word);
//main
extern SqList L;
extern SqList Ls;
extern HashTable H;
bool loadBook(char *path);
void getWord(char *word);
