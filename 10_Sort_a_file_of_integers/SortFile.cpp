void CreateFile(std::string fileName)
{
	std::ofstream outFile;
	uint64_t allOnes = ~0;
	outFile.open(fileName);

	for (uint64_t i = 0; i < allOnes; ++i)
	{
		uint16_t tmp = rand() % 10000;
		outFile << tmp << std::endl;
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

void SortFile(std::string fileName)
{
	std::ifstream inFile;
	inFile.open(fileName);
	int* data = new int[10000]{};
	std::string line;
	
	while (std::getline(inFile, line))
	{
		int num = strtoInt(line);
		++data[num];
	}

	inFile.close();
	std::ofstream outFile;
	outFile.open(fileName);

	for (int i = 0; i < 10000; ++i)
	{
		while (data[i]--)
		{
			outFile << i << std::endl;
		}
	}

	outFile.close();
	delete[] data;
}
