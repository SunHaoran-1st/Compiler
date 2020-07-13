#include "stdio.h"
#include "string.h"
#include "stdlib.h"


char OUT[4] = "OUT";//输出汉字的Type
char HaveReturnList[1000][100];//有返回值函数名
int have_dir = 0;//有返回值函数数量
char NoReturnList[1000][100];//无返回值函数名
int no_dir = 0;//无返回值函数数量
char Type[20000][100];//读取的词法分析结果
char Str[20000][100];//读取的词法分析结果
int Line[20000];//读取的词法分析结果
char Save_Type[20000][100];//语法分析输出序列的Type表
char Save_Str[20000][100];//语法分析输出序列的Str表
char sym[100];//当前字符串
int NOW = -1;//当前字符串位置
int Save_dir = -1;//Save数组存放位置
int line = 1;//词法分析时的单词的行数
int error_line[20000];//错误行号
char error_word[20000];//错误信息
int error_num = -1;//错误数量
int All_num = 0;//全局参数表中参数个数
int Local_num = 0;//局部参数表中参数个数
int Hanshu_num = 0;//函数表中函数个数
int Siyuan_num = 0;//四元式表中四元式个数
int if_return = -1;//是否需要返回语句，1为需要，0为不需要
int biaoda_l = 0;//表达式开始位置
int biaoda_r = 0;//表达式结束位置
int label_num = 0;//标签的数量
int temp_num = 0;//寄存器数量
int address = 0;//常量变量地址
int Mipsbiao_num = 0;//Mips表数量
int Mips_add = 0;//当前Mips表位置
int used[8] = { 0,0,0,0,0,0,0,0 };//寄存器是否用过标志

char con[6] = "const";
char var[4] = "var";
char null[5] = "NULL";
char func_def[9] = "Func_def";
char func_end[9] = "Func_end";
char para[5] = "para";
char label[6] = "label";
char temp_name[10] = "temp";
char label_name[20] = "label_";
char call[5] = "call";
char at0[3] = "@0";
char at[6] = "@@@@@";
char geta[5] = "geta";
char scan[6] = "scanf";
char print[7] = "printf";
char ret[4] = "ret";
char exp[4] = "exp";
char str[4] = "str";
char nextline[9] = "nextline";
char shuzu[4] = "[]=";
char all[4] = "All";
char local[6] = "Local";
char zero[5] = "zero";
char jump[5] = "jump";
char while_is[6] = "while";
char do_is[3] = "do";
char for_is[4] = "for";
char if_is[3] = "if";
char MAIN[5] = "main";
char back[5] = "back";
char push[5] = "push";

struct Canshubiao
{
	char type[100][100];
	char word[100][100];
	char value[100][100];
	char arr[100][100];//数组大小
	int flag[100];  //0为常量 1为变量
	int address[100];
}All, Local;//全局参数表和局部参数表
struct Hanshubiao {
	char name[100];//函数名
	char type[100];//函数类型
	int can_amount = 0;//函数参数数量
	char can_name[100][100];//函数参数名
	char can_type[100][100];//函数参数类型
}Hanshu_list[100];//函数表
struct Siyuanshi {
	char op[10];//操作符
	char label1[100];//操作数1
	char label2[100];//操作数2
	char result[100];//结果
}Siyuan_list[10000],Siyuan_out[10000];//四元式表
struct Mipsbiao {
	char fun_name[100];//函数名
	char fun_type[10];//函数类型
	int start_add;//函数起始地址
	char para_name[100][100];//参数名
	char para_type[100][100];//参数类型
	int para_num;//参数数量
	char var_name[100][100];//变量名
	char var_type[100][100];//变量类型
	char var_arr[100][100];//变量数组大小
	int var_add[100];//变量偏移
	int var_num;//变量数量
}Mips_list[100];
//Mips的符号表

void Siyuan_out_after();
void save_Siyuan_out(char a[], char b[], char c[], char d[],int i);
void change_Siyuan();
void Siyuan_out_before();
void have_used(char a[]);
void show_mips_biao();
char* check_value(char str[]);
char* kill_const(char str[]);
int get_const(char str[]);
int check_address(char str[]);
void temp_make();
void label_make();
void save_siyuan(char a[], char b[], char c[], char d[]);
void show_siyuan_table();
void show_hanshu_table();
void show_Local_table();
void show_All_table();
void Mips_out();
void error_out();
int check_const(char str[]);
int check_biaoda();
int check_can_type(char str[], int a, int b);
char* check_type(char str[], char str1[]);
void check_have_han(char str[]);
void check_have_can(char str[]);
void check_same_han(char str[]);
void check_same_can(char str[]);
void clear();
void Save_have(char str[]);
void Save_no(char str[]);
void Save(char str1[], char str2[]);
int which_words(int flag, char* words);
void CiFa();
void MakeList();
void getsym();
void regetsym();
void error(char wrong, int line);
void ZhengShu();
void ChangLiangDefine(int z);
void ChangLiang(int z);
void BianLiangDefine(int z);
void BianLiang(int z);
char* YinZi();
char* Xiang();
char* BiaoDaShi();
void ZhiCanShuBiao();
void TiaoJian(char str[]);
void TiaoJianYuJu();
void Head();
void CanShuBiao();
void HaveReturnDiaoYong();
void NoReturnDiaoYong();
void XunHuanYuJu();
void ReturnYuJu();
void PrintfYuJu();
void ScanfYuJu();
void FuZhiYuJu();
int YuJu();
void YuJuLie();
void FuHeYuJu();
void HaveReturnDefine();
void NoReturnDefine();
void Main();
void ChengXu();

int main() {
	//FILE* Output;
	//int i = 0, j = 0;
	//Output = fopen("error.txt", "w");
	CiFa();//跑一遍词法分析，生成middle.txt
	MakeList();//分析middle.txt，生成两个表存放middle.txt内容
	ChengXu();//语法分析执行
	error_out();//输出错误处理信息
	Mips_out();//生成Mips代码
//	//show_siyuan_table();//打印四元式表
//	Siyuan_out_before();//输出优化前四元式
//	Siyuan_out_after();//输出优化后四元式
	//show_All_table();//打印全局变量表
	//show_Local_table();//打印局部变量表
	//show_hanshu_table();//打印函数表
	//show_mips_biao();//打印mips下的符号表
	return 0;
}

void change_Siyuan() {
	int i,j;
	char temp[50];
	for (i = 0; i < Siyuan_num; i++) {
		if (strcmp(Siyuan_list[i].op, "Func_def") == 0) {
			strcpy(temp, Siyuan_list[i].label2);
			strcat(temp, "()");
			save_Siyuan_out(Siyuan_list[i].label1, temp, null, null, i);
			for (j = 0; j < strlen(temp); j++) temp[j] = '\000';
		}
		//函数声明
		else if (strcmp(Siyuan_list[i].op, "para") == 0) {
			save_Siyuan_out(Siyuan_list[i].op, Siyuan_list[i].label1, Siyuan_list[i].label2, null, i);
		}
		//函数参数
		else if (strcmp(Siyuan_list[i].op, "call") == 0) {
			save_Siyuan_out(Siyuan_list[i].op, Siyuan_list[i].label1, null, null, i);
		}
		//函数调用
		else if (strcmp(Siyuan_list[i].op, "push") == 0) {
			save_Siyuan_out(Siyuan_list[i].op, Siyuan_list[i].label1, null, null, i);
		}
		//调用参数
		else if (strcmp(Siyuan_list[i].op, "ret") == 0) {
			save_Siyuan_out(Siyuan_list[i].op, Siyuan_list[i].label1, null, null, i);
		}
		//函数返回
		else if (strcmp(Siyuan_list[i].op, "var") == 0) {
			save_Siyuan_out(Siyuan_list[i].op, Siyuan_list[i].label1, Siyuan_list[i].label2, null, i);
		}
		//变量定义
		else if (strcmp(Siyuan_list[i].op, "const") == 0) {
			save_Siyuan_out(Siyuan_list[i].op, Siyuan_list[i].label1, Siyuan_list[i].label2, Siyuan_list[i].result, i);
		}
		//常量定义
		else if (strcmp(Siyuan_list[i].op, "+") == 0 || strcmp(Siyuan_list[i].op, "-") == 0 ||
			strcmp(Siyuan_list[i].op, "*") == 0 || strcmp(Siyuan_list[i].op, "/") == 0) {
			strcpy(temp, Siyuan_list[i].result);
			strcat(temp, "=");
			save_Siyuan_out(temp, Siyuan_list[i].label1, Siyuan_list[i].op, Siyuan_list[i].label2, i);
			for (j = 0; j < strlen(temp); j++) temp[j] = '\000';
		}
		//四则运算(表达式)
		else if (strcmp(Siyuan_list[i].op, "=") == 0) {
			save_Siyuan_out(Siyuan_list[i].result, Siyuan_list[i].op, Siyuan_list[i].label1, null, i);
		}
		//赋值运算
		else if (strcmp(Siyuan_list[i].op, "label") == 0) {
			strcpy(temp, Siyuan_list[i].label2);
			strcat(temp, ":");
			save_Siyuan_out(temp, null, null, null, i);
			for (j = 0; j < strlen(temp); j++) temp[j] = '\000';
		}
		//标签
		else if (strcmp(Siyuan_list[i].op, "geta") == 0) {
			strcpy(temp, Siyuan_list[i].label1);
			strcat(temp, "=");
			char temp1[50] = "[";
			strcat(temp1, Siyuan_list[i].result);
			strcat(temp1, "]");
			save_Siyuan_out(temp, Siyuan_list[i].label2, temp1, null, i);
			for (j = 0; j < strlen(temp); j++) temp[j] = '\000';
			for (j = 0; j < strlen(temp1); j++) temp1[j] = '\000';
		}
		//数组调用
		else if (strcmp(Siyuan_list[i].op, "[]=") == 0) {
			strcpy(temp, Siyuan_list[i].label2);
			strcat(temp, "[");
			strcat(temp, Siyuan_list[i].result);
			strcat(temp, "]");
			strcat(temp, "=");
			save_Siyuan_out(temp, Siyuan_list[i].label1, null, null, i);
			for (j = 0; j < strlen(temp); j++) temp[j] = '\000';
		}
		//数组赋值
		else {
			save_Siyuan_out(Siyuan_list[i].op, Siyuan_list[i].label1, Siyuan_list[i].label2, Siyuan_list[i].result, i);
		}
	}
}
//生成要求的四元式
void save_Siyuan_out(char a[],char b[],char c[],char d[],int i) {
	strcpy(Siyuan_out[i].op, a);
	strcpy(Siyuan_out[i].label1, b);
	strcpy(Siyuan_out[i].label2, c);
	strcpy(Siyuan_out[i].result, d);
}
//存要求的四元式表
void Siyuan_out_before() {
	FILE* Out;
	Out = fopen("17182627_孙浩然_优化前中间代码.txt", "w");
	change_Siyuan();
	int i;
	for (i = 0; i < Siyuan_num; i++) {
		fprintf(Out, "%s %s %s %s\n", Siyuan_out[i].op, Siyuan_out[i].label1, Siyuan_out[i].label2, Siyuan_out[i].result);
	}
	fclose(Out);
}
//输出优化前四元式内容
void Siyuan_out_after() {
	FILE* Out;
	Out = fopen("17182627_孙浩然_优化后中间代码.txt", "w");
	change_Siyuan();
	int i;
	for (i = 0; i < Siyuan_num; i++) {
		fprintf(Out, "%s %s %s %s\n", Siyuan_out[i].op, Siyuan_out[i].label1, Siyuan_out[i].label2, Siyuan_out[i].result);
	}
	fclose(Out);
}
//输出优化后四元式内容
void show_mips_biao() {
	int i, j;
	for (i = 0; i <= Mipsbiao_num; i++) {
		printf("  fun_name   fun_type   para_num    var_num  start_add\n");
		printf("%10s %10s %10d %10d %10d\n", Mips_list[i].fun_name, Mips_list[i].fun_type, Mips_list[i].para_num, Mips_list[i].var_num, Mips_list[i].start_add);
		printf(" para_name  para_type\n");
		for (j = 0; j < Mips_list[i].para_num; j++) {
			printf("%10s %10s\n", Mips_list[i].para_name[j], Mips_list[i].para_type[j]);
		}
		printf("  var_name   var_type    var_add    var_arr\n");
		for (j = 0; j < Mips_list[i].var_num; j++) {
			printf("%10s %10s %10d %10s\n", Mips_list[i].var_name[j], Mips_list[i].var_type[j], Mips_list[i].var_add[j], Mips_list[i].var_arr[j]);
		}
		printf("------------------------------------------------------------\n");
	}
}
//输出Mips表内容
char* kill_const(char str[]) {
	char temp[1];
	temp[0] = str[0];
	return (null);
}
//消除@符号
int get_const(char str[]) {
	int i = 0;
	int len = strlen(str);
	for (i = 0; i < len; i++) {
		if (str[i] == '@' && str[0] != '@') {
			return 1;
		}
	}
	return 0;
}
//查看四元式是否是字符
void have_used(char a[]) {
	int i;
	i = a[2] - 48;
	used[i] = 0;
}
//使寄存器变为可用
void temp_make() {
	char temp[20] = "";
	int i;
	//strDst = to_string(temp_num).c_str();
	//char strDst[20] = "0";
	//itoa(temp_num, strDst, 10);
	//strcat(temp, strDst);
	for (i = 0; i < 8; i++) {
		if (used[i] == 0) {
			sprintf(temp, "$t%d", i);
			strcpy(temp_name, temp);
			used[i] = 1;
			break;
		}
	}
}
//生成下一个寄存器名
void label_make() {
	char label[20] = "";
	sprintf(label, "label_%d", label_num);
	label_num++;
	strcpy(label_name, label);
}
//生成下一个label
void save_siyuan(char a[], char b[], char c[], char d[]) {
	strcpy(Siyuan_list[Siyuan_num].op, a);
	strcpy(Siyuan_list[Siyuan_num].label1, b);
	strcpy(Siyuan_list[Siyuan_num].label2, c);
	strcpy(Siyuan_list[Siyuan_num].result, d);
	Siyuan_num++;
}
//存四元式表
void show_siyuan_table() {
	int i;
	for (i = 0; i < Siyuan_num; i++) {
		printf("%10s %10s %10s %10s\n", Siyuan_list[i].op, Siyuan_list[i].label1, Siyuan_list[i].label2, Siyuan_list[i].result);
	}
}
//输出四元式表
void show_hanshu_table() {
	int i, j;
	printf("函数表\n");
	for (i = 0; i < Hanshu_num - 1; i++) {
		printf("%10s %10s %10d\n", Hanshu_list[i].type, Hanshu_list[i].name, Hanshu_list[i].can_amount);
		for (j = 0; j < Hanshu_list[i].can_amount; j++) {
			printf("%10s %10s ", Hanshu_list[i].can_type[j], Hanshu_list[i].can_name[j]);
		}
		printf("\n");
	}
}
//输出函数表
void show_Local_table() {
	int i;
	printf("局部参数表\n");
	for (i = 0; i < Local_num; i++) {
		printf("%10s %10s %10s %10s %10d %10d\n", Local.type[i], Local.word[i], Local.value[i], Local.arr[i], Local.flag[i], Local.address[i]);
	}
}
//输出局部参数表
void show_All_table() {
	int i;
	printf("全局参数表\n");
	for (i = 0; i < All_num; i++) {
		printf("%10s %10s %10s %10s %10d %10d\n", All.type[i], All.word[i], All.value[i], All.arr[i], All.flag[i], All.address[i]);
	}
}
//输出全局参数表
void Mips_out() {
	FILE* Output;
	Output = fopen("mips.txt", "w");
	int i, s, k, l, j = 0, start = 0, flag = 0, each_get = 0;
	int main_flag = 0;
	int para_num_temp[100] = { 0 };
	char temp_str[100] = "\0";
	char state[10] = "\0";
	char fun_name_temp[50] = "\000";
	char now_use_fun[100][100];
	int now_use_num = 0;
	//以下为.data内容
	fprintf(Output, ".data\n");
	fprintf(Output, "temp_space:.space 6500\n");
	fprintf(Output, "nextline:.asciiz \"\\n\"\n");
	for (i = 0; i < Siyuan_num; i++) {
		if (strcmp(Siyuan_list[i].op, "printf") == 0 && strcmp(Siyuan_list[i].label1, "str") == 0) {
			j++;
			for (k = 0, l = 0; k < strlen(Siyuan_list[i].label2); k++, l++) {
				if (Siyuan_list[i].label2[k] == '\\') {
					temp_str[l] = Siyuan_list[i].label2[k];
					l++;
					temp_str[l] = '\\';
				}
				else {
					temp_str[l] = Siyuan_list[i].label2[k];
				}
			}
			fprintf(Output, "str%d:.asciiz \"%s\"\n", j, temp_str);
			for (l = 0; l < 100; l++) {
				temp_str[l] = '\000';
			}
		}
	}
	//查找字符串
	for (i = 0, j = 0; i < Siyuan_num; i++) {
		each_get = 0;
		l = 0;
		k = 0;
		if (strcmp(Siyuan_list[i].op, "main") == 0) {
			flag = 1;
			strcpy(Mips_list[j].fun_name, "main");
			Mips_list[j].para_num = 0;
			Mips_list[j].start_add = start;
		}
		if ((strcmp(Siyuan_list[i].op, "const") == 0 || strcmp(Siyuan_list[i].op, "var") == 0) && flag == 0) {
			flag = 1;
			strcpy(Mips_list[j].fun_name, "const");
			Mips_list[j].para_num = 0;
			Mips_list[j].start_add = start;
			while (strcmp(Siyuan_list[i].op, "const") == 0 || strcmp(Siyuan_list[i].op, "var") == 0) {
				strcpy(Mips_list[j].var_name[l], Siyuan_list[i].label2);
				strcpy(Mips_list[j].var_type[l], Siyuan_list[i].label1);
				if (strcmp(Siyuan_list[i].op, "var") == 0) {
					strcpy(Mips_list[j].var_arr[l], Siyuan_list[i].result);
				}
				else {
					strcpy(Mips_list[j].var_arr[l], null);
				}
				if (l == 0) {
					Mips_list[j].var_add[l] = 0;
				}
				else {
					Mips_list[j].var_add[l] = Mips_list[j].var_add[l - 1] + each_get;
				}
				if (strcmp(Siyuan_list[i].result, "NULL") != 0 && strcmp(Siyuan_list[i].op, "var") == 0) {
					each_get = 4 * atoi(Siyuan_list[i].result);
				}
				else {
					each_get = 4;
				}
				Mips_list[j].var_num++;
				l++;
				i++;
			}
			start = start + Mips_list[j].var_add[l - 1] + each_get;
			j++;
			i--;
			continue;
		}
		if ((strcmp(Siyuan_list[i].op, "const") == 0 || strcmp(Siyuan_list[i].op, "var") == 0) && flag == 1) {
			strcpy(Mips_list[j].fun_name, "main");
			Mips_list[j].para_num = 0;
			Mips_list[j].start_add = start;
			while (strcmp(Siyuan_list[i].op, "const") == 0 || strcmp(Siyuan_list[i].op, "var") == 0) {
				strcpy(Mips_list[j].var_name[l], Siyuan_list[i].label2);
				strcpy(Mips_list[j].var_type[l], Siyuan_list[i].label1);
				if (strcmp(Siyuan_list[i].op, "var") == 0) {
					strcpy(Mips_list[j].var_arr[l], Siyuan_list[i].result);
				}
				else {
					strcpy(Mips_list[j].var_arr[l], null);
				}
				if (l == 0) {
					Mips_list[j].var_add[l] = 0;
				}
				else {
					Mips_list[j].var_add[l] = Mips_list[j].var_add[l - 1] + each_get;
				}
				if (strcmp(Siyuan_list[i].result, "NULL") != 0 && strcmp(Siyuan_list[i].op, "var") == 0) {
					each_get = 4 * atoi(Siyuan_list[i].result);
				}
				else {
					each_get = 4;
				}
				Mips_list[j].var_num++;
				l++;
				i++;
			}
			start = start + Mips_list[j].var_add[l - 1] + each_get;
		}
		if (strcmp(Siyuan_list[i].op, "Func_def") == 0) {
			flag = 1;
			strcpy(Mips_list[j].fun_name, Siyuan_list[i].label2);
			strcpy(Mips_list[j].fun_type, Siyuan_list[i].label1);
			Mips_list[j].start_add = start;
			Mips_list[j].para_num = 0;
			Mips_list[j].var_num = 0;
			while (strcmp(Siyuan_list[i].op, "Func_end") != 0) {
				i++;
				if (strcmp(Siyuan_list[i].op, "para") == 0) {
					strcpy(Mips_list[j].para_name[k], Siyuan_list[i].label2);
					strcpy(Mips_list[j].para_type[k], Siyuan_list[i].label1);
					/*if (l == 0) {
						Mips_list[j].var_add[l] = 0;
					}
					else {
						Mips_list[j].var_add[l] = Mips_list[j].var_add[l-1] + each_get;
					}
					if (strcmp(Siyuan_list[i].result, "NULL") != 0 && strcmp(Siyuan_list[i].op, "var") == 0) {
						each_get = 4 * atoi(Siyuan_list[i].result);
					}
					else {
						each_get = 4;
					}*/
					Mips_list[j].para_num++;
					k++;
				}
				//参数
				if (strcmp(Siyuan_list[i].op, "const") == 0 || strcmp(Siyuan_list[i].op, "var") == 0) {
					strcpy(Mips_list[j].var_name[l], Siyuan_list[i].label2);
					strcpy(Mips_list[j].var_type[l], Siyuan_list[i].label1);
					if (strcmp(Siyuan_list[i].op, "var") == 0) {
						strcpy(Mips_list[j].var_arr[l], Siyuan_list[i].result);
					}
					else {
						strcpy(Mips_list[j].var_arr[l], null);
					}
					//strcpy(Mips_list[j].var_arr[l], Siyuan_list[i].result);
					if (l == 0) {
						Mips_list[j].var_add[l] = 0;
					}
					else {
						Mips_list[j].var_add[l] = Mips_list[j].var_add[l - 1] + each_get;
					}
					if (strcmp(Siyuan_list[i].result, "NULL") != 0 && strcmp(Siyuan_list[i].op, "var") == 0) {
						each_get = 4 * atoi(Siyuan_list[i].result);
					}
					else {
						each_get = 4;
					}
					Mips_list[j].var_num++;
					l++;
				}
				//变量
			}
			start = start + Mips_list[j].var_add[l - 1] + each_get;
			j++;
		}
	}
	Mipsbiao_num = j;
	//构建Mips符号表
	j = 0;
	s = 0;
	fprintf(Output, ".text\n");
	//以下为.text内容
	fprintf(Output, "add $fp,$sp,4\n");
	Mips_add = 0;
	for (i = 0; i < Siyuan_num; i++) {
		if (strcmp(Siyuan_list[i].op, "const") == 0) {
			if (strcmp(Siyuan_list[i].label1, "char") == 0)
				fprintf(Output, "li $t0,'%c'\n", Siyuan_list[i].result[0]);
			else
				fprintf(Output, "li $t0,%s\n", Siyuan_list[i].result);
			fprintf(Output, "la $t1,temp_space\n");
			fprintf(Output, "sw $t0,%d($t1)\n", check_address(Siyuan_list[i].label2));
			//fprintf(Output, "add $fp,$fp,4\n");
		}
		//常量定义
		if (strcmp(Siyuan_list[i].op, "var") == 0) {
			if (strcmp(Siyuan_list[i].result, "NULL") == 0) {
				//fprintf(Output, "add $fp,$fp,4\n");
			}
			else {
				//fprintf(Output, "li $t0,%s\n", Siyuan_list[i].result);
				//fprintf(Output, "mul $t0,$t0,4\n");
				//fprintf(Output, "add $fp,$fp,$t0\n");
			}
		}
		//变量定义
		if ((strcmp(Siyuan_list[i + 1].op, "Func_def") == 0 || strcmp(Siyuan_list[i + 1].op, "main") == 0 ||
			strcmp(Siyuan_list[i].op, "main") == 0 || strcmp(Siyuan_list[i].op, "Func_def") == 0) && main_flag == 0) {
			main_flag = 1;
			fprintf(Output, "j main\n");
		}
		//main跳转
		if (strcmp(Siyuan_list[i].op, "main") == 0) {
			Mips_add = Mipsbiao_num;
			fprintf(Output, "main:\n");
		}
		//main标记
		if (strcmp(Siyuan_list[i].op, "=") == 0) {
			if (Siyuan_list[i].result[0] == '$' && Siyuan_list[i].label1[0] == '@') {
				fprintf(Output, "move %s,$s%c\n", Siyuan_list[i].result, Siyuan_list[i].label1[1]);
				continue;
			}
			else if (Siyuan_list[i].label1[0] != '$') {
				if (get_const(Siyuan_list[i].label1) == 0 && Siyuan_list[i].label1[0] != '@') {
					if ((Siyuan_list[i].label1[0] >= '0' && Siyuan_list[i].label1[0] <= '9') ||
						Siyuan_list[i].label1[0] == '+' || Siyuan_list[i].label1[0] == '-') {
						fprintf(Output, "li $t8,%s\n", Siyuan_list[i].label1);
					}
					//整数
					else {
						if (check_address(Siyuan_list[i].label1) < 0) {
							fprintf(Output, "lw $t8,%d($sp)\n", (check_address(Siyuan_list[i].label1) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s7,temp_space\n");
							fprintf(Output, "lw $t8,%d($s7)\n", check_address(Siyuan_list[i].label1));
						}
					}
					//变量
				}
				//label1是非字符常量
				else if (Siyuan_list[i].label1[0] == '@') {
					fprintf(Output, "move $t8,$s%c\n", Siyuan_list[i].label1[1]);
				}
				else {
					fprintf(Output, "li $t8,'%c'\n", Siyuan_list[i].label1[0]);
				}
				//label1是字符常量
				if (check_address(Siyuan_list[i].result) < 0) {
					fprintf(Output, "sw $t8,%d($sp)\n", (check_address(Siyuan_list[i].result) + 1) * 4);
				}
				else {
					fprintf(Output, "la $t9,temp_space\n");
					fprintf(Output, "sw $t8,%d($t9)\n", check_address(Siyuan_list[i].result));
				}
			}
			//赋非寄存器
			else {
				if (check_address(Siyuan_list[i].result) < 0) {
					fprintf(Output, "sw %s,%d($sp)\n", Siyuan_list[i].label1, (check_address(Siyuan_list[i].result) + 1) * 4);
				}
				else {
					fprintf(Output, "la $t8,temp_space\n");
					fprintf(Output, "sw %s,%d($t8)\n", Siyuan_list[i].label1, check_address(Siyuan_list[i].result));
				}
			}
			//赋寄存器值
		}
		//非数组赋值
		if (strcmp(Siyuan_list[i].op, "[]=") == 0) {
			if (Siyuan_list[i].label1[0] != '$') {
				if (get_const(Siyuan_list[i].label1) == 0) {
					if ((Siyuan_list[i].label1[0] >= '0' && Siyuan_list[i].label1[0] <= '9') ||
						Siyuan_list[i].label1[0] == '+' || Siyuan_list[i].label1[0] == '-') {
						fprintf(Output, "li $t8,%s\n", Siyuan_list[i].label1);
					}
					//整数
					else {
						if (check_address(Siyuan_list[i].label1) < 0) {
							fprintf(Output, "lw $t8,%d($sp)\n", (check_address(Siyuan_list[i].label1) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s7,temp_space\n");
							fprintf(Output, "lw $t8,%d($s7)\n", check_address(Siyuan_list[i].label1));
						}
					}
					//变量
				}
				//label1是非字符常量
				else {
					fprintf(Output, "li $t8,'%c'\n", Siyuan_list[i].label1[0]);
				}
				//label1是字符常量

				if (Siyuan_list[i].label2[0] == '$') {
					fprintf(Output, "li $s6,%d\n", check_address(Siyuan_list[i].result));//基地址
					fprintf(Output, "mul %s,%s,4\n", Siyuan_list[i].label2, Siyuan_list[i].label2);//偏移量
					fprintf(Output, "add $s6,$s6,%s\n", Siyuan_list[i].label2);
					fprintf(Output, "sw $t8,temp_space($s6)\n");
				}
				else {
					if ((Siyuan_list[i].label2[0] >= '0' && Siyuan_list[i].label2[0] <= '9') ||
						Siyuan_list[i].label2[0] == '+' || Siyuan_list[i].label2[0] == '-') {
						fprintf(Output, "li $s7,%s\n", Siyuan_list[i].label2);
					}
					else {
						if (check_address(Siyuan_list[i].label2) < 0) {
							fprintf(Output, "lw $s7,%d($sp)\n", (check_address(Siyuan_list[i].label2) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s6,temp_space\n");
							fprintf(Output, "lw $s7,%d($s6)\n", check_address(Siyuan_list[i].label2));
						}
					}
					fprintf(Output, "li $s6,%d\n", check_address(Siyuan_list[i].result));//基地址
					fprintf(Output, "mul $s7,$s7,4\n");//偏移量
					fprintf(Output, "add $s6,$s6,$s7\n");
					fprintf(Output, "sw $t8,temp_space($s6)\n");
				}
			}
			//赋非寄存器
			else {
				if (Siyuan_list[i].label2[0] == '$') {
					fprintf(Output, "li $s6,%d\n", check_address(Siyuan_list[i].result));//基地址
					fprintf(Output, "mul %s,%s,4\n", Siyuan_list[i].label2, Siyuan_list[i].label2);//偏移量
					fprintf(Output, "add $s6,$s6,%s\n", Siyuan_list[i].label2);
					fprintf(Output, "sw %s,temp_space($s6)\n", Siyuan_list[i].label1);
				}
				else {
					if ((Siyuan_list[i].label2[0] >= '0' && Siyuan_list[i].label2[0] <= '9') ||
						Siyuan_list[i].label2[0] == '+' || Siyuan_list[i].label2[0] == '-') {
						fprintf(Output, "li $s7,%s\n", Siyuan_list[i].label2);
					}
					else {
						if (check_address(Siyuan_list[i].label2) < 0) {
							fprintf(Output, "lw $s7,%d($sp)\n", (check_address(Siyuan_list[i].label2) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s6,temp_space\n");
							fprintf(Output, "lw $s7,%d($s6)\n", check_address(Siyuan_list[i].label2));
						}
					}
					fprintf(Output, "li $s6,%d\n", check_address(Siyuan_list[i].result));//基地址
					fprintf(Output, "mul $s7,$s7,4\n");//偏移量
					fprintf(Output, "add $s6,$s6,$s7\n");
					fprintf(Output, "sw %s,temp_space($s6)\n", Siyuan_list[i].label1);
				}
			}
			//赋寄存器值
		}
		//数组赋值
		if (strcmp(Siyuan_list[i].op, "+") == 0 || strcmp(Siyuan_list[i].op, "-") == 0
			|| strcmp(Siyuan_list[i].op, "*") == 0 || strcmp(Siyuan_list[i].op, "/") == 0) {
			//label1赋值到t8
			int flag_t8 = 0;
			int flag_t9 = 0;
			if (Siyuan_list[i].label1[0] == '@') {
				fprintf(Output, "move $t8,$s%c\n", Siyuan_list[i].label1[1]);
			}
			else if (Siyuan_list[i].label1[0] == '$') {
				fprintf(Output, "move $t8,%s\n", Siyuan_list[i].label1);
				flag_t8 = 1;
			}
			else if (((Siyuan_list[i].label1[0] >= '0' && Siyuan_list[i].label1[0] <= '9') ||
				Siyuan_list[i].label1[0] == '-' || Siyuan_list[i].label1[0] == '+')&& get_const(Siyuan_list[i].label1) == 0) {
				fprintf(Output, "li $t8,%s\n", Siyuan_list[i].label1);
				flag_t8 = 1;
			}
			else if (get_const(Siyuan_list[i].label1) == 1 && Siyuan_list[i].label1[0] != '@') {
				fprintf(Output, "li $t8,'%c'\n", Siyuan_list[i].label1[0]);
				flag_t8 = 1;
			}
			else if (strcmp(Siyuan_list[i].label1, "NULL") == 0) {
				fprintf(Output, "move $t8,$0\n");
				flag_t8 = 1;
			}
			else if (flag_t8 == 0) {
				if (check_address(Siyuan_list[i].label1) < 0) {
					fprintf(Output, "lw $t8,%d($sp)\n", (check_address(Siyuan_list[i].label1) + 1) * 4);
				}
				else {
					fprintf(Output, "la $s7,temp_space\n");
					fprintf(Output, "lw $t8,%d($s7)\n", check_address(Siyuan_list[i].label1));
				}
			}
			//label2赋值到t9
			if (Siyuan_list[i].label2[0] == '@') {
				fprintf(Output, "move $t9,$s%c\n", Siyuan_list[i].label2[1]);
			}
			else if (Siyuan_list[i].label2[0] == '$') {
				fprintf(Output, "move $t9,%s\n", Siyuan_list[i].label2);
				flag_t9 = 1;
			}
			else if (((Siyuan_list[i].label2[0] >= '0' && Siyuan_list[i].label2[0] <= '9') ||
				Siyuan_list[i].label2[0] == '-' || Siyuan_list[i].label2[0] == '+')&& get_const(Siyuan_list[i].label2) == 0) {
				fprintf(Output, "li $t9,%s\n", Siyuan_list[i].label2);
				flag_t9 = 1;
			}
			else if (get_const(Siyuan_list[i].label2) == 1 && Siyuan_list[i].label2[0] != '@') {
				fprintf(Output, "li $t9,'%c'\n", Siyuan_list[i].label2[0]);
				flag_t9 = 1;
			}
			else if (flag_t9 == 0) {
				if (check_address(Siyuan_list[i].label2) < 0) {
					fprintf(Output, "lw $t9,%d($sp)\n", (check_address(Siyuan_list[i].label2) + 1) * 4);
				}
				else {
					fprintf(Output, "la $s7,temp_space\n");
					fprintf(Output, "lw $t9,%d($s7)\n", check_address(Siyuan_list[i].label2));
				}
			}
			//计算
			if (strcmp(Siyuan_list[i].op, "+") == 0)
				fprintf(Output, "add %s,$t8,$t9\n", Siyuan_list[i].result);
			if (strcmp(Siyuan_list[i].op, "-") == 0)
				fprintf(Output, "sub %s,$t8,$t9\n", Siyuan_list[i].result);
			if (strcmp(Siyuan_list[i].op, "*") == 0)
				fprintf(Output, "mul %s,$t8,$t9\n", Siyuan_list[i].result);
			if (strcmp(Siyuan_list[i].op, "/") == 0)
				fprintf(Output, "div %s,$t8,$t9\n", Siyuan_list[i].result);
		}
		//四则运算
		if (strcmp(Siyuan_list[i].op, "geta") == 0) {
			if ((Siyuan_list[i].result[0] >= '0' && Siyuan_list[i].result[0] <= '9') ||
				Siyuan_list[i].result[0] == '+' || Siyuan_list[i].result[0] == '-') {
				fprintf(Output, "li $t8,%d\n", check_address(Siyuan_list[i].label2));
				fprintf(Output, "li $t9,%s\n", Siyuan_list[i].result);
				fprintf(Output, "mul $t9,$t9,4\n");
				fprintf(Output, "add $t8,$t8,$t9\n");
				fprintf(Output, "lw %s,temp_space($t8)\n", Siyuan_list[i].label1);
			}
			else if (Siyuan_list[i].result[0] == '$') {
				fprintf(Output, "li $t8,%d\n", check_address(Siyuan_list[i].label2));
				fprintf(Output, "mul %s,%s,4\n", Siyuan_list[i].result, Siyuan_list[i].result);
				fprintf(Output, "add $t8,$t8,%s\n", Siyuan_list[i].result);
				fprintf(Output, "lw %s,temp_space($t8)\n", Siyuan_list[i].label1);
			}
			else if (Siyuan_list[i].result[0] == '@') {
				fprintf(Output, "li $t8,%d\n", check_address(Siyuan_list[i].label2));
				fprintf(Output, "move $t9,$s%c\n", Siyuan_list[i].result[1]);
				fprintf(Output, "mul $t9,$t9,4\n");
				fprintf(Output, "add $t8,$t8,$t9\n");
				fprintf(Output, "lw %s,temp_space($t8)\n", Siyuan_list[i].label1);
			}
			else {
				fprintf(Output, "li $t8,%d\n", check_address(Siyuan_list[i].label2));
				if (check_address(Siyuan_list[i].result) < 0) {
					fprintf(Output, "lw $t9,%d($sp)\n", (check_address(Siyuan_list[i].result) + 1) * 4);
				}
				else {
					fprintf(Output, "la $s7,temp_space\n");
					fprintf(Output, "lw $t9,%d($s7)\n", check_address(Siyuan_list[i].result));
				}
				fprintf(Output, "mul $t9,$t9,4\n");
				fprintf(Output, "add $t8,$t8,$t9\n");
				fprintf(Output, "lw %s,temp_space($t8)\n", Siyuan_list[i].label1);
			}
		}
		//数组取值
		if (strcmp(Siyuan_list[i].op, "scanf") == 0) {
			if (strcmp(Siyuan_list[i].label2, "int") == 0)
				fprintf(Output, "li $v0,5\n");
			else
				fprintf(Output, "li $v0,12\n");
			fprintf(Output, "syscall\n");
			fprintf(Output, "la $s7,temp_space\n");
			fprintf(Output, "sw $v0,%d($s7)\n", check_address(Siyuan_list[i].label1));
		}
		//scanf语句
		if (strcmp(Siyuan_list[i].op, "printf") == 0) {
			if (strcmp(Siyuan_list[i].label1, "str") == 0) {
				s++;
				fprintf(Output, "li $v0,4\n");
				fprintf(Output, "la $a0,str%d\n", s);
				fprintf(Output, "syscall\n");
			}
			if (strcmp(Siyuan_list[i].label1, "exp") == 0) {
				if (Siyuan_list[i].result[0] != '$') {
					if (strcmp(Siyuan_list[i].label2, "int") == 0) {
						fprintf(Output, "li $v0,1\n");

					}
					if (strcmp(Siyuan_list[i].label2, "char") == 0) {
						fprintf(Output, "li $v0,11\n");
					}
					if (Siyuan_list[i].result[0] == '@') {
						fprintf(Output, "move $a0,$s%c\n", Siyuan_list[i].result[1]);
					}
					else if (get_const(Siyuan_list[i].result) == 0 && Siyuan_list[i].result[0] != '@') {
						if ((Siyuan_list[i].result[0] >= '0' && Siyuan_list[i].result[0] <= '9') ||
							Siyuan_list[i].result[0] == '+' || Siyuan_list[i].result[0] == '-') {
							fprintf(Output, "li $a0,%s\n", Siyuan_list[i].result);
						}
						else {
							if (check_address(Siyuan_list[i].result) < 0) {
								fprintf(Output, "lw $a0,%d($sp)\n", (check_address(Siyuan_list[i].result) + 1) * 4);
							}
							else {
								fprintf(Output, "la $s7,temp_space\n");
								fprintf(Output, "lw $a0,%d($s7)\n", check_address(Siyuan_list[i].result));
							}
						}
					}
					else {
						fprintf(Output, "li $a0,'%c'\n", Siyuan_list[i].result[0]);
					}
					fprintf(Output, "syscall\n");
				}
				else {
					if (strcmp(Siyuan_list[i].label2, "int") == 0) {
						fprintf(Output, "li $v0,1\n");

					}
					if (strcmp(Siyuan_list[i].label2, "char") == 0) {
						fprintf(Output, "li $v0,11\n");
					}
					fprintf(Output, "move $a0,%s\n", Siyuan_list[i].result);
					fprintf(Output, "syscall\n");
				}
			}
			if (strcmp(Siyuan_list[i].label1, "nextline") == 0) {
				fprintf(Output, "li $v0,4\n");
				fprintf(Output, "la $a0,nextline\n");
				fprintf(Output, "syscall\n");
			}
		}
		//printf语句
		if (strcmp(Siyuan_list[i].op, "Func_def") == 0) {
			for (Mips_add = 0; Mips_add <= Mipsbiao_num; Mips_add++) {
				if (strcmp(Siyuan_list[i].label2, Mips_list[Mips_add].fun_name) == 0) {
					break;
				}
			}
			fprintf(Output, "%s:\n", Siyuan_list[i].label2);
			fprintf(Output, "sw $ra,-%d($sp)\n", (Mips_list[Mips_add].para_num + 1) * 4);
		}
		//函数定义
		if (strcmp(Siyuan_list[i].op, "Func_end") == 0) {
			fprintf(Output, "lw $ra,-%d($sp)\n", (Mips_list[Mips_add].para_num + 1) * 4);
			fprintf(Output, "jr $ra\n");
			for (Mips_add = 0; Mips_add <= Mipsbiao_num; Mips_add++) {
				if (strcmp(Mips_list[Mips_add].fun_name, "main") == 0) {
					break;
				}
			}
			Mips_add = Mipsbiao_num;
		}
		//函数结束
		if (strcmp(Siyuan_list[i].op, "ret") == 0) {
			if (strcmp(Mips_list[Mips_add].fun_name, "main") == 0) {
				
			}
			else {
				if (strcmp(Siyuan_list[i].label1, "NULL") != 0) {
					if (Siyuan_list[i].label1[0] == '$') {
						fprintf(Output, "move $s7,%s\n", Siyuan_list[i].label1);
					}
					else if (((Siyuan_list[i].label1[0] >= '0' && Siyuan_list[i].label1[0] <= '9') ||
						Siyuan_list[i].label1[0] == '+' || Siyuan_list[i].label1[0] == '-') && get_const(Siyuan_list[i].label1) == 0) {
						fprintf(Output, "li $s7,%s\n", Siyuan_list[i].label1);
					}
					else if (get_const(Siyuan_list[i].label1) == 1 && Siyuan_list[i].label1[0] != '@') {
						fprintf(Output, "li $s7,'%c'\n", Siyuan_list[i].label1[0]);
					}
					else if (Siyuan_list[i].label1[0] == '@') {
						fprintf(Output, "move $s7,$s%c\n", Siyuan_list[i].label1[1]);
					}
					else {
						if (check_address(Siyuan_list[i].label1) < 0) {
							fprintf(Output, "lw $s7,%d($sp)\n", (check_address(Siyuan_list[i].label1) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s6,temp_space\n");
							fprintf(Output, "lw $s7,%d($s6)\n", check_address(Siyuan_list[i].label1));
						}
					}
					fprintf(Output, "sw $s7,-%d($sp)\n", Mips_list[Mips_add].para_num * 4);
				}
				fprintf(Output, "lw $ra,-%d($sp)\n", (Mips_list[Mips_add].para_num + 1) * 4);
				fprintf(Output, "jr $ra\n");
			}
		}
		//return语句
		if (strcmp(Siyuan_list[i].op, "call") == 0) {
			now_use_num++;
			strcpy(now_use_fun[now_use_num], Siyuan_list[i].label1);
			fprintf(Output, "add $sp,$sp,-%d\n", (Mips_list[Mips_add].para_num + 2) * 4);
			for (l = 0; l < Mips_list[Mips_add].var_num; l++) {
				if (strcmp(Mips_list[Mips_add].var_arr[l], "NULL") == 0) {
					//fprintf(Output, "la $s6,temp_space\n");
					//fprintf(Output, "lw $s7,%d($s6)\n", Mips_list[Mips_add].var_add[l] + Mips_list[Mips_add].start_add);
					//fprintf(Output, "sw $s7,-%d($sp)\n", (Mips_list[Mips_add].var_add[l]));
				}
				else {
					for (j = 0; j < atoi(Mips_list[Mips_add].var_arr[l]); j++) {
						//fprintf(Output, "la $s6,temp_space\n");
						//fprintf(Output, "lw $s7,%d($s6)\n", Mips_list[Mips_add].var_add[l] + Mips_list[Mips_add].start_add + 4 * j);
						//fprintf(Output, "sw $s7,-%d($sp)\n", (Mips_list[Mips_add].var_add[l] + 4 * j));
					}
				}
			}
			fprintf(Output, "add $sp,$sp,%d\n", (Mips_list[Mips_add].para_num + 2) * 4);
			fprintf(Output, "add $sp,$sp,-%d\n", para_num_temp[now_use_num - 1] * 4);
			strcpy(fun_name_temp, Siyuan_list[i].label1);
			para_num_temp[now_use_num] = 0;
		}
		//函数调用
		if (strcmp(Siyuan_list[i].op, "push") == 0) {
			if (Siyuan_list[i].label1[0] == '$') {
				fprintf(Output, "move $s7,%s\n", Siyuan_list[i].label1);
			}
			else if (((Siyuan_list[i].label1[0] >= '0' && Siyuan_list[i].label1[0] <= '9') ||
				Siyuan_list[i].label1[0] == '+' || Siyuan_list[i].label1[0] == '-') && get_const(Siyuan_list[i].label1) == 0) {
				fprintf(Output, "li $s7,%s\n", Siyuan_list[i].label1);
			}
			else if (get_const(Siyuan_list[i].label1) == 1 && Siyuan_list[i].label1[0] != '@') {
				fprintf(Output, "li $s7,'%c'\n", Siyuan_list[i].label1[0]);
			}
			else if (Siyuan_list[i].label1[0] == '@') {
				fprintf(Output, "move $s7,$s%c\n", Siyuan_list[i].label1[1]);
			}
			else {
				if (check_address(Siyuan_list[i].label1) < 0) {
					fprintf(Output, "lw $s7,%d($sp)\n", (check_address(Siyuan_list[i].label1) + 1) * 4);
				}
				else {
					fprintf(Output, "la $s6,temp_space\n");
					fprintf(Output, "lw $s7,%d($s6)\n", check_address(Siyuan_list[i].label1));
				}
			}
			j = 0;
			for (l = 0; l < Mips_list[Mips_add].var_num; l++) {
				if (strcmp(Mips_list[Mips_add].var_arr[l], "NULL") == 0) {
					j += 4;
				}
				else {
					j += 4 * (atoi(Mips_list[Mips_add].var_arr[l]));
				}
			}
			para_num_temp[now_use_num]++;
			fprintf(Output, "add $sp,$sp,-%d\n", (Mips_list[Mips_add].para_num + 2) * 4 + j);
			fprintf(Output, "sw $s7,%d($sp)\n", (para_num_temp[now_use_num] - 1) * (-4));
			fprintf(Output, "add $sp,$sp,%d\n", (Mips_list[Mips_add].para_num + 2) * 4 + j);
		}
		//参数
		if (strcmp(Siyuan_list[i].op, "back") == 0) {
			j = 0;
			for (l = 0; l < Mips_list[Mips_add].var_num; l++) {
				if (strcmp(Mips_list[Mips_add].var_arr[l], "NULL") == 0) {
					j += 4;
				}
				else {
					j += 4 * (atoi(Mips_list[Mips_add].var_arr[l]));
				}
			}
			fprintf(Output, "add $sp,$sp,-%d\n", (Mips_list[Mips_add].para_num + 2) * 4 + j);
			for (k = 0; k <= Mipsbiao_num; k++) {
				if (strcmp(now_use_fun[now_use_num], Mips_list[k].fun_name) == 0) {
					l = Mips_list[k].para_num;
					break;
				}
			}
			for (k = 0; k < 8; k++) {
				fprintf(Output, "sw $t%d,temp_space($fp)\n", k);
				fprintf(Output, "add $fp,$fp,4\n");

			}
			if (strcmp(Siyuan_list[i].label2, "NULL") != 0) {
				fprintf(Output, "jal %s\n", now_use_fun[now_use_num]);
				for (k = 7; k >= 0; k--) {
					fprintf(Output, "add $fp,$fp,-4\n");
					fprintf(Output, "lw $t%d,temp_space($fp)\n", k);
				}
				if (Siyuan_list[i].label2[1] == '0')
					fprintf(Output, "lw $s0,-%d($sp)\n", (l) * 4);
				if (Siyuan_list[i].label2[1] == '1')
					fprintf(Output, "lw $s1,-%d($sp)\n", (l) * 4);
				fprintf(Output, "add $sp,$sp,%d\n", (Mips_list[Mips_add].para_num + 2) * 4 + j);
			}
			else {
				fprintf(Output, "jal %s\n", now_use_fun[now_use_num]);
				fprintf(Output, "add $fp,$fp,-32\n");
				for (k = 0; k < 8; k++) {
					fprintf(Output, "lw $t%d,%d($fp)\n", k, k * 4);
				}
				fprintf(Output, "add $sp,$sp,%d\n", (Mips_list[Mips_add].para_num + 2) * 4 + j);
			}

			for (l = 0, k = (Mips_list[Mips_add].para_num + 2) * 4; k < (Mips_list[Mips_add].para_num + 2) * 4 + j; l++, k += 4) {
				//fprintf(Output, "la $s7,temp_space\n");
				//fprintf(Output, "lw $s6,-%d($sp)\n", k);
				//fprintf(Output, "sw $s6,%d($s7)\n", Mips_list[Mips_add].start_add + 4 * l);
			}
			fprintf(Output, "add $sp,$sp,%d\n", para_num_temp[now_use_num - 1] * 4);
			para_num_temp[now_use_num] = 0;
			now_use_num--;
		}
		//函数调用返回
		if (strcmp(Siyuan_list[i].op, "if") == 0 || strcmp(Siyuan_list[i].op, "while") == 0 ||
			strcmp(Siyuan_list[i].op, "do") == 0 || strcmp(Siyuan_list[i].op, "for") == 0) {
			for (l = 0; l < 10; l++) {
				state[l] = '\000';
			}
			strcpy(state, Siyuan_list[i].op);
		}
		//条件
		if (strcmp(Siyuan_list[i].op, "label") == 0) {
			fprintf(Output, "%s:\n", Siyuan_list[i].label1);
		}
		//标签
		if (strcmp(Siyuan_list[i].op, "jump") == 0) {
			fprintf(Output, "j %s\n", Siyuan_list[i].label1);
		}
		//直接跳转
		if (strcmp(Siyuan_list[i].op, "zero") == 0 || strcmp(Siyuan_list[i].op, "GEQ") == 0 || strcmp(Siyuan_list[i].op, "GRE") == 0
			|| strcmp(Siyuan_list[i].op, "LEQ") == 0 || strcmp(Siyuan_list[i].op, "LSS") == 0 ||
			strcmp(Siyuan_list[i].op, "EQL") == 0 || strcmp(Siyuan_list[i].op, "NEQ") == 0) {
			if (strcmp(state, "do") == 0) {
				if (strcmp(Siyuan_list[i].op, "zero") == 0) {
					if (Siyuan_list[i].label1[0] == '$') {
						fprintf(Output, "BNE %s,$0,%s\n", Siyuan_list[i].label1, Siyuan_list[i].result);
					}
					else if (Siyuan_list[i].label1[0] == '@') {
						fprintf(Output, "move $s7,$s%c\n", Siyuan_list[i].label1[1]);
						fprintf(Output, "BNE $s7,$0,%s\n", Siyuan_list[i].result);
					}
					else if (get_const(Siyuan_list[i].label1) == 1 && Siyuan_list[i].label1[0] != '@') {
						fprintf(Output, "li $s7,'%c'\n", Siyuan_list[i].label1[0]);
						fprintf(Output, "BNE $s7,$0,%s\n", Siyuan_list[i].result);
					}
					else if ((Siyuan_list[i].label1[0] == '+' || Siyuan_list[i].label1[0] == '-' ||
						(Siyuan_list[i].label1[0] >= '0' && Siyuan_list[i].label1[0] <= '9'))) {
						fprintf(Output, "li $s7,%s\n", Siyuan_list[i].label1);
						fprintf(Output, "BNE $s7,$0,%s\n", Siyuan_list[i].result);
					}
					else {
						if (check_address(Siyuan_list[i].label1) < 0) {
							fprintf(Output, "lw $s7,%d($sp)\n", (check_address(Siyuan_list[i].label1) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s7,%d($s5)\n", check_address(Siyuan_list[i].label1));
						}
						fprintf(Output, "BNE $s7,$0,%s\n", Siyuan_list[i].result);
					}
				}
				//zero
				if (strcmp(Siyuan_list[i].op, "GEQ") == 0) {
					 if (get_const(Siyuan_list[i].label1) == 1 && Siyuan_list[i].label1[0] != '@') {
						fprintf(Output, "li $s6,'%c'\n", Siyuan_list[i].label1[0]);
					}
					else if (Siyuan_list[i].label1[0] == '+' || Siyuan_list[i].label1[0] == '-' ||
						(Siyuan_list[i].label1[0] >= '0' && Siyuan_list[i].label1[0] <= '9')) {
						fprintf(Output, "li $s6,%s\n", Siyuan_list[i].label1);
					}
					else if (Siyuan_list[i].label1[0] == '@') {
						fprintf(Output, "move $s6,$s%c\n", Siyuan_list[i].label1[1]);
					}
					else if (Siyuan_list[i].label1[0] == '$') {
						fprintf(Output, "move $s6,%s\n", Siyuan_list[i].label1);
					}
					else {
						if (check_address(Siyuan_list[i].label1) < 0) {
							fprintf(Output, "lw $s6,%d($sp)\n", (check_address(Siyuan_list[i].label1) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s6,%d($s5)\n", check_address(Siyuan_list[i].label1));
						}
					}
					 if (get_const(Siyuan_list[i].label2) == 1 && Siyuan_list[i].label2[0] != '@') {
						 fprintf(Output, "li $s7,'%c'\n", Siyuan_list[i].label2[0]);
					 }
					else if (Siyuan_list[i].label2[0] == '+' || Siyuan_list[i].label2[0] == '-' ||
						(Siyuan_list[i].label2[0] >= '0' && Siyuan_list[i].label2[0] <= '9')) {
						fprintf(Output, "li $s7,%s\n", Siyuan_list[i].label2);
					}
					else if (Siyuan_list[i].label2[0] == '@') {
						fprintf(Output, "move $s7,$s%c\n", Siyuan_list[i].label2[1]);
					}
					else if (Siyuan_list[i].label2[0] == '$') {
						fprintf(Output, "move $s7,%s\n", Siyuan_list[i].label2);
					}
					else {
						if (check_address(Siyuan_list[i].label2) < 0) {
							fprintf(Output, "lw $s7,%d($sp)\n", (check_address(Siyuan_list[i].label2) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s7,%d($s5)\n", check_address(Siyuan_list[i].label2));
						}
					}
					fprintf(Output, "BGE $s6,$s7,%s\n", Siyuan_list[i].result);
				}
				//GEQ>=
				if (strcmp(Siyuan_list[i].op, "GRE") == 0) {
					if (get_const(Siyuan_list[i].label1) == 1 && Siyuan_list[i].label1[0] != '@') {
						fprintf(Output, "li $s6,'%c'\n", Siyuan_list[i].label1[0]);
					}
					else if (Siyuan_list[i].label1[0] == '+' || Siyuan_list[i].label1[0] == '-' ||
						(Siyuan_list[i].label1[0] >= '0' && Siyuan_list[i].label1[0] <= '9')) {
						fprintf(Output, "li $s6,%s\n", Siyuan_list[i].label1);
					}
					else if (Siyuan_list[i].label1[0] == '@') {
						fprintf(Output, "move $s6,$s%c\n", Siyuan_list[i].label1[1]);
					}
					else if (Siyuan_list[i].label1[0] == '$') {
						fprintf(Output, "move $s6,%s\n", Siyuan_list[i].label1);
					}
					else {
						if (check_address(Siyuan_list[i].label1) < 0) {
							fprintf(Output, "lw $s6,%d($sp)\n", (check_address(Siyuan_list[i].label1) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s6,%d($s5)\n", check_address(Siyuan_list[i].label1));
						}
					}
					if (get_const(Siyuan_list[i].label2) == 1 && Siyuan_list[i].label2[0] != '@') {
						fprintf(Output, "li $s7,'%c'\n", Siyuan_list[i].label2[0]);
					}
					else if (Siyuan_list[i].label2[0] == '+' || Siyuan_list[i].label2[0] == '-' ||
						(Siyuan_list[i].label2[0] >= '0' && Siyuan_list[i].label2[0] <= '9')) {
						fprintf(Output, "li $s7,%s\n", Siyuan_list[i].label2);
					}
					else if (Siyuan_list[i].label2[0] == '@') {
						fprintf(Output, "move $s7,$s%c\n", Siyuan_list[i].label2[1]);
					}
					else if (Siyuan_list[i].label2[0] == '$') {
						fprintf(Output, "move $s7,%s\n", Siyuan_list[i].label2);
					}
					else {
						if (check_address(Siyuan_list[i].label2) < 0) {
							fprintf(Output, "lw $s7,%d($sp)\n", (check_address(Siyuan_list[i].label2) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s7,%d($s5)\n", check_address(Siyuan_list[i].label2));
						}
					}
					fprintf(Output, "BGT $s6,$s7,%s\n", Siyuan_list[i].result);
				}
				//GRE>
				if (strcmp(Siyuan_list[i].op, "LEQ") == 0) {
					if (get_const(Siyuan_list[i].label1) == 1 && Siyuan_list[i].label1[0] != '@') {
						fprintf(Output, "li $s6,'%c'\n", Siyuan_list[i].label1[0]);
					}
					else if (Siyuan_list[i].label1[0] == '+' || Siyuan_list[i].label1[0] == '-' ||
						(Siyuan_list[i].label1[0] >= '0' && Siyuan_list[i].label1[0] <= '9')) {
						fprintf(Output, "li $s6,%s\n", Siyuan_list[i].label1);
					}
					else if (Siyuan_list[i].label1[0] == '@') {
						fprintf(Output, "move $s6,$s%c\n", Siyuan_list[i].label1[1]);
					}
					else if (Siyuan_list[i].label1[0] == '$') {
						fprintf(Output, "move $s6,%s\n", Siyuan_list[i].label1);
					}
					else {
						if (check_address(Siyuan_list[i].label1) < 0) {
							fprintf(Output, "lw $s6,%d($sp)\n", (check_address(Siyuan_list[i].label1) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s6,%d($s5)\n", check_address(Siyuan_list[i].label1));
						}
					}
					if (get_const(Siyuan_list[i].label2) == 1 && Siyuan_list[i].label2[0] != '@') {
						fprintf(Output, "li $s7,'%c'\n", Siyuan_list[i].label2[0]);
					}
					else if (Siyuan_list[i].label2[0] == '+' || Siyuan_list[i].label2[0] == '-' ||
						(Siyuan_list[i].label2[0] >= '0' && Siyuan_list[i].label2[0] <= '9')) {
						fprintf(Output, "li $s7,%s\n", Siyuan_list[i].label2);
					}
					else if (Siyuan_list[i].label2[0] == '@') {
						fprintf(Output, "move $s7,$s%c\n", Siyuan_list[i].label2[1]);
					}
					else if (Siyuan_list[i].label2[0] == '$') {
						fprintf(Output, "move $s7,%s\n", Siyuan_list[i].label2);
					}
					else {
						if (check_address(Siyuan_list[i].label2) < 0) {
							fprintf(Output, "lw $s7,%d($sp)\n", (check_address(Siyuan_list[i].label2) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s7,%d($s5)\n", check_address(Siyuan_list[i].label2));
						}
					}
					fprintf(Output, "BLE $s6,$s7,%s\n", Siyuan_list[i].result);
				}
				//LEQ<=
				if (strcmp(Siyuan_list[i].op, "LSS") == 0) {
					if (get_const(Siyuan_list[i].label1) == 1 && Siyuan_list[i].label1[0] != '@') {
						fprintf(Output, "li $s6,'%c'\n", Siyuan_list[i].label1[0]);
					}
					else if (Siyuan_list[i].label1[0] == '+' || Siyuan_list[i].label1[0] == '-' ||
						(Siyuan_list[i].label1[0] >= '0' && Siyuan_list[i].label1[0] <= '9')) {
						fprintf(Output, "li $s6,%s\n", Siyuan_list[i].label1);
					}
					else if (Siyuan_list[i].label1[0] == '@') {
						fprintf(Output, "move $s6,$s%c\n", Siyuan_list[i].label1[1]);
					}
					else if (Siyuan_list[i].label1[0] == '$') {
						fprintf(Output, "move $s6,%s\n", Siyuan_list[i].label1);
					}
					else {
						if (check_address(Siyuan_list[i].label1) < 0) {
							fprintf(Output, "lw $s6,%d($sp)\n", (check_address(Siyuan_list[i].label1) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s6,%d($s5)\n", check_address(Siyuan_list[i].label1));
						}
					}
					if (get_const(Siyuan_list[i].label2) == 1 && Siyuan_list[i].label2[0] != '@') {
						fprintf(Output, "li $s7,'%c'\n", Siyuan_list[i].label2[0]);
					}
					if (Siyuan_list[i].label2[0] == '+' || Siyuan_list[i].label2[0] == '-' ||
						(Siyuan_list[i].label2[0] >= '0' && Siyuan_list[i].label2[0] <= '9')) {
						fprintf(Output, "li $s7,%s\n", Siyuan_list[i].label2);
					}
					else if (Siyuan_list[i].label2[0] == '@') {
						fprintf(Output, "move $s7,$s%c\n", Siyuan_list[i].label2[1]);
					}
					else if (Siyuan_list[i].label2[0] == '$') {
						fprintf(Output, "move $s7,%s\n", Siyuan_list[i].label2);
					}
					else {
						if (check_address(Siyuan_list[i].label2) < 0) {
							fprintf(Output, "lw $s7,%d($sp)\n", (check_address(Siyuan_list[i].label2) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s7,%d($s5)\n", check_address(Siyuan_list[i].label2));
						}
					}
					fprintf(Output, "BLT $s6,$s7,%s\n", Siyuan_list[i].result);
				}
				//LSS<
				if (strcmp(Siyuan_list[i].op, "EQL") == 0) {
					if (get_const(Siyuan_list[i].label1) == 1 && Siyuan_list[i].label1[0] != '@') {
						fprintf(Output, "li $s6,'%c'\n", Siyuan_list[i].label1[0]);
					}
					else if (Siyuan_list[i].label1[0] == '+' || Siyuan_list[i].label1[0] == '-' ||
						(Siyuan_list[i].label1[0] >= '0' && Siyuan_list[i].label1[0] <= '9')) {
						fprintf(Output, "li $s6,%s\n", Siyuan_list[i].label1);
					}
					else if (Siyuan_list[i].label1[0] == '@') {
						fprintf(Output, "move $s6,$s%c\n", Siyuan_list[i].label1[1]);
					}
					else if (Siyuan_list[i].label1[0] == '$') {
						fprintf(Output, "move $s6,%s\n", Siyuan_list[i].label1);
					}
					else {
						if (check_address(Siyuan_list[i].label1) < 0) {
							fprintf(Output, "lw $s6,%d($sp)\n", (check_address(Siyuan_list[i].label1) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s6,%d($s5)\n", check_address(Siyuan_list[i].label1));
						}
					}
					if (get_const(Siyuan_list[i].label2) == 1 && Siyuan_list[i].label2[0] != '@') {
						fprintf(Output, "li $s7,'%c'\n", Siyuan_list[i].label2[0]);
					}
					else if (Siyuan_list[i].label2[0] == '+' || Siyuan_list[i].label2[0] == '-' ||
						(Siyuan_list[i].label2[0] >= '0' && Siyuan_list[i].label2[0] <= '9')) {
						fprintf(Output, "li $s7,%s\n", Siyuan_list[i].label2);
					}
					else if (Siyuan_list[i].label2[0] == '@') {
						fprintf(Output, "move $s7,$s%c\n", Siyuan_list[i].label2[1]);
					}
					else if (Siyuan_list[i].label2[0] == '$') {
						fprintf(Output, "move $s7,%s\n", Siyuan_list[i].label2);
					}
					else {
						if (check_address(Siyuan_list[i].label2) < 0) {
							fprintf(Output, "lw $s7,%d($sp)\n", (check_address(Siyuan_list[i].label2) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s7,%d($s5)\n", check_address(Siyuan_list[i].label2));
						}
					}
					fprintf(Output, "BEQ $s6,$s7,%s\n", Siyuan_list[i].result);
				}
				//EQL==
				if (strcmp(Siyuan_list[i].op, "NEQ") == 0) {
					if (get_const(Siyuan_list[i].label1) == 1 && Siyuan_list[i].label1[0] != '@') {
						fprintf(Output, "li $s6,'%c'\n", Siyuan_list[i].label1[0]);
					}
					else if (Siyuan_list[i].label1[0] == '+' || Siyuan_list[i].label1[0] == '-' ||
						(Siyuan_list[i].label1[0] >= '0' && Siyuan_list[i].label1[0] <= '9')) {
						fprintf(Output, "li $s6,%s\n", Siyuan_list[i].label1);
					}
					else if (Siyuan_list[i].label1[0] == '@') {
						fprintf(Output, "move $s6,$s%c\n", Siyuan_list[i].label1[1]);
					}
					else if (Siyuan_list[i].label1[0] == '$') {
						fprintf(Output, "move $s6,%s\n", Siyuan_list[i].label1);
					}
					else {
						if (check_address(Siyuan_list[i].label1) < 0) {
							fprintf(Output, "lw $s6,%d($sp)\n", (check_address(Siyuan_list[i].label1) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s6,%d($s5)\n", check_address(Siyuan_list[i].label1));
						}
					}
					if (get_const(Siyuan_list[i].label2) == 1 && Siyuan_list[i].label2[0] != '@') {
						fprintf(Output, "li $s7,'%c'\n", Siyuan_list[i].label2[0]);
					}
					else if (Siyuan_list[i].label2[0] == '+' || Siyuan_list[i].label2[0] == '-' ||
						(Siyuan_list[i].label2[0] >= '0' && Siyuan_list[i].label2[0] <= '9')) {
						fprintf(Output, "li $s7,%s\n", Siyuan_list[i].label2);
					}
					else if (Siyuan_list[i].label2[0] == '@') {
						fprintf(Output, "move $s7,$s%c\n", Siyuan_list[i].label2[1]);
					}
					else if (Siyuan_list[i].label2[0] == '$') {
						fprintf(Output, "move $s7,%s\n", Siyuan_list[i].label2);
					}
					else {
						if (check_address(Siyuan_list[i].label2) < 0) {
							fprintf(Output, "lw $s7,%d($sp)\n", (check_address(Siyuan_list[i].label2) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s7,%d($s5)\n", check_address(Siyuan_list[i].label2));
						}
					}
					fprintf(Output, "BNE $s6,$s7,%s\n", Siyuan_list[i].result);
				}
				//NEQ!=
			}
			//do while是满足条件便跳转
			else {
				if (strcmp(Siyuan_list[i].op, "zero") == 0) {
					if (get_const(Siyuan_list[i].label1) == 1 && Siyuan_list[i].label1[0] != '@') {
						fprintf(Output, "li $s7,'%c'\n", Siyuan_list[i].label1[0]);
						fprintf(Output, "BEQ $s7,$0,%s\n", Siyuan_list[i].result);
					}
					else if (Siyuan_list[i].label1[0] == '$') {
						fprintf(Output, "BEQ %s,$0,%s\n", Siyuan_list[i].label1, Siyuan_list[i].result);
					}
					else if (Siyuan_list[i].label1[0] == '@') {
						fprintf(Output, "move $s7,$s%c\n", Siyuan_list[i].label1[1]);
						fprintf(Output, "BEQ $s7,$0,%s\n", Siyuan_list[i].result);
					}
					else if (Siyuan_list[i].label2[0] == '+' || Siyuan_list[i].label2[0] == '-' ||
						(Siyuan_list[i].label2[0] >= '0' && Siyuan_list[i].label2[0] <= '9')) {
						fprintf(Output, "li $s7,%s\n", Siyuan_list[i].label1);
						fprintf(Output, "BEQ $s7,$0,%s\n", Siyuan_list[i].result);
					}
					else {
						if (check_address(Siyuan_list[i].label1) < 0) {
							fprintf(Output, "lw $s7,%d($sp)\n", (check_address(Siyuan_list[i].label1) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s7,%d($s5)\n", check_address(Siyuan_list[i].label1));
						}
						fprintf(Output, "BEQ $s7,$0,%s\n", Siyuan_list[i].result);
					}
				}
				//zero
				if (strcmp(Siyuan_list[i].op, "GEQ") == 0) {
					if (get_const(Siyuan_list[i].label1) == 1 && Siyuan_list[i].label1[0] != '@') {
						fprintf(Output, "li $s6,'%c'\n", Siyuan_list[i].label1[0]);
					}
					else if (Siyuan_list[i].label1[0] == '+' || Siyuan_list[i].label1[0] == '-' ||
						(Siyuan_list[i].label1[0] >= '0' && Siyuan_list[i].label1[0] <= '9')) {
						fprintf(Output, "li $s6,%s\n", Siyuan_list[i].label1);
					}
					else if (Siyuan_list[i].label1[0] == '@') {
						fprintf(Output, "move $s6,$s%c\n", Siyuan_list[i].label1[1]);
					}
					else if (Siyuan_list[i].label1[0] == '$') {
						fprintf(Output, "move $s6,%s\n", Siyuan_list[i].label1);
					}
					else {
						if (check_address(Siyuan_list[i].label1) < 0) {
							fprintf(Output, "lw $s6,%d($sp)\n", (check_address(Siyuan_list[i].label1) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s6,%d($s5)\n", check_address(Siyuan_list[i].label1));
						}
					}
					if (get_const(Siyuan_list[i].label2) == 1 && Siyuan_list[i].label2[0] != '@') {
						fprintf(Output, "li $s7,'%c'\n", Siyuan_list[i].label2[0]);
					}
					else if (Siyuan_list[i].label2[0] == '+' || Siyuan_list[i].label2[0] == '-' ||
						(Siyuan_list[i].label2[0] >= '0' && Siyuan_list[i].label2[0] <= '9')) {
						fprintf(Output, "li $s7,%s\n", Siyuan_list[i].label2);
					}
					else if (Siyuan_list[i].label2[0] == '@') {
						fprintf(Output, "move $s7,$s%c\n", Siyuan_list[i].label2[1]);
					}
					else if (Siyuan_list[i].label2[0] == '$') {
						fprintf(Output, "move $s7,%s\n", Siyuan_list[i].label2);
					}
					else {
						if (check_address(Siyuan_list[i].label2) < 0) {
							fprintf(Output, "lw $s7,%d($sp)\n", (check_address(Siyuan_list[i].label2) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s7,%d($s5)\n", check_address(Siyuan_list[i].label2));
						}
					}
					fprintf(Output, "BLT $s6,$s7,%s\n", Siyuan_list[i].result);
				}
				//GEQ>=
				if (strcmp(Siyuan_list[i].op, "GRE") == 0) {
					if (get_const(Siyuan_list[i].label1) == 1 && Siyuan_list[i].label1[0] != '@') {
						fprintf(Output, "li $s6,'%c'\n", Siyuan_list[i].label1[0]);
					}
					else if (Siyuan_list[i].label1[0] == '+' || Siyuan_list[i].label1[0] == '-' ||
						(Siyuan_list[i].label1[0] >= '0' && Siyuan_list[i].label1[0] <= '9')) {
						fprintf(Output, "li $s6,%s\n", Siyuan_list[i].label1);
					}
					else if (Siyuan_list[i].label1[0] == '@') {
						fprintf(Output, "move $s6,$s%c\n", Siyuan_list[i].label1[1]);
					}
					else if (Siyuan_list[i].label1[0] == '$') {
						fprintf(Output, "move $s6,%s\n", Siyuan_list[i].label1);
					}
					else {
						if (check_address(Siyuan_list[i].label1) < 0) {
							fprintf(Output, "lw $s6,%d($sp)\n", (check_address(Siyuan_list[i].label1) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s6,%d($s5)\n", check_address(Siyuan_list[i].label1));
						}
					}
					if (get_const(Siyuan_list[i].label2) == 1 && Siyuan_list[i].label2[0] != '@') {
						fprintf(Output, "li $s7,'%c'\n", Siyuan_list[i].label2[0]);
					}
					else if (Siyuan_list[i].label2[0] == '+' || Siyuan_list[i].label2[0] == '-' ||
						(Siyuan_list[i].label2[0] >= '0' && Siyuan_list[i].label2[0] <= '9')) {
						fprintf(Output, "li $s7,%s\n", Siyuan_list[i].label2);
					}
					else if (Siyuan_list[i].label2[0] == '@') {
						fprintf(Output, "move $s7,$s%c\n", Siyuan_list[i].label2[1]);
					}
					else if (Siyuan_list[i].label2[0] == '$') {
						fprintf(Output, "move $s7,%s\n", Siyuan_list[i].label2);
					}
					else {
						if (check_address(Siyuan_list[i].label2) < 0) {
							fprintf(Output, "lw $s7,%d($sp)\n", (check_address(Siyuan_list[i].label2) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s7,%d($s5)\n", check_address(Siyuan_list[i].label2));
						}
					}
					fprintf(Output, "BLE $s6,$s7,%s\n", Siyuan_list[i].result);
				}
				//GRE>
				if (strcmp(Siyuan_list[i].op, "LEQ") == 0) {
					if (get_const(Siyuan_list[i].label1) == 1 && Siyuan_list[i].label1[0] != '@') {
						fprintf(Output, "li $s6,'%c'\n", Siyuan_list[i].label1[0]);
					}
					else if (Siyuan_list[i].label1[0] == '+' || Siyuan_list[i].label1[0] == '-' ||
						(Siyuan_list[i].label1[0] >= '0' && Siyuan_list[i].label1[0] <= '9')) {
						fprintf(Output, "li $s6,%s\n", Siyuan_list[i].label1);
					}
					else if (Siyuan_list[i].label1[0] == '@') {
						fprintf(Output, "move $s6,$s%c\n", Siyuan_list[i].label1[1]);
					}
					else if (Siyuan_list[i].label1[0] == '$') {
						fprintf(Output, "move $s6,%s\n", Siyuan_list[i].label1);
					}
					else {
						if (check_address(Siyuan_list[i].label1) < 0) {
							fprintf(Output, "lw $s6,%d($sp)\n", (check_address(Siyuan_list[i].label1) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s6,%d($s5)\n", check_address(Siyuan_list[i].label1));
						}
					}
					if (get_const(Siyuan_list[i].label2) == 1 && Siyuan_list[i].label2[0] != '@') {
						fprintf(Output, "li $s7,'%c'\n", Siyuan_list[i].label2[0]);
					}
					else if (Siyuan_list[i].label2[0] == '+' || Siyuan_list[i].label2[0] == '-' ||
						(Siyuan_list[i].label2[0] >= '0' && Siyuan_list[i].label2[0] <= '9')) {
						fprintf(Output, "li $s7,%s\n", Siyuan_list[i].label2);
					}
					else if (Siyuan_list[i].label2[0] == '@') {
						fprintf(Output, "move $s7,$s%c\n", Siyuan_list[i].label2[1]);
					}
					else if (Siyuan_list[i].label2[0] == '$') {
						fprintf(Output, "move $s7,%s\n", Siyuan_list[i].label2);
					}
					else {
						if (check_address(Siyuan_list[i].label2) < 0) {
							fprintf(Output, "lw $s7,%d($sp)\n", (check_address(Siyuan_list[i].label2) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s7,%d($s5)\n", check_address(Siyuan_list[i].label2));
						}
					}
					fprintf(Output, "BGT $s6,$s7,%s\n", Siyuan_list[i].result);
				}
				//LEQ<=
				if (strcmp(Siyuan_list[i].op, "LSS") == 0) {
					if (get_const(Siyuan_list[i].label1) == 1 && Siyuan_list[i].label1[0] != '@') {
						fprintf(Output, "li $s6,'%c'\n", Siyuan_list[i].label1[0]);
					}
					else if (Siyuan_list[i].label1[0] == '+' || Siyuan_list[i].label1[0] == '-' ||
						(Siyuan_list[i].label1[0] >= '0' && Siyuan_list[i].label1[0] <= '9')) {
						fprintf(Output, "li $s6,%s\n", Siyuan_list[i].label1);
					}
					else if (Siyuan_list[i].label1[0] == '@') {
						fprintf(Output, "move $s6,$s%c\n", Siyuan_list[i].label1[1]);
					}
					else if (Siyuan_list[i].label1[0] == '$') {
						fprintf(Output, "move $s6,%s\n", Siyuan_list[i].label1);
					}
					else {
						if (check_address(Siyuan_list[i].label1) < 0) {
							fprintf(Output, "lw $s6,%d($sp)\n", (check_address(Siyuan_list[i].label1) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s6,%d($s5)\n", check_address(Siyuan_list[i].label1));
						}
					}
					if (get_const(Siyuan_list[i].label2) == 1 && Siyuan_list[i].label2[0] != '@') {
						fprintf(Output, "li $s7,'%c'\n", Siyuan_list[i].label2[0]);
					}
					else if (Siyuan_list[i].label2[0] == '+' || Siyuan_list[i].label2[0] == '-' ||
						(Siyuan_list[i].label2[0] >= '0' && Siyuan_list[i].label2[0] <= '9')) {
						fprintf(Output, "li $s7,%s\n", Siyuan_list[i].label2);
					}
					else if (Siyuan_list[i].label2[0] == '@') {
						fprintf(Output, "move $s7,$s%c\n", Siyuan_list[i].label2[1]);
					}
					else if (Siyuan_list[i].label2[0] == '$') {
						fprintf(Output, "move $s7,%s\n", Siyuan_list[i].label2);
					}
					else {
						if (check_address(Siyuan_list[i].label2) < 0) {
							fprintf(Output, "lw $s7,%d($sp)\n", (check_address(Siyuan_list[i].label2) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s7,%d($s5)\n", check_address(Siyuan_list[i].label2));
						}
					}
					fprintf(Output, "BGE $s6,$s7,%s\n", Siyuan_list[i].result);
				}
				//LSS<
				if (strcmp(Siyuan_list[i].op, "EQL") == 0) {
					if (get_const(Siyuan_list[i].label1) == 1 && Siyuan_list[i].label1[0] != '@') {
						fprintf(Output, "li $s6,'%c'\n", Siyuan_list[i].label1[0]);
					}
					else if (Siyuan_list[i].label1[0] == '+' || Siyuan_list[i].label1[0] == '-' ||
						(Siyuan_list[i].label1[0] >= '0' && Siyuan_list[i].label1[0] <= '9')) {
						fprintf(Output, "li $s6,%s\n", Siyuan_list[i].label1);
					}
					else if (Siyuan_list[i].label1[0] == '@') {
						fprintf(Output, "move $s6,$s%c\n", Siyuan_list[i].label1[1]);
					}
					else if (Siyuan_list[i].label1[0] == '$') {
						fprintf(Output, "move $s6,%s\n", Siyuan_list[i].label1);
					}
					else {
						if (check_address(Siyuan_list[i].label1) < 0) {
							fprintf(Output, "lw $s6,%d($sp)\n", (check_address(Siyuan_list[i].label1) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s6,%d($s5)\n", check_address(Siyuan_list[i].label1));
						}
					}
					if (get_const(Siyuan_list[i].label2) == 1 && Siyuan_list[i].label2[0] != '@') {
						fprintf(Output, "li $s7,'%c'\n", Siyuan_list[i].label2[0]);
					}
					else if (Siyuan_list[i].label2[0] == '+' || Siyuan_list[i].label2[0] == '-' ||
						(Siyuan_list[i].label2[0] >= '0' && Siyuan_list[i].label2[0] <= '9')) {
						fprintf(Output, "li $s7,%s\n", Siyuan_list[i].label2);
					}
					else if (Siyuan_list[i].label2[0] == '@') {
						fprintf(Output, "move $s7,$s%c\n", Siyuan_list[i].label2[1]);
					}
					else if (Siyuan_list[i].label2[0] == '$') {
						fprintf(Output, "move $s7,%s\n", Siyuan_list[i].label2);
					}
					else {
						if (check_address(Siyuan_list[i].label2) < 0) {
							fprintf(Output, "lw $s7,%d($sp)\n", (check_address(Siyuan_list[i].label2) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s7,%d($s5)\n", check_address(Siyuan_list[i].label2));
						}
					}
					fprintf(Output, "BNE $s6,$s7,%s\n", Siyuan_list[i].result);
				}
				//EQL==
				if (strcmp(Siyuan_list[i].op, "NEQ") == 0) {
					if (get_const(Siyuan_list[i].label1) == 1 && Siyuan_list[i].label1[0] != '@') {
						fprintf(Output, "li $s6,'%c'\n", Siyuan_list[i].label1[0]);
					}
					else if (Siyuan_list[i].label1[0] == '+' || Siyuan_list[i].label1[0] == '-' ||
						(Siyuan_list[i].label1[0] >= '0' && Siyuan_list[i].label1[0] <= '9')) {
						fprintf(Output, "li $s6,%s\n", Siyuan_list[i].label1);
					}
					else if (Siyuan_list[i].label1[0] == '@') {
						fprintf(Output, "move $s6,$s%c\n", Siyuan_list[i].label1[1]);
					}
					else if (Siyuan_list[i].label1[0] == '$') {
						fprintf(Output, "move $s6,%s\n", Siyuan_list[i].label1);
					}
					else {
						if (check_address(Siyuan_list[i].label1) < 0) {
							fprintf(Output, "lw $s6,%d($sp)\n", (check_address(Siyuan_list[i].label1) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s6,%d($s5)\n", check_address(Siyuan_list[i].label1));
						}
					}
					if (get_const(Siyuan_list[i].label2) == 1 && Siyuan_list[i].label2[0] != '@') {
						fprintf(Output, "li $s7,'%c'\n", Siyuan_list[i].label2[0]);
					}
					else if (Siyuan_list[i].label2[0] == '+' || Siyuan_list[i].label2[0] == '-' ||
						(Siyuan_list[i].label2[0] >= '0' && Siyuan_list[i].label2[0] <= '9')) {
						fprintf(Output, "li $s7,%s\n", Siyuan_list[i].label2);
					}
					else if (Siyuan_list[i].label2[0] == '@') {
						fprintf(Output, "move $s7,$s%c\n", Siyuan_list[i].label2[1]);
					}
					else if (Siyuan_list[i].label2[0] == '$') {
						fprintf(Output, "move $s7,%s\n", Siyuan_list[i].label2);
					}
					else {
						if (check_address(Siyuan_list[i].label2) < 0) {
							fprintf(Output, "lw $s7,%d($sp)\n", (check_address(Siyuan_list[i].label2) + 1) * 4);
						}
						else {
							fprintf(Output, "la $s5,temp_space\n");
							fprintf(Output, "lw $s7,%d($s5)\n", check_address(Siyuan_list[i].label2));
						}
					}
					fprintf(Output, "BEQ $s6,$s7,%s\n", Siyuan_list[i].result);
				}
				//NEQ!=
			}
			//其他是不满足条件便跳转
		}
		//条件跳转

	}
	fprintf(Output, "li $v0,10\n");
	fprintf(Output, "syscall\n");
	fclose(Output);
}
//输出Mips指令信息
int check_address(char str[]) {
	int i;
	for (i = 0; i < Mips_list[Mips_add].para_num; i++) {
		if (strcmp(str, Mips_list[Mips_add].para_name[i]) == 0) {
			return (i + 1) * (-1);
		}
	}
	for (i = 0; i < Mips_list[Mips_add].var_num; i++) {
		if (strcmp(str, Mips_list[Mips_add].var_name[i]) == 0) {
			return Mips_list[Mips_add].var_add[i] + Mips_list[Mips_add].start_add;
		}
	}
	if (strcmp(Mips_list[0].fun_name, "const") == 0) {
		for (i = 0; i < Mips_list[0].var_num; i++) {
			if (strcmp(str, Mips_list[0].var_name[i]) == 0) {
				return Mips_list[0].var_add[i];
			}
		}
	}
	return 0;
}
//查看变量地址
char* check_value(char str[]) {
	int i;
	char temp[2] = "!";
	for (i = 0; i < Local_num; i++) {
		if (strcmp(str, Local.word[i]) == 0) {
			return (Local.value[i]);
		}
	}
	for (i = 0; i < All_num; i++) {
		if (strcmp(str, All.word[i]) == 0) {
			return (All.value[i]);
		}
	}
	return (temp);
}
//查看变量值
void error_out() {
	FILE* Output;
	int i = 0, j = 0;
	Output = fopen("error.txt", "w");
	int line_temp;
	char word_temp;
	for (i = 0; i <= error_num; i++) {
		for (j = i + 1; j <= error_num; j++) {
			if (error_line[i] > error_line[j]) {
				line_temp = error_line[j];
				error_line[j] = error_line[i];
				error_line[i] = line_temp;
				word_temp = error_word[j];
				error_word[j] = error_word[i];
				error_word[i] = word_temp;
			}
		}
	}
	//上边为将错误信息排序
	for (i = 0; i <= error_num; i++) {
		fprintf(Output, "%d %c\n", error_line[i], error_word[i]);
		for (j = i + 1; j <= error_num; j++) {
			if (error_line[i] != error_line[j]) {
				i = j - 1;
				break;
			}
		}
		if (j == error_num + 1) break;
	}
	fclose(Output);
}
//输出错误信息到error.txt
int check_const(char str[]) {
	int i;
	for (i = 0; i < All_num; i++) {
		if (strcmp(All.word[i], str) == 0) {
			if (All.flag[i] == 1) {
				return 1;
			}
			return 0;
		}
	}
	for (i = 0; i < Local_num; i++) {
		if (strcmp(Local.word[i], str) == 0) {
			if (Local.flag[i] == 1) {
				return 1;
			}
			return 0;
		}
	}
	return 1;
}
//查看是否为常量
int check_biaoda() {
	int i;
	if (strcmp(Type[biaoda_l], "CHARCON") == 0 && biaoda_l + 1 == biaoda_r) {
		return 1;
	}
	else if (strcmp(Type[biaoda_l], "IDENFR") == 0 && strcmp(Str[biaoda_l + 1], "(") != 0) {
		for (i = 0; i < All_num; i++) {
			if (strcmp(Str[biaoda_l], All.word[i]) == 0) {
				if (strcmp(All.type[i], "char") == 0) {
					if (biaoda_l + 1 == biaoda_r) {
						return 1;
					}
					if (strcmp(Str[biaoda_l + 1], "[") == 0 && strcmp(Str[biaoda_r - 1], "]") == 0) {
						return 1;
					}
				}//找到char类型的标识符
				return 0;
			}
		}//查全局变量表
		for (i = 0; i < Local_num; i++) {
			if (strcmp(Str[biaoda_l], Local.word[i]) == 0) {
				if (strcmp(Local.type[i], "char") == 0) {
					if (biaoda_l + 1 == biaoda_r) {
						return 1;
					}
					if (strcmp(Str[biaoda_l + 1], "[") == 0 && strcmp(Str[biaoda_r - 1], "]") == 0) {
						return 1;
					}
				}//找到char类型的标识符
				return 0;
			}
		}//查局部变量表
	}
	else if (strcmp(Type[biaoda_l], "IDENFR") == 0 && strcmp(Str[biaoda_l + 1], "(") == 0) {
		for (i = 0; i < Hanshu_num; i++) {
			if (strcmp(Hanshu_list[i].name, Str[biaoda_l]) == 0) {
				if (strcmp(Hanshu_list[i].type, "char") == 0) {
					if (strcmp(Str[biaoda_l + 1], "(") == 0 && strcmp(Str[biaoda_r - 1], ")") == 0) {
						return 2;
					}
				}//找到char类型的函数
				return 0;
			}
		}
	}
	return 0;
}
//查看表达式类型
int check_can_type(char str[], int a, int b) {
	int i;
	char hanshu[100];
	strcpy(hanshu, str);
	if (b == 0) {
		for (i = 0; i < Hanshu_num; i++) {
			if (strcmp(Hanshu_list[i].name, hanshu) == 0) {
				if (strcmp(Hanshu_list[i].can_type[a], "char") == 0) {
					return 1;
				}
				else {
					return 0;
				}
			}
		}
	}//输入为int
	if (b == 1) {
		for (i = 0; i < Hanshu_num; i++) {
			if (strcmp(Hanshu_list[i].name, hanshu) == 0) {
				if (strcmp(Hanshu_list[i].can_type[a], "int") == 0) {
					return 1;
				}
				else {
					return 0;
				}
			}
		}
	}//输入为char
	return 0;
}
//查看函数参数类型是否正确
char* check_type(char str[], char str1[]) {
	int i;
	if (strcmp(str1, "Local") == 0) {
		for (i = 0; i < Local_num; i++) {
			if (strcmp(Local.word[i], str) == 0) {
				return Local.type[i];
			}
		}
	}
	if (strcmp(str1, "All") == 0) {
		for (i = 0; i < All_num; i++) {
			if (strcmp(All.word[i], str) == 0) {
				return All.type[i];
			}
		}
	}
	if (strcmp(str1, "Hanshu") == 0) {
		for (i = 0; i < Hanshu_num; i++) {
			if (strcmp(str, Hanshu_list[i].name) == 0) {
				return Hanshu_list[i].type;
			}
		}
	}
	return null;
}
//查看str类型
void check_have_han(char str[]) {
	int i, flag = 0;
	for (i = 0; i < Hanshu_num; i++) {
		if (strcmp(Hanshu_list[i].name, str) == 0) {
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		error('c', Line[NOW]);
	}
}
//查看是否未定义函数
void check_have_can(char str[]) {
	int i, flag = 0;
	for (i = 0; i < Local_num; i++) {
		if (strcmp(Local.word[i], str) == 0) {
			flag = 1;
			break;
		}
	}
	for (i = 0; i < All_num; i++) {
		if (strcmp(All.word[i], str) == 0) {
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		error('c', Line[NOW]);
	}
}
//查看是否未定义参数
void check_same_han(char str[]) {
	int i;
	for (i = 0; i < Hanshu_num; i++) {
		if (strcmp(Hanshu_list[i].name, str) == 0) {
			error('b', Line[NOW]);
			break;
		}
	}
}
//查函数是否重定义
void check_same_can(char str[]) {
	int i, flag = 0;
	for (i = 0; i < Local_num; i++) {
		if (strcmp(Local.word[i], str) == 0) {
			error('b', Line[NOW]);
			flag = 1;
			break;
		}
	}
	if (flag != 1) {
		for (i = 0; i < All_num; i++) {
			if (strcmp(All.word[i], str) == 0) {
				error('b', Line[NOW]);
				flag = 1;
				break;
			}
		}
	}
	if (flag != 1 && Hanshu_list[Hanshu_num].can_amount != 0) {
		for (i = 0; i < Hanshu_list[Hanshu_num].can_amount; i++) {
			if (strcmp(Hanshu_list[Hanshu_num].can_name[i], str) == 0) {
				error('b', Line[NOW]);
				flag = 1;
				break;
			}
		}
	}
}
//查参数是否重定义
void clear() {
	char temp[2] = "\0";
	for (int i = 0; i < 100; i++) {
		Local.flag[i] = 0;
		strcpy(Local.type[i], temp);
		strcpy(Local.word[i], temp);
		strcpy(Local.value[i], temp);
	}
	Local_num = 0;
}
//清空局部参数表
void Save_have(char str[]) {
	int i, len;
	len = strlen(str);
	for (i = 0; i < len; i++) {
		HaveReturnList[have_dir][i] = str[i];
	}
	have_dir++;
}
//存入有返回值函数表
void Save_no(char str[]) {
	int i, len;
	len = strlen(str);
	for (i = 0; i < len; i++) {
		NoReturnList[no_dir][i] = str[i];
	}
	no_dir++;
}
//存入无返回值函数表
void Save(char str1[], char str2[]) {
	Save_dir++;
	int len, i;
	len = strlen(str1);
	for (i = 0; i < len; i++) {
		Save_Type[Save_dir][i] = str1[i];
	}
	len = strlen(str2);
	for (i = 0; i < len; i++) {
		Save_Str[Save_dir][i] = str2[i];
	}
}
//存入输出列表
int which_words(int flag, char* words) {
	char temp[1000] = "\0";
	int i = 0, flag_num = 1;
	FILE* Input;
	FILE* Middle;
	Input = fopen("testfile.txt", "r");
	Middle = fopen("middle.txt", "a");
	while (*(words + i) != '\0') {
		temp[i] = *(words + i);
		if (temp[i]<'0' || temp[i]>'9') {
			flag_num = 0;
		}
		i++;
	}
	temp[i] = '\0';
	char CONSTTK_const[6] = "const";
	char INTTK_int[4] = "int";
	char CHARTK_char[5] = "char";
	char VOIDTK_void[5] = "void";
	char MAINTK_main[5] = "main";
	char IFTK_if[3] = "if";
	char ELSETK_else[5] = "else";
	char DOTK_do[3] = "do";
	char WHILETK_while[6] = "while";
	char FORTK_for[4] = "for";
	char SCANFTK_scanf[6] = "scanf";
	char PRINTFTK_printf[7] = "printf";
	char RETURNTK_return[7] = "return";

	if (flag_num == 1) {
		fprintf(Middle, "INTCON %s %d\n", temp, line);
	}
	else {
		switch (strlen(temp)) {
		case 2:
			if (strcmp(temp, IFTK_if) == 0) {
				fprintf(Middle, "IFTK %s %d\n", temp, line);
				break;
			}
			if (strcmp(temp, DOTK_do) == 0) {
				fprintf(Middle, "DOTK %s %d\n", temp, line);
				break;
			}
		case 3:
			if (strcmp(temp, INTTK_int) == 0) {
				fprintf(Middle, "INTTK %s %d\n", temp, line);
				break;
			}
			if (strcmp(temp, FORTK_for) == 0) {
				fprintf(Middle, "FORTK %s %d\n", temp, line);
				break;
			}
		case 4:
			if (strcmp(temp, CHARTK_char) == 0) {
				fprintf(Middle, "CHARTK %s %d\n", temp, line);
				break;
			}
			if (strcmp(temp, VOIDTK_void) == 0) {
				fprintf(Middle, "VOIDTK %s %d\n", temp, line);
				break;
			}
			if (strcmp(temp, MAINTK_main) == 0) {
				fprintf(Middle, "MAINTK %s %d\n", temp, line);
				break;
			}
			if (strcmp(temp, ELSETK_else) == 0) {
				fprintf(Middle, "ELSETK %s %d\n", temp, line);
				break;
			}
		case 5:
			if (strcmp(temp, CONSTTK_const) == 0) {
				fprintf(Middle, "CONSTTK %s %d\n", temp, line);
				break;
			}
			if (strcmp(temp, WHILETK_while) == 0) {
				fprintf(Middle, "WHILETK %s %d\n", temp, line);
				break;
			}
			if (strcmp(temp, SCANFTK_scanf) == 0) {
				fprintf(Middle, "SCANFTK %s %d\n", temp, line);
				break;
			}
		case 6:
			if (strcmp(temp, PRINTFTK_printf) == 0) {
				fprintf(Middle, "PRINTFTK %s %d\n", temp, line);
				break;
			}
			if (strcmp(temp, RETURNTK_return) == 0) {
				fprintf(Middle, "RETURNTK %s %d\n", temp, line);
				break;
			}
		default:
			fprintf(Middle, "IDENFR %s %d\n", temp, line);
			break;
		}
	}
	fclose(Input);
	fclose(Middle);
	return 0;
}
//词法分析查看那个单词
void CiFa() {
	char words[1000] = "\0";
	char string[1000] = "\0";
	char ch;
	int i = 0, j = 0, len = 0, flag = 0, flag_str = 0;
	FILE* Input;
	FILE* Middle;
	Input = fopen("testfile.txt", "r");
	Middle = fopen("middle.txt", "w");
	fclose(Middle);
	while (1) {//读取字符
		Middle = fopen("middle.txt", "a");
		if ((ch = fgetc(Input)) == EOF) {
			break;
		}
	nextTime:
		flag_str = 0;
		if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == '_') {
			words[i] = ch;
			flag = 1;
			i++;
		}
		else {
			if (flag == 1) {
				flag = which_words(flag, words);
				len = strlen(words);
				for (j = 0; j < len; j++) {
					words[j] = '\000';
				}
				i = 0;
			}
			switch (ch) {
			case ' ':
				break;
			case '\t':
				break;
			case '\n':
				line++;
				break;
			case '\r':
				break;
			case '+':
				fprintf(Middle, "PLUS %c %d\n", ch, line);
				break;
			case '-':
				fprintf(Middle, "MINU %c %d\n", ch, line);
				break;
			case '*':
				fprintf(Middle, "MULT %c %d\n", ch, line);
				break;
			case '/':
				fprintf(Middle, "DIV %c %d\n", ch, line);
				break;
			case ';':
				fprintf(Middle, "SEMICN %c %d\n", ch, line);
				break;
			case ',':
				fprintf(Middle, "COMMA %c %d\n", ch, line);
				break;
			case '(':
				fprintf(Middle, "LPARENT %c %d\n", ch, line);
				break;
			case ')':
				fprintf(Middle, "RPARENT %c %d\n", ch, line);
				break;
			case '[':
				fprintf(Middle, "LBRACK %c %d\n", ch, line);
				break;
			case ']':
				fprintf(Middle, "RBRACK %c %d\n", ch, line);
				break;
			case '{':
				fprintf(Middle, "LBRACE %c %d\n", ch, line);
				break;
			case '}':
				fprintf(Middle, "RBRACE %c %d\n", ch, line);
				break;
			case '<':
				ch = fgetc(Input);
				if (ch == '=') fprintf(Middle, "LEQ <= %d\n", line);
				else {
					fprintf(Middle, "LSS < %d\n", line);
					goto nextTime;
				}
				break;
			case '>':
				ch = fgetc(Input);
				if (ch == '=') fprintf(Middle, "GEQ >= %d\n", line);
				else {
					fprintf(Middle, "GRE > %d\n", line);
					goto nextTime;
				}
				break;
			case '=':
				ch = fgetc(Input);
				if (ch == '=') fprintf(Middle, "EQL == %d\n", line);
				else {
					fprintf(Middle, "ASSIGN = %d\n", line);
					goto nextTime;
				}
				break;
			case '!':
				ch = fgetc(Input);
				if (ch == '=') fprintf(Middle, "NEQ != %d\n", line);
				else {
					error('a', line);
					goto nextTime;
				}
				break;
			case '\'':
				ch = fgetc(Input);
				fprintf(Middle, "CHARCON %c %d\n", ch, line);
				if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '_' || ch == '+' || ch == '-' || ch == '*' || ch == '/') {
					ch = fgetc(Input);
					if (ch == '\'') {
						//正确
					}
					else {
						error('a', line);
						goto nextTime;
					}
				}
				else {
					ch = fgetc(Input);
					error('a', line);
					if (ch != '\'') {
						goto nextTime;
					}
				}
				break;
			case '\"':
				j = 0;
				while ((ch = fgetc(Input)) != '\"') {
					if (ch == '\n') {
						flag_str = 1;
						break;
					}
					string[j] = ch;
					j++;
				}
				if (flag_str == 0) {
					fprintf(Middle, "STRCON %s %d\n", string, line);
					len = strlen(string);
					for (j = 0; j < len; j++) {
						string[j] = '\000';
					}
				}
				if (flag_str == 1) {
					len = strlen(string);
					for (j = len - 2; j < len; j++) {
						string[j] = '\000';
					}
					fprintf(Middle, "STRCON %s %d\n", string, line);
					for (j = 0; j < len - 2; j++) {
						string[j] = '\000';
					}
					//字符串只出现在printf语句中
					fprintf(Middle, "RPARENT ) %d\n", line);
					fprintf(Middle, "SEMICN ; %d\n", line);
					error('a', line);
					line++;
				}
				break;
			default:
				error('a', line);
				break;
			}
		}
		fclose(Middle);
	}
	fclose(Input);
	fclose(Middle);
}
//词法分析
void MakeList() {
	char temp[1000] = "\0";
	char ch;
	int len, i, j, k = 0, l = 0, num = 0;
	FILE* Input;
	Input = fopen("middle.txt", "r");
	while (1) {
		if ((ch = fgetc(Input)) == EOF) break;
		else {
			if (ch == ' ') {
				l = 0;
				len = strlen(temp);
				for (i = 0; i < len; i++) {
					Type[k][i] = temp[i];
				}
				for (j = 0; j < len; j++) {
					temp[j] = '\000';
				}
				while (1) {
					if ((ch = fgetc(Input)) == EOF) break;
					else {//会出现字符串的情况
						if (ch == '\n') {
							num = 0;
							len = strlen(temp);
							for (i = len - 1; i > 0; i--) {
								if (temp[i] == ' ') {
									for (j = i + 1; j < len; j++) {
										num = 10 * num + (int)(temp[j] - 48);//字符型转整型
									}
									Line[k] = num;
									for (j = 0; j < i; j++) {
										Str[k][j] = temp[j];
									}
									for (j = 0; j < len; j++) {
										temp[j] = '\000';
									}
									k++;
									l = 0;
									break;
								}
							}
							break;
						}
						else {
							temp[l] = ch;
							l++;
						}
					}
				}
			}
			else {
				temp[l] = ch;
				l++;
			}
		}
	}
	fclose(Input);
}
//构建表格
void getsym() {
	int len = strlen(sym), j;
	NOW++;
	for (j = 0; j < len; j++) {
		sym[j] = '\000';
	}
	len = strlen(Str[NOW]);
	for (j = 0; j < len; j++) {
		sym[j] = Str[NOW][j];
	}
}
//读取字符串
void regetsym() {
	int len = strlen(sym), j;
	NOW--;
	for (j = 0; j < len; j++) {
		sym[j] = '\000';
	}
	len = strlen(Str[NOW]);
	for (j = 0; j < len; j++) {
		sym[j] = Str[NOW][j];
	}
}
//回退字符串
void error(char wrong, int line) {
	error_num++;
//	if (wrong == 'o') *(int*) NULL = 1;
	if (line == 0) {
		error_line[error_num] = Line[NOW];
		error_word[error_num] = wrong;
	}
	else {
		error_line[error_num] = line;
		error_word[error_num] = wrong;
	}
}
//错误处理
void ZhengShu() {
	if (strcmp(Type[NOW], "PLUS") == 0 || strcmp(Type[NOW], "MINU") == 0) {
		getsym();
		if (sym[0] == '0') {
			error('a', Line[NOW]);
		}
		Save(Type[NOW], Str[NOW]);
		char a[500] = "<无符号整数>";
		Save(OUT, a);
		char b[500] = "<整数>";
		Save(OUT, b);
	}
	else {
		char a[500] = "<无符号整数>";
		Save(OUT, a);
		char b[500] = "<整数>";
		Save(OUT, b);
	}
}
//整数
void ChangLiangDefine(int z) {
	char type[5];
	if (z == 0) {
		if (strcmp(sym, "int") == 0) {
			strcpy(type, sym);
			//存表
			Save(Type[NOW], Str[NOW]);
			getsym();
			while (strcmp(Type[NOW], "IDENFR") == 0) {
				check_same_can(sym);
				//查看是否重定义
				strcpy(All.type[All_num], type);
				//存表
				Save(Type[NOW], Str[NOW]);
				//标识符
				All.address[All_num] = address;
				address = address + 4;
				strcpy(All.word[All_num], sym);
				//存表
				getsym();
				Save(Type[NOW], Str[NOW]);
				//=
				getsym();
				Save(Type[NOW], Str[NOW]);
				//整数
				if (strcmp(Type[NOW], "INTCON") != 0 && strcmp(Type[NOW], "MINU") != 0 && strcmp(Type[NOW], "PLUS") != 0) {
					error('o', Line[NOW - 1]);
				}
				ZhengShu();
				if (strcmp(Str[NOW - 1], "-") == 0) {
					strcat(Str[NOW - 1], sym);
					strcpy(sym, Str[NOW - 1]);
				}
				strcpy(All.value[All_num], sym);
				//存表
				All.flag[All_num] = 0;
				All_num++;
				getsym();
				if (strcmp(Type[NOW], "COMMA") != 0) {
					break;
				}
				Save(Type[NOW], Str[NOW]);
				//逗号
				getsym();
			}
			char a[500] = "<常量定义>";
			Save(OUT, a);
		}
		else if (strcmp(sym, "char") == 0) {
			strcpy(type, sym);
			Save(Type[NOW], Str[NOW]);
			getsym();
			while (strcmp(Type[NOW], "IDENFR") == 0) {
				check_same_can(sym);
				//参看是否重定义
				strcpy(All.type[All_num], type);
				//存表
				Save(Type[NOW], Str[NOW]);
				//标识符
				All.address[All_num] = address;
				address = address + 4;
				strcpy(All.word[All_num], sym);
				getsym();
				Save(Type[NOW], Str[NOW]);
				//=
				getsym();
				if (strcmp(Type[NOW], "CHARCON") != 0) {
					error('o', Line[NOW - 1]);
				}
				Save(Type[NOW], Str[NOW]);
				//字符
				strcpy(All.value[All_num], sym);
				All.flag[All_num] = 0;
				All_num++;
				getsym();
				if (strcmp(Type[NOW], "COMMA") != 0) {
					break;
				}
				Save(Type[NOW], Str[NOW]);
				//逗号
				getsym();
			}
			char a[500] = "<常量定义>";
			Save(OUT, a);
		}
		else {
			//error();
		}
	}
	else {
		if (strcmp(sym, "int") == 0) {
			strcpy(type, sym);
			Save(Type[NOW], Str[NOW]);
			getsym();
			while (strcmp(Type[NOW], "IDENFR") == 0) {
				check_same_can(sym);
				//参看是否重定义
				strcpy(Local.type[Local_num], type);
				//存表
				Local.address[Local_num] = address;
				address = address + 4;
				Save(Type[NOW], Str[NOW]);
				//标识符
				strcpy(Local.word[Local_num], sym);
				//存表
				getsym();
				Save(Type[NOW], Str[NOW]);
				//=
				getsym();
				Save(Type[NOW], Str[NOW]);
				//整数
				if (strcmp(Type[NOW], "INTCON") != 0 && strcmp(Type[NOW], "MINU") != 0 && strcmp(Type[NOW], "PLUS") != 0) {
					error('o', Line[NOW - 1]);
				}
				ZhengShu();
				if (strcmp(Str[NOW - 1], "-") == 0) {
					strcat(Str[NOW - 1], sym);
					strcpy(sym, Str[NOW - 1]);
				}
				strcpy(Local.value[Local_num], sym);
				//存表
				Local.flag[Local_num] = 0;
				Local_num++;
				getsym();
				if (strcmp(Type[NOW], "COMMA") != 0) {
					break;
				}
				Save(Type[NOW], Str[NOW]);
				//逗号
				getsym();
			}
			char a[500] = "<常量定义>";
			Save(OUT, a);
		}
		else if (strcmp(sym, "char") == 0) {
			strcpy(type, sym);
			Save(Type[NOW], Str[NOW]);
			strcpy(Local.type[Local_num], sym);
			//存表
			getsym();
			while (strcmp(Type[NOW], "IDENFR") == 0) {
				check_same_can(sym);
				//参看是否重定义
				strcpy(Local.type[Local_num], type);
				//存表
				Save(Type[NOW], Str[NOW]);
				//标识符
				Local.address[Local_num] = address;
				address = address + 4;
				strcpy(Local.word[Local_num], sym);
				//存表
				getsym();
				Save(Type[NOW], Str[NOW]);
				//=
				getsym();
				Save(Type[NOW], Str[NOW]);
				//字符
				if (strcmp(Type[NOW], "CHARCON") != 0) {
					error('o', Line[NOW - 1]);
				}
				strcpy(Local.value[Local_num], sym);
				//存表
				Local.flag[Local_num] = 0;
				Local_num++;
				getsym();
				if (strcmp(Type[NOW], "COMMA") != 0) {
					break;
				}
				Save(Type[NOW], Str[NOW]);
				//逗号
				getsym();
			}
			char a[500] = "<常量定义>";
			Save(OUT, a);
		}
		else {
			//error();
		}
	}
}
//常量定义
void ChangLiang(int z) {
	if (strcmp(sym, "const") == 0) {
		while (strcmp(sym, "const") == 0) {
			Save(Type[NOW], Str[NOW]);
			getsym();
			ChangLiangDefine(z);
			if (strcmp(Type[NOW], "SEMICN") == 0) {
				Save(Type[NOW], Str[NOW]);
				//；
				getsym();
			}
			else {
				error('k', Line[NOW - 1]);
			}
		}
		char a[50] = "<常量说明>";
		Save(OUT, a);
	}
}
//常量说明
void BianLiangDefine(int z) {
	char type[5];
	strcpy(type, Str[NOW - 1]);
	//char or int
	if (z == 0) {
		while (strcmp(Type[NOW], "IDENFR") == 0) {
			check_same_can(sym);
			//参看是否重定义
			strcpy(All.type[All_num], type);
			//存表
			Save(Type[NOW], Str[NOW]);
			//标识符
			strcpy(All.word[All_num], sym);
			//存表
			All.flag[All_num] = 1;
			getsym();
			if (strcmp(sym, ";") == 0) {
				strcpy(All.arr[All_num], "NULL");
				All.address[All_num] = address;
				address = address + 4;
				All_num++;
				break;
			}
			else if (strcmp(Type[NOW], "COMMA") == 0) {
				strcpy(All.arr[All_num], "NULL");
				All.address[All_num] = address;
				address = address + 4;
				All_num++;
				Save(Type[NOW], Str[NOW]);
				getsym();
				continue;
			}
			else if (strcmp(sym, "[") == 0) {
				Save(Type[NOW], Str[NOW]);
				getsym();
				Save(Type[NOW], Str[NOW]);
				strcpy(All.arr[All_num], sym);
				if (strcmp(Type[NOW], "INTCON") != 0) {
					error('i', Line[NOW]);
				}
				All.address[All_num] = address;
				address = address + 4 * atoi(sym);
				char a[50] = "<无符号整数>";
				Save(OUT, a);
				getsym();
				if (strcmp(sym, "]") == 0) {
					Save(Type[NOW], Str[NOW]);
					//sym==']'
					getsym();
				}
				else {
					error('m', Line[NOW]);
				}
				if (strcmp(sym, ",") == 0) {
					All_num++;
					Save(Type[NOW], Str[NOW]);
					getsym();
					continue;
				}
				if (strcmp(sym, ";") == 0) {
					All_num++;
					break;
				}
			}
		}
		char a[50] = "<变量定义>";
		Save(OUT, a);
	}
	else {
		while (strcmp(Type[NOW], "IDENFR") == 0) {
			check_same_can(sym);
			//参看是否重定义
			strcpy(Local.type[Local_num], type);
			//存表
			Save(Type[NOW], Str[NOW]);
			//标识符
			strcpy(Local.word[Local_num], sym);
			//存表
			Local.flag[Local_num] = 1;
			getsym();
			if (strcmp(sym, ";") == 0) {
				strcpy(Local.arr[Local_num], "NULL");
				Local.address[Local_num] = address;
				address = address + 4;
				Local_num++;
				break;
			}
			else if (strcmp(Type[NOW], "COMMA") == 0) {
				strcpy(Local.arr[Local_num], "NULL");
				Local.address[Local_num] = address;
				address = address + 4;
				Local_num++;
				Save(Type[NOW], Str[NOW]);
				getsym();
				continue;
			}
			else if (strcmp(sym, "[") == 0) {
				Save(Type[NOW], Str[NOW]);
				getsym();
				Save(Type[NOW], Str[NOW]);
				strcpy(Local.arr[Local_num], sym);
				if (strcmp(Type[NOW], "INTCON") != 0) {
					error('i', Line[NOW]);
				}
				Local.address[Local_num] = address;
				address = address + 4 * atoi(sym);
				char a[50] = "<无符号整数>";
				Save(OUT, a);
				getsym();
				if (strcmp(sym, "]") == 0) {
					Save(Type[NOW], Str[NOW]);
					//sym==']'
					getsym();
				}
				else {
					error('m', Line[NOW]);
				}
				if (strcmp(sym, ",") == 0) {
					Local_num++;
					Save(Type[NOW], Str[NOW]);
					getsym();
					continue;
				}
				if (strcmp(sym, ";") == 0) {
					Local_num++;
					break;
				}
			}
		}
		char a[50] = "<变量定义>";
		Save(OUT, a);
	}
}
//变量定义
void BianLiang(int z) {
	if (strcmp(sym, "int") == 0 || strcmp(sym, "char") == 0) {
		while (strcmp(sym, "int") == 0 || strcmp(sym, "char") == 0) {
			if (strcmp(Str[NOW + 2], "(") == 0) {
				break;
			}
			Save(Type[NOW], Str[NOW]);
			getsym();
			BianLiangDefine(z);
			if (strcmp(Type[NOW], "SEMICN") == 0) {
				Save(Type[NOW], Str[NOW]);
				//；
				getsym();
			}
			else {
				error('k', Line[NOW - 1]);
			}
		}
		char a[50] = "<变量说明>";
		Save(OUT, a);
	}
}
//变量说明
char* YinZi() {
	char temp[50];
	char temp1[50] = "";
	if (strcmp(Type[NOW], "IDENFR") == 0) {
		if (strcmp(Type[NOW + 1], "LPARENT") == 0) {
			strcpy(temp, sym);
			HaveReturnDiaoYong();
			char a[50] = "<因子>";
			Save(OUT, a);
			strcpy(temp, Siyuan_list[Siyuan_num - 1].label2);
			strcpy(temp1, "=");
			temp_make();
			save_siyuan(temp1, temp, null, temp_name);
			return (temp_name);
		}//(有返回值函数调用)
		else if (strcmp(Type[NOW + 1], "LBRACK") == 0) {
			check_have_can(sym);
			//查看是否参数未定义
			Save(Type[NOW], Str[NOW]);
			//标识符
			strcpy(temp1, sym);
			getsym();
			Save(Type[NOW], Str[NOW]);
			//"["
			getsym();
			strcpy(temp, BiaoDaShi());
			temp_make();
			save_siyuan(geta, temp_name, temp1, temp);
			if (temp[0] == '$') {
				have_used(temp);
			}
			if (check_biaoda() != 0) {
				error('i', Line[NOW]);
			}
			if (strcmp(Str[NOW], "]") == 0) {
				Save(Type[NOW], Str[NOW]);
				//"]"
			}
			else {
				error('m', Line[NOW]);
				regetsym();
			}
			char a[50] = "<因子>";
			Save(OUT, a);
			return (temp_name);
		}//标识符[表达式]
		else {
			check_have_can(sym);
			//查看是否参数未定义
			Save(Type[NOW], Str[NOW]);
			//标识符
			char a[50] = "<因子>";
			Save(OUT, a);
			return (sym);
		}
	}
	else if (strcmp(Type[NOW], "LPARENT") == 0) {
		Save(Type[NOW], Str[NOW]);
		//"("
		getsym();
		strcpy(temp, BiaoDaShi());
		if (strcmp(Str[NOW], ")") == 0) {
			Save(Type[NOW], Str[NOW]);
			//")"
		}
		else {
			error('l', Line[NOW]);
			regetsym();
		}
		char a[50] = "<因子>";
		Save(OUT, a);
		return (temp);
	}
	else if (strcmp(Type[NOW], "INTCON") == 0 || strcmp(Type[NOW], "PLUS") == 0 || strcmp(Type[NOW], "MINU") == 0) {
		Save(Type[NOW], Str[NOW]);
		ZhengShu();
		char a[50] = "<因子>";
		Save(OUT, a);
		if ((strcmp(Type[NOW - 1], "PLUS") == 0 || strcmp(Type[NOW - 1], "MINU") == 0) &&
			(strcmp(Type[NOW - 2], "PLUS") == 0 || strcmp(Type[NOW - 2], "MINU") == 0 ||
				strcmp(Type[NOW - 2], "MULT") == 0 || strcmp(Type[NOW - 2], "DIV") == 0)) {
			strcpy(temp, Str[NOW - 1]);
			return (strcat(temp, Str[NOW]));
		}
		else {
			return (sym);
		}
	}
	else if (strcmp(Type[NOW], "CHARCON") == 0) {
		Save(Type[NOW], Str[NOW]);
		char a[50] = "<因子>";
		Save(OUT, a);
		strcpy(temp, sym);
		strcat(temp, "@const");
		return (temp);
	}
}
//因子
char* Xiang() {
	char temp1[20] = "";
	char temp2[20] = "";
	char temp3[20] = "";
	strcpy(temp2, YinZi());
	getsym();
	if (strcmp(Type[NOW], "MULT") == 0 || strcmp(Type[NOW], "DIV") == 0) {
		Save(Type[NOW], Str[NOW]);
		//*||/
		strcpy(temp1, sym);
		while (1) {
			getsym();
			strcpy(temp3, YinZi());
			temp_make();
			save_siyuan(temp1, temp2, temp3, temp_name);
			if (temp2[0] == '$') {
				have_used(temp2);
			}
			if (temp3[0] == '$') {
				have_used(temp3);
			}
			//存四元式
			getsym();
			if (strcmp(Type[NOW], "MULT") != 0 && strcmp(Type[NOW], "DIV") != 0) {
				char a[50] = "<项>";
				Save(OUT, a);
				return (temp_name);
				break;
			}
			Save(Type[NOW], Str[NOW]);
			strcpy(temp1, sym);
			//+ or -
			strcpy(temp2, temp_name);
		}
	}
	else {
		char a[50] = "<项>";
		Save(OUT, a);
		return (temp2);
	}
}
//项
char* BiaoDaShi() {
	char temp1[20] = "";
	char temp2[20] = "";
	char temp3[20] = "";
	char temp4[20] = "";
	int start = NOW;
	if (strcmp(Type[NOW], "PLUS") == 0 || strcmp(Type[NOW], "MINU") == 0) {
		Save(Type[NOW], Str[NOW]);
		//+||-
		strcpy(temp1, sym);
		getsym();
		strcpy(temp2, Xiang());
		temp_make();
		save_siyuan(temp1, null, temp2, temp_name);
		if (temp2[0] == '$') {
			have_used(temp2);
		}
		strcpy(temp2, temp_name);
		if (strcmp(Type[NOW], "PLUS") == 0 || strcmp(Type[NOW], "MINU") == 0) {
			strcpy(temp1, sym);
			Save(Type[NOW], Str[NOW]);
			while (1) {
				getsym();
				strcpy(temp3, Xiang());
				temp_make();
				//生成寄存器名
				save_siyuan(temp1, temp2, temp3, temp_name);
				if (temp2[0] == '$') {
					have_used(temp2);
				}
				if (temp3[0] == '$') {
					have_used(temp3);
				}
				//存四元式
				if (strcmp(Type[NOW], "PLUS") != 0 && strcmp(Type[NOW], "MINU") != 0) {
					char a[50] = "<表达式>";
					Save(OUT, a);
					biaoda_l = start;
					biaoda_r = NOW;
					return (temp_name);
					break;
				}
				Save(Type[NOW], Str[NOW]);
				strcpy(temp1, sym);
				//+ or -
				strcpy(temp2, temp_name);
			}
		}
		else {
			char a[50] = "<表达式>";
			Save(OUT, a);
			biaoda_l = start;
			biaoda_r = NOW;
			return (temp2);
		}
	}
	else {
		strcpy(temp2, Xiang());
		if (strcmp(Type[NOW], "PLUS") == 0 || strcmp(Type[NOW], "MINU") == 0) {
			Save(Type[NOW], Str[NOW]);
			strcpy(temp1, sym);
			while (1) {
				getsym();
				strcpy(temp3, Xiang());
				temp_make();
				//生成寄存器名
				save_siyuan(temp1, temp2, temp3, temp_name);
				if (temp2[0] == '$') {
					have_used(temp2);
				}
				if (temp3[0] == '$') {
					have_used(temp3);
				}
				//存四元式
				if (strcmp(Type[NOW], "PLUS") != 0 && strcmp(Type[NOW], "MINU") != 0) {
					char a[50] = "<表达式>";
					Save(OUT, a);
					biaoda_l = start;
					biaoda_r = NOW;
					return (temp_name);
					break;
				}
				Save(Type[NOW], Str[NOW]);
				strcpy(temp1, sym);
				//+ or -
				strcpy(temp2, temp_name);
			}
		}
		else {
			char a[50] = "<表达式>";
			Save(OUT, a);
			biaoda_l = start;
			biaoda_r = NOW;
			return (temp2);
		}
	}
}
//表达式
void ZhiCanShuBiao() {
	int i = 0;//参数位置
	char hanshu[100];
	char temp[50];
	strcpy(hanshu, Str[NOW - 2]);
	if (strcmp(Type[NOW], "RPARENT") == 0) {
		char a[50] = "<值参数表>";
		Save(OUT, a);
	}
	else if (strcmp(Type[NOW], "SEMICN") != 0) {
		strcpy(temp, BiaoDaShi());
		save_siyuan(push, temp, null, null);
		if (temp[0] == '$') {
			have_used(temp);
		}
		if (check_biaoda() != 0) {
			if (check_can_type(hanshu, i, 1) == 1) {
				error('e', Line[NOW]);
			}
		}//表达式是char
		if (check_biaoda() == 0) {
			if (check_can_type(hanshu, i, 0) == 1) {
				error('e', Line[NOW]);
			}
		}//表达式是int
		if (strcmp(Type[NOW], "COMMA") == 0) {
			Save(Type[NOW], Str[NOW]);
			//","
			while (1) {
				i++;
				getsym();
				strcpy(temp, BiaoDaShi());
				save_siyuan(push, temp, null, null);
				if (temp[0] == '$') {
					have_used(temp);
				}
				if (check_biaoda() != 0) {
					if (check_can_type(hanshu, i, 1) == 1) {
						error('e', Line[NOW]);
					}
				}//表达式是char
				if (check_biaoda() == 0) {
					if (check_can_type(hanshu, i, 0) == 1) {
						error('e', Line[NOW]);
					}
				}//表达式是int
				if (strcmp(Type[NOW], "COMMA") != 0) {
					i++;
					char a[50] = "<值参数表>";
					Save(OUT, a);
					break;
				}
				Save(Type[NOW], Str[NOW]);
				//","
				for (int j = 0; j < strlen(temp); j++) {
					temp[j] = '\000';
				}
			}
		}
		else {
			i++;
			char a[50] = "<值参数表>";
			Save(OUT, a);
		}
	}
	for (int j = 0; j < Hanshu_num; j++) {
		if (strcmp(Hanshu_list[j].name, hanshu) == 0) {
			if (i != Hanshu_list[j].can_amount) {
				error('d', Line[NOW]);
			}
			break;
		}
	}//函数参数个数不匹配
}
//值参数表
void TiaoJian(char str[]) {
	int flag = 0;
	char temp1[20];
	char temp2[20];
	char temp0[20];
	strcpy(temp1, BiaoDaShi());
	if (check_biaoda() != 0) {
		flag++;
	}
	if (strcmp(Type[NOW], "LEQ") == 0 || strcmp(Type[NOW], "LSS") == 0 || strcmp(Type[NOW], "GEQ") == 0 || strcmp(Type[NOW], "GRE") == 0 || strcmp(Type[NOW], "EQL") == 0 || strcmp(Type[NOW], "NEQ") == 0) {
		Save(Type[NOW], Str[NOW]);
		strcpy(temp0, Type[NOW]);
		//temp0 = Type[NOW];
		getsym();
		strcpy(temp2, BiaoDaShi());
		if (strcmp(str, null) == 0) {
			save_siyuan(temp0, temp1, temp2, label_name);
			if (temp1[0] == '$') {
				have_used(temp1);
			}
			if (temp2[0] == '$') {
				have_used(temp2);
			}
		}
		else {
			save_siyuan(temp0, temp1, temp2, str);
			if (temp1[0] == '$') {
				have_used(temp1);
			}
			if (temp2[0] == '$') {
				have_used(temp2);
			}
		}
		for (int k = 0; k < strlen(temp0); k++) {
			temp0[k] = '\000';
		}
		if (check_biaoda() != 0) {
			flag++;
		}
		char a[50] = "<条件>";
		Save(OUT, a);
	}
	else if (strcmp(Str[NOW], ")") == 0) {
		save_siyuan(zero, temp1, null, label_name);
		if (temp1[0] == '$') {
			have_used(temp1);
		}
		char a[50] = "<条件>";
		Save(OUT, a);
	}
	else {
		save_siyuan(zero, temp1, null, label_name);
	}
	if (flag != 0) {
		error('f', Line[NOW]);
	}
}
//条件
void TiaoJianYuJu() {
	char label_temp1[20];
	char label_temp2[20];
	Save(Type[NOW], Str[NOW]);
	//if
	getsym();
	Save(Type[NOW], Str[NOW]);
	//"("
	getsym();
	label_make();
	save_siyuan(if_is, null, null, null);
	TiaoJian(null);
	strcpy(label_temp1, label_name);
	if (strcmp(Str[NOW], ")") == 0) {
		Save(Type[NOW], Str[NOW]);
		//")"
		getsym();
	}
	else {
		error('l', Line[NOW]);
	}

	YuJu();
	label_make();
	strcpy(label_temp2, label_name);
	save_siyuan(jump, label_temp2, null, null);
	save_siyuan(label, label_temp1, null, null);
	//条件语句跳转标签
	if (strcmp(Type[NOW], "ELSETK") == 0) {
		//label_make();
		//save_siyuan(jump, label_name, null, null);
		//strcpy(label_temp2, label_name);
		//save_siyuan(label, label_temp1, null, null);
		Save(Type[NOW], Str[NOW]);
		//else
		getsym();
		YuJu();
		//save_siyuan(label, label_temp2, null, null);
		char a[50] = "<条件语句>";
		Save(OUT, a);
	}
	else {
		//save_siyuan(label, label_temp1, null, null);
		char a[50] = "<条件语句>";
		Save(OUT, a);
	}
	save_siyuan(label, label_temp2, null, null);
}
//条件语句
void Head() {
	if (strcmp(Type[NOW], "IDENFR") == 0) {
		check_same_han(sym);
		//查看函数是否重定义
		strcpy(Hanshu_list[Hanshu_num].name, sym);
		//函数名存表
		Save(Type[NOW], Str[NOW]);
		char a[50] = "<声明头部>";
		Save(OUT, a);
	}
}
//声明头部
void CanShuBiao() {
	int i = 0;
	char type[100] = "\000";
	char char_tk[5] = "char";
	char int_tk[4] = "int";
	if (strcmp(Type[NOW], "CHARTK") == 0 || strcmp(Type[NOW], "INTTK") == 0) {
		if (strcmp(Type[NOW], "CHARTK") == 0) {
			strcpy(type, char_tk);
		}
		if (strcmp(Type[NOW], "INTTK") == 0) {
			strcpy(type, int_tk);
		}
		strcpy(Hanshu_list[Hanshu_num].can_type[i], type);
		//参数类型存表函数表
		strcpy(Local.type[Local_num], type);
		//参数类型存表参数表
		Save(Type[NOW], Str[NOW]);
		while (1) {
			getsym();
			check_same_can(sym);
			//查看参数是否重定义
			strcpy(Hanshu_list[Hanshu_num].can_name[i], sym);
			//参数名存表函数表
			strcpy(Local.word[Local_num], Str[NOW]);
			//参数名存表参数表
			Local.flag[Local_num] = 1;
			Save(Type[NOW], Str[NOW]);
			//标识符
			getsym();
			if (strcmp(Type[NOW], "COMMA") != 0) {
				Hanshu_list[Hanshu_num].can_amount++;
				//参数个数++
				Local_num++;
				//局部变量++
				char a[50] = "<参数表>";
				Save(OUT, a);
				break;
			}
			Save(Type[NOW], Str[NOW]);
			//逗号
			getsym();
			i++;
			Hanshu_list[Hanshu_num].can_amount++;
			//参数个数++
			Local_num++;
			//局部变量++
			if (strcmp(Type[NOW], "CHARTK") == 0) {
				strcpy(type, char_tk);
			}
			if (strcmp(Type[NOW], "INTTK") == 0) {
				strcpy(type, int_tk);
			}
			strcpy(Hanshu_list[Hanshu_num].can_type[i], type);
			//参数类型存表函数表
			strcpy(Local.type[Local_num], type);
			//参数类型存表参数表
			Save(Type[NOW], Str[NOW]);
			//类型标识符
		}
	}
	else if (strcmp(Type[NOW], "RPARENT") == 0) {
		char a[50] = "<参数表>";
		Save(OUT, a);
	}
}
//参数表
void HaveReturnDiaoYong() {
	char temp[100] = "\000";
	strcpy(temp, at0);
	check_have_han(sym);
	//查看是否函数未定义
	Save(Type[NOW], Str[NOW]);
	//标识符
	save_siyuan(call, sym, strcat(temp, sym), null);
	//存四元式
	getsym();
	Save(Type[NOW], Str[NOW]);
	//"("
	getsym();
	ZhiCanShuBiao();
	save_siyuan(back, null, temp, null);
	if (temp[1] == '0') {
		at0[1] = '1';
	}
	else if (temp[1] == '1') {
		at0[1] = '0';
	}
	for (int i = 0; i < strlen(temp); i++) {
		temp[i] = '\000';
	}
	if (strcmp(sym, ")") == 0) {
		Save(Type[NOW], Str[NOW]);
		//")"
	}
	else {
		error('l', Line[NOW]);
		regetsym();
	}
	char a[50] = "<有返回值函数调用语句>";
	Save(OUT, a);
}
//有返回值函数调用
void NoReturnDiaoYong() {
	check_have_han(sym);
	//查看是否函数未定义
	Save(Type[NOW], Str[NOW]);
	//标识符
	save_siyuan(call, sym, null, null);
	//存四元式
	getsym();
	Save(Type[NOW], Str[NOW]);
	//"("
	getsym();
	ZhiCanShuBiao();
	save_siyuan(back, null, null, null);
	if (strcmp(sym, ")") == 0) {
		Save(Type[NOW], Str[NOW]);
		//")"
	}
	else {
		error('l', Line[NOW]);
		regetsym();
	}
	char a[50] = "<无返回值函数调用语句>";
	Save(OUT, a);
}
//无返回值函数调用
void FuZhiYuJu() {
	char temp1[2] = "=";
	char temp2[20];
	char temp3[20];
	char temp4[20];
	check_have_can(sym);
	//查看是否参数未定义
	if (check_const(sym) == 0) {
		error('j', Line[NOW]);
	}//查看是否改变常量值
	Save(Type[NOW], Str[NOW]);
	//IDENFR
	strcpy(temp4, sym);
	getsym();
	if (strcmp(sym, "[") == 0) {
		Save(Type[NOW], Str[NOW]);
		//"["
		getsym();
		strcpy(temp3, BiaoDaShi());
		if (check_biaoda() != 0) {
			error('i', Line[NOW]);
		}
		if (strcmp(Str[NOW], "]") == 0) {
			Save(Type[NOW], Str[NOW]);
			//"]"
			getsym();
		}
		else {
			error('m', Line[NOW]);
		}
		Save(Type[NOW], Str[NOW]);
		//"="
		getsym();
		strcpy(temp2, BiaoDaShi());
		save_siyuan(shuzu, temp2, temp3, temp4);
		if (temp2[0] == '$') {
			have_used(temp2);
		}
		if (temp3[0] == '$') {
			have_used(temp3);
		}
		//[]= 赋的值 数组位置 数组名
		char a[50] = "<赋值语句>";
		Save(OUT, a);
	}
	else if (strcmp(sym, "=") == 0) {
		Save(Type[NOW], Str[NOW]);
		//"="
		getsym();
		strcpy(temp2, BiaoDaShi());
		//赋值语句要赋的值
		save_siyuan(temp1, temp2, null, temp4);
		if (temp2[0] == '$') {
			have_used(temp2);
		}
		char a[50] = "<赋值语句>";
		Save(OUT, a);
	}
	temp_num = 0;
}
//赋值语句
void XunHuanYuJu() {
	char label_temp1[20];
	char label_temp2[20];
	char yunsuan[2] = "\0";
	char temp0[2] = "=";
	char temp1[20];
	char temp2[20];
	char temp[20];
	if (strcmp(Type[NOW], "WHILETK") == 0) {
		label_make();
		strcpy(label_temp1, label_name);
		save_siyuan(label, label_temp1, null, null);
		Save(Type[NOW], Str[NOW]);
		//while
		getsym();
		Save(Type[NOW], Str[NOW]);
		//"("
		getsym();
		label_make();
		strcpy(label_temp2, label_name);
		save_siyuan(while_is, null, null, null);
		TiaoJian(null);
		if (strcmp(Str[NOW], ")") == 0) {
			Save(Type[NOW], Str[NOW]);
			//")"
			getsym();
		}
		else {
			error('l', Line[NOW]);
		}
		YuJu();
		save_siyuan(jump, label_temp1, null, null);
		save_siyuan(label, label_temp2, null, null);
		char a[50] = "<循环语句>";
		Save(OUT, a);
	}
	else if (strcmp(Type[NOW], "DOTK") == 0) {
		label_make();
		strcpy(label_temp1, label_name);
		save_siyuan(label, label_temp1, null, null);
		Save(Type[NOW], Str[NOW]);
		//do
		getsym();
		YuJu();
		if (strcmp(sym, "while") == 0) {
			Save(Type[NOW], Str[NOW]);
			//while
			getsym();
		}
		else {
			error('n', Line[NOW]);
		}
		Save(Type[NOW], Str[NOW]);
		//"("
		getsym();
		save_siyuan(do_is, null, null, null);
		TiaoJian(label_temp1);
		if (strcmp(Str[NOW], ")") == 0) {
			Save(Type[NOW], Str[NOW]);
			//")"
			getsym();
		}
		else {
			error('l', Line[NOW]);
		}
		char a[50] = "<循环语句>";
		Save(OUT, a);
	}
	else if (strcmp(Type[NOW], "FORTK") == 0) {
		label_make();
		strcpy(label_temp1, label_name);
		Save(Type[NOW], Str[NOW]);
		//"for"
		getsym();
		Save(Type[NOW], Str[NOW]);
		//"("
		getsym();
		strcpy(temp1, sym);//for中的第一次赋值
		check_have_can(sym);
		//查看是否参数未定义
		if (check_const(sym) == 0) {
			error('j', Line[NOW]);
		}//查看是否改变常量值
		Save(Type[NOW], Str[NOW]);
		//标识符
		getsym();
		Save(Type[NOW], Str[NOW]);
		//"="
		getsym();
		strcpy(temp, BiaoDaShi());
		save_siyuan(temp0, temp, null, temp1);
		if (temp[0] == '$') {
			have_used(temp);
		}
		save_siyuan(label, label_temp1, null, null);
		if (strcmp(Str[NOW], ";") == 0) {
			Save(Type[NOW], Str[NOW]);
			//";"
			getsym();
		}
		else {
			error('k', Line[NOW - 1]);
		}
		label_make();
		strcpy(label_temp2, label_name);
		save_siyuan(for_is, null, null, null);
		TiaoJian(label_temp2);
		if (strcmp(Str[NOW], ";") == 0) {
			Save(Type[NOW], Str[NOW]);
			//";"
			getsym();
		}
		else {
			error('k', Line[NOW - 1]);
		}
		check_have_can(sym);
		//查看是否参数未定义
		if (check_const(sym) == 0) {
			error('j', Line[NOW]);
		}//查看是否改变常量值
		Save(Type[NOW], Str[NOW]);
		//标识符
		strcpy(temp1, sym);//for中自加操作对象
		getsym();
		Save(Type[NOW], Str[NOW]);
		//"="
		getsym();
		check_have_can(sym);
		//查看是否参数未定义
		Save(Type[NOW], Str[NOW]);
		//标识符
		getsym();
		strcpy(yunsuan, sym);
		Save(Type[NOW], Str[NOW]);
		//+||-
		getsym();
		strcpy(temp2, sym);//步长
		Save(Type[NOW], Str[NOW]);
		//整数
		char c[50] = "<无符号整数>";
		Save(OUT, c);
		char a[50] = "<步长>";
		Save(OUT, a);
		getsym();
		if (strcmp(Str[NOW], ")") == 0) {
			Save(Type[NOW], Str[NOW]);
			//")"
			getsym();
		}
		else {
			error('l', Line[NOW]);
		}
		YuJu();
		temp_make();
		save_siyuan(yunsuan, temp1, temp2, temp_name);
		if (temp1[0] == '$') {
			have_used(temp1);
		}
		if (temp2[0] == '$') {
			have_used(temp2);
		}
		save_siyuan(temp0, temp_name, null, temp1);
		if (temp_name[0] == '$') {
			have_used(temp_name);
		}
		save_siyuan(jump, label_temp1, null, null);
		save_siyuan(label, label_temp2, null, null);
		char b[50] = "<循环语句>";
		Save(OUT, b);
	}
}
//循环语句
void ScanfYuJu() {
	char type[10];//标识符类型
	Save(Type[NOW], Str[NOW]);
	//scanf
	getsym();
	Save(Type[NOW], Str[NOW]);
	//"("
	getsym();
	check_have_can(sym);
	//查看是否参数未定义
	Save(Type[NOW], Str[NOW]);
	//标识符
	if (strcmp("NULL", check_type(sym, local)) == 0) {
		strcpy(type, check_type(sym, all));
	}
	else {
		strcpy(type, check_type(sym, local));
	}
	save_siyuan(scan, sym, type, null);
	//存四元式表
	getsym();
	if (strcmp(Type[NOW], "RPARENT") == 0) {
		Save(Type[NOW], Str[NOW]);
		//")"
		char a[50] = "<读语句>";
		Save(OUT, a);
	}
	else if (strcmp(Type[NOW], "COMMA") == 0) {
		Save(Type[NOW], Str[NOW]);
		//","
		while (1) {
			getsym();
			check_have_can(sym);
			//查看是否参数未定义
			Save(Type[NOW], Str[NOW]);
			//标识符
			if (strcmp("NULL", check_type(sym, local)) == 0) {
				strcpy(type, check_type(sym, all));
			}
			else {
				strcpy(type, check_type(sym, local));
			}
			save_siyuan(scan, sym, type, null);
			//存四元式表
			getsym();
			if (strcmp(Type[NOW], "RPARENT") == 0) {
				Save(Type[NOW], Str[NOW]);
				//")"
				char a[50] = "<读语句>";
				Save(OUT, a);
				break;
			}
			else if (strcmp(sym, ";") == 0) {
				error('l', Line[NOW]);
				regetsym();
				char a[50] = "<读语句>";
				Save(OUT, a);
				break;
			}
			Save(Type[NOW], Str[NOW]);
			//","
		}
	}
	else {
		error('l', Line[NOW]);
		regetsym();
	}
}
//读语句
void PrintfYuJu() {
	char temp[20];
	char temp_str[100];
	char type[5];
	Save(Type[NOW], Str[NOW]);
	//printf
	getsym();
	Save(Type[NOW], Str[NOW]);
	//"("
	getsym();
	if (strcmp(Type[NOW], "STRCON") == 0) {
		Save(Type[NOW], Str[NOW]);
		//字符串
		strcpy(temp_str, sym);
		char b[50] = "<字符串>";
		Save(OUT, b);
		getsym();
		if (strcmp(Type[NOW], "RPARENT") == 0) {
			Save(Type[NOW], Str[NOW]);
			//")"
			save_siyuan(print, str, temp_str, null);
			save_siyuan(print, nextline, null, null);
			char a[50] = "<写语句>";
			Save(OUT, a);
		}
		else if (strcmp(Type[NOW], "COMMA") == 0) {
			Save(Type[NOW], Str[NOW]);
			//","
			getsym();
			strcpy(temp, BiaoDaShi());
			if (check_biaoda() == 0) {
				strcpy(type, "int");
			}
			else {
				strcpy(type, "char");
			}
			save_siyuan(print, str, temp_str, null);
			save_siyuan(print, exp, type, temp);
			if (temp[0] == '$') {
				have_used(temp);
			}
			save_siyuan(print, nextline, null, null);
			//存四元式表
			if (strcmp(sym, ")") == 0) {
				Save(Type[NOW], Str[NOW]);
				//")"
			}
			else {
				error('l', Line[NOW]);
				regetsym();
			}
			char a[50] = "<写语句>";
			Save(OUT, a);
		}
		else if (strcmp(sym, ";") == 0) {
			error('l', Line[NOW]);
			regetsym();
			char a[50] = "<写语句>";
			Save(OUT, a);
		}
	}
	else {
		strcpy(temp, BiaoDaShi());
		if (check_biaoda() == 0) {
			strcpy(type, "int");
		}
		else {
			strcpy(type, "char");
		}
		save_siyuan(print, exp, type, temp);
		if (temp[0] == '$') {
			have_used(temp);
		}
		save_siyuan(print, nextline, null, null);
		//存四元式表
		if (strcmp(sym, ")") == 0) {
			Save(Type[NOW], Str[NOW]);
			//")"
		}
		else {
			error('l', Line[NOW]);
			regetsym();
		}
		char a[50] = "<写语句>";
		Save(OUT, a);
	}
	for (int k = 0; k < strlen(temp_str); k++) {
		temp_str[k] = '\000';
	}
}
//写语句
void ReturnYuJu() {
	char temp[100];
	char* reback;
	/*if (strcmp(Hanshu_list[Hanshu_num].type, "void") == 0) {
		error('g', Line[NOW]);
	}*/
	if (if_return == 0) {
		error('g', Line[NOW]);
	}
	Save(Type[NOW], Str[NOW]);
	//return
	getsym();
	if (strcmp(Type[NOW], "LPARENT") == 0) {
		Save(Type[NOW], Str[NOW]);
		getsym();
		strcpy(temp, Str[NOW]);
		reback = BiaoDaShi();
		save_siyuan(ret, reback, null, null);
		if (strcmp(Hanshu_list[Hanshu_num].type, "int") == 0) {
			if (check_biaoda() != 0) {
				error('h', Line[NOW]);
			}
		}
		if (strcmp(Hanshu_list[Hanshu_num].type, "char") == 0) {
			if (check_biaoda() == 0) {
				error('h', Line[NOW]);
			}
		}
		if (strcmp(sym, ")") == 0) {
			Save(Type[NOW], Str[NOW]);
			//")"
		}
		else {
			error('l', Line[NOW]);
			regetsym();
		}
		char a[50] = "<返回语句>";
		Save(OUT, a);
		getsym();
	}
	else {
		save_siyuan(ret, null, null, null);
		char a[50] = "<返回语句>";
		Save(OUT, a);
	}
}
//返回语句
int YuJu() {
	if (strcmp(sym, "if") == 0) {
		TiaoJianYuJu();
		char a[50] = "<语句>";
		Save(OUT, a);
		//getsym();
		return 1;
	}
	//条件语句
	else if (strcmp(sym, "while") == 0 || strcmp(sym, "do") == 0 || strcmp(sym, "for") == 0) {
		XunHuanYuJu();
		char a[50] = "<语句>";
		Save(OUT, a);
		return 1;
	}
	//循环语句
	else if (strcmp(sym, "{") == 0) {
		Save(Type[NOW], Str[NOW]);
		//"{"
		getsym();
		YuJuLie();
		Save(Type[NOW], Str[NOW]);
		//"}"
		getsym();
		char a[50] = "<语句>";
		Save(OUT, a);
		return 1;
	}
	//{语句列}
	else if (strcmp(Type[NOW], "IDENFR") == 0 && strcmp(Str[NOW + 1], "(") == 0) {
		int i = 0;
		for (i = 0; i < have_dir; i++) {
			if (strcmp(sym, HaveReturnList[i]) == 0) break;
		}
		if (i == have_dir) {
			NoReturnDiaoYong();
			getsym();
			if (strcmp(Str[NOW], ";") == 0) {
				Save(Type[NOW], Str[NOW]);
				//";"
				getsym();
			}
			else {
				error('k', Line[NOW - 1]);
			}
			char a[50] = "<语句>";
			Save(OUT, a);
			return 1;
		}
		else {
			HaveReturnDiaoYong();
			getsym();
			if (strcmp(Str[NOW], ";") == 0) {
				Save(Type[NOW], Str[NOW]);
				//";"
				getsym();
			}
			else {
				error('k', Line[NOW - 1]);
			}
			char a[50] = "<语句>";
			Save(OUT, a);
			return 1;
		}
	}
	//函数调用语句
	else if ((strcmp(Type[NOW], "IDENFR") == 0 && strcmp(Str[NOW + 1], "=") == 0) || (strcmp(Type[NOW], "IDENFR") == 0 && strcmp(Str[NOW + 1], "[") == 0)) {
		FuZhiYuJu();
		if (strcmp(Str[NOW], ";") == 0) {
			Save(Type[NOW], Str[NOW]);
			//";"
			getsym();
		}
		else {
			error('k', Line[NOW - 1]);
		}
		char a[50] = "<语句>";
		Save(OUT, a);
		return 1;
	}
	//赋值语句
	else if (strcmp(Str[NOW], "scanf") == 0) {
		ScanfYuJu();
		getsym();
		if (strcmp(Str[NOW], ";") == 0) {
			Save(Type[NOW], Str[NOW]);
			//";"
			getsym();
		}
		else {
			error('k', Line[NOW - 1]);
		}
		char a[50] = "<语句>";
		Save(OUT, a);
		return 1;
	}
	//读语句
	else if (strcmp(Str[NOW], "printf") == 0) {
		PrintfYuJu();
		getsym();
		if (strcmp(Str[NOW], ";") == 0) {
			Save(Type[NOW], Str[NOW]);
			//";"
			getsym();
		}
		else {
			error('k', Line[NOW - 1]);
		}
		char a[50] = "<语句>";
		Save(OUT, a);
		return 1;
	}
	//写语句
	else if (strcmp(Str[NOW], "return") == 0) {
		ReturnYuJu();
		if (strcmp(Str[NOW], ";") == 0) {
			Save(Type[NOW], Str[NOW]);
			//";"
			getsym();
		}
		else {
			error('k', Line[NOW - 1]);
		}
		char a[50] = "<语句>";
		Save(OUT, a);
		return 1;
	}
	//返回语句
	else if (strcmp(Str[NOW], ";") == 0) {
		Save(Type[NOW], Str[NOW]);
		getsym();
		char a[50] = "<语句>";
		Save(OUT, a);
		return 1;
	}
	//空语句
	else {
		return 0;
	}
}
//语句
void YuJuLie() {
	while (YuJu() == 1);
	char a[50] = "<语句列>";
	Save(OUT, a);
}
//语句列
void FuHeYuJu() {
	int i;
	ChangLiang(1);//常量说明
	BianLiang(1);//变量说明
	for (i = Hanshu_list[Hanshu_num].can_amount; i < Local_num; i++) {
		if (Local.flag[i] == 0)
			save_siyuan(con, Local.type[i], Local.word[i], Local.value[i]);
		else
			save_siyuan(var, Local.type[i], Local.word[i], Local.arr[i]);
	}//存四元式表
	YuJuLie();//语句列
	char a[50] = "<复合语句>";
	Save(OUT, a);
}
//复合语句
void HaveReturnDefine() {
	int i;
	if_return = 1;
	Save(Type[NOW], Str[NOW]);
	//int||char
	strcpy(Hanshu_list[Hanshu_num].type, sym);
	//函数类型存表
	getsym();
	Head();
	Save_have(sym);
	//有返回值函数名
	getsym();
	Save(Type[NOW], Str[NOW]);
	//"("
	getsym();
	CanShuBiao();
	if (strcmp(Str[NOW], ")") == 0) {
		Save(Type[NOW], Str[NOW]);
		//")"
		getsym();
	}
	else {
		error('l', Line[NOW]);
	}
	Save(Type[NOW], Str[NOW]);
	//"{"
	save_siyuan(func_def, Hanshu_list[Hanshu_num].type, Hanshu_list[Hanshu_num].name, null);
	for (i = 0; i < Hanshu_list[Hanshu_num].can_amount; i++) {
		save_siyuan(para, Hanshu_list[Hanshu_num].can_type[i], Hanshu_list[Hanshu_num].can_name[i], null);
	}//存四元式表
	getsym();
	FuHeYuJu();
	int flag = 0;
	for (int i = NOW; strcmp(Str[i], Hanshu_list[Hanshu_num].name) != 0; i--) {
		if (strcmp(Str[i], "return") == 0) {
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		error('h', Line[NOW]);
	}//查看是否函数无return

	//if(strcmp(Str[NOW-1],";")==0 && strcmp(Str[NOW - 2], "return") != 0)
	Save(Type[NOW], Str[NOW]);
	//"}"
	char a[50] = "<有返回值函数定义>";
	Save(OUT, a);
	if_return = -1;
	save_siyuan(func_end, Hanshu_list[Hanshu_num].type, Hanshu_list[Hanshu_num].name, null);
}
//有返回值函数定义
void NoReturnDefine() {
	int i;
	if_return = 0;
	Save(Type[NOW], Str[NOW]);
	//void
	strcpy(Hanshu_list[Hanshu_num].type, sym);
	//函数类型存表
	getsym();
	Save(Type[NOW], Str[NOW]);
	//函数名
	check_same_han(sym);
	//查看函数是否重定义
	strcpy(Hanshu_list[Hanshu_num].name, sym);
	//函数名存表
	getsym();
	Save(Type[NOW], Str[NOW]);
	//"("
	getsym();
	CanShuBiao();
	if (strcmp(Str[NOW], ")") == 0) {
		Save(Type[NOW], Str[NOW]);
		//")"
		getsym();
	}
	else {
		error('l', Line[NOW]);
	}
	Save(Type[NOW], Str[NOW]);
	//"{"
	save_siyuan(func_def, Hanshu_list[Hanshu_num].type, Hanshu_list[Hanshu_num].name, null);
	for (i = 0; i < Hanshu_list[Hanshu_num].can_amount; i++) {
		save_siyuan(para, Hanshu_list[Hanshu_num].can_type[i], Hanshu_list[Hanshu_num].can_name[i], null);
	}//存四元式表
	getsym();
	FuHeYuJu();
	Save(Type[NOW], Str[NOW]);
	//"}"
	char a[50] = "<无返回值函数定义>";
	Save(OUT, a);
	if_return = -1;
	save_siyuan(func_end, Hanshu_list[Hanshu_num].type, Hanshu_list[Hanshu_num].name, null);
}
//无返回值函数定义
void Main() {
	Save(Type[NOW], Str[NOW]);
	//void
	getsym();
	Save(Type[NOW], Str[NOW]);
	//main
	getsym();
	Save(Type[NOW], Str[NOW]);
	//"("
	getsym();
	if (strcmp(Str[NOW], ")") == 0) {
		Save(Type[NOW], Str[NOW]);
		//")"
		getsym();
	}
	else {
		error('l', Line[NOW]);
	}
	Save(Type[NOW], Str[NOW]);
	//"{"
	getsym();
	FuHeYuJu();
	Save(Type[NOW], Str[NOW]);
	//"}"
	char a[50] = "<主函数>";
	Save(OUT, a);
}
//主函数
void ChengXu() {
	int i;
	getsym();
	//判断常量说明
	if (strcmp(sym, "const") == 0) {
		ChangLiang(0);
	}
	//判断变量说明
	if (strcmp(sym, "int") == 0 || strcmp(sym, "char") == 0) {
		if (strcmp(Str[NOW + 2], "(") != 0) {
			BianLiang(0);
		}
	}
	//生成四元式
	for (i = 0; i < All_num; i++) {
		if (All.flag[i] == 0)
			save_siyuan(con, All.type[i], All.word[i], All.value[i]);
		else
			save_siyuan(var, All.type[i], All.word[i], All.arr[i]);
	}
	//判断函数说明
	while (1) {
		if (strcmp(sym, "void") == 0 && strcmp(Str[NOW + 1], "main") == 0) {
			save_siyuan(MAIN, null, null, null);
			Main();
			Hanshu_num++;
			break;
		}
		else if (strcmp(sym, "int") == 0 || strcmp(sym, "char") == 0) {
			HaveReturnDefine();
			clear();//清空局部参数表
			Hanshu_num++;
			getsym();
		}
		else if (strcmp(sym, "void") == 0 && strcmp(Str[NOW + 1], "main") != 0) {
			NoReturnDefine();
			clear();//清空局部参数表
			Hanshu_num++;
			getsym();
		}
		else {
			//error
			getsym();
			break;
		}
	}
	char a[50] = "<程序>";
	Save(OUT, a);
}
//程序
