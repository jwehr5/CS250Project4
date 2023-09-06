/*
	Jayden Wehr
	FloodFill.h

*/


#pragma once
#ifndef FLOODFILL_H
#define FLOODFILL_H

#include<queue>
#include "OrderedPair.h"
using namespace std;

class FloodFill {

private:
	char** imgPtr;
	int imageSize;

	char** trackerArr;

	/** 
	* deleteImage deletes both the imgPtr and trackerArr arrays.
	* 
	* @pre imgPtr and trackerArr should not be nullptr.
	**/
	void deleteImage();

	/** 
	*  checkAdjacentPixels takes in a pixel and checks all the pixels that are adjacent to it 
	   to see if its the same color.

	*  @param aQueue This is the queue that contains ordered pairs.
	*  @param currentRowIndex This is the index of the row where we are starting.
	*  @param currentColumnIndex This is the index of the column where we are starting.
	*  @param matchColor This is the color that were checking for when we check the adjacent pixels.
	*  @return aQueue containing the ordered pairs that have been enqueued.
	*  @pre imgPtr must be randomly filled with the letters  c, m, y, and k.
	*  @pre trackerArr must be initialized.
	**/
	void checkAdjacentPixels(queue<OrderedPair>& aQueue, int currentRowIndex, int currentColumnIndex, char matchColor);

public:
	FloodFill(int size);
	~FloodFill();

	/** 
	*  generateImage creates a new image of the size that is passed in the parameter. The image will be randomly 
	   filled with the letters c, m, y, and k. The array, trackerArr will also be initialized here.

	*  @param size This will be the size of the image.
	*  @pre imgPtr and trackerArr must not be nullptr.
	**/
	void generateImage(int size);

	/** 
	* displayImage displays the image to the screen.

	* @pre The image must be initialized and be filled with the random letters c, m, y, and k.
	**/
	void displayImage();

	/** 
	* fill takes the image and flood fills starting at a specific row and column index.
	* 
	* @param row This is the row index.
	* @param col This is the column index.
	* @param newColor This is the new color that will be replaced starting at the passed in row and column index.
	* @pre imgPtr and trackerArr must not be nullptr.
	**/
	void fill(int row, int col, char newColor);


};


#endif 
