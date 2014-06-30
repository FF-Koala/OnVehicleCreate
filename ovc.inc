/*
*	Author:		Koala
*	Title:		Simple OnVehicleCreate, OnVehicleDestroy callback
*	Version:	0.1
*	Description:
*
*	This include gives you 2 usefull callbacks:
*	//
*	public OnVehicleCreate(modelid, cx, cy, cz, cangle, vehid)
*	public OnVehicleDestroy(modelid, cx, cy, cz, vehid, succes, sremove)
*	//
*	I also made a replacement for the classic "for(new i; i<MAX_VEHICLES; i++)".
*
*	If you use the foreach inc, this inc automatically creates an array with all the vehicles created.
*	You can then simply use it like:
*	
*	foreach(Vehicle, i)
*	{
*		ChangeVehicleColor(i, random(256), random(256));
*	}
*
*	If you don't use the foreach inc, then this inc will automatically create an var wich contains the total number of vehicles created.
*	You can then simply use it like:
*
*	for(new i; i<OVC_TC; i++;)
*	{
*		ChangeVehicleColor(i, random(256), random(256));
*	}
*
*	This was first seen at Gta-Mp.ro
*
* Credits: Y_Less for "foreach"
*
*/

#include <a_samp>

#if defined _OVC_INCLUDE
	#endinput
#endif
#define _OVC_INCLUDE

#if defined _FOREACH_LOCAL_VERSION
	#define _OVC_UseForeach
#endif

#if defined _OVC_UseForeach
	#if !defined Iter_Add
		#if defined Itter_Add
			#define Iter_Add Itter_Add
		#endif
	#endif
	#if !defined Iter_SafeRemove
		#if defined Itter_SafeRemove
			#define Iter_SafeRemove Itter_SafeRemove
		#endif
	#endif
#endif

forward OnVehicleCreate(modelid, Float:cx, Float:cy, Float:cz, Float:cangle, vehid);
/* native OnVehicleCreate(modelid, cx, cy, cz, cangle, vehid) */
forward OnVehicleDestroy(modelid, Float:cx, Float:cy, Float:cz, vehid, succes, saferemove);
/* native OnVehicleDestroy(modelid, cx, cy, cz, vehid, succes) */

new
	OVC_vehid,
	#if defined _OVC_UseForeach
		Iterator:Vehicle<MAX_VEHICLES>;
	#else
		OVC_TC;
	#endif

//Vehicle Creates
stock OVC_CreateVehicle(modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, respawn_delay)
{
	OVC_vehid=CreateVehicle(modelid, x, y, z, angle, color1, color2, respawn_delay);
	OnVehicleCreate(modelid, x, y, z, angle, OVC_vehid);
	#if defined _OVC_UseForeach
		Iter_Add(Vehicle, OVC_vehid);
	#else
		OVC_TC++;
	#endif
	return OVC_vehid;
}
stock OVC_AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:angle, color1, color2)
{
	OVC_vehid=AddStaticVehicle(modelid, spawn_x, spawn_y, spawn_z, angle, color1, color2);
	OnVehicleCreate(modelid, spawn_x, spawn_y, spawn_z, angle, OVC_vehid);
	#if defined _OVC_UseForeach
		Iter_Add(Vehicle, OVC_vehid);
	#else
		OVC_TC++;
	#endif
	return OVC_vehid;
}
stock OVC_AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:angle, color1, color2, respawn_delay)
{
	OVC_vehid=AddStaticVehicleEx(modelid, spawn_x, spawn_y, spawn_z, angle, color1, color2, respawn_delay);
	OnVehicleCreate(modelid, spawn_x, spawn_y, spawn_z, angle, OVC_vehid);
	#if defined _OVC_UseForeach
		Iter_Add(Vehicle, OVC_vehid);
	#else
		OVC_TC++;
	#endif
	return OVC_vehid;
}
#if defined _ALS_CreateVehicle
	#undef CreateVehicle
#else
	#define _ALS_CreateVehicle
#endif
#if defined _ALS_AddStaticVehicle
	#undef AddStaticVehicle
#else
	#define _ALS_AddStaticVehicle
#endif
#if defined _ALS_AddStaticVehicleEx
	#undef AddStaticVehicleEx
#else
	#define _ALS_AddStaticVehicleEx
#endif
#define CreateVehicle OVC_CreateVehicle
#define AddStaticVehicle OVC_AddStaticVehicle
#define AddStaticVehicleEx OVC_AddStaticVehicleEx

//Vehicle destroys
stock OVC_DestroyVehicle(vehicleid)
{
	new Float:OVC_Dx, Float:OVC_Dy, Float:OVC_Dz, OVC_saferemove=-1, OVC_modelid=GetVehicleModel(vehicleid);
	GetVehiclePos(vehicleid, OVC_Dx, OVC_Dy, OVC_Dz);
	OVC_vehid=DestroyVehicle(vehicleid);
	#if defined _OVC_UseForeach
		Iter_SafeRemove(Vehicle, vehicleid, OVC_saferemove);
	#else
		if(vehicleid==OVC_TC)OVC_TC--;
	#endif
	OnVehicleDestroy(OVC_modelid, OVC_Dx, OVC_Dy, OVC_Dz, vehicleid, OVC_vehid, OVC_saferemove);
	return OVC_vehid;
}
#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif
#define DestroyVehicle OVC_DestroyVehicle