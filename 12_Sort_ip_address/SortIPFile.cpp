
#define t_10000 167772160
#define t_10255255255 184549375
#define t_1721600 2886729728
#define t_19231255255 2887778303
#define t_19216800 3232235520
#define t_192168255255 3232301055

uint64_t uint64Rand()
{
#ifndef __UINT64RAND__
#define __UINT64RAND__
#define UINT64RAND_MAX 18446744073709551615
#endif

	uint64_t result{};

	for (size_t i = 0; i < 4; ++i)
	{
		result = result << 15;
		result |= rand();
	}
	result = result << 4;
	result |= rand() % 16;
	return result;
}

struct IP
{
public:
	uint64_t m_a = 0;
	uint64_t m_b = 0;
	uint64_t m_c = 0;
	uint64_t m_d = 0;

	IP()
	{
		m_a = 0;
		m_b = 0;
		m_c = 0;
		m_d = 0;
	}

	IP(uint64_t value)
	{
		uint64_t module_;

		module_ = value / pow(256, 3);
		m_a = module_;
		value -= module_ * pow(256, 3);
		///
		module_ = value / pow(256, 2);
		m_b = module_;
		value -= module_ * pow(256, 2);
		///
		module_ = value / pow(256, 1);
		m_c = module_;
		value -= module_ * pow(256, 1);
		///
		module_ = value / pow(256, 0);
		m_d = module_;
		value -= module_ * pow(256, 0);
	}
	
	IP(uint16_t a, uint16_t b, uint16_t c, uint16_t d)
	{
		m_a = a;
		m_b = b;
		m_c = c;
		m_d = d;
	}

	IP& operator=(uint64_t value)
	{
		m_a = value / pow(256, 3);
		value -= m_a * pow(256, 3);
		m_b = value / pow(256, 2);
		value -= m_b * pow(256, 2);
		m_c = value / pow(256, 1);
		value -= m_c * pow(256, 1);
		m_d = value / pow(256, 0);
		value -= m_d * pow(256, 0);

		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const IP& obj)
	{
		os << obj.m_a << "." << obj.m_b << "." << obj.m_c << "." << obj.m_d << std::endl;
		return os;
	}
	
	uint64_t intValue()
	{
		return m_a * (uint64_t)pow(256, 3) + m_b * (uint64_t)pow(256, 2) + m_c * (uint64_t)pow(256, 1) + m_d * (uint64_t)pow(256, 0);
	}
};

void FillIPFile(std::string fileName)
{
	std::ofstream outFile;
	uint64_t Limit = 6250000;
	IP tmp;
	int stage = 0;
	uint64_t randIP = 0;
	outFile.open(fileName);

	for (uint64_t i = 0; i < Limit; ++i)
	{
		stage = rand() % 3; /// 0 for t_10.0.0.0 to t_10.255.255.255 ...
		if (stage == 0)
		{
			randIP = uint64Rand() % (184549375 - t_10000);
			randIP += t_10000;
		}
		else if (stage == 1)
		{
			randIP = uint64Rand() % (2887778303 - 2886729728);
			randIP += 2886729728;
		}
		else
		{
			randIP = uint64Rand() % (t_192168255255 - t_19216800);
			randIP += t_19216800;
		}
		tmp = randIP;
		outFile << tmp;
	}
	outFile.close();
}

int strtoInt(std::string str)
{
	int result = 0;
	int mulofTen = 1;
	for (auto i = str.rbegin(); i < str.rend(); ++i)
	{
		result += mulofTen * (*i - 48);
		mulofTen *= 10;
	}
	return result;
}

uint64_t LinetoInt(std::string line) ///
{
	uint64_t result{};
	std::string tmp;
	int degree = 3;


	for (size_t i = 0; i < line.size() + 1; ++i)
	{
		if (line[i] == '.' || line[i] == '\0')
		{
			result += (uint64_t)strtoInt(tmp) * (uint64_t)pow(256, degree);
			--degree;
			tmp = "";
		}
		else
		{
			tmp += line[i];
		}
	}

	return result;
}

void SortIPFile(std::string fileName)
{
	std::ifstream inFile;
	std::string line;
	uint64_t valueofIP;
	int* firstArr = new int[t_10255255255 - t_10000]{};
	int* secondArr = new int[t_19231255255 - t_1721600]{};
	int* thirdArr = new int[t_192168255255 - t_19216800]{};

	inFile.open(fileName);

	while (std::getline(inFile, line))
	{
		valueofIP = LinetoInt(line);
		if (valueofIP < t_10255255255)
		{
			++firstArr[valueofIP - t_10000];
		}
		else if (valueofIP < t_19231255255)
		{
			++secondArr[valueofIP - t_1721600];
		}
		else
		{
			++thirdArr[valueofIP - t_19216800];
		}
	}
	inFile.close();
	IP tmp;
	std::ofstream outFile;
	outFile.open(fileName);
	for (uint64_t i = 0; i < t_10255255255 - t_10000; ++i)
	{
		while (firstArr[i]--)
		{
			tmp = i + t_10000;
			outFile << tmp;
		}
	}
	for (uint64_t i = 0; i < t_19231255255 - t_1721600; ++i)
	{
		while (secondArr[i]--)
		{
			tmp = i + t_1721600;
			outFile << tmp;
		}
	}
	for (uint64_t i = 0; i < t_192168255255 - t_19216800; ++i)
	{
		while (thirdArr[i]--)
		{
			tmp = i + t_19216800;
			outFile << tmp;
		}
	}
	outFile.close();
}