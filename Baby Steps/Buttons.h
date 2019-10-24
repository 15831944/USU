#define BUTTONS 9

// this defines in the program the order the 
// buttons are in in the bitmap.

#define B_FILE_NEW			0
#define B_FILE_OPEN			1
#define B_FILE_SAVE			2
#define B_PLAY				3
#define B_PAUSE				4
#define B_STOP				5
#define B_START_STATE		6
#define B_GOAL_STATE		7
#define B_OBSTACLE			8

UINT ButtonOrder[] = {	B_FILE_NEW,
						B_FILE_OPEN,
						B_FILE_SAVE,
						B_PLAY,
						B_PAUSE,
						B_STOP,
						B_START_STATE,
						B_GOAL_STATE,
						B_OBSTACLE };

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

UINT RES_BUT_ID[ BUTTONS ] = {	ID_FILE_NEW, 
								ID_FILE_OPEN, 
								ID_FILE_SAVE, 
								ID_PLAY, 
								ID_PAUSE,
								ID_STOP,
								ID_START_STATE,
								ID_GOAL_STATE,
								ID_OBSTACLE };

