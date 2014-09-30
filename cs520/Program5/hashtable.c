
int hashKey(char * str)
{
	int key = 0;
	for(int j = 0; j <= 51; j++)
	{
		if(str[j] == '\0')
			break;
		
		key += pow((int)str[j], j);
	}
	key = key % HASH_SIZE;
	return key;
}