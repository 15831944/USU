// used in LadaTest.cpp
//#define IL_PROGRAM_TYPE 1 // Exists in Wetup also

#define AIRTEMP			2
#define ABPRESSURE		3
#define HUMIDITY		4
#define AIROXYGEN		5
#define CARBONDIOXIDE	6

#define VOLTAGE_1		9	//DC12Vn_V
#define CURRENT_1		10	//DC12Vc_I
#define VOLTAGE_2		11	//DC12Vn_V
#define CURRENT_2		12	//DC12Vn_I
#define VOLTAGE_3		13	//DC16V_V
#define CURRENT_3		14	//DC16V_I
#define VOLTAGE_4		15	//DC5V_V
#define CURRENT_4		16	//DC5V_I

#define MOISTURE_CONTROL_B		22	//WatVolMul For chamber B

#define IL_WATER_PUMPED	106  // see note in "questions about checkout.doc" regarding this...
#define	MAXPMPVOL		27
#define	MAVOLNEED		105

#define VOLTAGE_5		47	//
#define CURRENT_5		48


#define IHumOut			50	//Not Sure	CA_RH
#define IBallTemp		51	//Not Sure	CA_Blst_T
#define IInlet			52	//Not Sure	CA_Intk_T
#define ILeaf1			53	//Not Sure	CA_Top_T
#define ILeaf2			54	//Not Sure	CA_Mid_T
#define ILeaf3			55	//Not Sure	CA_Bot_T
#define IRefTemp		56	//Not Sure	CA_Ref_T
#define ILeafSurface	57	//Not Sure	CA_Leaf_T
#define ITemp1			58	//CA_SMP1iT
#define ITemp2			59	//CA_SMP2iT
#define ITemp3			60	//CA_SMP3iT
#define ITemp4			61	//CA_SMP4dT
#define ITemp5			62	//CA_SMP5dT
#define ITemp6			63	//CA_SMP6dT
#define ITemp7			64	//CA_SMP7iT
#define ITemp8			65	//CA_SMP8iT

#define IDTemp1			74	//CA_SMP1dT
#define IDTemp2			75	//CA_SMP2dT
#define IDTemp3			76	//CA_SMP3dT
#define IDTemp4			77	//CA_SMP4dT
#define IDTemp5			78	//CA_SMP5dT
#define IDTemp6			79	//CA_SMP6dT
#define IDTemp7			80	//CA_SMP7dT
#define IDTemp8			81	//CA_SMP8dT
#define ISat1			82	//CA_SMP1_T
#define ISat2			83	//CA_SMP2_T
#define ISat3			84	//CA_SMP3_T
#define ISat4			85	//CA_SMP4_T
#define ISat5			86	//CA_SMP5_T
#define ISat6			87	//CA_SMP6_T
#define ISat7			88	//CA_SMP7_T
#define ISat8			89	//CA_SMP8_T

#define CA_O2_1			91	//CA_O2_1
#define CA_O2_2			92	//CA_O2_2
#define CA_O2_3			93	//CA_O2_3
#define CA_O2_4			94	//CA_O2_4

#define	CA_TOP_L		96	//CA_Top_L
#define CA_MID_L		97	//CA_Mid_L
#define CA_BOT_L		98	//CA_Bot_L
#define ABS_TENSIOMETER	99	//ARefPress
#define	TENSIOMETER_1	100	//ATensio_1
#define	TENSIOMETER_2	101	//ATensio_2
#define	TENSIOMETER_3	102	//ATensio_3
#define	TENSIOMETER_4	103	//ATensio_4
#define MOISTURE_CONTROL_A		104 //  GCASatLvl

#define A_WTR_INTVL				111 //  AWtrIntvl
// used in paramdlg.cpp
#define IL_AVERAGE_SMP_A		90
#define IL_MAX_DOSAGE			27
#define LIGHT_ON_TIME_A			112	//	ALightsOn
#define	LIGHT_OFF_TIME_A		113	//	ALightsOff
#define A_READ_20_MN			114	//	ARead20mn	used to set the frequency of final storage collection
#define A_READ_1_HR				115	//	ARead1Hr
#define A_WRITE_20_MN			116	//	AWrite20m
#define A_WRITE_1_HR			117	//	AWrite1Hr
// used in commoperations.cpp
#define CHAMBER_1_CONTROL		118	//	AManCtrl	manual control input location, chamber A

//#define CHAMBER_1_STATUS		118 //  AMnCtBits
#define LIGHT_A_STATUS			122
#define FAN_A_STATUS			123
#define PUMP1_A_STATUS			124
#define PUMP2_A_STATUS			125



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
#define	IL_N_ELAPSED_INTERVALS	112 // TotWtrCnt	this is how we count number of intervals
#define IL_TOTAL_TO_PUMP		102	// TotVolReq	this should be set initially 
#define IL_BURST_VOLUME			103	// CAVolNeed    this should be set initially
#define IL_N_INTERVALS			111	// TotWtrInt    this should be set initially
#define	WETUP_CONTROL_FLAG		3	// user flag
#define TENSIOMETER_CONTROL_FLAG	5	// 

#define MA_PUMP_IN				105
#define PUMP_VOL				113
// used in CLADAControlModudleView (when connecting)
#define IL_PROGRAM_TYPE			1	// input location which stores a value denoting the type of program it is running
//#define REGULAR_PROGRAM			13000  // arbitrary value (must be the same in the CR10 code) for regular program 
//#define WETUP_PROGRAM			96 // arbitrary value (must be the same in the CR10 code) for wetup program 