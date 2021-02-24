uint32_t calcHash(std::string str, int base = 256, int modulus = 101)
{
	uint32_t size = str.size();
	uint32_t hash = 0;

	for (size_t i = 0; i < size - 1; ++i)
	{
		hash = (((uint8_t)str[i] + hash) * base) % modulus;
	}

	hash += str[size - 1];
	hash %= modulus;

	return  hash;
}

bool RabinKarp(std::string str, std::string subStr, int base = 256, int modulus = 101)
{
	uint32_t size = str.size();
	uint32_t subSize = subStr.size();
	uint32_t subStrHash = calcHash(subStr, base, modulus);
	uint32_t strHash = calcHash(str.substr(0, subSize), base, modulus);

	for (size_t i = subSize - 1; i < size; ++i)
	{
		if (strHash == subStrHash)
		{
			if (str.substr(i - subSize + 1, subSize) == subStr)
			{
				return true;
			}
		}
		strHash = ((strHash + modulus - str[i + 1 - subSize] * ((uint32_t)pow(base, subSize - 1)) % 101) * base + str[i + 1]) % modulus;
	}
	return false;
}
