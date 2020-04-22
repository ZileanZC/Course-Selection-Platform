//编译预处理命令，调用标准库函数
#include <stdio.h>			
#include <string.h> 
#include <stdlib.h> 
#include<malloc.h> 
void Mangers();
void readfile();
void savefile();
void savefile1();
void search();
void Students();
void prin1();				//定义函数prin1
void choose();				//定义函数choose
typedef struct subjects
{
	int num;                 //整型 课程编号   
	char name[20];           //字符 课程名称   
	char kind[10];           //字符 课程性质   
	int stime;               //整型 总学时   
	int ttime;               //整型 授课学时   
	int etime;               //整型 实验或上机学时   
	int score;               //整型 学分   
	int term;                //整型 开课学期
	struct subjects* next;	 //next是指针变量，指向结构体变量
}SUB;						 //typedef struct subjects SUB
SUB* head = NULL;
SUB* create_form()          //创建链表  
{
	SUB* head, * tail, * p;
	int num, stime, ttime;
	int etime, score, term;
	char name[20], kind[10];
	int size = sizeof(SUB);
	head = tail = NULL;
	//C++中的实现为 cout << "输入选修课程信息：\n" << endl;
	printf("输入选修课程信息:\n");
	//C++中的实现为 cin>> num >> name >> kind >> stime >> ttime >> etime >> score>>term;
	scanf_s("%d,%s,%s,%d,%d,%d,%d,%d", &num, name, kind, &stime, &ttime, &etime, &score, &term);
	while (num != 0)
	{
		p = (SUB*)malloc(size);
		//不断使p指向下一结点，并赋值
		p->num = num;
		strcpy(p->name, name);
		strcpy(p->kind, kind);
		p->stime = stime;
		p->ttime = ttime;
		p->etime = etime;
		p->score = score;
		p->term = term;
		if (head == NULL)
			head = p;		//如果head=NULL即链表开头，就将p赋予head使其有值存在
		else
			tail->next = p;	//否则将p赋予下一结点
		tail = p;
		scanf("%d,%s,%s,%d,%d,%d,%d,%d", &num, name, kind, &stime, &ttime, &etime, &score, &term);
	}
	tail->next = NULL;
	return head;
}
void savefile()         //保存文件  
{
	SUB* p;

	FILE* fp;			//定义1个指向文件的指针变量fp
	fp = fopen("2.txt", "w");			//将fopen函数的返回值赋给指针变量fp
	if (fp == NULL)exit(0);				//关闭所有文件，终止正在执行的程序
	printf("课程编号  课程名称  课程性质  总学时  授课学时  实验或上机学时  学分  开课学期\n");
	for (p = head; p; p = p->next)
		fprintf(fp, "%5d%12s%9s%9d%9d%11d%11d%7d\n", p->num, p->name, p->kind, p->stime, p->ttime, p->etime, p->score, p->term);
	fclose(fp);
	printf("创建后的信息已放入'2.txt'文件中\n");
	system("pause");
}
void savefile1()         //保存文件  
{
	SUB* p;

	FILE* fp;
	fp = fopen("3.txt", "w");
	if (fp == NULL)exit(0);				//关闭所有文件，终止正在执行的程序
	for (p = head; p; p = p->next)
		fprintf(fp, "%5d%12s%9s%9d%9d%11d%11d%7d\n", p->num, p->name, p->kind, p->stime, p->ttime, p->etime, p->score, p->term);
	fclose(fp);
	printf("创建后的信息已放入'3.txt'文件中\n");
	system("pause");
}

void readfile()                    //阅读文件  
{
	void* myInsert(SUB*);
	SUB* newSub;     //定义新课程     
	int num, stime, ttime, etime;
	int score, term;
	char c, name[20], kind[10], fname[20];
	FILE* fp;
	fp = fopen("2.txt", "r");		//为了输入数据，打开一个已存在的文本文件
	while (!feof(fp))
	{
		newSub = (SUB*)malloc(sizeof(SUB));
		fscanf(fp, "%d%s%s%d%d%d%d%d\n", &newSub->num, newSub->name, newSub->kind, &newSub->stime, &newSub->ttime, &newSub->etime, &newSub->score, &newSub->term);
		myInsert(newSub);
	}
	fclose(fp);						//关闭fp指向的文件
}
void prin()   //浏览所有课程 
{
	SUB* ptr;
	head = NULL;
	readfile();
	if (head == NULL)
	{
		printf("\n\n\t*********NO RECORDS FOUND!************\n");
		return;
	}
	printf("课程编号  课程名称  课程性质  总学时  授课学时  实践或上机学时   学分  开课学期\n");
	for (ptr = head; ptr; ptr = ptr->next)
	{
		printf("%5d%12s%9s%9d%9d%11d%11d%7d\n", ptr->num, ptr->name, ptr->kind, ptr->stime, ptr->ttime, ptr->etime, ptr->score, ptr->term);
	}
	system("pause");
}
void prin1()   //浏览所有选修课程 
{
	SUB* ptr;
	FILE* fp;
	if ((fp = fopen("3.txt", "r")) == NULL)
	{
		printf("Cannot open this file.\n");
		choose();
	}
	printf("课程编号  课程名称  课程性质  总学时  授课学时  实践或上机学时   学分  开课学期\n");
	while (!feof(fp))		//条件为不是文件尾时均执行后续代码
	{
		ptr = (SUB*)malloc(sizeof(SUB));
		fscanf(fp, "%d%s%s%d%d%d%d%d\n", &ptr->num, ptr->name, ptr->kind, &ptr->stime, &ptr->ttime, &ptr->etime, &ptr->score, &ptr->term);

		printf("%5d%12s%9s%9d%9d%11d%11d%7d\n", ptr->num, ptr->name, ptr->kind, ptr->stime, ptr->ttime, ptr->etime, ptr->score, ptr->term);

	}
	system("pause");
}
void* myInsert(SUB* subj)  //链表插入操作
{
	SUB* ptr, * ptr2;
	ptr = subj;
	if (head == NULL)
	{
		head = ptr;
		head->next = NULL;
	}
	else
	{
		for (ptr2 = head; ptr2; ptr2 = ptr2->next)
			if (ptr2->next == NULL)
			{
				ptr2->next = subj;
				subj->next = NULL;
				break;
			}
	}
	return head;
}
void* insert()//插入课程信息
{
	SUB* ptr, * subj;
	int size = sizeof(SUB);
	char ch;
	char ch1;
	while (ch != '0')		//将0作为结束符
	{
		subj = (SUB*)malloc(size);
		ptr = subj;
		printf("输入要插入的课程信息:\n");
		printf("\n\t\t请输入课程编号:");
		scanf("%d", &subj->num);
		printf("\n\t\t请输入课程名称:");
		scanf("%s", &subj->name);
		printf("\n\t\t请输入课程性质:");
		scanf("%s", &subj->kind);
		printf("\n\t\t请输入总学时:");
		scanf("%d", &subj->stime);
		printf("\n\t\t请输入授课学时:");
		scanf("%d", &subj->ttime);
		printf("\n\t\t请输入实践或上机学时:");
		scanf("%d", &subj->etime);
		printf("\n\t\t请输入学分:");
		scanf("%d", &subj->score);
		printf("\n\t\t请输入开课学期:");
		scanf("%d", &subj->term);
		myInsert(subj);
		printf("\n添加完毕,新信息存入文件中\n");
		printf("\n继续插入请按回车\n");
		printf("\n结束添加课程按 0: [ ]\b\b");
		ch1 = getchar();                      //将回车键赋给CH1,否则 subj->term输完后输入的回车键会赋给CH,因此用CH1填补。     
		ch = getchar();
	}
	return head;
}
void* del()  //删除课程 
{
	SUB* p1, * p2;
	char ch;
	char ch1;
	int num;
	while (ch != '0')
	{
		printf("输入想要删除的课程编号:[    ]\b\b\b\b\b");
		scanf("%d", &num);
		if (head->num == num)
		{
			p2 = head;
			head = head->next;
			free(p2);
		}
		if (head == NULL)
			return NULL;
		p1 = head;
		p2 = head->next;
		while (p2)
		{
			if (p2->num == num)
			{
				p1->next = p2->next;
				free(p2);
			}
			else
				p1 = p2;
			p2 = p1->next;
		}
		printf("\n继续删除请按回车\n");
		printf("\n结束删除课程按 0: [ ]\b\b");
		ch1 = getchar();                       //将回车键赋给CH1,否则num输完后 再输入的回车键会赋给CH,因此用CH1填补。    
		ch = getchar();
		printf("\n删除完毕,新信息存入文件中\n");
		system("pause");
	}
	return head;
	system("pause");
}
void choose()//选新课程--学生选课统计函数 
{
	SUB* p, * q;
	int a[5];
	int num, total = 0, i = 0, j;
	printf("输入要选修的课程的编号,编号之间以空格分开\n");
	scanf("%d", &num);
	printf("如果确认输入完要选修的课程的编号,请输入0: [ ]\b\b");
	while (num != 0)
	{
		for (p = head; p; p = p->next)
			if (p->num == num)
			{
				total = total + p->score;
				a[i] = num;
				i++;
			}
		scanf("%d", &num);
	}
	if (total < 30)
	{
		printf("选修总学分为%d,未达到30,选修失败!\n", total);
		system("pause");
	}
	else
	{
		FILE* fp;
		fp = fopen("3.txt", "w");     //  fprintf(fp,"课程编号  课程名称  课程性质  总学时  授课学时  实践或上机学时  学分  开课学期\n");    
		for (j = 0; j < i; j++)
			for (q = head; q; q = q->next)
				if (q->num == a[j])
					fprintf(fp, "%5d%12s%9s%9d%9d%11d%11d%7d\n", q->num, q->name, q->kind, q->stime, q->ttime, q->etime, q->score, q->term);
		//fprintf(文件指针fp，输出格式，[附加参数列表])
		fclose(fp);
		printf("\t\t\n*********选修成功!*********\n");
		printf("\n您选修的课程总学分为%d,课程分别为:\n", total);
		printf("\n课程编号  课程名称  课程性质  总学时  授课学时  实践或上机 学时  学分  开课学期\n");

		for (j = 0; j < i; j++)
			for (q = head; q; q = q->next)
				if (q->num == a[j])
					printf("%5d%12s%9s%9d%9d%11d%11d%7d\n", q->num, q->name, q->kind, q->stime, q->ttime, q->etime, q->score, q->term);
		printf("\n以上信息全部保存在'3.txt'中\n");
	}
	system("pause");
}
void search()                        //课程信息查询 
{
	int a, num;
	int t = 1;
	char type[10], min[10];
	SUB* ptr;

Loop1:
	system("cls");
	printf("\n\n\t\t**********请选择查询方式*************\n");
	printf("\n\t\t\t1---按课程名称查找\n");
	printf("\n\t\t\t2---按课程性质查找\n");
	printf("\n\t\t\t3---按学分查找\n");
	printf("\n\t\t\t4---退出查找\n");
	printf("\n\n\t\t**************************************\n");
	printf("\n\n请输入查询的方式(1-4):[ ]\b\b");
	scanf("%d", &a);
	switch (a)
	{
	case 1:printf("请输入要查找的课程的名称:");
		scanf("%s", min);
		printf("课程编号  课程名称  课程性质  总学时  授课学时  实践或上 机学时  学分  开课学期\n");
		for (ptr = head; ptr; ptr = ptr->next)
			if (strcmp(min, ptr->name) == 0)
				//通过strcmp对比字符串
			{
				printf("%5d%12s%9s%9d%9d%11d%11d%7d\n", ptr->num, ptr->name, ptr->kind, ptr->stime, ptr->ttime, ptr->etime, ptr->score, ptr->term);
				t = 0;
			}
		if (t)
			printf("\t\n未找到!\n");
		t = 1;
		system("pause");
		goto Loop1;
		//返回查询开始处
	case 2:printf("请输入要查找的课程的性质:");
		scanf("%s", type);
		printf("课程编号  课程名称  课程性质  总学时  授课学时  实践或上机 学时  学分  开课学期\n");
		for (ptr = head; ptr; ptr = ptr->next)
			if (strcmp(type, ptr->kind) == 0)
			{
				printf("%5d%12s%9s%9d%9d%11d%11d%7d\n", ptr->num, ptr->name, ptr->kind, ptr->stime, ptr->ttime, ptr->etime, ptr->score, ptr->term);
				t = 0;
			}
		if (t)
			printf("\t\n未找到!\n");
		t = 1;
		system("pause");
		goto Loop1;

	case 3:printf("输入要查找的课程的学分:");
		scanf("%d", &num);
		printf("课程编号  课程名称  课程性质  总学时  授课学时  实践或上机 学时  学分  开课学期\n");
		for (ptr = head; ptr; ptr = ptr->next)
			if (ptr->score == num)
			{
				printf("%5d%12s%9s%9d%9d%11d%11d%7d\n", ptr->num, ptr->name, ptr->kind, ptr->stime, ptr->ttime, ptr->etime, ptr->score, ptr->term);
				t = 0;
			}
		if (t)
			printf("\n\t未找到!\n");
		t = 1;
		system("pause");
		goto Loop1;

	case 4:break;	//终止程序
	}
}
void Mangers()		//管理员菜单
{
	int n, w = 1, flag = 0, i = 3;
	char s[8];		//固定8位来存放输入密码
	char password[8] = "1";
	do
	{
		printf("\n\n请输入密码:");
		scanf("%s", s);
		if (!strcmp(s, password))              //进行密码匹配验证
		{
			flag = 1;
			break;
		}
		else
		{
			printf("\n\n输入错误！你还剩 %d 次输入的机会，请输入：\n", i - 1);
			i--;
		}
	} while (i > 0);
	if (!flag)
	{
		printf("you have Enter 3 times!");       //输入密码错误次数超过3次         
		exit(0);                                //自动退出       
	}
	do
	{
		system("cls");
		puts("\n\n\t\t********************* 管 理 员 菜 单 ***********************\n\n");
		puts("\t\t\t\t1---浏览课程\n");
		puts("\t\t\t\t2---查询课程\n");
		puts("\t\t\t\t3---添加课程\n");
		puts("\t\t\t\t4---删除课程\n");
		puts("\t\t\t\t5---返回主菜单");
		puts("\n\n\t\t******************************************************\n");
		printf("Chiose your number(1-5):[ ]\b\b");
		scanf("%d", &n);
		switch (n)
		{
		case 1:prin(); break;
		case 2:search(); break;
		case 3:insert(); savefile(); break;
		case 4:del(); savefile(); break;
		case 5:return;
		default:;
		}
	} while (w == 1);
}
void Students()		//学生菜单
{
	int n, w = 1;
	do
	{
		system("cls");
		puts("\n\n\t\t********************* 学 生 菜 单 ***********************\n\n");
		puts("\t\t\t\t1---浏览所有课程\n");
		puts("\t\t\t\t2---查询课程信息\n");
		puts("\t\t\t\t3---选择选修课程\n");
		puts("\t\t\t\t4---浏览我选修的课程\n");
		puts("\t\t\t\t5---删除错选课程\n");
		puts("\t\t\t\t6---返回主菜单");
		puts("\n\n\t\t****************************************************\n");
		printf("输入想要实现功能对应的数字(1-6):[ ]\b\b");
		scanf("%d", &n);
		switch (n)
		{
		case 1:prin(); break;
		case 2:search(); break;
		case 3:choose(); break;
		case 4:prin1(); break;
		case 5:del(); savefile1(); break;
		case 6:return;
		default:;
		}
	} while (w == 1);
}
int  main()		//main函数
{
	int n, w = 1;
	do
	{
		system("cls");
		puts("\n\n\t\t*********************MENU***********************\n\n");
		puts("\t\t\t\t1.以管理员身份登录(password 1)\n");
		puts("\t\t\t\t2.以学生身份登录\n");
		puts("\t\t\t\t3.退出");
		puts("\n\n\t\t************************************************\n");
		printf("Chiose your number(1-3):[ ]\b\b");
		scanf("%d", &n);
		switch (n)
		{
		case 1:Mangers(); break;
		case 2:Students(); break;
		case 3:w = 0; break;
		default:;
		}
	} while (w == 1);
	return 0;
}