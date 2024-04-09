#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>

using namespace std; 

void decision(vector<vector<double>> strategy, vector<double>p, int B, int A, double k) // ������� ����� ����, � ������� ������ �����, 
																						//�� ��� �������� � �������� ��� �� �����
{
	ofstream fout("output.txt"); 
	double sum = 0; 
	vector<double> Wm(A); //������ ��������������� ��������
	vector<double> sigma(A);//�������������������� ����������
	vector<double> Ws(A);//�������� ���������
	fout << "Wm: "; 
	for (int i = 0; i < A; ++i) 
	{
		for (int j = 0; j < B; ++j) 
			sum += strategy[i][j] * p[j];	//��������� �������������� �������� ��� i-��� ���������
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
			sum += strategy[i][j] * strategy[i][j] * p[j]; //��������� ������������������ ����������
		sigma[i] = sqrt(sum - Wm[i] * Wm[i]);
		sum = 0;
		fout << sigma[i] << " "; 
		cout << sigma[i] << " "; 
	}
	fout << endl << "Ws: ";
	cout << endl; 

	for (int i = 0; i < sigma.size(); ++i)
	{
		Ws[i] = Wm[i] - sigma[i] * k; //�������� ���������
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
	cout << "������� ���������� ���������, �������� � ���������� ���������� � �����" << endl; 
	cin >> B >> A >> k; 
	vector<double> p(B);// ������ ������������
	vector<vector<double>> strategy(A, vector<double>(B));  
	cout << "������� ������ � ����� ����������" << endl; 
	for (int i = 0; i < A; ++i)
		for (int j = 0; j < B; ++j)
		{ 
			cin >> strategy[i][j]; 
		}
	cout << "������� ����������� ��������" << endl; 
	double sump = 0;
	for (int i = 0; i < B; ++i)
	{
		cin >> p[i];
		sump += p[i];
	}
	if (sump != 1)
		cout << "����� ������������ ������ �������� 1, �� ���-�� ������������, ��������� �����";
	else
		decision(strategy, p, B, A, k); 
}