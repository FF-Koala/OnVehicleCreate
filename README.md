OnVehicleCreate
===============

*	Author:		Koala
*	Title:		Simple OnVehicleCreate, OnVehicleDestroy callback
*	Version:	0.1
*	Description:
*
*	This include gives you 2 usefull callbacks:

*	public OnVehicleCreate(modelid, cx, cy, cz, cangle, vehid)
*	public OnVehicleDestroy(modelid, cx, cy, cz, vehid, succes, sremove)

	I also made a replacement for the classic "for(new i; i<MAX_VEHICLES; i++)".

	If you use the foreach inc, this inc automatically creates an array with all the vehicles created.
	You can then simply use it like:
	
	foreach(Vehicle, i)
	{
		ChangeVehicleColor(i, random(256), random(256));
	}

	If you don't use the foreach inc, then this inc will automatically create an var wich contains the total number of ehicles created.
	You can then simply use it like:

	for(new i; i<OVC_TC; i++;)
	{
		ChangeVehicleColor(i, random(256), random(256));
	}

	This was first seen at Gta-Mp.ro

 Credits: Y_Less for "foreach"

