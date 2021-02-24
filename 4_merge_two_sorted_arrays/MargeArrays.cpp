int* MargeArrays(int* firstArr, int firstSize, int* secondtArr, int secondSize)
{
	int* newArr = new int[firstSize + secondSize];
	int newitter = 0;
	int firstitter = 0;
	int seconditter = 0;

	while (firstitter != firstSize && seconditter != secondSize)
	{
		newArr[newitter++] = (firstArr[firstitter] < secondtArr[seconditter])? firstArr[firstitter++] : secondtArr[seconditter++];
	}
	while (firstitter != firstSize)
	{
		newArr[newitter++] = firstArr[firstitter++];
	}
	while (seconditter != secondSize)
	{
		newArr[newitter++] = secondtArr[seconditter++];
	}
	return newArr;
}
