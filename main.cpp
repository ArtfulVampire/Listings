#include <iostream>
#include <QDir>
#include <iostream>
#include <ios>
#include <fstream>
#include <chrono>
using namespace std;

std::ostream & operator<< (std::ostream &os, const std::vector<int> & toOut)
{
	std::string separ = "\t";
	for(auto in : toOut)
	{
		os << in << separ;
	}
	os.flush();
	return os;
}

QString rightNumber(const int input, int N) // prepend zeros
{
	QString h;
	h.setNum(input);
	h.prepend(QString(N, '0'));
	return h.right(N);
}

int main(int argc, char *argv[])
{
	int num = 40;
	int exper = 1; /// 1, 2, 3

	std::vector<int> mixNum1(num); /// CF
	std::vector<int> mixNum2(num); /// anagrams

	ofstream lst("/media/Files/Pictures/list1.txt");
	std::iota(std::begin(mixNum1), std::end(mixNum1), 1);
	std::iota(std::begin(mixNum2), std::end(mixNum2), 1 + num);
	std::shuffle(std::begin(mixNum1), std::end(mixNum1),
				 std::default_random_engine(
					 std::chrono::system_clock::now().time_since_epoch().count()));
	std::shuffle(std::begin(mixNum2), std::end(mixNum2),
				 std::default_random_engine(
					 std::chrono::system_clock::now().time_since_epoch().count()));

	std::vector<int> mixNum3(80);
	for(int i = 0; i < num; ++i)
	{
		mixNum3[i] = mixNum1[i];
		mixNum3[i + num] = mixNum2[i];
	}
	std::shuffle(std::begin(mixNum3), std::end(mixNum3), std::default_random_engine(
					 std::chrono::system_clock::now().time_since_epoch().count()));

	for(int i = 0; i < 2 * num; ++i)
	{
		if(mixNum3[i] <= num)
		{
			int currNum = mixNum3[i] + (exper - 1) * num;
			lst<< "S1" << '\t' << currNum << '\t' << "cf_" << rightNumber(currNum, 3).toStdString() << ".jpg" << "\r\n";
		}
		else
		{
			int currNum = mixNum3[i] + (exper - 1) * num - num;
			lst << "V1" << '\t' << currNum << '\t' << "anagramm_" << rightNumber(currNum, 3).toStdString() << ".jpg" << "\r\n";
		}
	}
	lst.close();

    return 0;
}
