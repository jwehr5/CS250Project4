/*
	Jayden Wehr
	FloodFill.cpp

*/


#include<iostream>
#include "FloodFill.h"
#include <cstdlib>
#include <ctime>
#include <queue>
#include "OrderedPair.h"

using namespace std;

FloodFill::FloodFill(int size) {

	//Creating an image of the specified size
	imgPtr = new char* [size];
	for (int i = 0; i < size; i++) {
		imgPtr[i] = new char[size];
	}

	//Create the tracker array which will be used to keep track of all processed pixels
	trackerArr = new char* [size];
	for (int i = 0; i < size; i++) {
		trackerArr[i] = new char[size];
	}

	imageSize = size;
}

FloodFill::~FloodFill() {

	deleteImage();
}

void FloodFill::deleteImage() {
	
	//Delete the image
	if (imgPtr != nullptr) {

		for (int i = 0; i < imageSize; i++) {
			delete imgPtr[i];
		}
	}

	delete[] imgPtr;

	//Delete the tracker array
	if (trackerArr != nullptr) {

		for (int i = 0; i < imageSize; i++) {
			delete trackerArr[i];
		}
	}

	delete [] trackerArr;
}

void FloodFill::generateImage(int size) {

	//Delete the exisiting board before creating a new one
	deleteImage();

	//Create the new image
	imgPtr = new char* [size];
	for (int i = 0; i < size; i++) {
		imgPtr[i] = new char[size];
	}

	//Create a new tracker array
	trackerArr = new char* [size];
	for (int i = 0; i < size; i++) {
		trackerArr[i] = new char[size];
	}

	imageSize = size;


	//Randomly fill the board with the characters c m y and k
	srand(time(NULL));
	int randomInt;

	for (int i = 0; i < imageSize; i++) {
		for (int j = 0; j < imageSize; j++) {
			randomInt = rand() % 4 + 1;

			switch (randomInt) {
				case 1: 
					imgPtr[i][j] = 'c'; 
					break;
				case 2: 
					imgPtr[i][j] = 'm'; 
					break;
				case 3: 
					imgPtr[i][j] = 'y'; 
					break;
				case 4: 
					imgPtr[i][j] = 'k'; 
					break;
			}

		}
	}
	

	//Fill the the tracker array with blanks indicated by *
	for (int i = 0; i < imageSize; i++) {
		for (int j = 0; j < imageSize; j++) {
			trackerArr[i][j] = '*';
		}
	}

}

void FloodFill::displayImage() {

	//Display the column numbers
	cout << "  ";
	int tracker = 0;
	for (int i = 0; i < imageSize; i++, tracker++) {

		if (tracker == 10) {
			tracker = 0;
		}

		cout << tracker << " ";
	}

	cout << endl;

	//Display the contents of the image along with the row numbers
	tracker = 0;
	for (int i = 0; i < imageSize; i++, tracker++) {

		if (tracker == 10) {
			tracker = 0;
		}

		cout << tracker << " ";
		for (int j = 0; j < imageSize; j++) {
			cout << imgPtr[i][j] << " ";

		}

		cout << endl;
	}

}

void FloodFill::fill(int row, int col, char newColor) {

	cout << "Beginning at [" << row << "] [" << col << "] I will flood fill and replace " 
		<< imgPtr[row][col] << " with " << newColor << endl;

	//Create the queue
	queue<OrderedPair> aQueue;
	
	char matchColor = imgPtr[row][col];

	//Enqueue the pixel and mark is processed in the tracker array
	OrderedPair op = OrderedPair(row, col);
	aQueue.push(op);
	trackerArr[row][col] = 'X'; //Processed pixels will marked with an X

	while (!aQueue.empty()) {

		int currentRowIndex = aQueue.front().getRow();
		int currentColumnIndex = aQueue.front().getColumn();
		char currentPixel = imgPtr[currentRowIndex][currentColumnIndex];

		aQueue.pop();

		imgPtr[currentRowIndex][currentColumnIndex] = newColor;


		checkAdjacentPixels(aQueue, currentRowIndex, currentColumnIndex, matchColor);


	}

}

void FloodFill::checkAdjacentPixels(queue<OrderedPair>& aQueue, int currentRowIndex, int currentColumnIndex, char matchColor) {

	int shiftedRowIndex = currentRowIndex;
	int shiftedColumnIndex = currentColumnIndex;

	/* We will check the adjacent pixels clockwise starting with the one above. 
	   We will also make sure that we do not go out of bounds.
	*/
	shiftedRowIndex--;
	if (shiftedRowIndex >= 0 && trackerArr[shiftedRowIndex][shiftedColumnIndex] != 'X' &&  imgPtr[shiftedRowIndex][shiftedColumnIndex] == matchColor) {

		OrderedPair op = OrderedPair(shiftedRowIndex, shiftedColumnIndex);
		aQueue.push(op);
		trackerArr[shiftedRowIndex][shiftedColumnIndex] = 'X';

	}

	//Reset the shiftedRowIndex and shiftedColumnIndex
	shiftedRowIndex = currentRowIndex;
	shiftedColumnIndex = currentColumnIndex;

	//Check the pixel in the top right diagonal
	shiftedRowIndex--;
	shiftedColumnIndex++;
	if (shiftedRowIndex >= 0 && shiftedColumnIndex < imageSize && trackerArr[shiftedRowIndex][shiftedColumnIndex] != 'X' 
		&& imgPtr[shiftedRowIndex][shiftedColumnIndex] == matchColor) {

		OrderedPair op = OrderedPair(shiftedRowIndex, shiftedColumnIndex);
		aQueue.push(op);
		trackerArr[shiftedRowIndex][shiftedColumnIndex] = 'X';

	}

	//Reset the shiftedRowIndex and shiftedColumnIndex
	shiftedRowIndex = currentRowIndex;
	shiftedColumnIndex = currentColumnIndex;


	//Check the pixel to the right of currentPixel
	shiftedColumnIndex++;
	if (shiftedColumnIndex < imageSize && trackerArr[shiftedRowIndex][shiftedColumnIndex] != 'X' && imgPtr[shiftedRowIndex][shiftedColumnIndex] == matchColor) {

		OrderedPair op = OrderedPair(shiftedRowIndex, shiftedColumnIndex);
		aQueue.push(op);
		trackerArr[shiftedRowIndex][shiftedColumnIndex] = 'X';

	}

	//Reset the shiftedRowIndex and shiftedColumnIndex
	shiftedRowIndex = currentRowIndex;
	shiftedColumnIndex = currentColumnIndex;

	//Check the pixel in the lower right diagonal
	shiftedRowIndex++;
	shiftedColumnIndex++;
	if (shiftedRowIndex < imageSize && shiftedColumnIndex < imageSize && trackerArr[shiftedRowIndex][shiftedColumnIndex] != 'X' 
		&& imgPtr[shiftedRowIndex][shiftedColumnIndex] == matchColor) {

		OrderedPair op = OrderedPair(shiftedRowIndex, shiftedColumnIndex);
		aQueue.push(op);
		trackerArr[shiftedRowIndex][shiftedColumnIndex] = 'X';

	}

	//Reset the shiftedRowIndex and shiftedColumnIndex
	shiftedRowIndex = currentRowIndex;
	shiftedColumnIndex = currentColumnIndex;

	//Check the pixel directly below
	shiftedRowIndex++;
	if (shiftedRowIndex < imageSize && trackerArr[shiftedRowIndex][shiftedColumnIndex] != 'X' && imgPtr[shiftedRowIndex][shiftedColumnIndex] == matchColor) {

		OrderedPair op = OrderedPair(shiftedRowIndex, shiftedColumnIndex);
		aQueue.push(op);
		trackerArr[shiftedRowIndex][shiftedColumnIndex] = 'X';

	}

	//Reset the shiftedRowIndex and shiftedColumnIndex
	shiftedRowIndex = currentRowIndex;
	shiftedColumnIndex = currentColumnIndex;

	//Check the pixel in the lower left diagonal
	shiftedRowIndex++;
	shiftedColumnIndex--;
	if (shiftedRowIndex < imageSize && shiftedColumnIndex >= 0 && trackerArr[shiftedRowIndex][shiftedColumnIndex] != 'X'
		&& imgPtr[shiftedRowIndex][shiftedColumnIndex] == matchColor) {

		OrderedPair op = OrderedPair(shiftedRowIndex, shiftedColumnIndex);
		aQueue.push(op);
		trackerArr[shiftedRowIndex][shiftedColumnIndex] = 'X';

	}

	//Reset the shiftedRowIndex and shiftedColumnIndex
	shiftedRowIndex = currentRowIndex;
	shiftedColumnIndex = currentColumnIndex;

	//Check the pixel directly to the left
	shiftedColumnIndex--;
	if (shiftedColumnIndex >= 0 && trackerArr[shiftedRowIndex][shiftedColumnIndex] != 'X' && imgPtr[shiftedRowIndex][shiftedColumnIndex] == matchColor) {

		OrderedPair op = OrderedPair(shiftedRowIndex, shiftedColumnIndex);
		aQueue.push(op);
		trackerArr[shiftedRowIndex][shiftedColumnIndex] = 'X';

	}

	//Reset the shiftedRowIndex and shiftedColumnIndex
	shiftedRowIndex = currentRowIndex;
	shiftedColumnIndex = currentColumnIndex;

	//Check the pixel in the upper left diagonal
	shiftedRowIndex--;
	shiftedColumnIndex--;
	if (shiftedRowIndex >= 0 && shiftedColumnIndex >= 0 && trackerArr[shiftedRowIndex][shiftedColumnIndex] != 'X'
		&& imgPtr[shiftedRowIndex][shiftedColumnIndex] == matchColor) {

		OrderedPair op = OrderedPair(shiftedRowIndex, shiftedColumnIndex);
		aQueue.push(op);
		trackerArr[shiftedRowIndex][shiftedColumnIndex] = 'X';

	}

}