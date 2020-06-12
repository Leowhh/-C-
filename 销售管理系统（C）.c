#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
//万年历数组
int dp[2][13] = { {0,31,28,31,30,31,30,31,31,30,31,30,31},
				{0,31,29,31,30,31,30,31,31,30,31,30,31} };
//销售员节点 
typedef struct _SAL
{
	char no[12];    	/*代号*/
	char name[40];  	/*姓名*/
	int month[12];		/*月份*/
	float sales[12];	/*月销售额*/
	float total;		/*年度总销售额*/
	struct _SAL* next;	/*指向下一节点的指针*/
} SALNODE;

//声明链表的头和尾
SALNODE* g_pHead = NULL;	//0 
SALNODE* g_pEnd = NULL;

void SaleManageSystem();
SALNODE* FindSaleByNo(char* no);
int ConfirmSaleByNo(char* no);
void DeleteSaleNode(SALNODE* pNode);
void ShowAddSale();
void AddSaleMSG(char no[12], char name[40], float total, float sales[12]);
void ShowSearchSale();
void ShowReviseSale();
void ShowDeleteSale();
void ShowAnalyzeSale();
void SystemMenu();
void SaleSystemMenu();
int GetWeekend(int y, int m, int d);
int Check(int year);
void Show(int year, int month, int wd);
void Calender();
void Mountain();

//主函数入口
int main()
{
	int iOrder = -1;
	//初始化 
	while (1)
	{
		system("cls");
		SystemMenu();
		printf("请输入指令_");
		scanf("%d", &iOrder);
		switch (iOrder)
		{

		case 1:
			//万年历
			Calender();
			break;
		case 2:
			//搬山游戏
			Mountain();
			break;
		case 3:
			//销售管理系统
			SaleManageSystem();
			break;
		case 0:
			//退出程序
			exit(1);
		default:
			printf("输入的指令不对！\n");
		}
	}
	return 0;
}


//根据代号查询链表
SALNODE* FindSaleByNo(char* no)
{
	SALNODE* pTemp = g_pHead;
	//检测参数的合法性
	if (NULL == no)
	{
		printf("代号输入错误\n");
		system("pause");
		return NULL;
	}
	//判断链表是否为空
	if (NULL == g_pHead || NULL == g_pEnd)
	{
		printf("您还未录入任何数据！\n");
		system("pause");
		return NULL;
	}
	//遍历链表
	while (pTemp != NULL)
	{
		if (0 == strcmp(pTemp->no, no))
		{
			return pTemp;
		}
		pTemp = pTemp->next;
	}
	printf("该代号不存在！\n");
	system("pause");
	return NULL;
}
//根据代号判断链表是否已有记录
int ConfirmSaleByNo(char* no)
{
	SALNODE* pTemp = g_pHead;

	//判断链表是否为空
	if (NULL == g_pHead || NULL == g_pEnd)
	{
		return 1;
	}
	//遍历链表
	while (pTemp != NULL)
	{
		if (0 == strcmp(pTemp->no, no))
		{
			return 0;
		}
		pTemp = pTemp->next;
	}
	return 1;
}
//删除节点
void DeleteSaleNode(SALNODE* pNode)
{
	//只存在一个节点时
	if (g_pHead == g_pEnd)
	{
		free(g_pHead);
		g_pEnd = NULL;
		g_pHead = NULL;
	}
	//存在两个节点时
	else if (g_pHead->next == g_pEnd)
	{
		if (g_pHead == pNode)
		{
			free(g_pHead);
			g_pHead = g_pEnd;
		}
		else
		{
			free(g_pEnd);
			g_pEnd = g_pHead;
			g_pHead->next = NULL;
		}
	}
	// 节点数大于2
	else
	{
		SALNODE* pTemp = g_pHead;
		//判断是否为头节点
		if (g_pHead == pNode)
		{
			pTemp = g_pHead;
			g_pHead = g_pHead->next;
			//释放节点
			free(pTemp);
			pTemp = NULL;
			return;
		}
		while (pTemp)
		{
			if (pTemp->next == pNode)
			{
				if (pNode == g_pEnd)
				{
					free(pNode);
					pNode = NULL;
					g_pEnd = pTemp;
					g_pEnd->next = NULL;
					return;
				}
				else
				{
					SALNODE* p = pTemp->next;
					pTemp->next = pTemp->next->next;
					free(p);
					p = NULL;
					return;
				}
			}
			pTemp = pTemp->next;
		}
	}
}
//添加一个销售信息
void AddSaleMSG(char no[12], char name[40], float total, float sales[12])
{
	int i;
	//创建一个节点
	SALNODE* pTemp = malloc(sizeof(SALNODE));
	//检验参数的合法性
	if (NULL == no || NULL == name)
	{
		printf("销售信息输入错误\n");
		free(pTemp);
		return;
	}
	//给节点成员赋值
	if (pTemp)
	{
		strcpy(pTemp->no, no);
		strcpy(pTemp->name, name);
		for (i = 0;i < 12;i++)
		{
			pTemp->sales[i] = sales[i];
		}
		pTemp->total = total;
		pTemp->next = NULL;
	}
	//接在链表上
	if (NULL == g_pHead || NULL == g_pEnd)
	{
		g_pHead = pTemp;
	}
	else
	{
		g_pEnd->next = pTemp;	//链接
	}
	g_pEnd = pTemp;
	printf("添加成功！\n");
	system("cls");
}
//销售信息录入界面
void ShowAddSale()
{
	//初始化变量;
	int Order = -1;
	int i = -1;
	char no[12] = { 0 };
	char name[40] = { 0 };
	float total = 0;
	float sales[12] = { 0 };
	system("cls");
	printf("请输入销售员代号：");
	scanf("%s", no);
	//检验代号是否重复
	if (ConfirmSaleByNo(no))
		;
	else
	{
		printf("与现有记录重复，请重新输入！\n");
		system("pause");
		ShowAddSale();
	}
	printf("请输入销售员姓名：");
	scanf("%s", name);
	printf("\n------------------------------------------------------------\n");
	printf("\t1：录入销售额\n\t2：录入新的\n\t0：返回菜单\n请输入指令：");
	scanf("%d", &Order);
	switch (Order)
	{
	case 1:
		for (i = 0;i < 12;i++)
		{
			printf("请输入该销售员%d月的销售额", i + 1);
			scanf("%f", &sales[i]);
			total += sales[i];
		}
		AddSaleMSG(no, name, total, sales);
		break;
	case 2:
		AddSaleMSG(no, name, total, sales);
		ShowAddSale();
		break;
	case 0:
		//调用添加函数
		AddSaleMSG(no, name, total, sales);
		SaleManageSystem();
		break;
	default:
		printf("输入的指令不对！\n");
	}
}
//销售额查询界面
void ShowSearchSale()
{
	//初始化变量
	int Order = -1;
	SALNODE* pTemp = NULL;
	char no[12] = { '\0' };
	system("cls");
	printf("请输入要查询的销售员代号：\n");
	scanf("%s", no);
	system("cls");
	//调用查询函数
	pTemp = FindSaleByNo(no);
	if (NULL != pTemp)
	{
		//输出结果
		printf("销售员代号：%s\n销售员姓名：%s\n年度总销售额%.2f\n", pTemp->no, pTemp->name, pTemp->total);
		//printf("一月\t二月\t三月\t四月\t五月\t六月\t七月\t八月\t九月\t十月\t十一月\t十二月\n");
		//printf("%-8.2f%-8.2f%-8.2f%-8.2f%-8.2f%-8.2f%-8.2f%-8.2f%-8.2f%-8.2f%-8.2f%-8.2f", pTemp->sales[0], pTemp->sales[1], pTemp->sales[2], pTemp->sales[3], pTemp->sales[4], pTemp->sales[5], pTemp->sales[6], pTemp->sales[7], pTemp->sales[8], pTemp->sales[9], pTemp->sales[10], pTemp->sales[11]);
		for (int i = 0;i < 12;i++)
		{
			printf("%d月销售额：%.2f\n", i + 1, pTemp->sales[i]);
		}
	}
	else
	{
		printf("\n------------------------------------------------------------\n");
		printf("\t1：重新输入\n\t0：返回菜单\n请输入指令：");
		scanf("%d", &Order);
		switch (Order)
		{
		case 1:
			ShowSearchSale();
			break;
		case 0:
			SaleManageSystem();
			break;
		default:
			printf("输入的指令不对！\n");
		}
	}
	printf("\n------------------------------------------------------------\n");
	printf("\t1：查询新的\n\t0：返回菜单\n请输入指令：");
	scanf("%d", &Order);
	switch (Order)
	{
	case 1:
		ShowSearchSale();
		break;
	case 0:
		break;
	default:
		printf("输入的指令不对！\n");
	}
}
//销售额修改界面
void ShowReviseSale()
{
	SALNODE* pTemp = NULL;
	int Order = -1;
	float num;
	char no[12] = { '\0' };
	system("cls");
	printf("请输入要修改的销售员代号：\n");
	scanf("%s", no);
	system("cls");
	pTemp = FindSaleByNo(no);
	if (NULL != pTemp)
	{
		while (1)
		{
			printf("该销售员当前信息如下：\n销售员代号：%s\n销售员姓名：%s\n年度总销售额%.2f\n", pTemp->no, pTemp->name, pTemp->total);
			for (int i = 0;i < 12;i++)
			{
				printf("%d月销售额：%.2f\n", i + 1, pTemp->sales[i]);
			}
			printf("\n------------------------------------------------------------\n");
			printf("\t1-12：要修改的销售额月份（如修改一月输入1即可）\n\t其他数值：修改新的\n\t0：返回菜单\n请输入指令：");
			scanf("%d", &Order);
			if (Order > 0 && Order < 13)
			{
				printf("请输入新值：");
				scanf("%f", &num);
				pTemp->total = pTemp->total - pTemp->sales[Order - 1] + num;
				pTemp->sales[Order - 1] = num;
				printf("修改成功\n");
				system("cls");
			}
			else if (Order == 0)
			{
				break;
			}
			else
			{
				ShowReviseSale();
			}

		}
	}
	else
	{
		printf("\n------------------------------------------------------------\n");
		printf("\t1：重新输入\n\t0：返回菜单\n请输入指令：");
		scanf("%d", &Order);
		switch (Order)
		{
		case 1:
			ShowReviseSale();
			break;
		case 0:
			SaleManageSystem();
			break;
		default:
			printf("输入的指令不对！\n");
		}
	}
}
//销售信息删除界面
void ShowDeleteSale()
{
	SALNODE* pTemp = NULL;
	int Order = -1;
	char no[12] = { '\0' };
	system("cls");
	printf("请输入要删除的销售员代号：\n");
	scanf("%s", no);
	pTemp = FindSaleByNo(no);
	if (NULL != pTemp)
	{
		printf("该销售员当前信息如下：\n销售员代号：%s\n销售员姓名：%s\n年度总销售额%.2f\n", pTemp->no, pTemp->name, pTemp->total);
		for (int i = 0;i < 12;i++)
		{
			printf("%d月销售额：%.2f\n", i + 1, pTemp->sales[i]);
		}
		printf("\n------------------------------------------------------------\n");
		printf("\t1：确认删除\n\t2：取消并重新输入\n\t0：返回主菜单\n请输入指令：");
		scanf("%d", &Order);
		switch (Order)
		{
		case 1:
			DeleteSaleNode(pTemp);
			break;
		case 2:
			ShowDeleteSale();
			break;
		case 0:
			SaleManageSystem();
			break;
		default:
			printf("输入的指令不对！\n");
		}
	}
	else
	{
		printf("\n------------------------------------------------------------\n");
		printf("\t1：重新输入\n\t0：返回菜单\n请输入指令：");
		scanf("%d", &Order);
		switch (Order)
		{
		case 1:
			ShowDeleteSale();
			break;
		case 0:
			SaleManageSystem();
			break;
		default:
			printf("输入的指令不对！\n");
		}
	}
}
//销售额分析界面
void ShowAnalyzeSale()
{
	float year_total = 0;
	float month_total[12] = { 0 };
	float max, min;
	int MinMonth = 0, MaxMonth = 0;
	SALNODE* pTemp = g_pHead;
	system("cls");
	//判断链表是否为空
	if (NULL == g_pHead || NULL == g_pEnd)
	{
		printf("你还未录入任何数据！\n");
		system("pause");
	}
	//遍历链表
	while (pTemp != NULL)
	{
		for (int i = 0;i < 12;i++)
		{
			month_total[i] += pTemp->sales[i];
		}
		year_total += pTemp->total;
		pTemp = pTemp->next;
	}
	max = 0;
	for (int i = 0;i < 12;i++)
	{
		if (max < month_total[i])
		{
			max = month_total[i];
			MaxMonth = i + 1;
		}

	}
	min = max;
	for (int i = 0;i < 12;i++)
	{
		if (min > month_total[i])
		{
			min = month_total[i];
			MinMonth = i + 1;
		}
	}
	printf("当前年度总销售额：%.2f元\n", year_total);
	for (int i = 0;i < 12;i++)
	{
		printf("当前年度%d月总销售额：%.2f元\n", i + 1, month_total[i]);
	}
	printf("%d月为当前年度销售额最大月：%.2f元\n", MaxMonth, max);
	printf("%d月为当前年度销售额最小月：%.2f元\n", MinMonth, min);
	system("pause");
}
//主菜单 
void SystemMenu()
{
	printf("--------------------[C语言课程设计]-------------------\n");
	printf("|                                                    |\n");
	printf("|             【1】          万年历                  |\n");
	printf("|             【2】         搬山游戏                 |\n");
	printf("|             【3】       销售管理系统               |\n");
	printf("|             【0】         退出系统                 |\n");
	printf("|                                                    |\n");
	printf("------------------------------------------------------\n");
}
//销售管理主菜单 
void SaleSystemMenu()
{
	printf("--------------------[销售管理系统]--------------------\n");
	printf("|                                                    |\n");
	printf("|             【1】       销售信息录入               |\n");
	printf("|             【2】        销售额查询                |\n");
	printf("|             【3】        销售额修改                |\n");
	printf("|             【4】       销售信息删除               |\n");
	printf("|             【5】       年销售额分析               |\n");
	printf("|             【0】           返回                   |\n");
	printf("|                                                    |\n");
	printf("------------------------------------------------------\n");
}


//万年历
int GetWeekend(int y, int m, int d) {
	if (m == 1 || m == 2) {
		m += 12;y--;
	}
	int w = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400 + 1) % 7;
	return w;
}
int Check(int year) {
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}
void Show(int year, int month, int wd) {
	int leep = Check(year);
	printf("\t\t\t\t%d月\n\n", month);
	printf("	日	一	二	三	四	五	六\n");
	int c = wd, i;
	for (i = 0;i < wd;i++)
		printf("\t  ");
	for (i = 1;i <= dp[leep][month];i++)
	{
		printf("\t%2d", i);

		c++;
		if (c == 7)
		{
			c = 0;
			printf("\n");
			printf("\n");
		}
	}
	printf("\n\n");
}
void Calender() {
	int Order = -1;
	int year = 1, month, wd;
	system("cls");
	printf("请输入要查询的年份\n");
	scanf("%d", &year);
	for (month = 1;month <= 12;month++)
	{
		wd = GetWeekend(year, month, 1);
		Show(year, month, wd);
	}
	year++;
	printf("------------------------------------------------------\n");
	if (Check(year))
		printf("生成完毕。%d不是闰年。\n\t1：重新查询\n\t0：返回上一级\n请输入指令：", year - 1);
	else
		printf("生成完毕。%d是闰年。\n\t1：重新查询\n\t0：返回上一级\n请输入指令：", year - 1);
	scanf("%d", &Order);
	switch (Order)
	{

	case 1:
		//万年历
		Calender();
		break;
	case 0:
		//主菜单
		break;
	default:
		printf("输入的指令不对！\n");
	}

}


//搬山游戏
void Mountain()
{
	int Order = -1;
	int n, k, player = 0, computer = 0;
	unsigned int i;
	system("cls");
	printf("---------------------游戏规则-----------------------\n");
	printf("|   设有n座山，计算机与人为比赛的双方，轮流搬山。规|\n");
	printf("|定每次搬山的数量不能超过k座，谁搬最后一座谁输。   |\n");
	printf("----------------------------------------------------\n");
	while (1)
	{
		printf("请输入山的总数：\n");
		scanf("%d", &n);
		if (n <= 0)
			printf("请输入大于0的数\n");
		printf("请输入每次允许搬山的最大数：\n");
		scanf("%d", &k);
		if (k > (n - 2))
		{
			printf("非法输入，将重新开始游戏\n");
			system("pause");
			Mountain();
		}

		system("cls");
		printf("游戏开始\n");
		while (n > 0)
		{
			if (n <= 1)
			{
				printf("你输了\n");
				player++;
				printf("------------------------------------------------------\n");
				printf("\t1：再来一局\n\t0：结束游戏并结算\n请输入指令：\n");
				scanf("%d", &Order);
				if (Order == 1)
				{
					system("cls");
					break;
				}
				else if (Order == 0)
				{
					printf("您一共玩了%d局\n赢了%d局\n输了%d局\n", player + computer, computer, player);
					system("pause");
					main();
				}
				else
					printf("输入的指令不对！\n");
			}
			printf("请输入你要搬走的山的数目：\n");
			scanf("%d", &i);
			if (i > k)
			{
				system("cls");
				printf("不能大于最大数哦，请重新输入\n");
				continue;
			}
			system("cls");
			n = n - i;
			printf("你搬走了%d座山，还剩%d座山。\n", i, n);
			system("pause");
			if (n <= 1)
			{
				printf("你赢了\n");
				computer++;
				printf("------------------------------------------------------\n");
				printf("\t1：再来一局\n\t0：结束游戏并结算\n请输入指令：\n");
				scanf("%d", &Order);
				if (Order == 1)
				{
					system("cls");
					break;
				}
				else if (Order == 0)
				{
					system("cls");
					printf("您一共玩了%d局\n赢了%d局\n输了%d局\n", player + computer, computer, player);
					system("pause");
					main();
				}
				else
					printf("输入的指令不对！\n");
			}
			if ((n - 1) <= k)
				i = n - 1;
			else
				i = (n - 1) % (k + 1);
			if (i == 0)
				i = 1;
			n = n - i;
			system("cls");
			printf("计算机搬走了%d座山，还剩%d座山。\n", i, n);
		}
	}
	system("pause");
}


//销售管理系统
void SaleManageSystem()
{
	int iOrder = -1;
	//初始化 
	while (1)
	{
		system("cls");
		SaleSystemMenu();
		printf("请输入指令_");
		scanf("%d", &iOrder);
		switch (iOrder)
		{
		case 1:
			//销售信息录入
			ShowAddSale();
			break;
		case 2:
			//销售额查询
			ShowSearchSale();
			break;
		case 3:
			//销售额修改
			ShowReviseSale();
			break;
		case 4:
			//销售信息删除
			ShowDeleteSale();
			break;
		case 5:
			//年销售额分析
			ShowAnalyzeSale();
		case 0:
			//返回主菜单
			main();
		default:
			printf("输入的指令不对！\n");
		}
	}
}