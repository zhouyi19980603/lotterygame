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
void read_all_message(void);
void modify_value(void);
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
void award_message(int n);
void lottery(int i,int b);
int num_prize(int j);
void unlottery(int i,int b);
void set_display(void);
void play_show1(void);
void play_show2(void);
void play_show3(void);
void revamp_award(void);
void show_message(int n);
void all_award(void);

//void statistics(int n, int a);
void query(void);
void delete();

#define MAX 10
#define MAX1 100
typedef struct{
    char *buff_name[MAX1];
    char *buff_ID[MAX1];
    char *buff_student_ID[MAX1];
    char *buff_message[MAX1];
    char *buff_sex[MAX1];
    char *buff_grade[MAX1];
}called;
static called people;
static int num;
static struct termios old_set, new_set;
static int flag=-1;
static int num=0;
static char *my_buf[MAX1]={" "};

static int a[MAX1];
static int level = 0;
 
int main()
{
    message();
    remove("first_list.txt");
    remove("second_list.txt");
    remove("third_list.txt");
    while(1){ 
        information();
        struct termios old,new;
        tcgetattr(0,&old);//取得当前值，保存在结构体old中。
        new=old;
        new.c_lflag &= ~ECHO;//c_lflag局部模式。ECHO：设置此位则启用回显，即在终端显示输入字符。
        tcsetattr(0,TCSANOW,&new);//设置当前值为new
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
            case 7:
                query();break;
            case 8:
                delete();break;
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
    printf("8:历史信息清除\n");
    printf("0:退出程序\n");
}
void input_message(void)
{
     printf("请你按要求输入相应的信息,输入over结束.\n");
     int i=0;
     FILE *fp,*fd;
     fp=fopen("message.txt","w");
     fd=fopen("allmessage.txt","a+");
     char buff[MAX1]={' '};
     printf("姓名:");
     fgets(buff,MAX1,stdin);
     string line=SubString(buff,0,strlen(buff)-2);
     while(strcmp(line,"over"))
     {
         fputs(buff,fp);
         fputs(buff,fd);
         printf("学号:");
         fgets(buff,MAX1,stdin);
         fputs(buff,fp);
         fputs(buff,fd);
         printf("性别:");
         fgets(buff,MAX1,stdin);
         fputs(buff,fp);
         fputs(buff,fd);
         printf("身份ID:");
         fgets(buff,MAX1,stdin);
         fputs(buff,fp);
         fputs(buff,fd);
         printf("姓名:");
         fgets(buff,MAX1,stdin);
         line=SubString(buff,0,strlen(buff)-2);
     }
     fclose(fp);
     fclose(fd);
     read_all_message();
     char mybuff[MAX1];
     printf("\033[1;31m是否确定提交，一旦提交后便只能在文件目录message.txt中去修改\033[0m(\033[1;31myes\033[0m or \033[1;31mno\033[0m）\n");
     fgets(mybuff,MAX1,stdin);
     string word=SubString(mybuff,0,strlen(mybuff)-2);
     if(!strcmp(word,"no"))
         modify_value();
     
}
void modify_value(void)
{
    int j;
    printf("\033[1;31m现在将例出你输入的所有信息\033[0m");
    for(int i=0;i<num;i++)
    {
        printf(" %d %s %s %s %s\n",i,people.buff_name[i],
        people.buff_student_ID[i],
        people.buff_sex[i],
        people.buff_ID[i]);
        
    } 
    printf("\033[1;31m选择你想修改的序数,如果想新增候选人请输入-1\033[0m");
    j=GetInteger();
    if(j==-1){
        printf("姓名：");people.buff_name[num]=GetLine();
        printf("学号：");people.buff_student_ID[num]=GetLine();
        printf("性别：");people.buff_sex[num]=GetLine();
        printf("身份：");people.buff_ID[num]=GetLine();
        num++;
    }else {
        printf("\033[1;31m删除该候选人输1,修改输2\033[0m");
        int k=GetInteger();
        if(k==1){
            people.buff_name[j]=people.buff_name[j+1];
            people.buff_student_ID[j]=people.buff_student_ID[j+1];
            people.buff_sex[j]=people.buff_sex[j+1];
            people.buff_ID[j]=people.buff_ID[j+1];
            num=num-1;
        }else{
            people.buff_name[j]=GetLine();
            people.buff_student_ID[j]=GetLine();
            people.buff_sex[j]=GetLine();
            people.buff_ID[j]=GetLine();
        }
    }
    for(int i=0;i<num;i++)
    {
        printf(" %d %s %s %s %s\n",i,people.buff_name[i],
        people.buff_student_ID[i],
        people.buff_sex[i],
        people.buff_ID[i]);
        
    }
    printf("\033[1;32m诺以上信息还存在错误，请在该文件目录下message.txt文档下去纠正\033[0m\n");
}
void read_all_message(void){
    FILE *stream;
    stream=fopen("message.txt","r");
    char buf[MAX1];
    char *my_buf[MAX1];
    
    while(fgets(buf,MAX1,stream)!= NULL){
        int j=strlen(buf);
        string aline=SubString(buf,0,j-2);
        people.buff_name[num]=aline;
        
        fgets(buf,MAX1,stream);
         j=strlen(buf);
         aline=SubString(buf,0,j-2);
        people.buff_student_ID[num]=aline;
        
        fgets(buf,MAX1,stream);
         j=strlen(buf);
         aline=SubString(buf,0,j-2);
        people.buff_sex[num]=aline;
        
        fgets(buf,MAX1,stream);
         j=strlen(buf);
         aline=SubString(buf,0,j-2);
        people.buff_ID[num]=aline;
        
        num++;
    }
    fclose(stream);
}

void set_message(void)
{
    printf("请输入活动名称：\n");
	char ch0[MAX1], ch1[MAX1];
    FILE *fp0, *fp1;
    fp0=fopen("tital.txt", "w+");
	fgets(ch0, MAX1, stdin);
    fputs(ch0,fp0);
    printf("请输入活动简介：\n");
    fp1=fopen("introduction.txt", "w+");
	fgets(ch1, MAX1, stdin);
    fputs(ch1,fp1);
    
    fclose(fp0);
    fclose(fp1);
}

void awards_number(void)
{
    printf("您一共需要几等奖？\n");
	level=GetInteger();
	printf("请输入每等几分别有几个，从一等奖开始\n",level);
	for(int i=1;i<=level;i++){
		a[i]=GetInteger();
	}
}

void set_awards(void)
{
    puts("修改奖品信息请输入1 否则输入0");
    int i = GetInteger();
    if(i==0){
        puts("输入一等奖奖品: (输入over结束)");
        award_message(1);
        puts("输入二等奖奖品: (输入over结束)");
        award_message(2);
        puts("输入三等奖奖品: (输入over结束)");
        award_message(3);
    }else if(i==1)
        revamp_award();
}
void revamp_award(void)
{
    puts("输入yes可以查看每等奖的奖品信息(\033[1;31myes\033[0m or \033[1;31mno\033[0m)");
    all_award();
    puts("输入你想修改几等奖，用1 2 3序号代替");
    int i = GetInteger();
    puts("现在开始修改，输over结束");
    award_message(i);
    puts("\033[1;31m修改成功！\033[0m and 是否查看（\033[1;31myes\033[0m or \033[1;31mno\033[0m）");
    all_award();
}
void all_award(void)
{
    char buff[MAX1];
    while(1){
            char mybuff[MAX1];
            fgets(mybuff,MAX1,stdin);
            string line=SubString(mybuff,0,strlen(mybuff)-2);
            if(!strcmp(line,"yes")){
                FILE *fp,*fp1,*fp2;
                printf("一等奖：\n");
                fp=fopen("first_awards.txt","r");
                while(fgets(buff,MAX1,fp)!=NULL)
                    printf("%s",buff);
                fclose(fp);
                printf("二等奖：\n");
                fp1=fopen("second_awards.txt","r");
                while(fgets(buff,MAX1,fp1)!=NULL)
                    printf("%s",buff);
                fclose(fp1);
                printf("三等奖：\n");
                fp2=fopen("third_awards.txt","r");
                while(fgets(buff,MAX1,fp2)!=NULL)
                    printf("%s",buff);
                fclose(fp2);
                break;}
            else if(!strcmp(line,"no")){
                break;}
            else puts("请按要求输入(\033[1;31myes\033[0m or \033[1;31mno\033[0m)");
    }
            
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
              fflush(fp);
            
        }
        fclose(fp);
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
    
    //输出活动名称和简介
    FILE *fp0, *fp1;
    char ch0[MAX1], ch1[MAX1];
    fp0=fopen("tital.txt", "r");
    fp1=fopen("introduction.txt", "r");
    fgets(ch0,MAX1,fp0);
    fgets(ch1,MAX1,fp1);
    fputs(ch0,stdout);
    fputs(ch1,stdout);
    
    fclose(fp0);
    fclose(fp1);
    
    
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
        //j=num_prize(b);
            if(!strcmp(line,"yes"))
            {
                lottery(a[b],b);
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

/*int num_prize(int j)
{
    if(j==1)
        return 1;
    if(j==2)
        return 2;
    if(j==3)
        return 3;
    return 0;
}*/

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
    if(n==1)
        for(int i=0;i<num;i++)
            my_buf[i]=people.buff_student_ID[i];
    else if(n==2)
        for(int j=0;j<num;j++)
            my_buf[j]=people.buff_name[j];
    else if(n==3)
        for(int k=0;k<num;k++)
            my_buf[k]=people.buff_name[k];
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
    
 //   statistics(n ,a);
    
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
    new_set.c_lflag &= ~ICANON;//设置此位则使用加工方式输入，这使EOF、EOL等字符也起作用，这些字符也被装配到输入行中。
    new_set.c_lflag &= ~ISIG;//此位控制是否识别INTR、OUIT等特殊字符。内核会将输入字符与这些特殊字符相比较，相同则生成对应信号。
    new_set.c_cc[VMIN]=1;//c_cc特殊控制模式。VMIN非加工方式，MIN值。
    new_set.c_cc[VTIME]=0;//VTIME非加工方式，TIME值。
    tcsetattr(0,TCSANOW,&new_set);//改变终端属性，TCSANOW立即作出改变。
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
            int k = GetInteger();
            if(k == 1)
            {
                play_show1();break;
            }else if(k == 2)
            {
                play_show2();break;
            }else if(k == 3)
            {
                play_show3();break;
            }else {
                puts("请输入正确序号：");}
            
    }
    
        
}
void play_show1(void)
{
    for(int i=1;i<=3;i++)
        show_message(i);
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


void show_message(int n)
{
    FILE *fp;
    char buff[MAX1];
    if(n==1){
        fp = fopen("first_list.txt","r");
        printf("一等奖: ");
    }else if(n==2){
        fp = fopen("second_list.txt","r");
        printf("二等奖: ");
    }else if(n==3){
        fp = fopen("third_list.txt","r");
        printf("三等奖: ");
    }
    while(fgets(buff,MAX1,fp)){
        string line=SubString(buff,0,strlen(buff)-2);
        printf("学号:%s  ",line);}
        printf("\n");
    fclose(fp);
}

/*
void statistics( int n, int a)
{
    FILE *fp;
    switch(n){
        case 1:
            fp=fopen("first.txt", "a+");
            break;
        case 2:
            fp=fopen("second.txt", "a+");
            break;
        case 3:
            fp=fopen("third.txt", "a+");
            break;
    }
    fprintf(fp, "%d", a);
    fclose(fp);
}*/

void query(void)
{
    //int n=0;
    FILE *fp;
    /*called s;
    fp1=fopen("message.txt","r");
    while(!feof(fp1))
    {
        fscanf(fp1,"%s" "%d" "%s" "%d",
               s.buff_name[n], &s.buff_student_ID[n], s.buff_sex[n],&s.buff_ID[n]);
        n++;
    }*/
    
    printf("请问需要查询几等奖的中奖信息：");
    int n, a;
    char c[MAX1];
    n=GetInteger();
    switch(n){
        case 1:
            fp=fopen("first_list.txt", "r");
            break;
        case 2:
            fp=fopen("second_list.txt", "r");
            break;
        case 3:
            fp=fopen("third_list.txt", "r");
            break;
    }
    if(fp==NULL){
        printf("没有中奖人信息\n");
    }

    
    while(fscanf(fp,"%s", c)>0){
        /*for(int i=0;i<num;i++){
            if(a==*people.buff_student_ID[i]){
                printf("姓名：%s\n",people.buff_name[i]);*/
                printf("%s\n",c);
       // }
        //}
    }
     /*   char ch[MAX1];
        fread(ch,sizeof(ch),MAX,fp);
        printf("%s",ch);*/
    fclose(fp);
}

void delete()
{
    printf("请问需要删除几等奖的中奖信息：\n");
    int n;
    FILE *fp;
    n=GetInteger();
    switch(n){
        case 1:
            fp=fopen("first_list.txt", "w");
            break;
        case 2:
            fp=fopen("second_list.txt", "w");
            break;
        case 3:
            fp=fopen("third_list.txt", "w");
            break;
    }
    fputs(" ",fp);
    fclose(fp);
}
