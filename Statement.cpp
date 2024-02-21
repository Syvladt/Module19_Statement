#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

bool checkNumber(std::string inStr)
{
	int pCount = 0, i = 0;
	bool result = true;
	for (int i = 0; i < inStr.length(); i++)
	{
		if (inStr[i] < '0' || inStr[i] > '9')
		{
			if (inStr[i] == '.')
			{
				pCount++;
				if (pCount > 1)
					result = false;
			}
			else
				result = false;
		}
	}
	return result;
}

bool checkDate(std::string inStr)
{
	bool result = true;
	std::string day, month, year;
	int pCount = 0, pLeft = 0, pRight = 0;
	for (int i = 0; i < inStr.length(); i++)
	{
		if (inStr[i] < '0' || inStr[i] > '9')
		{
			if (inStr[i] == '.')
			{
				if (pCount == 0)
				{
					day = inStr.substr(pLeft, i);
					pLeft = i + 1;
				}
				else if (pCount == 1)
				{
					month = inStr.substr(pLeft, i - pLeft);
					pLeft = i + 1;
					year = inStr.substr(pLeft, inStr.length() - pLeft);
				}
				else
					result = false;
				pCount++;
			}
			else
				result = false;
		}
	}
	if (result)
	{
		if (std::stoi(day) > 0 && std::stoi(day) < 32 && std::stoi(month) > 0 && std::stoi(month) < 13)
			result = true;
		else
			result = false;
	}
	return result;
}

int main()
{
	std::fstream src;
	std::string fName, sName, salary, pDate, maxFName, maxSName;
	float sSum = 0.0, maxSalary = 0.0, nSalary = 0.0;
	int counter = 1;
	src.open("statement.txt");
	if (src.is_open())
	{
		while (!src.eof())
		{
			src >> fName >> sName >> salary >> pDate;
			if (checkNumber(salary))
			{
				nSalary = std::stof(salary);
				if (maxSalary < nSalary)
				{
					maxFName = fName;
					maxSName = sName;
					maxSalary = nSalary;
				}
				sSum += nSalary;
			}
			else
				std::cout << "Payout in " << counter << " row is not correct.\n";
			if (!checkDate(pDate))
				std::cout << "Data payout in " << counter << " row is not correct.\n";
			counter++;
		}
		src.close();
		std::cout << std::fixed << std::setprecision(2);
		std::cout << "Maximum payout for " << maxFName << ' ' << maxSName << ' ' << maxSalary << "\nSum all payouts: " << sSum << '\n';
	}
	else
		std::cout << "File statement.txt not exist.\n";
}