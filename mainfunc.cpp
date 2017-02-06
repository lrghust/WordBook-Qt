#include "load.h"
#include "WordBook.h"
SqList L;
SqList Ls;
HashTable H;
double Load::ct1;
double Load::ct2;
double Load::ct3;

bool init(char *path){
    Load::ct1=0;
    Load::ct2=0;
    Load::ct3=0;

    //char path[INIT_LEN]="/Users/lrg/data_structure/test.txt";
    if(!createSqList()){
        return false;
    }
    if(!initHash()){
        return false;
    }
    if(!loadBook(path)){
        return false;
    }
    clock_t start=clock();
    if(!createSortedSqList()){
        return false;
    }
    SortSqList(Ls.elem,Ls.length);
    clock_t end=clock();
    Load::ct2=(double)(end-start)/CLOCKS_PER_SEC*1000.0;
    return true;
}

bool loadBook(char *path){
    FILE *pf=fopen(path,"r");
    if(!pf){
        //cout<<"文件打开失败！"<<endl;
        //QMessageBox::information(this,"Error","文件打开失败！");
        return false;
    }
    int letters=0;
    int lines=0;
    int pages=1;
    char line[LETTERS_PER_LINE+1];
    char word[DEFAULT_LEN];
    while(fgets(line,LETTERS_PER_LINE-letters,pf)!=NULL){//读取一行（可能是空行、可能读到一半单词、可能提前结束）
        lines++;
        if(lines>LINES_PER_PAGE){
            pages++;
            lines=1;
        }
        char *pline=line;
        while(sscanf(pline,"%s",word)!=-1){//读取单词（可能有标点符号、可能是一半单词）
            int len=(int)strlen(word);
            while(isspace(*pline))
                pline++;
            pline+=len;
            if( *pline=='\0' && !isspace(*(pline-1)) ){//读到结尾，判断是否为半个单词
                char next;
                char last[DEFAULT_LEN];//存储后一半单词
                int ntmp=0;//后一半单词字母数
                while(true){
                    next=fgetc(pf);
                    if(!isspace(next)){
                        last[ntmp]=next;
                        ntmp++;
                    }
                    else break;
                }
                last[ntmp]='\0';
                strcat(word, last);//拼成完整单词
                letters=ntmp;
                ungetc(next, pf);
            }
            getWord(word);

            clock_t start=clock();
            loadSqList(word,pages,lines);
            clock_t end=clock();
            Load::ct1+=(double)(end-start)/CLOCKS_PER_SEC*1000.0;

            start=clock();
            insertHash(word,pages,lines);
            end=clock();
            Load::ct3+=(double)(end-start)/CLOCKS_PER_SEC*1000.0;
        }
    }
    return true;
}

void getWord(char *word){//问题：破折号、连字符只能提取第一个单词
    while(isalpha(*word)){
        *word=tolower(*word);
        word++;
    }
    *word='\0';
}

bool saveData(void){
    char path[100]="save.dat";
    FILE *p=fopen(path,"wb+");
    if(!p){
        return false;
    }
    //建表时间
    fwrite(&Load::ct1,sizeof(double),1,p);
    fwrite(&Load::ct2,sizeof(double),1,p);
    fwrite(&Load::ct3,sizeof(double),1,p);

    fwrite(&L.length,sizeof(int),1,p);//单词数
    for(int i=0;i<L.length;i++){
        fwrite(L.elem[i].word,sizeof(L.elem[i].word),1,p);//单词
        fwrite(&L.elem[i].count,sizeof(int),1,p);//重复次数
        WordInfo *q=L.elem[i].info.next;
        while(q){
            fwrite(&q->pages,sizeof(int),1,p);//页码
            fwrite(&q->lines,sizeof(int),1,p);//行号
            q=q->next;
        }
        fwrite(&L.elem[i].info.pages,sizeof(int),1,p);
        fwrite(&L.elem[i].info.lines,sizeof(int),1,p);
    }
    fclose(p);
    return true;
}

bool loadData(char *path){
    FILE *p=fopen(path,"rb");
    if(!p){
        return false;
    }
    fread(&Load::ct1,sizeof(double),1,p);
    fread(&Load::ct2,sizeof(double),1,p);
    fread(&Load::ct3,sizeof(double),1,p);

    fread(&L.length,sizeof(int),1,p);
    L.listsize=L.length;
    L.elem=(SqElemType *)malloc(L.listsize*sizeof(SqElemType));

    if(!L.elem||!initHash()){
        return false;
    }

    char word[DEFAULT_LEN];
    int count;
    for(int i=0;i<L.length;i++){
        fread(word,sizeof(word),1,p);
        fread(&count,sizeof(int),1,p);
        //线性表
        strcpy(L.elem[i].word,word);
        L.elem[i].count=count;
        L.elem[i].info.next=NULL;
        //哈希表
        int index=hashFunction(word);
        WordInfo *hinfo=NULL;
        if(H.elem[index].count==0){
            strcpy(H.elem[index].word,word);
            H.elem[index].count=count;
            hinfo=&H.elem[index].info;
        }
        else{//冲突
            HashElemType *h=(HashElemType *)malloc(sizeof(HashElemType));
            strcpy(h->word,word);
            h->count=count;
            h->info.next=NULL;
            h->next=H.elem[index].next;
            H.elem[index].next=h;
            hinfo=&h->info;
        }
        fread(&L.elem[i].info.pages,sizeof(int),1,p);
        fread(&L.elem[i].info.lines,sizeof(int),1,p);
        hinfo->pages=L.elem[i].info.pages;
        hinfo->lines=L.elem[i].info.lines;
        for(int j=1;j<count;j++){
            WordInfo *tmp=(WordInfo *)malloc(sizeof(WordInfo));
            fread(&tmp->pages,sizeof(int),1,p);
            fread(&tmp->lines,sizeof(int),1,p);
            tmp->next=L.elem[i].info.next;
            L.elem[i].info.next=tmp;
            hinfo->next=tmp;//线性表和哈希表共用一个子链表
        }
    }
    fclose(p);
    if(!createSortedSqList()){
        return false;
    }
    SortSqList(Ls.elem,Ls.length);
    return true;
}
