#include <algorithm>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>
#include <cmath>
#include <windows.h>
using namespace std;
void xingxing();
void bankrate();
void random_month();
void redbag();
void redbag1();
void array_test();
int test(int a)
{
	static int n = a / 2;
	a&& test(a - 1);
	a < n ? cout << setw(n - a) << "*" << setw(2 * a + 2) << "*" << endl : a  > n + 1 ? cout << setw(a - n) << "*" << setw(2 * (2 * n - a + 1)) << "*" << endl : cout;
	return  n;
}

int main()
{
	//cout << "请输入半菱形高度n" << endl;
	//int n = 0;
	//cin >> n;
	//cout << setw(n) << "*" << endl;
	//test(2 * n - 2);
	//cout << setw(n) << "*" << endl;
	////system("pause");
	//return 0;
	//按键进行循环
	array_test();
	return 0;

	//四个数字中最大的数字
	/*int a[5], max;
	cout << "请输入四个数字：";
	cin >> a[1] >> a[2] >> a[3] >> a[4];
	max = a[a[a[1] > a[2] ? 1 : 2] > a[a[3] > a[4] ? 3 : 4] ? a[1] > a[2] ? 1 : 2 : a[3] > a[4] ? 3 : 4];
	cout << "最大值为：" << max << endl;
	return 0;*/
}

//n个月后的利率问题


void bankrate()
{
	double principal, rate, time, interest;
	cout << "Enter the principal amount: ";
	cin >> principal;
	cout << "Enter the annual interest rate: ";
	cin >> rate;
	cout << "Enter the number of monthes: ";
	cin >> time;
	while (time>0)
	{
		principal += principal * rate / 100;
		time--;
	}
	
	cout << "The interest earned is " << principal << endl;
	
}

//编写一个随机产生1和12之间的整数的程序，并且根据数字显示相应的月份单词

void random_month()
{
	int month;
	month = rand()%12+1;
	const char *month_name[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	cout << "This month is " << month_name[month-1] << endl;
}
void xingxing()
{
	/*cout << "请输入半菱形高度n" << endl;
	int n = 0, i = 1;
	cin >> n;
	cout << setw(n) << "*" << endl;
	for (; i < n; ++i)
		cout << setw(n - i) << "*" << setw(2 * i) << "*" << endl;
	i = i - 2;
	while (i > 0)
	{
		cout << setw(n - i) << "*" << setw(2 * i) << "*" << endl;
		i--;
	}*/
	/*[capture] (parameters) mutable ->return-type{ statement }*/
	//cout << setw(n) << "*" << "\t\t" << endl;
	//lambda表达式

	//auto testlambda = [](int a, int b) {return a *b; };
	//auto testlambda2 = [](int a, int b)->double{return (a + b) / 2.0; };
	//cout << testlambda(2, 3) << endl;
	//cout << testlambda2(2, 3) << endl;
	//int x = 10;
	//int y = 20;
	//auto printValues = [&x, &y]() { x+=10; y+=10; cout << "x=" << x << " y=" << y << endl; };
	//printValues();

	vector<int> numbers = { 1, 2, 3, 4, 5 };
	numbers.push_back(6);
	// 使用 lambda 表达式打印每个元素
	for_each(numbers.begin(), numbers.end(), [](int num) { cout << num << " "; });
	cout << endl; // 输出: 1 2 3 4 5
	cout << "数字为: " << numbers.begin()[0] << endl; // 输出: 5
	numbers.pop_back(); // 删除最后一个元素
	// 使用 lambda 表达式对向量进行排序
	sort(numbers.begin(), numbers.end(), [](int a, int b) { return a > b; });
	cout << "数字为: "<< numbers.begin()[0]<< endl; // 输出: 5
	// 打印排序后的向量
	for (int num : numbers) {
		cout << num << " ";
	}
	//找出tan(x)=1时x的值
	int x = 0;
	auto tanlam = [=]() { return tan(0.78539816); };
	cout << "角度为45的正切值为: "<<tanlam() << endl;
	cout << endl; // 输出: 5 4 3 2 1

}
void redbag1()
{
	int i, number;
	int best;//手气最佳
	float total;

	cout << "请输入红包金额：";
	cin >> total;
	cout << "请输入抢红包人数：";
	cin >> number;
	/* 生成随机数 */
	// 设置种子
	srand((unsigned)time(NULL));
	float a[1024];//保存每个人的随机数。最多支持1024个人抢红包。
	float b[1024];//保存每个人获得的红包金额。
	float suma = 0;//随机数总和。
	float sumb = 0;//红包总和。
	int max = 0;
	for (i = 0; i < number; i++)
	{
		// 生成实际的随机数
		a[i] = rand() % 100;

		if (a[i] > max) {
			max = a[i];
			best = i;//获取手气最佳
		}
		suma += a[i];
	}

	for (i = 0; i < number - 1; i++)
	{
		b[i] = a[i] / suma * total;//按照随机数计算每个人实际获得的金额
		sumb += round(b[i] * 100) / 100.0;//将红包金额保留两位小数
		//输出信息
		cout << "第" << setiosflags(ios::right) << setw(3) << i + 1 <<
			"个人的红包是:" << setiosflags(ios::right) << setw(6) <<
			setiosflags(ios::fixed) << setprecision(2) <<
			round(b[i] * 100) / 100.0;
		if (best == i) {
			cout << "(手气最佳)" << endl;
		}
		else {

			cout << endl;
		}
	}
	//最后一人的红包金额等于总金额减去前面的金额。
	cout << "第" << setiosflags(ios::right) <<
		setw(3) << number << "个人的红包是:" <<
		setiosflags(ios::right) << setw(6) << setiosflags(ios::fixed) <<
		setprecision(2) << round((total - sumb) * 100) / 100.0;
	if (best == number - 1) {
		cout << "(手气最佳)" << endl;
	}
	else {

		cout << endl;
	}
}
void redbag()
{
	int i, number, best;
	float total;
	std::cout << "请输入总额：" << std::endl;
	std::cin >> total;
	std::cout << "请输入个数：" << std::endl;
	std::cin >> number;

	// 配置种子
	/*std::srand(std::time(0));*/
	std::srand(42);
	// 根据实际需要动态分配数组
	float* rand_number = new float[number];
	float* person_money = new float[number];
	float sum_rand_number = 0;
	float sum_person_money = 0;
	int max = 0;

	for (i = 0; i < number; i++) {
		rand_number[i] = std::rand() % 100;

		if (rand_number[i] > max) {
			max = rand_number[i];
			best = i;
		}
		sum_rand_number += rand_number[i];
	}

	for (i = 0; i < number - 1; i++) {
		person_money[i] = rand_number[i] / sum_rand_number * total;
		person_money[i] = std::round(person_money[i] * 100) / 100.0; // 保留两位小数
		sum_person_money += person_money[i];

		std::cout << "第" << i + 1 << "个金额为：" << person_money[i] << std::endl;
	}
	person_money[i] = total - sum_person_money;
	std::cout << "第" << i + 1 << "个金额为：" << person_money[i] << std::endl;
	std::cout << "最佳运气为:" << person_money[best] << std::endl;

	// 释放动态分配的内存
	delete[] rand_number;
	delete[] person_money;

	// 是否循环
	std::cout << "是否继续？y/n" << std::endl;
	char c;
	std::cin.ignore(); // 清空输入缓冲区
	std::cin >> c;
	while (c == 'y' || c == 'Y') {
		redbag();
	}
}
void array_test()
{
	int arr[] = { 6,7,4,4,5 };
	int random_arr[5];
	for (int i = 0; i < 5; i++)
	{
		random_arr[i] = rand() % 100;
	}
	for (int i = 0; i < 5; i++)
	{
		std::cout << "第"<<i+1<<"个随机数为：" << setw(5) << random_arr[i] << std::endl;
	}
}