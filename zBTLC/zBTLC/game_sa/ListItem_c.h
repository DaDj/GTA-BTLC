#pragma once

#include "plbase/PluginBase_SA.h"

class ListItem_c
{
protected:
	ListItem_c *next;
	ListItem_c *prev;

protected:
	ListItem_c(void);
	~ListItem_c(void);

	friend class List_c;
};