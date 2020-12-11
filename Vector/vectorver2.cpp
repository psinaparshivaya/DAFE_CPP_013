#include <iostream>
using namespace std;
class vector11
{
	int sz;
	double* elem;
	public:
		vector11(const vector11&);
		vector11& operator=(vector11&&);
		vector11(int s)
		:sz{s}, elem{new double[s]}
		{
			int i;
			for (i = 0; i < sz; ++i)
			elem[i] = 0.0;
		}
	vector11::vector11(vector11&& a)
	:sz{a.sz}, elem{a.elem}
	{
		a.sz = 0;
		a.elem = nullptr;
	}
	vector11& vector11::operator=(vector11&& a)
	{
		delete[] elem;
		elem = a.elem;
		sz = a.sz;
		a.elem = nullptr;
		a.sz = 0;
		return *this;
	}
	double get(int n) const {return elem[n];}
	void set(int n, double v) {elem[n]=v;}
	~vector11()
	{
		delete[] elem;
	}
	double& operator[](int n)
		{return elem[n];}
};
