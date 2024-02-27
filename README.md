graph_data.txt存放的是数据文件

以下是测试c语言字符数组存放中文的一些代码
#include<stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    char ch1[10];
    char ch2[] = "你好";
    scanf("%s",ch1);
    printf("%s\n",ch1);
    int res = strcmp(ch1,ch2);
    printf("%d\n",res);
if(ch1[0]==ch2[0]&&ch1[1]==ch2[1])
		printf("ch1与ch2相等\n"); 
	else printf("ch1与ch2不相等\n");

    printf("%c%c%c\n",ch1[0],ch1[1],ch1[2]);
    printf("%c%c%c\n",ch2[0],ch2[1],ch2[2]);
    printf("%d %d %d %d %d\n",strlen(ch1),sizeof(ch1),strlen(ch2),sizeof(ch2),sizeof(char));
    
    printf("以下是采用gets输入的结果\n");
    char ch3[10];
    gets(ch3);

    char ch[15]="这里有三个"; 
	
	printf("char数组中第1个中文：\n");
	printf("%c%c\n",ch[0],ch[1]);
	
	printf("char数组中第2个中文：\n");
	printf("%c%c\n",ch[2],ch[3]);
	
	printf("全部中文：\n");
	int j=1;
	for(int i=0;i<=12;i+=2)
		printf("第%d个中文是：%c%c\n",j++,ch[i],ch[i+1]);


    return 0;
}
