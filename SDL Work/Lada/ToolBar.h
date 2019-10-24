// This is Version 1.0 PLEASE DOCUMENT CHANGES
#include "LadaStrings.h"

#define BUTTONS 11

// this defines in the program the order the 
// buttons are in in the bitmap.

#define B_DATA_TRANSFER		0
#define B_GRAPH				1
#define B_CAMERAS			2
#define B_SYSTEM_CHECK		3
#define B_CHANGE_LANGUAGE	4
#define B_MAN_SAMPLE		5
#define B_SYSTEM_CONTROLS	6
#define B_HELP				7
#define B_HISTORY			8
#define B_ERRORS			9
#define B_EXIT				10


UINT ButtonOrder[] = {	B_GRAPH,
						B_CAMERAS,
						B_DATA_TRANSFER,
						B_MAN_SAMPLE,
						B_SYSTEM_CONTROLS,
						B_SYSTEM_CHECK,
						B_HISTORY,
						B_ERRORS,
						B_CHANGE_LANGUAGE,
						B_HELP,
						B_EXIT };

UINT RES_BUT_STYLE[] ={	NULL, //TBBS_CHECKBOX
						NULL, 
						NULL,
						NULL, 
						NULL,
						NULL,
						NULL,
						NULL,
						NULL,
						NULL,
						NULL };

// do not change this order.  It is dependent on the 
// toolbar bitmap.
UINT RES_BUT_ID[ BUTTONS ] = {	IDC_DATA_TRANSFER, 
								IDC_GRAPH, 
								IDC_CAMERAS, 
								IDC_SYSTEM_CHECK, 
								IDC_CHANGE_LANGUAGE,
								IDC_MAN_SAMPLE,
								IDC_SYSTEM_CONTROLS,
								IDC_HELP_BUTTON,
								IDC_HISTORY,
								IDC_ERRORS,
								IDC_EXIT};
// do not change this order.  It is dependent on the 
// toolbar bitmap.

UINT RES_BUT_IDS[ BUTTONS ] = {	IDS_D3, 
								IDS_D1, 
								IDS_D2, 
								IDS_D6, 
								IDS_D8,
								IDS_D4,
								IDS_D5,
								IDS_D7,
								IDS_D9,
								IDS_D10,
								IDS_D11};
