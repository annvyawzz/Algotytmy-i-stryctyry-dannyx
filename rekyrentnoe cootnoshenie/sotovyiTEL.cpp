#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	ifstream in("in.txt");
	if (!in)
	{
		cout << "нельзя считать in.txt" << endl;
		return 1;
	}

	ofstream out("out.txt");
	if (!out)
	{
		cout << "ошибка out.txt" << endl;
		return 1;
	}

	int n;
	in >> n;
	if (n < 1 || n > 100)
	{
		cerr << "n должно быть от 1 до 100" << endl;
		return 1;
	}

	int m;
	in >> m;
	if (m < 1 || m > 1000)
	{
		cerr << " m должно быть от 1 до 1000" << endl;
		return 1;
	}
	
	vector<int> chisla(m + 1);
	for (int i = 1; i <= m; i++)
	{
		int num;
		in >> num;

		if (num < 0 || num > 100000)
		{
			cerr << "Ошибка: число " << num << " не из [0, 100000]" << endl;
			return 1;
		}

		chisla[i] = num; 
	}
	in.close();

	if (n >= m)
	{
		long long s = 0;
		for (int i = 1; i <= m; ++i) s += chisla[i];
		out << s;
		out.close();
		return 0;
	}


	long long s = 0;

	vector<long long> sum(m + 1, 0), stoimost(m + 1, 0);
	for (int i = 1; i <= m; ++i)
	{
		sum[i] = sum[i - 1] + chisla[i];
		stoimost[i] = stoimost[i - 1] + chisla[i] * i;
	}

	if (n >= m)
	{
		long long s = 0;
		for (int i = 1; i <= m; ++i) s += chisla[i];
		out << s;
		return 0;
	}

	vector<long long> prev(m + 1, 0), cur(m + 1, 0);

	for (int i = 1; i <= m; ++i)
		cur[i] = stoimost[i];

	for (int klavisha = 2; klavisha <= n; ++klavisha)
	{
		prev = cur;
		for (int i = 1; i <= m; ++i)
		{
			long long best = -1;
			for (int p = 0; p < i; ++p) 
			{
				long long sumZ = sum[i] - sum[p];
				long long sumstoimost = stoimost[i] - stoimost[p];
				long long cost = sumstoimost - p * sumZ;
				long long optoin = prev[p] + cost;
				if (best == -1 || optoin < best)
					best = optoin;
			}
			cur[i] = best;
		}
	}

	out << cur[m];
	out.close();
	return 0;
}



