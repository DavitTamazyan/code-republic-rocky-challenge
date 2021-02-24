bool IsUnique(std::string obj)
{
	bool* arr = new bool[128]{};
	for (int i = 0; obj[i] != '\0'; ++i)
	{
		if (arr[(int)obj[i]])
		{
			delete[] arr;
			return false;
		}
		arr[(int)obj[i]] = true;
	}
	delete[] arr;
	return true;
}

bool IsPermutation(std::string obj1, std::string obj2)
{
	int obj1Size = obj1.size();
	int obj2Size = obj2.size();
	if (obj1Size != obj2Size)
	{
		return false;
	}
	for (int i = 0; i < obj1Size; ++i)
	{
		if (obj1[i] ^ obj2[obj2Size - 1 - i])
		{
			return false;
		}
	}
	return true;
}

std::string URLify(std::string obj, int size)
{
	int endIter = size;
	int startIter = size;
	while (obj[++endIter] != '\0') {}
	while (startIter--)
	{
		if (obj[startIter] == ' ')
		{
			obj[--endIter] = '0';
			obj[--endIter] = '2';
			obj[--endIter] = '%';
		}
		else {
			std::swap(obj[startIter], obj[--endIter]);
		}
	}
	return obj;
}

bool Permutation(std::string obj)
{
	bool* arr = new bool[128]{};
	int evenCount = 0;
	size_t objSize = obj.size();
	for (size_t i = 0; i < objSize; ++i)
	{
		bool tmp = arr[(int)obj[i]];
		if (tmp)
		{
			--evenCount;
		}
		else
		{
			++evenCount;
		}
		arr[(int)obj[i]] = !tmp;
	}
	return (evenCount < 2);
}

bool OneAwayReplace(std::string first, std::string second)
{
	bool toggle = false;
	int firstSize = first.size();
	int secondSize = second.size();

	if (firstSize != secondSize)
	{
		return false;
	}
	for (int i = 0; i < firstSize; ++i)
	{
		if (first[i] != second[i])
		{
			if (toggle)
			{
				return false;
			}
			toggle = true;
		}
	}
	return true;
}

bool OneAwayInsert(std::string first, std::string second)
{
	bool toggle = false;
	int firstSize = first.size();
	int secondSize = second.size();
	int max = std::max(firstSize, secondSize);

	if (firstSize - secondSize != 1 && secondSize - firstSize != 1)
	{
		return false;
	}
	for (int i = 0, j = 0; i < max; ++i, ++j)
	{
		if (first[i] != second[j])
		{
			if (firstSize > secondSize)
			{
				--j;
			}
			else
			{
				--i;
			}
			if (toggle)
			{
				return false;
			}
			toggle = true;
		}
	}
	return true;
}

bool OneAway(std::string first, std::string second)
{
	return OneAwayReplace(first, second) || OneAwayInsert(first, second);	
}

std::string StringCompression(std::string str)
{
	int strSize = str.size();
	int count = 1;
	std::string result = "";

	for (int i = 1; i < strSize + 1; ++i)
	{
		if (i != (strSize) && str[i] == str[i - 1])
		{
			++count;
		}
		else
		{
			result += str[i - 1];
			result += (count + 48);
			count = 1;
		}
	}
	return result;
}

void rotate(std::vector<int>& nums, int k) {
    std::vector<int> tmp;
    int numsSize = nums.size();
    k = k % nums.size();
    for (int i = numsSize - k; i < numsSize; ++i)
    {
        tmp.push_back(nums[i]);
    }
    for (int i = 0; i < numsSize - k ; ++i)
    {
        tmp.push_back(nums[i]);
    }
    nums = tmp;
}

void ZeroMatrix(int** arr, int size)
{
	bool* row = new bool[size] {};// -
	bool* col = new bool[size] {};// |

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (arr[i][j] == 0)
			{
				row[j] = true;
				col[i] = true;
			}
		}
	}

	for (int i = 0; i < size; ++i)
	{
		if (row[i])
		{
			for (int j = 0; j < size; ++j)
			{
				arr[j][i] = 0;
			}
		}
	}


	for (int i = 0; i < size; ++i)
	{
		if (col[i])
		{
			for (int j = 0; j < size; ++j)
			{
				arr[i][j] = 0;
			}
		}
	}
	delete[] row;	
	delete[] col;
}

bool IsSubstring(std::string str1, std::string str2)
{
	if (str1.size() != str2.size())
	{
		return false;
	}
	std::string str1str1 = str1 + str1;
	std::cout << str1str1.find(str2) << std::endl;
	return str1str1.find(str2) < str1str1.size();
}
