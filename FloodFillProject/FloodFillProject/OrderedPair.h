/*
	Jayden Wehr
	OrderedPair.h

*/


#pragma once

#ifndef ORDEREDPAIR_H
#define ORDEREDPAIR_H


class OrderedPair {
	
private:
	int row;
	int column;

public:

	OrderedPair(int row, int col);
	void setRow(int newRow);
	int getRow();
	void setColumn(int newCol);
	int getColumn();


};


#endif 

