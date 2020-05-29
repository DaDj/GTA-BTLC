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
	ListItem_c * GetItemOffset(bool bFromHead, int iOffset);
};


template <
	typename ItemType
>
class TList_c : public List_c
{
public:
	ItemType * GetHead(void) {
		return static_cast<ItemType *>(List_c::GetHead());
	}

	ItemType * RemoveHead(void) {
		return static_cast<ItemType *>(List_c::RemoveHead());
	}

	ItemType * GetNext(ItemType * pItem) {
		return static_cast<ItemType *>(List_c::GetNext(pItem));
	}

	ItemType * GetPrev(ItemType * pItem) {
		return static_cast<ItemType *>(List_c::GetPrev(pItem));
	}

	ItemType * GetItemOffset(bool bFromHead, int iOffset) {
		return static_cast<ItemType *>(List_c::GetItemOffset(bFromHead, iOffset));
	}
};


VALIDATE_SIZE(List_c, 0xC);