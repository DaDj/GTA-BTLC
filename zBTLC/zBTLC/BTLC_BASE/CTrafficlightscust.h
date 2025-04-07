#pragma once
class CTrafficlights
{
public:
	CTrafficlights();

	/// <summary>Changes the Size of the RED/GREEN/ORANGE Polygon of Trafficlights</summary>
	static void Set_polygon_size(int size);

	/// <summary>Sets all the Trafficlightsmodels to the ones given in the function</summary>
	static	void Set_Trafficlight_models();

	/// <summary>Position  of PED TRAFFICLIGHTS</summary>
	static void Set_Trafficlight_PED_COORD();

public:
	struct data
	{
		char	*name;
		int		adress;
	};

	data *entrys;
};


