#include"objects.h"
#include<iostream>
using namespace std;

Object::Object(string name) : m_name(name),m_row(-1), m_col(-1)
{

}

Object::Object(string name, int row, int col): m_name(name), m_row(row), m_col(col)
{

}

Object::~Object()
{
}

string Object::getName() const
{
	return m_name;
}

int Object::getRow() const
{
	return m_row;
}

int Object::getCol() const
{
	return m_col;
}

void Object::setPos(int row, int col)
{
	m_row = row;
	m_col = col;
}
