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
	//cout << "����������θ߶�n" << endl;
	//int n = 0;
	//cin >> n;
	//cout << setw(n) << "*" << endl;
	//test(2 * n - 2);
	//cout << setw(n) << "*" << endl;
	////system("pause");
	//return 0;
	//��������ѭ��
	array_test();
	return 0;

	//�ĸ���������������
	/*int a[5], max;
	cout << "�������ĸ����֣�";
	cin >> a[1] >> a[2] >> a[3] >> a[4];
	max = a[a[a[1] > a[2] ? 1 : 2] > a[a[3] > a[4] ? 3 : 4] ? a[1] > a[2] ? 1 : 2 : a[3] > a[4] ? 3 : 4];
	cout << "���ֵΪ��" << max << endl;
	return 0;*/
}

//n���º����������


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

//��дһ���������1��12֮��������ĳ��򣬲��Ҹ���������ʾ��Ӧ���·ݵ���

void random_month()
{
	int month;
	month = rand()%12+1;
	const char *month_name[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	cout << "This month is " << month_name[month-1] << endl;
}
void xingxing()
{
	/*cout << "����������θ߶�n" << endl;
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
	//lambda���ʽ

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
	// ʹ�� lambda ���ʽ��ӡÿ��Ԫ��
	for_each(numbers.begin(), numbers.end(), [](int num) { cout << num << " "; });
	cout << endl; // ���: 1 2 3 4 5
	cout << "����Ϊ: " << numbers.begin()[0] << endl; // ���: 5
	numbers.pop_back(); // ɾ�����һ��Ԫ��
	// ʹ�� lambda ���ʽ��������������
	sort(numbers.begin(), numbers.end(), [](int a, int b) { return a > b; });
	cout << "����Ϊ: "<< numbers.begin()[0]<< endl; // ���: 5
	// ��ӡ����������
	for (int num : numbers) {
		cout << num << " ";
	}
	//�ҳ�tan(x)=1ʱx��ֵ
	int x = 0;
	auto tanlam = [=]() { return tan(0.78539816); };
	cout << "�Ƕ�Ϊ45������ֵΪ: "<<tanlam() << endl;
	cout << endl; // ���: 5 4 3 2 1

}
void redbag1()
{
	int i, number;
	int best;//�������
	float total;

	cout << "����������";
	cin >> total;
	cout << "�����������������";
	cin >> number;
	/* ��������� */
	// ��������
	srand((unsigned)time(NULL));
	float a[1024];//����ÿ���˵�����������֧��1024�����������
	float b[1024];//����ÿ���˻�õĺ����
	float suma = 0;//������ܺ͡�
	float sumb = 0;//����ܺ͡�
	int max = 0;
	for (i = 0; i < number; i++)
	{
		// ����ʵ�ʵ������
		a[i] = rand() % 100;

		if (a[i] > max) {
			max = a[i];
			best = i;//��ȡ�������
		}
		suma += a[i];
	}

	for (i = 0; i < number - 1; i++)
	{
		b[i] = a[i] / suma * total;//�������������ÿ����ʵ�ʻ�õĽ��
		sumb += round(b[i] * 100) / 100.0;//�����������λС��
		//�����Ϣ
		cout << "��" << setiosflags(ios::right) << setw(3) << i + 1 <<
			"���˵ĺ����:" << setiosflags(ios::right) << setw(6) <<
			setiosflags(ios::fixed) << setprecision(2) <<
			round(b[i] * 100) / 100.0;
		if (best == i) {
			cout << "(�������)" << endl;
		}
		else {

			cout << endl;
		}
	}
	//���һ�˵ĺ���������ܽ���ȥǰ��Ľ�
	cout << "��" << setiosflags(ios::right) <<
		setw(3) << number << "���˵ĺ����:" <<
		setiosflags(ios::right) << setw(6) << setiosflags(ios::fixed) <<
		setprecision(2) << round((total - sumb) * 100) / 100.0;
	if (best == number - 1) {
		cout << "(�������)" << endl;
	}
	else {

		cout << endl;
	}
}
void redbag()
{
	int i, number, best;
	float total;
	std::cout << "�������ܶ" << std::endl;
	std::cin >> total;
	std::cout << "�����������" << std::endl;
	std::cin >> number;

	// ��������
	/*std::srand(std::time(0));*/
	std::srand(42);
	// ����ʵ����Ҫ��̬��������
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
		person_money[i] = std::round(person_money[i] * 100) / 100.0; // ������λС��
		sum_person_money += person_money[i];

		std::cout << "��" << i + 1 << "�����Ϊ��" << person_money[i] << std::endl;
	}
	person_money[i] = total - sum_person_money;
	std::cout << "��" << i + 1 << "�����Ϊ��" << person_money[i] << std::endl;
	std::cout << "�������Ϊ:" << person_money[best] << std::endl;

	// �ͷŶ�̬������ڴ�
	delete[] rand_number;
	delete[] person_money;

	// �Ƿ�ѭ��
	std::cout << "�Ƿ������y/n" << std::endl;
	char c;
	std::cin.ignore(); // ������뻺����
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
		std::cout << "��"<<i+1<<"�������Ϊ��" << setw(5) << random_arr[i] << std::endl;
	}
}