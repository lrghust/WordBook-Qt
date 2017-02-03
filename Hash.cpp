#include "WordBook.h"
bool initHash(void){
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

void insertHash(char *word, int pages, int lines){
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
HashElemType *searchHash(char *word){
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
