#include "WordBook.h"
bool initHash(HashTable &H){
    H.length=HASH_LEN;
    H.elem=(HashElemType *)malloc(H.length*sizeof(HashElemType));
    if(!H.elem){
        cout<<"内存申请失败！"<<endl;
        return false;
    }
    for(int i=0;i<H.length;i++){
        H.elem[i].count=0;
        H.elem[i].next=NULL;
        H.elem[i].info.next=NULL;
    }
    return true;
}

void insertHash(HashTable &H,char *word, int pages, int lines){
    int index=hashFunction(word);
    if(H.elem[index].count==0){
        strcpy(H.elem[index].word,word);
        H.elem[index].count=1;
        H.elem[index].info.pages=pages;
        H.elem[index].info.lines=lines;
    }
    else if(!strcmp(word,H.elem[index].word)){
        H.elem[index].count++;
        WordInfo *tmp=(WordInfo *)malloc(sizeof(WordInfo));
        *tmp={pages,lines,NULL};
        tmp->next=H.elem[index].info.next;
        H.elem[index].info.next=tmp;
    }
    else{//冲突
        HashElemType *tmp=H.elem[index].next;
        while(tmp){
            if(!strcmp(tmp->word,word)){
                tmp->count++;
                WordInfo *tmpinfo=(WordInfo *)malloc(sizeof(WordInfo));
                *tmpinfo={pages,lines,NULL};
                tmpinfo->next=tmp->info.next;
                tmp->info.next=tmpinfo;
                break;
            }
            tmp=tmp->next;
        }
        if(tmp==NULL){
            tmp=(HashElemType *)malloc(sizeof(HashElemType));
            strcpy(tmp->word, word);
            tmp->count=1;
            tmp->info.pages=pages;
            tmp->info.lines=lines;
            tmp->info.next=NULL;
            tmp->next=H.elem[index].next;
            H.elem[index].next=tmp;
        }
    }
}
//BKDR hash function
int hashFunction(char *word){
    int seed=131;
    unsigned long hash=0;
    while(*word!='\0'){
        hash=hash*seed+*word++;
    }
    return hash%H.length;
}
HashElemType *searchHash(HashTable H,char *word){
    int index=hashFunction(word);
    HashElemType *tmp=&H.elem[index];
    while(tmp){
        if(!strcmp(tmp->word,word)){
            return tmp;
        }
        tmp=tmp->next;
    }
    return NULL;
}
bool destroyHash(HashTable &H){
    if(!H.elem)
        return false;
    for(int i=0;i<H.length;i++){
        HashElemType *p1=H.elem[i].next;
        HashElemType *q1=p1;
        while(p1){//冲突链表
            q1=q1->next;
            WordInfo *p2=p1->info.next;
            WordInfo *q2=p2;
            while(p2){//重复链表
                q2=q2->next;
                free(p2);
                p2=q2;
            }
            free(p1);
            p1=q1;
        }
    }
    free(H.elem);
    H.length=0;
    H.elem=NULL;
    return true;
}
bool traverseHash(HashTable &H){
    if(!H.elem)
        return false;
    for(int i=0;i<H.length;i++){
        cout<<i+1<<":"<<endl;
        if(H.elem[i].count==0)
            continue;
        cout<<H.elem[i].word<<" ";
        HashElemType *p=H.elem[i].next;
        while(p){
            cout<<p->word<<" ";
            p=p->next;
        }
        cout<<endl;
    }
    return true;
}

bool deleteHash(HashTable &H, char *word){
    if(!H.elem)
        return false;
    int index=hashFunction(word);
    HashElemType *p=&H.elem[index];
    HashElemType *q=p;
    if(!strcmp(p->word,word)){
        q=q->next;
        WordInfo *p1=p->info.next;
        WordInfo *q1=p1;
        while(q1){
            q1=q1->next;
            free(p1);
            p1=q1;
        }
        *p=*q;
        free(q);
        return true;
    }
    while(q->next){
        q=q->next;
        if(!strcmp(q->word,word)){
            p->next=q->next;
            WordInfo *p1=q->info.next;
            WordInfo *q1=p1;
            while(q1){
                q1=q1->next;
                free(p1);
                p1=q1;
            }
            free(q);
            return true;
        }
        p=q;
    }
    return false;
}
