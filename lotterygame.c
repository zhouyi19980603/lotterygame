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
void unroll_lottery(int n);
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
void unlottery(int i,int b);
void set_display(void);
void play_show1(void);
void play_show2(void);
void play_show3(void);

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
    puts("修改奖品信息请输入1 否则输入0");
    int i = GetInteger();
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
            if(!strcmp(line,"yes"))
            {
                lottery(j,b);
            }else if(!strcmp(line,"no"))
            {
                unlottery(j,b);}
        }
            printf("_____________________________________\n");
            printf("|\033[1;44m                                    \033[0m|\n");
            printf("|\033[1;44m                                    \033[0m|\n");
            printf("|\033[1;44m                 抽奖结束           \033[0m|\n");
            printf("|\033[1;44m                                    \033[0m|\n");
            printf("|\033[1;44m                                    \033[0m|\n");
            printf("|\033[1;44m____________________________________\033[0m|\n");
            set_display();
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
void unlottery(int i,int b)/*i每个奖项个数,b为第几等奖*/
{
    for(int j=0;j<i;j++)
        unroll_lottery(b);
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
void unroll_lottery(int n)
{
    FILE *fp;
    if(n==1)
        fp = fopen("first_list.txt","a+");
    if(n==2)
        fp = fopen("second_list.txt","a+");
    if(n==3)
        fp = fopen("third_list.txt","a+");
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
    fputs(my_buf[i],fp);
    fclose(fp);
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
void set_display(void)
{
    puts("(选择你想输出的最终格式，now三种选项供你选择");
    puts("example: ");
    puts("\033[1;31m1)\033[0m只显示学号和姓名并且每一个奖项显示一排 eg:");
    puts("一等奖：张三 837583096");
    puts("\033[1;31m2)\033[0m只显示学号和姓名并且每一个奖项分排显示 eg:");
    puts("一等奖：\n张三\n16375489");
    puts("\033[1;31m3)\033[0m显示姓名以及获奖奖品 eg: ");
    puts("张三 获得100万奖金)");
    printf("\n\n");  
    printf("请输入相应的序号：");
    while(1)
    {
         int i = GetInteger();
        if(i==1){
            play_show1();break;}
            else if(i==2)
            { play_show2();break;}
            else if(i==3){play_show3();break;}
            else {puts("请输入正确序号：");}
    }
    
        
}
void play_show1(void)
{
    FILE *fp,*fp1,*fp2;
    char buff[MAX1];
    char buff1[MAX1];
    char buff2[MAX1];
    fp = fopen("first_list.txt","r");
    printf("一等奖: ");
    fgets(buff,MAX1,fp);
    fclose(fp);
    printf("学号:%s",buff);
    fp1 = fopen("second_list.txt","r");
    printf("二等奖: ");
    while(fgets(buff1,MAX1,fp1)){
        string line=SubString(buff1,0,strlen(buff1)-2);
        printf("学号:%s  ",line);}
    fclose(fp1);
    fp2 = fopen("third_list.txt","r");
    puts("\n");
    printf("三等奖: ");
    while(fgets(buff2,MAX1,fp2)){
        string line=SubString(buff2,0,strlen(buff1)-2);
        printf("学号:%s  ",line);}
    fclose(fp2);
    
}
void play_show2(void)
{
    FILE *fp,*fp1,*fp2;
    char buff[MAX1];
    char buff1[MAX1];
    char buff2[MAX1];
    fp = fopen("first_list.txt","r");
    printf("一等奖: \n");
    fgets(buff,MAX1,fp);
    fclose(fp);
    printf("学号:%s",buff);
    fp1 = fopen("second_list.txt","r");
    printf("二等奖: \n");
    while(fgets(buff1,MAX1,fp1)){
        printf("学号:%s",buff1);}
    fclose(fp1);
    fp2 = fopen("third_list.txt","r");
    printf("三等奖: \n");
    while(fgets(buff2,MAX1,fp2)){
        printf("学号:%s",buff2);}
    fclose(fp2);
}
void play_show3(void)
{
    
    FILE *fp,*fp1,*fp2;
    FILE *stream,*stream1,*stream2;
    char buff[MAX1],mybuff[MAX1];
    char buff1[MAX1],mybuff1[MAX1];
    char buff2[MAX1],mybuff2[MAX1];
    int i=1;
    
    fp = fopen("first_list.txt","r");
    printf("一等奖: \n");
    fgets(buff,MAX1,fp);
    fclose(fp);
    printf("学号:%s",buff);
     printf("恭喜他喜提: ");
    stream = fopen("first_awards.txt","r");
    while(fgets(mybuff,MAX1,stream)){
        string line=SubString(mybuff,0,strlen(mybuff)-2);
        printf("%d) %s",i,line);
        i++;
    }
    fclose(stream);
    fp1 = fopen("second_list.txt","r");
    printf("\n二等奖: \n");
    while(fgets(buff1,MAX1,fp1)){
        printf("学号:%s",buff1);}
    fclose(fp1);
    i=1;
    printf("恭喜他们喜提: ");
    stream1 = fopen("second_awards.txt","r");
    while(fgets(mybuff1,MAX1,stream1)){
        string line=SubString(mybuff1,0,strlen(mybuff1)-2);
        printf("%d) %s",i,line);
        i++;
    }
    fclose(stream1);
    fp2 = fopen("third_list.txt","r");
    printf("\n三等奖: \n");
    while(fgets(buff2,MAX1,fp2)){
        printf("学号:%s",buff2);}
    fclose(fp2);
    i=1;
    printf("恭喜他们喜提: ");
    stream2 = fopen("third_awards.txt","r");
    while(fgets(mybuff2,MAX1,stream2)){
        string line=SubString(mybuff2,0,strlen(mybuff2)-2);
        printf("%d) %s",i,line);
        i++;
    }
    fclose(stream2);
    
}
