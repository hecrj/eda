#include <iostream>
#include <vector>

using namespace std;

typedef vector< vector<bool> > Fractal;

void read(Fractal &f)
{
	int n = f.size();
	int m = f[0].size();

	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < m; ++j)
		{
			char c;
			cin >> c;
	
			f[i][j] = (c == 'X');
		}
	}
}

void print(const Fractal &f)
{
	int n = f.size();
	int m = f[0].size();

	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < m; ++j)
			cout << (f[i][j] ? 'X' : '.');

		cout << endl;
	}

	cout << endl;
}

void fractal_copy(const Fractal &o, Fractal &d, int di, int dj, bool copy)
{
	int n = o.size();
	int m = o[0].size();

	di = di * n;
	dj = dj * m;

	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < m; ++j)
		{
			if(copy) d[di+i][dj+j] = o[i][j];
			else d[di+i][dj+j] = false;
		}
	}
}

void fractalize_model(const Fractal &fm, const Fractal &o, Fractal &d)
{
	int dn = fm.size() * o.size();
	int dm = fm[0].size() * o[0].size();

	d = Fractal(dn, vector<bool>(dm));
	
	int n = fm.size();
	int m = fm[0].size();

	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < m; ++j)
		{
			fractal_copy(o, d, i, j, fm[i][j]);
		}
	}
}

void fractalize(const Fractal &f, Fractal &fk, int k)
{
	if(k <= 0)
	{
		fk = Fractal(1, vector<bool>(1, true));
	}
	else if(k == 1)
	{
		fk = f;
	}
	else
	{
		Fractal fk_2;
		fractalize(f, fk_2, k/2);

		fractalize_model(fk_2, fk_2, fk);

		if(k%2 != 0)
		{
			Fractal fke;
			fractalize_model(fk, f, fke);

			fk = fke;
		}
	}
}

long long int my_power(int n, int k)
{
	if(k == 0) return 1;
	if(k == 1) return n;

	long long int res = my_power(n, k/2);

	res = res * res;

	if(k%2 != 0)
		return res * n;
	else
		return res;
}

bool is_marked(const Fractal &f, int k, long long int r, long long int c)
{
	if(k <= 0) return true;
	if(k == 1) return f[r][c];

	if(k%2 != 0)
	{
		if(! f[r % f.size()][c % f[0].size()])
			return false;

		r = r / f.size();
		c = c / f[0].size();
	}

	int k_2 = k/2;
	long long int nk_2 = my_power(f.size(), k_2);
	long long int mk_2 = my_power(f[0].size(), k_2);

	if(! is_marked(f, k_2, r / nk_2, c / mk_2) or ! is_marked(f, k_2, r % nk_2, c % mk_2))
		return false;

	return true;
}

int main()
{
	int n, m;

	while(cin >> n >> m)
	{
		Fractal f(n, vector<bool>(m));

		read(f);

		int k;
		cin >> k;

		Fractal fk;
		fractalize(f, fk, k);

		print(fk);

		int q;
		cin >> q;

		for(int i = 0; i < q; ++i)
		{
			int k;
			long long int r, c;
			cin >> k >> r >> c;

			cout << "after " << k << " step(s), (" << r << ", " << c << ") ";
			cout << "is " << (is_marked(f, k, r-1, c-1) ? "marked" : "empty") << endl;
		}

		cout << endl;
	}

	return 0;
}