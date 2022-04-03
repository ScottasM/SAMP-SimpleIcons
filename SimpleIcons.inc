// by Scottas https://github.com/ScottasM/SAMP-SimpleIcons
#include <a_samp>
#include <YSI\y_iterate>

#define MAX_ICONS 101

enum IconEnum {
    bool:created[MAX_ICONS],
    Float:IposX[MAX_ICONS],
    Float:IposY[MAX_ICONS],
    Float:IposZ[MAX_ICONS],
    Float:Idist[MAX_ICONS],
    ITime[MAX_ICONS],
};

new Iterator:Icons[MAX_PLAYERS]<100>;

new IconData[MAX_PLAYERS][IconEnum];

forward SetIconDistance(playerid,iconid,Float:distance);
forward SetIconTimeout(playerid,iconid,seconds);


public OnGameModeInit(){
    SetTimer("CheckIcons",1000,true);
    #if defined sp_OnGameModeInit
        sp_OnGameModeInit();
    #endif
    return 1;
}

stock sp_SetPlayerMapIcon(playerid, iconid, Float:x, Float:y, Float:z, markertype, color, style = MAPICON_LOCAL){
    DeleteSimpleIcon(playerid,iconid);
    IconData[playerid][created][iconid]= true;
    IconData[playerid][IposX][iconid] = x;
    IconData[playerid][IposY][iconid] = y;
    IconData[playerid][IposZ][iconid] = z;
    Iter_Add(Icons[playerid],iconid);

    return SetPlayerMapIcon(playerid, iconid, Float:x, Float:y, Float:z, markertype, color, style = MAPICON_LOCAL);
}

stock sp_RemovePlayerMapIcon(playerid, iconid){

    Iter_Remove(Icons[playerid],iconid);
    IconData[playerid][created][iconid] = false;
    IconData[playerid][Idist][iconid] = 0.0;
    IconData[playerid][ITime][iconid] = 0;
    RemovePlayerMapIcon(playerid, iconid);
    
    return RemovePlayerMapIcon(playerid, iconid);
}

public OnPlayerDisconnect(playerid,reason){
    for(new i = 0;i<MAX_ICONS;i++){
        DeleteSimpleIcon(playerid,i);
    }
    #if defined sp_OnPlayerDisconnect
        sp_OnPlayerDisconnect(playerid,reason);
    #endif
    return 1;
}

public SetIconDistance(playerid,iconid,Float:distance){
    if(IconData[playerid][created][iconid] == false || distance < 0)
        return 0;
    IconData[playerid][Idist][iconid] = distance;
    return 1;
}

public SetIconTimeout(playerid,iconid,seconds){
    if(IconData[playerid][created][iconid] == false || seconds < 0)
        return 0;
    if(seconds == 0)
        IconData[playerid][ITime][iconid] = 0;
    else IconData[playerid][ITime][iconid] = gettime() + seconds;
    
    return 1; 
}

forward CheckIcons();
public CheckIcons(){
    foreach(new i : Player){
        foreach(new j : Icons[i]){
            if(IconData[i][ITime][j] > 0 && IconData[i][ITime][j] <= gettime()){
                j = DeleteSimpleIcon(i,j);
                continue;
            }
            if(IconData[i][Idist][j] > 0){
                if(GetPlayerDistanceFromPoint(i,IconData[i][IposX][j],IconData[i][IposY][j],IconData[i][IposZ][j]) <= IconData[i][Idist][j]){
                    j = DeleteSimpleIcon(i,j);
                    continue;
                }
            }
        }
    }
}

DeleteSimpleIcon(playerid,id){
    new prev;
    Iter_SafeRemove(Icons[playerid],id,prev);
    IconData[playerid][created][id] = false;
    IconData[playerid][Idist][id] = 0.0;
    IconData[playerid][ITime][id] = 0;
    RemovePlayerMapIcon(playerid, id);
    return prev;
}

#if defined _ALS_SetPlayerMapIcon
	#undef SetPlayerMapIcon
#else
	#define _ALS_SetPlayerMapIcon
#endif
#define SetPlayerMapIcon sp_SetPlayerMapIcon


#if defined _ALS_RemovePlayerMapIcon
	#undef RemovePlayerMapIcon
#else
	#define _ALS_RemovePlayerMapIcon
#endif
#define RemovePlayerMapIcon sp_RemovePlayerMapIcon


#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit sp_OnGameModeInit

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect sp_OnPlayerDisconnect

#if defined sp_OnGameModeInit
	forward sp_OnGameModeInit();
#endif

#if defined sp_OnPlayerDisconnect
	forward sp_OnPlayerDisconnect();
#endif
