#pragma once
#include "objects.h"
#include <string>
class Scroll :
	public Object
{
public:
	Scroll(std::string name) : Object(name)
	{}
	Scroll(std::string name, int row, int col) : Object(name, row, col)
	{}
};

class teleportationScroll : public Scroll
{
public:
	teleportationScroll() : Scroll("scroll of teleportation")
	{}
	teleportationScroll(int row, int col) : Scroll("scroll of teleportation", row, col)
	{}
};

class enhanceArmorScroll : public Scroll
{
public:
	enhanceArmorScroll() :Scroll("scroll of enhance armor")
	{}
	enhanceArmorScroll(int row, int col) :Scroll("scroll of improve armor", row, col)
	{}
};

class StrengthScroll : public Scroll
{
public:
	StrengthScroll() : Scroll("scroll of strength")
	{}
	StrengthScroll(int row, int col) : Scroll("scroll of raise strength", row, col)
	{}
};

class enhanceHealthScroll : public Scroll
{
public:
	enhanceHealthScroll() : Scroll("scroll of enhance health")
	{}
	enhanceHealthScroll(int row, int col) : Scroll("scroll of enhance power", row, col)
	{}
};

class enhanceDexterityScroll : public Scroll
{
	public:
	enhanceDexterityScroll() : Scroll("scroll of enhance dexterity")
	{}
	enhanceDexterityScroll(int row, int col) : Scroll("scroll of enhance dexterity", row, col)
	{}
};
