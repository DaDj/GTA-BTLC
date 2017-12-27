#pragma once

#include "plbase/PluginBase_SA.h"
#include "ListItem_c.h"

class List_c
{
public:
	ListItem_c *last;
	ListItem_c *first;
	unsigned int count;

	List_c(void);
	~List_c(void);

public:
	/**
	* Add new item to the head
	*/
	void AddItem(ListItem_c * pItem);

	/**
	* Remove given item from the list and decrease counter
	*/
	void RemoveItem(ListItem_c * pItem);

	/**
	* Get list head
	*/
	ListItem_c * GetHead(void);

	/**
	* Remove heading item and return it's pointer
	*/
	ListItem_c * RemoveHead(void);

	/**
	* Get next item in a list
	*/
	ListItem_c * GetNext(ListItem_c * pItem);

	/**
	* Get previous item
	*/
	ListItem_c * GetPrev(ListItem_c * pItem);

	/**
	* Get N-th item from list head/tail
	*/
	ListItem_c * GetItemOffset(Bool bFromHead, Int32 iOffset);
};

VALIDATE_SIZE(List_c, 0xC);