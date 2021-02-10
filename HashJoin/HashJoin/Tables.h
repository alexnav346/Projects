#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class FirstTable 
{

private:

	vector<int> a, b, c;

	vector<int>::iterator it1, it2, it3;


public:
	FirstTable()
	{
		;
	}

	FirstTable(int x, int y, int z)
	{
		a.push_back(x);
		b.push_back(y);
		c.push_back(z);
	}

	vector<int> getA()
	{
		return a;
	}

	vector<int> getB()
	{
		return b;
	}

	vector<int> getC()
	{
		return c;
	}

	void addTuple(int x, int y, int z)
	{
		a.push_back(x);
		b.push_back(y);
		c.push_back(z);
	}

	void printRows()
	{
		cout << "Table 1:\n";

		it1 = a.begin();
		it2 = b.begin();
		it3 = c.begin();

		int tupleCount = a.size();

		for (int i = 0; i < tupleCount; i++)
		{
			cout << *it1 << "  ";
			cout << *it2 << "  ";
			cout << *it3 << endl;

			it1++;
			it2++;
			it3++;
		}

		cout << endl;
	}

	void getTuple(int lineNumber, int&one, int&two, int&three)
	{
		if (lineNumber > a.size())
		{
			cout << "out of bound error...\n";
		}
		else
		{
			it1 = a.begin();
			it2 = b.begin();
			it3 = c.begin();

			it1 = it1 + (lineNumber - 1);
			it2 = it2 + (lineNumber - 1);
			it3 = it3 + (lineNumber - 1);

			one = *it1; two = *it2; three = *it3;
		}
	}

};

class SecondTable
{

private:

	vector<int> w, x, y, z;

	vector<int>::iterator it1, it2, it3, it4;

public:

	SecondTable()
	{
		;
	}

	SecondTable(int a, int b, int c, int d)
	{
		w.push_back(a);
		x.push_back(b);
		y.push_back(c);
		z.push_back(d);
	}

	vector<int> getW()
	{
		return w;
	}

	vector<int> getX()
	{
		return x;
	}

	vector<int> getY()
	{
		return y;
	}

	vector<int> getZ()
	{
		return z;
	}

	void addTuple(int a, int b, int c, int d)
	{
		w.push_back(a);
		x.push_back(b);
		y.push_back(c);
		z.push_back(d);
	}

	void printRows()
	{

		cout << "Table 2:\n";

		it1 = w.begin();
		it2 = x.begin();
		it3 = y.begin();
		it4 = z.begin();

		int tupleCount = w.size();

		for (int i = 0; i < tupleCount; i++)
		{
			cout << *it1 << "  ";
			cout << *it2 << "  ";
			cout << *it3 << "  ";
			cout << *it4 << endl;

			it1++;
			it2++;
			it3++;
			it4++;
		}

		cout << endl;
	}

	void getTuple(int lineNumber, int&one, int&two, int&three, int&four)
	{
		if (lineNumber > w.size())
		{
			cout << "out of bound error...\n";
		}
		else
		{
			it1 = w.begin();
			it2 = x.begin();
			it3 = y.begin();
			it4 = z.begin();

			it1 = it1 + (lineNumber - 1);
			it2 = it2 + (lineNumber - 1);
			it3 = it3 + (lineNumber - 1);
			it4 = it4 + (lineNumber - 1);

			one = *it1; two = *it2; three = *it3; four = *it4;
		}
	}

};

class FinalTable
{

private:

	//from FirstTable
	vector<int> a, b, c;
	vector<int>::iterator itA, itB, itC;

	//from Second Table
	vector<int> w, x, y, z;
	vector<int>::iterator itW, itX, itY, itZ;

public:

	FinalTable()
	{
		;
	}

	void addTuple(int t1a, int t1b, int t1c, int t2w, int t2x, int t2y, int t2z)
	{
		a.push_back(t1a);
		b.push_back(t1b);
		c.push_back(t1c);
		w.push_back(t2w);
		x.push_back(t2x);
		y.push_back(t2y);
		z.push_back(t2z);
	}

	void printRows()
	{
		cout << "New Table:\n";

		itA = a.begin();
		itB = b.begin();
		itC = c.begin();
		itW = w.begin();
		itX = x.begin();
		itY = y.begin();
		itZ = z.begin();

		int tupleCount = w.size();

		for (int i = 0; i < tupleCount; i++)
		{
			cout << *itA << "  ";
			cout << *itB << "  ";
			cout << *itC << "  ";
			cout << *itW << "  ";
			cout << *itX << "  ";
			cout << *itY << "  ";
			cout << *itZ << endl;

			itA++; itB++; itC++;
			itW++; itX++; itY++; itZ++;
		}

		cout << endl;
	}

};

//test3.addTuple(0, 1, 2, 0, 1, 2, 3);
//test3.addTuple(3, 2, 1, 4, 3, 2, 1);
//test3.printRows();

//test1.getTuple(3, x, y, z);
//cout << "Table 1, Tuple 3: " << x << ' ' << y << ' ' << z << endl;

//test1.getTuple(2, x, y, z);
//cout << "Table 1, Tuple 2: " << x << ' ' << y << ' ' << z << endl;

//test2.getTuple(2, w, x, y, z);
//cout << "Table 2, Tuple 2: " << w << ' ' << x << ' ' << y << ' ' << z << endl;

//test2.getTuple(1, w, x, y, z);
//cout << "Table 2, Tuple 1: " << w << ' ' << x << ' ' << y << ' ' << z << endl;