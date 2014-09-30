/** CS515 Assignment3
	File: image.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 12/13/13
	Collaboration Declaration: none
	*/


#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void deleteArr(int** arr, bool isRotArr);
void outputNewImage(string outputFileName, int ** image, bool isRotArr);
int** makeNegativeImage(int** original);
int** makeRotatedImage(int** original);
int** makeFlippedImage(int** original);

string format;
int width = 0;
int height = 0;	
int maxValue = 0;

int main(int argc, char ** argv)
{
	if(argc != 5)
	{
		cout << "Usage: image <input image> <neg image> <flip image> <rotate image>" << endl;
		return -1;
	}

	ifstream inputFile(argv[1]);

	if(!inputFile)
	{
		cout << "Error opening input file!";
		return -1;
	}

	string negImageName = argv[2];
	string flipImageName = argv[3];
	string rotateImageName = argv[4];
	
	inputFile >> format >> width >> height >> maxValue;

	if(format != "P2")
	{
		cout << "Incorrect Format. Must be P2 format." << endl;
		return -1;
	}

	if(maxValue > 255)
	{
		cout << "Max grey value is over 255." << endl;
		return -1;
	}

	int ** originalArray;

	originalArray = new int*[height];

    for( int i = 0 ; i < height ; i++ )
		originalArray[i] = new int[width];
		
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
			inputFile >> originalArray[i][j];

	int ** negArray = makeNegativeImage(originalArray);
	int ** flipArray = makeFlippedImage(originalArray);
	int ** rotArray = makeRotatedImage(originalArray);

	outputNewImage(negImageName, negArray, false);	
	outputNewImage(flipImageName, flipArray, false);
	outputNewImage(rotateImageName, rotArray, true);

	deleteArr(originalArray, false);
	deleteArr(negArray, false);
	deleteArr(flipArray, false);
	deleteArr(rotArray, true);

	return 0;
}

void deleteArr(int** arr, bool isRotArr)
{
	//cout << "deleting!!" << endl;

	if(isRotArr)
	{
		for (int i=0; i < width; i++)
			delete [] arr[i];
	}
	else
	{
		for (int i=0; i < height; i++)
			delete [] arr[i]; 
	}
    
    delete [] arr; 
}

void outputNewImage(string outputFileName, int ** image, bool isRotArr)
{
	//cout << "Outputting!!" << endl;

	ofstream outputFile(outputFileName.c_str());

	outputFile << format;
	outputFile << '\n';

	if(isRotArr)
	{
		outputFile << height;
		outputFile << ' ';
		outputFile << width;
	}
	else
	{
		outputFile << width;
		outputFile << ' ';
		outputFile << height;
	}
	outputFile << '\n';
	outputFile << maxValue;
	outputFile << '\n';

	if(isRotArr)
	{
		for(int i = 0; i < width; i++)
		{
			for(int j = 0; j < height; j++)
			{
				outputFile << image[i][j];
				outputFile << ' ';
			}
			outputFile << '\n';
		}
	}
	else
	{
		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				outputFile << image[i][j];
				outputFile << ' ';
			}
			outputFile << '\n';
		}
	}
}

int** makeNegativeImage(int** original)
{
	//cout << "Negative!!" << endl;

	int ** negArray;
	negArray = new int*[height];

    for( int i = 0 ; i < height ; i++ )
		negArray[i] = new int[width];

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			negArray[i][j] = maxValue - original[i][j];
		}
	}

	return negArray;
}

int** makeFlippedImage(int** original)
{
	//cout << "Flipping!!" << endl;

	int ** flipArray;
	flipArray = new int*[height];

    for( int i = 0 ; i < height ; i++ )
		flipArray[i] = new int[width];

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			flipArray[i][(width - 1) - j] = original[i][j];
		}
	}

	return flipArray;
}

int** makeRotatedImage(int** original)
{
	//cout << "Rotating!!" << endl;

	int ** rotArray;
	rotArray = new int*[width];

    for( int i = 0 ; i < width; i++ )
		rotArray[i] = new int[height];

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			rotArray[j][(height - 1) - i] = original[i][j];
		}
	}

	return rotArray;
}