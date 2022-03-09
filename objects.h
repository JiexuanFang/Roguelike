#ifndef OBJECTS_H
#define OBJECTS_H
#include<string>
const int MAXROW = 18;
const int MAXCOL = 70;
const int MAXMONSTERS = 26;


class Object
{
public: 
	Object(std::string name);
	Object(std::string name, int row, int col);
	virtual ~Object();
	std::string getName() const;
	int getRow() const;
	int getCol() const;
	void setPos(int row, int col);
private:
	std::string m_name;
	int m_row;
	int m_col;
};

class GoldenIdol : public Object
{
public:
	GoldenIdol() : Object("the golden idol")
	{}
	GoldenIdol(int row, int col) : Object("the golden idol", row, col)
	{}
	~GoldenIdol()
	{}
};

class Stair : public Object
{
public:
	Stair() : Object("stair")
	{}
	Stair(int row, int col) : Object("stair", row, col)
	{}
	~Stair()
	{}
};

#endif


