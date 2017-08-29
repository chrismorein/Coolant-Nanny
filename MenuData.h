#ifndef _sampleMenu_
#define _sampleMenu_
#include "MenuManager.h"
#include <avr/pgmspace.h>

/*
Generated using LCD Menu Builder at http://lcd-menu-bulder.cohesivecomputing.co.uk/.
*/

enum sampleMenuCommandId
{
  mnuCmdBack = 0,
  mnuCmdReading,
  mnuCmdSettings,
  mnuCmdpHCal,
  mnuCmdRfCal,
  mnuCmdT1Secs,
  mnuCmdReset
};

PROGMEM const char sampleMenu_back[] = "Back";
PROGMEM const char sampleMenu_exit[] = "Exit";

PROGMEM const char sampleMenu_2_1[] = "pH Cal";
PROGMEM const char sampleMenu_2_2[] = "Refratometer Ca";
PROGMEM const char sampleMenu_2_3[] = "Timer1 set secs";
PROGMEM const MenuItem sampleMenu_List_2[] = {{mnuCmdpHCal, sampleMenu_2_1}, {mnuCmdRfCal, sampleMenu_2_2}, {mnuCmdT1Secs, sampleMenu_2_3}, {mnuCmdBack, sampleMenu_back}};

PROGMEM const char sampleMenu_1[] = "Get Reading";
PROGMEM const char sampleMenu_2[] = "Settings";
PROGMEM const char sampleMenu_3[] = "Reset Device";
PROGMEM const MenuItem sampleMenu_Root[] = {{mnuCmdReading, sampleMenu_1}, {mnuCmdSettings, sampleMenu_2, sampleMenu_List_2, menuCount(sampleMenu_List_2)}, {mnuCmdReset, sampleMenu_3}, {mnuCmdBack, sampleMenu_exit}};

/*
case mnuCmdReading :
  break;
case mnuCmdpHCal :
  break;
case mnuCmdRfCal :
  break;
case mnuCmdT1Secs :
  break;
case mnuCmdReset :
  break;
*/

/*
<?xml version="1.0"?>
<RootMenu xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema">
  <Config IdPrefix="mnuCmd" VarPrefix="sampleMenu" UseNumbering="false" IncludeNumberHierarchy="false"
          MaxNameLen="15" MenuBackFirstItem="false" BackText="Back" ExitText="Exit" AvrProgMem="true"/>
  <MenuItems>
   <Item Id="Reading" Name="Get Reading"/>
    <Item Id="Settings" Name="Settings">
      <MenuItems>
        <Item Id="pHCal" Name="pH Cal"/>
        <Item Id="RfCal" Name="Refratometer Cal"/>
        <Item Id="T1Secs" Name="Timer1 set secs"/>
      </MenuItems>
    </Item>
   <Item Id="Reset" Name="Reset Device"/>
  </MenuItems>
</RootMenu>
*/
#endif

