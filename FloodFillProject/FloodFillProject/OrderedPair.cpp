/*
	Jayden Wehr
	OrderedPair.cpp

*/


#include<iostream>
#include "OrderedPair.h"
using namespace std;

OrderedPair::OrderedPair(int row, int col) {

	this->row = row;
	this->column = col;

}

void OrderedPair::setRow(int newRow) {

	row = newRow;
}

int OrderedPair::getRow() {

	return row;
}

void OrderedPair::setColumn(int newCol) {

	column = newCol;
}

int OrderedPair::getColumn() {

	return column;
}