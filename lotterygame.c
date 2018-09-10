#include <stdio.h>
#include <simpio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <random.h>
#include <ctype.h>
#include <strlib.h>


void information(void);
void input_message(void);
void set_message(void);
void awards_number(void);
void start_lottery(void);
void unroll_lottery(void);
void message(void);
void roll_lottery(int b);
void read_file_studmessage(int n);
void set_awards(void);
int newkbhit(void);
void close_keyboard(void);
void init_keyboard(void);
void zhouyi(char *buf);
void award_message(int n);
void lottery(int i,int b);
int num_prize(int j);

#define MAX 10
#define MAX1 100
static struct termios old_set, new_set;
static int flag=-1;
static int num=0;
static char *my_buf[MAX1]={" "};
 
int main()
{
    message();
    remove("first_list.txt");
    remove("second_list.txt");
    remove("third_list.txt");
    while(1){ 
        information();
        struct termios old,new;
        tcgetattr(0,&old);
        new=old;
        new.c_lflag &= ~ECHO;
        tcsetattr(0,TCSANOW,&new);
        int i=GetInteger();
        tcsetattr(0,TCSANOW,&old);
        if(i==0)break;
        switch(i){
            case 1: 
                input_message();break;
            case 2:
                set_message();break;
            case 3:
                awards_number();break;
            case 4:
                set_awards();break;
            case 5:
                start_lottery();break;
            case 0:
                break;
            default:
                puts("请输入正确序号");break;
               
        }
    }
    return 0;
}
void message(void)
{
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("*                                                 *\n");
    printf("*                                                 *\n");
    printf("*             \033[1;31mWELCOME TO LOTTERYGAME\033[0m              *\n");
    printf("*                                                 *\n");
    printf("*                                                 *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * *\n");
}
void information(void)
{
    printf("\033[1;34m选择你想设置的 请输入其序号\033[0m\n");
    printf("1:输入抽奖人信息\n");
    printf("2:设置抽奖项目信息简介\n");
    printf("3:定抽奖奖项以及每个奖项个数\n");
    printf("4:抽奖奖品信息设置\n");
    printf("5:开始抽奖\n");
    printf("6:抽奖历史信息的统计\n");
    printf("7:历史信息的查询\n");
    printf("8：历史信息清除\n");
    printf("0:退出程序\n");
}
void input_message(void){}
void set_message(void){}
void awards_number(void){}
void set_awards(void)
{
    puts("输入一等奖奖品: (输入over结束)");
    award_message(1);
    puts("输入二等奖奖品: (输入over结束)");
    award_message(2);
    puts("输入三等奖奖品: (输入over结束)");
    award_message(3);
}
    
void award_message(int n)
{
    FILE *fp;
    char data[MAX1];
    char *record[MAX1];
    if(n==1)
        fp = fopen("first_awards.txt","w+");
    else if(n==2)
        fp = fopen("second_awards.txt","w+");
    else if(n==3)
        fp = fopen("third_awards.txt","w+");
    while(1)
        {
            fgets(data,MAX1,stdin);
            string line=SubString(data,0,strlen(data)-2);
            if(!strcmp(line,"over"))break;
            fputs(data,fp);
        }
}
void start_lottery(void) 
{
    int b,j;
    string line;
    puts("请选择抽奖候选人信息（1：学号2：姓名3：身份证号）输入相应序号");
    int i=GetInteger();
    switch(i){
        case 1:
            read_file_studmessage(1);break;
        case 2:
            read_file_studmessage(2);break;
        case 3:
            read_file_studmessage(3);break;
        default:
            break;
    }
    printf("一起都要准备就绪了哟，马上即将开始抽奖\n");
    puts("现在进入最后一个设置哟！抽奖时是否要求滚动显示啦(\033[1;31myes\033[0m or \033[1;31mno\033[0m)");
    while(1){
            char mybuff[MAX1];
            fgets(mybuff,MAX1,stdin);
            line=SubString(mybuff,0,strlen(mybuff)-2);
            if(!strcmp(line,"yes"))break;
            else if(!strcmp(line,"no"))break;
            else puts("请按要求输入(\033[1;31myes\033[0m or \033[1;31mno\033[0m)");
    }
    
    for(int k=1;k<=3;k++){
        puts("现在请选择你想抽取第几等奖");
        int b=GetInteger();
        j=num_prize(b);
       // puts("抽奖时是否要求滚动显示啦(\033[1;31myes\033[0m or \033[1;31mno\033[0m)");
        /*while(1){
            char mybuff[MAX1];
            fgets(mybuff,MAX1,stdin);
            string line=SubString(mybuff,0,strlen(mybuff)-2);*/
            if(!strcmp(line,"yes"))
            {
                lottery(j,b);
                //break;
            }else if(!strcmp(line,"no"))
            {
                unroll_lottery();}
              //  break;
          //  }else{
               // puts("请按要求输入(\033[1;31myes\033[0m or \033[1;31mno\033[0m)");
          //  }
        }
    
}
int num_prize(int j)
{
    if(j==1)
        return 1;
    if(j==2)
        return 2;
    if(j==3)
        return 3;
    return 0;
}
void lottery(int i,int b)/*i每个奖项个数,b为第几等奖*/
{
    for(int j=0;j<i;j++)
        roll_lottery(b);
}
void read_file_studmessage(int n)
{ 
    FILE *stream;
    char buf[MAX1];
    if(n==1)
        stream = fopen("student_num","r");
    else if(n==2)
        stream = fopen("student_name","r");
    else if(n==3)
        stream = fopen("student_idcard","r");
    
    while(fgets(buf,MAX1,stream)!= NULL){
        int j=strlen(buf);
        string aline=SubString(buf,0,j-2);
        my_buf[num]=aline;
        num++;
    }
    fclose(stream);
}
void unroll_lottery(void)
{
    init_keyboard();
    int a,i;
    printf("\033[1;31m中奖号码:\033[0m \n");
    getchar();
    while(1){
        int a=RandomInteger(0,num-1);
        printf("%s\n",my_buf[a]);
        i=a;
        if(newkbhit())break;
        fflush(stdout);
    }
    close_keyboard(); 
    printf("\033[1;31m中奖号码是:\033[0m %s",my_buf[i]);
    printf("\n");
}
void roll_lottery(int n)//n为第几等奖
{
    char buf[MAX1]={" "};
    char ch;
    int i=0,j=0;
    FILE *fp;
    if(n==1)
        fp = fopen("first_list.txt","a+");
    if(n==2)
        fp = fopen("second_list.txt","a+");
    if(n==3)
        fp = fopen("third_list.txt","a+");
    
    init_keyboard();
    
    printf("\033[1;31m中奖号码：\033[0m ");
    int a=0;
    getchar();
    while(1){
            i = strlen(buf);
            memset(buf, 0, 100);
            strcpy(buf, my_buf[a]);
            a=RandomInteger(0,num-1);
            printf("\r\033[1;31m中奖号码：\033[0m ");
            for(j = 0; j < i; j++)
            printf(" ");
            printf("\r\033[1;31m中奖号码：\033[0m%s",buf);
            if(newkbhit())break;
             fflush(stdout);
    }
    close_keyboard();
    fputs(buf,fp);
    fputs("\n",fp);
    fclose(fp);
    printf("\n");
}

void init_keyboard(void)
{
    tcgetattr(0,&old_set);
    new_set=old_set;
    new_set.c_lflag &= ~ECHO;
    new_set.c_lflag &= ~ICANON;
    new_set.c_lflag &= ~ISIG;
    new_set.c_cc[VMIN]=1;
    new_set.c_cc[VTIME]=0;
    tcsetattr(0,TCSANOW,&new_set);
}

void close_keyboard(void)
{
    tcsetattr(0,TCSANOW,&old_set);
}
int newkbhit(void)
{
    char ch;
    int nread;
    if(flag != -1)
        return -1;
    new_set.c_cc[VMIN]=0;
    tcsetattr(0,TCSANOW,&new_set);
    nread=read(0,&ch,1);
    new_set.c_cc[VMIN]=1;
    tcsetattr(0,TCSANOW,&new_set);
    
    if(nread==1)
    {
        flag=-1;
        return 1;
    }
    return 0;
}
