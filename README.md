# SAMP-SimpleIcons
A simple include that lets you define map icon destroy distance and/or time without changing anything in your code

## Instalation
Place SimpleIcons.inc in your pawno >> includes folder.

Ysi/y_iterate / y_foreach include required. You can get it here : https://github.com/YSI-Data/y_iterate

Add this next to your includes:
```pawn
#include <SimpleIcons>
```
## Usage

```pawn
SetIconDistance(playerid,iconid,float:distance); // specify the distance at which the icon should be removed when player gets near it
SetIconTimeout(playerid,iconid,seconds); // specify the time (in seconds) after which the icon should be removed
```

## Example
```pawn
CMD:spawnpoint(playerid,params[]){ // a simple command to mark the spawn point on players map
  SetPlayerMapIcon(playerid, 45, 0.0,0.0,0.0, 0, 0xD44939FF, MAPICON_GLOBAL_CHECKPOINT);
  SetIconDistance(playerid,45,15.0); // when player gets less than 15.0 m from the 0.0,0.0,0.0 coordinates, the icon will be automatically removed
  SetIconDistance(playerid,45,60); // After 60 seconds the icon will be automatically removed
  SendClientMessage(playerid,-1,"Spawn point successfully marked");
}
```
