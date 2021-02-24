uint32_t greatComDiv(uint32_t firstNum, uint32_t secondNum)
{
	uint32_t minof = std::min(firstNum, secondNum);
	for (uint32_t i = 0; i < minof; ++i)
	{
		if (firstNum % (minof - i) == 0 && secondNum % (minof - i) == 0)
		{
			return minof - i;
		}
	}
	return 1;
}

uint32_t EuclideanAlgorithm(uint32_t firstNum, uint32_t secondNum)
{
	if (!firstNum) { return secondNum; }
	if (!secondNum) { return firstNum; }
	return EuclideanAlgorithm(secondNum, firstNum - (firstNum / secondNum) * secondNum);
}
