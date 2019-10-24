// used in LadaTest.cpp
#define IL_WATER_PUMPED	26  // see note in "questions about checkout.doc" regarding this...

#define VOLTAGE_1		9	//Correct DC12Vn_V
#define CURRENT_1		10	//Correct DC12Vc_I
#define VOLTAGE_2		11	//Correct DC12Vn_V
#define CURRENT_2		12	//Correct DC12Vn_I
#define VOLTAGE_3		13	//Correct DC16V_V
#define CURRENT_3		14	//Correct DC16V_I
#define VOLTAGE_4		15	//Correct DC5V_V
#define CURRENT_4		16	//Correct DC5V_I
#define VOLTAGE_5		45
#define CURRENT_5		46

#define IAirTemp		50	//Not Sure	CA_Intk_T
#define IBallTemp		49	//Not Sure	CA_Blst_T
#define ILeaf1			51	//Not Sure	CA_Top_T
#define ILeaf2			52	//Not Sure	CA_Mid_T
#define ILeaf3			53	//Not Sure	CA_Bot_T
#define ILeaf4			54	//Not Sure	CA_Ref_T
#define ILeafSurface	55	//Not Sure	CA_Leaf_T
#define IHumOut			48	//Not Sure	CA_RH

#define	CA_TOP_L		94	//Pretty Sure	CA_Top_L
#define CA_MID_L		95	//Pretty Sure	CA_Mid_L
#define CA_BOT_L		96	//Pretty Sure	CA_Bot_L
#define CA_O2_1			89	//Pretty Sure	CA_O2_1
#define CA_O2_2			90	//Pretty Sure	CA_O2_2
#define CA_O2_3			91	//Pretty Sure	CA_O2_3
#define CA_O2_4			92	//Pretty Sure	CA_O2_4

#define ABS_TENSIOMETER	97	//Pretty Sure	ARefPress
#define	TENSIOMETER_1	98	//Pretty Sure	ATensio_1
#define	TENSIOMETER_2	99	//Pretty Sure	ATensio_2
#define	TENSIOMETER_3	100	//Pretty Sure	ATensio_3
#define	TENSIOMETER_4	101	//Pretty Sure	ATensio_4


#define ISat1			80	//Pretty Sure	CA_SMP1_T
#define ISat2			81	//Pretty Sure	CA_SMP2_T
#define ISat3			82	//Pretty Sure	CA_SMP3_T
#define ISat4			83	//Pretty Sure	CA_SMP4_T
#define ISat5			84	//Pretty Sure	CA_SMP5_T
#define ISat6			85	//Pretty Sure	CA_SMP6_T
#define ISat7			86	//Pretty Sure	CA_SMP7_T
#define ISat8			87	//Pretty Sure	CA_SMP8_T

#define IDTemp1			72	//diff. temperature	CA_SMP1dT
#define IDTemp2			73	//Pretty Sure	CA_SMP2dT
#define IDTemp3			74	//Pretty Sure	CA_SMP3dT
#define IDTemp4			75	//Pretty Sure	CA_SMP4dT
#define IDTemp5			76	//Pretty Sure	CA_SMP5dT
#define IDTemp6			77	//Pretty Sure	CA_SMP6dT
#define IDTemp7			78	//Pretty Sure	CA_SMP7dT
#define IDTemp8			79	//Pretty Sure	CA_SMP8dT

#define ITemp1			56	//initial temp	CA_SMP1iT
#define ITemp2			57	//Pretty Sure	CA_SMP2iT
#define ITemp3			58	//Pretty Sure	CA_SMP3iT
#define ITemp4			59	//Pretty Sure	CA_SMP4dT
#define ITemp5			60	//Pretty Sure	CA_SMP5dT
#define ITemp6			61	//Pretty Sure	CA_SMP6dT
#define ITemp7			62	//Pretty Sure	CA_SMP7iT
#define ITemp8			63	//Pretty Sure	CA_SMP8iT


// used in commoperations.cpp
#define CHAMBER_1_CONTROL		115	//	AManCtrl	manual control input location, chamber A
#define CHAMBER_1_STATUS		121 //  AMnCtBits
#define A_READ_20_MN			111	//	ARead20mn	used to set the frequency of final storage collection
#define A_WRITE_20_MN			113	//	AWrite20m
#define A_READ_1_HR				112	//	ARead1Hr
#define A_WRITE_1_HR			114	//	AWrite1Hr
#define A_WTR_INTVL				108 //  AWtrIntvl
// used in paramdlg.cpp
#define MOISTURE_CONTROL_A		102 //  GCASatLvl
#define LIGHT_ON_TIME_A			109	//	ALightsOn
#define	LIGHT_OFF_TIME_A		110	//	ALightsOff


#define MOISTURE_CONTROL_B		22	//	WatVolMul
#define LIGHT_ON_TIME_B			109	//	ALightsOn
#define	LIGHT_OFF_TIME_B		110	//	ALightsOff
#define CHAMBER_2_CONTROL		100 // THIS IS WRONG  ""							  chamber B


// used in wetup.cpp
/*
102 TotVolReq 1 1 1
103 CAVolNeed 1 1 1
104 CATotVolP 1 4 3
105 CA_Pump_L 1 5 5
106 CA_PCount 1 1 1
107 ASMPCount 1 5 3
108 ARead20mn 1 1 1
109 AWrite20m 1 1 1
110 TotWtrInt 1 1 1
111 TotWtrCnt 1 1 2
112 PumpVolum 1 1 1
*/

#define IL_VOLUME_PUMPED		104	// CATotVolP	volume pumped since wetup has started, 
									//				only gets incremented at the end of every ten 
									//				minute interval
#define IL_CUR_VOL_PUMPED		105	// CA_Pump_L	gets incremented during the interval,
									//				reset at the end of every interval
#define	IL_N_ELAPSED_INTERVALS	111 // TotWtrCnt	this is how we count number of intervals
#define IL_TOTAL_TO_PUMP		102	// TotVolReq	this should be set initially 
#define IL_BURST_VOLUME			103	// CAVolNeed    this should be set initially
#define IL_N_INTERVALS			110	// TotWtrInt    this should be set initially
#define	WETUP_CONTROL_FLAG		3	// user flag

// used in CLADAControlModudleView (when connecting)
#define IL_PROGRAM_TYPE			1	// input location which stores a value denoting the type of program it is running
#define REGULAR_PROGRAM			32  // arbitrary value (must be the same in the CR10 code) for regular program 
#define WETUP_PROGRAM			96 // arbitrary value (must be the same in the CR10 code) for wetup program 