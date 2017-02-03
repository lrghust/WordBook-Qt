#include "WordBook.h"

bool createSqList(void){//创建线性表
    L.elem=(SqElemType *)malloc(INIT_LEN*sizeof(SqElemType));
    if(!L.elem){
        cout<<"内存申请失败！"<<endl;
        return false;
    }
    return true;
}
bool createSortedSqList(void){
    Ls.length=L.length;
    Ls.listsize=L.length;
    Ls.elem=(SqElemType *)malloc(Ls.listsize*sizeof(SqElemType));
    if(!Ls.elem){
        cout<<"内存申请失败！"<<endl;
        return false;
    }
    for(int i=0;i<Ls.length;i++){
        Ls.elem[i]=L.elem[i];
    }
    return true;
}
void loadSqList(char *word,int pages,int lines){//向线性表中加入新单词
    int i;
    for(i=0;i<L.length;i++){
        if(!strcmp(word,L.elem[i].word)){//找到该单词已存在
            L.elem[i].count++;
            WordInfo *newinfo=(WordInfo *)malloc(sizeof(WordInfo));//将新信息插入链表
            *newinfo={pages,lines,NULL};
            newinfo->next=L.elem[i].info.next;
            L.elem[i].info.next=newinfo;
            return;
        }
    }
    //该单词不存在
    if(L.length==L.listsize){//线性表大小不足
        L.listsize+=STEP_LEN;//线性表重新分配内存，增加大小
        L.elem=(SqElemType *)realloc(L.elem,L.listsize*sizeof(SqElemType));
    }
    L.length++;//线性表存储单词个数增加1
    //加入新单词
    strcpy(L.elem[i].word, word);
    L.elem[i].count=1;
    L.elem[i].info.pages=pages;
    L.elem[i].info.lines=lines;
    L.elem[i].info.next=NULL;
}

int searchUnsortedSqList(char *word){
    for(int i=0;i<L.length;i++){
        if(!strcmp(L.elem[i].word, word)){
            return i+1;
        }
    }
    return -1;
}

int searchSortedSqList(char *word){
    return biSearch(word,1,Ls.length);
}

int biSearch(char *word,int begin,int end){
    if(begin>end)
        return -1;
    int mid=(begin+end)/2;
    int n=strcmp(Ls.elem[mid-1].word,word);
    if(n==0)
        return mid;
    else if(n<0)
        return biSearch(word, mid+1, end);
    else
        return biSearch(word, begin, mid-1);
}

void SortSqList(SqElemType *elem,int num){
    QuickSort(elem,1,num);
}
void QuickSort(SqElemType *elem,int low,int high){
    if(low<high){
        int pivot=Partition(elem,low,high);
        QuickSort(elem,low,pivot-1);
        QuickSort(elem,pivot+1,high);
    }
}
int Partition(SqElemType *elem,int low,int high){
    SqElemType pivot=elem[low-1];
    while(low<high){
        while(low<high&&strcmp(elem[high-1].word,pivot.word)>=0)high--;
        elem[low-1]=elem[high-1];
        while(low<high&&strcmp(elem[low-1].word,pivot.word)<=0)low++;
        elem[high-1]=elem[low-1];
    }
    elem[low-1]=pivot;
    return low;
}
