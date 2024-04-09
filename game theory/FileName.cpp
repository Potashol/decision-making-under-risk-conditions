#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>

using namespace std; 

void decision(vector<vector<double>> strategy, vector<double>p, int B, int A, double k) // функция выдаёт файл, в котором указан ответ, 
																						//но для удобства я дублирую его на экран
{
	ofstream fout("output.txt"); 
	double sum = 0; 
	vector<double> Wm(A); //вектор математического ожидания
	vector<double> sigma(A);//среднеквардратичного отклонения
	vector<double> Ws(A);//критерий дисперсии
	fout << "Wm: "; 
	for (int i = 0; i < A; ++i) 
	{
		for (int j = 0; j < B; ++j) 
			sum += strategy[i][j] * p[j];	//находится математическое ожидание для i-той стратегии
		Wm[i] = sum;
		sum = 0;
		fout << Wm[i] << " ";
		cout << Wm[i] << " "; 
	}

	cout << endl; 
	fout << endl << "sigma: ";

	for (int i = 0; i < A; ++i)
	{
		for (int j = 0; j < B; ++j)
			sum += strategy[i][j] * strategy[i][j] * p[j]; //находится среднеквадратичное отклонение
		sigma[i] = sqrt(sum - Wm[i] * Wm[i]);
		sum = 0;
		fout << sigma[i] << " "; 
		cout << sigma[i] << " "; 
	}
	fout << endl << "Ws: ";
	cout << endl; 

	for (int i = 0; i < sigma.size(); ++i)
	{
		Ws[i] = Wm[i] - sigma[i] * k; //критерий дисперсии
		fout << Ws[i] << " ";
		cout << Ws[i] << " "; 
	}
	fout.close();
}


int main()
{
	setlocale(LC_ALL, "Russian");

	int A, B;
	double k;
	cout << "Введите количество стратегий, факторов и коэфициент готовности к риску" << endl; 
	cin >> B >> A >> k; 
	vector<double> p(B);// вектор вероятностей
	vector<vector<double>> strategy(A, vector<double>(B));  
	cout << "введите данные о ваших стратегиях" << endl; 
	for (int i = 0; i < A; ++i)
		for (int j = 0; j < B; ++j)
		{ 
			cin >> strategy[i][j]; 
		}
	cout << "введите вероятности факторов" << endl; 
	double sump = 0;
	for (int i = 0; i < B; ++i)
	{
		cin >> p[i];
		sump += p[i];
	}
	if (sump != 1)
		cout << "Сумма вероятностей должна ровнятся 1, вы где-то просчитались, вернитесь позже";
	else
		decision(strategy, p, B, A, k); 
}