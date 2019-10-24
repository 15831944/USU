
#define MAX_ENGL_BUTTONS 9
#define MAX_RUSS_BUTTONS 9
#define BUTTONS 7

// this defines in the program the order the 
// buttons are in in the bitmap.

#define B_DATA_TRANSFER		0
#define B_GRAPH				1
#define B_CAMERAS			2
#define B_SYSTEM_CHECK		3
#define B_CHANGE_LANGUAGE	4
#define B_MAN_SAMPLE		5
#define B_SYS_DIAGNOSIS		6

UINT ButtonOrder[] = {	B_GRAPH,
						B_CAMERAS,
						B_DATA_TRANSFER,
						B_MAN_SAMPLE,
						B_SYS_DIAGNOSIS,
						B_SYSTEM_CHECK,
						B_CHANGE_LANGUAGE };

UINT RES_BUT_STYLE[] ={	NULL, //TBBS_CHECKBOX
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
								IDC_SYS_DIAGNOSIS};
// do not change this order.  It is dependent on the 
// toolbar bitmap.

UINT RES_BUT_IDS[ BUTTONS ] = {	IDS_DATA_TRANSFER, 
								IDS_GRAPH, 
								IDS_CAMERAS, 
								IDS_SYSTEM_CHECK, 
								IDS_CHANGE_LANGUAGE,
								IDS_MAN_SAMPLE,
								IDS_SYS_DIAGNOSIS};
