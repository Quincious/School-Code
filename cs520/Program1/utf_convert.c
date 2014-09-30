/*
Jonathan Hart
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
int utf16_to_utf32(FILE *inputFile, FILE *outputFile)
{
	unsigned short convert;
	do
	{
		convert = fgetc(inputFile);//retrieve character from file
		
		if(convert != EOF)
		{
			//reverse endianness
			convert = ((convert << 8) | (convert >> 8 ));
			
			if(convert < 0xD800 || convert > 0xDFFF)//No need to decode if not within range
			{
				unsigned int output = convert;
				//reverse endianness
				output = ((output << 8) & 0xFF00FF00 ) | ((output >> 8) & 0xFF00FF );
				output = (output << 16) | (output >> 16);
				fputc(output, outputFile);				
			}
			else
			{
				if(0xD800 != (convert & 0xD800))//means not first part which means error
				{
					fprintf(stderr, "Invalid input for W1");
					return -1;
				}
				else
				{
					unsigned short W1 = convert;
					convert = fgetc(inputFile);
					if(convert != EOF)
					{
						if(0xDC00 != (convert & 0xDC00))//if not flagged as W2 then error
						{
							fprintf(stderr, "Invalid input for W1");
							return -1;
						}
						else
						{
							unsigned short W2 = convert;
							unsigned int output = 0x3FF & W2;
							output = output + ((W1 & 0x3FF) << 10);
							output += 0x10000;
							//reverse endianness
							output = ((output << 8) & 0xFF00FF00 ) | ((output >> 8) & 0xFF00FF );
							output = (output << 16) | (output >> 16);
							fputc(output, outputFile);
						}
					}
				}
			}
		}
		//printf("Retrieved: %c\n", c);
	}while(convert != EOF);	
	
	return 0;
}

int utf32_to_utf16(FILE *inputFile, FILE *outputFile)
{
	unsigned int convert;
	do
	{
		convert = fgetc(inputFile);//retrieve character from file
		
		if(convert != EOF)
		{
			//reverse endianness
			convert = ((convert << 8) & 0xFF00FF00 ) | ((convert >> 8) & 0xFF00FF );
			convert = (convert << 16) | (convert >> 16);
					
			if(convert >= 0xD800 && convert <= 0xDFFF)//Invalid character if within this range
			{
				fprintf(stderr, "Invalid character");
				return -1;
			}
			else
			{
				convert = convert - 0x10000;
				unsigned short W1 = 0xD800;
				unsigned short W2 = 0xDC00;
				
				W2 = W2 | (0x3FF8 & convert);
				W1 = W1 | (0x3FF8 & (convert >> 10));
				
				W1 = ((W1 << 8) | (W1 >> 8 ));
				W2 = ((W2 << 8) | (W2 >> 8 ));
				
				fputc(W1, outputFile);
				fputc(W2, outputFile);
			}
		}
		//printf("Retrieved: %c\n", c);
	}while(convert != EOF);	
	
	return 0;
}

int main(int argc, char** argv)
{
	if(argc > 4)
	{
		fprintf(stderr, "Too many arguments!\n");
		return -1;
	}
	else if(argc < 3)
	{
		fprintf(stderr, "Not enough arguments!\n");
		return -1;
	}
	
	char* end;
	errno = 0;
	unsigned int format = 0;
	
	if(argc == 4)
	{
		format = strtol(argv[3], &end, 10);
		
		if(errno != 0)
		{
			fprintf(stderr, "%s is not a valid format (Overflow)\n", argv[3]);
			return -1;
		}
		
		if((*end) != 0)
		{
			fprintf(stderr, "%s is not a valid format\n", argv[3]);
			return -1;
		}
			
		if(format != 32 && format != 16)
		{
			fprintf(stderr, "%s is not a valid format\n", argv[3]);
			return -1;
		}
		//printf("Input format: %d\n", format);
	}
			
	FILE *inputFile = fopen(argv[1], "r");//open input file
	
	if(inputFile == NULL) //ensure input file exists
	{
		fprintf(stderr, "Error creating input file\n");
		return -1;
	}
	
	FILE *outputFile = fopen(argv[2], "w");
	
	if(inputFile == NULL) //ensure input file exists
	{
		fprintf(stderr, "Error creating output file\n");
		return -1;
	}
	
	//determine input format
	if(format == 0)
	{
		fseek(inputFile, 0, SEEK_END);
		unsigned long size = (unsigned long)ftell(inputFile);
		if((size % 4) == 0)
			format = 32;
		else
			format = 16;
	}
	
	if(format == 16)//utf16 input file
	{
		int retVal = utf16_to_utf32(inputFile, outputFile);
		if(retVal == -1)
		{
			//close streams
			fclose(inputFile);
			fclose(outputFile);
			return -1;
		}				
	}
	else//will only reach here if input is utf32
	{
		int retVal = utf32_to_utf16(inputFile, outputFile);
		if(retVal == -1)
		{
			//close streams
			fclose(inputFile);
			fclose(outputFile);
			return -1;
		}
	}			
	
	//close streams
	fclose(inputFile);
	fclose(outputFile);
	
	return 0;		
}