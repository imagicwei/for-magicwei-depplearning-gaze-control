#include "stdafx.h"

// this header files contains all of "#define" and "enum"

#if !defined( DEFINE_H ) 
#define DEFINE_H 

//放入 extern 等原本在header裡面的資料，避免重複宣告 

#define PI 3.141592653589793238462643383279502884197169399375105820974944
#define CAM_WIDTH 320
#define CAM_HEIGHT 240

#pragma region Motion Code Table
// ---- Motion Code Table ---- //

struct MOTION{

	// ---- Body Motion Code Table ---- //
	struct BODY{
		enum
		{	
			DONE = 0, NONE = 0,

			STEP_F     = 11,	//// 約1~2cm
			STEP_B     = 12,	//// 約1~2cm 
			STEP_FF    = 13,	//// 約3~4cm
			STEP_BB    = 14,	//// 約3~4cm
			STEP_FFF   = 15,	//// 先保留定義，動作暫時不需要
			STEP_BBB   = 16,	//// 先保留定義，動作暫時不需要
			SHIFT_R    = 17,	//// 約1~2cm
			SHIFT_L    = 18,	//// 約1~2cm
			SHIFT_RR   = 19,	//// 約3~4cm  
			SHIFT_LL   = 20,	//// 約3~4cm
			SHIFT_RRR  = 21,	//// 先保留定義，動作暫時不需要
			SHIFT_LLL  = 22,	//// 先保留定義，動作暫時不需要
			TURN_R     = 23,	//// 約10~15度
			TURN_L     = 24,	//// 約10~15度
			TURN_RR    = 25,	//// 約20~25度
			TURN_LL    = 26,	//// 約20~25度
			TURN_RRR   = 27,	//// 先保留定義，動作暫時不需要
			TURN_LLL   = 28,	//// 先保留定義，動作暫時不需要
			TURNBALL_R = 29,	//// 距離球5~7cm，一次轉約15~20度，轉的時候盡量不要踢到球
			TURNBALL_L = 30,	//// 距離球5~7cm，一次轉約15~20度，轉的時候盡量不要踢到球
			KICK_R     = 31,	//// 踢出去的距離視策略的需求而定
			KICK_L     = 32,	//// 踢出去的距離視策略的需求而定  目前沒有 KICK L
			KICK_RR    = 33,	//// 
			KICK_LL    = 34,	//// 
			DRIBBLE_R  = 35,	//// 左腳先走
			DRIBBLE_L  = 36,	//// 右腳先走
			//KICK_OFF_R = 43,
			//KICK_OFF_L = 44,
			SIDE_KICK_R = 45,
			SIDE_KICK_L = 46,


			PICK_UP = 74,
			THROW = 75,
			PUT_IN = 79,
			TWIST_WAIST = 77,
			PLACE_BALL = 76,
			CLIMBING = 78,

			RIGHTHAND_UP = 81,
			LEFTHAND_UP = 82,
			OB_HAND_UP = 83,
			WARM_UP = 85,		    
			CLAP = 86,

			THROW_BKL_1 = 88,
			THROW_BKL_2 = 89,
			THROW_BKL_3 = 90,
			THROW_BKL_4 = 91,
			THROW_BKL_5 = 92,
			THROW_BKL_6 = 93,
			HOLD_BALL = 95,

			STOP = 100,
			STEP = 101,
			SHIFT = 102, 
			TURN = 103,	
			TURNBALL = 104,
			WALK = 105,

			ADULT_WEIGHT_WALK = 107

		};
	};

	// ---- Head Motion Code Table ---- //
	struct HEAD{
		enum{
			STOP = 1,
			GO_SLOW = 2,
			GO_MIDDLE = 3,
			GO_FAST = 4,

			NO_FIX=10,
			FIX_PAN=11,
			FIX_TILT=12
		};

		struct STATE{
			enum{
				SEARCH_STRAIGHT = 1,
				SEARCH_STRAIGHT_TWICE,
				SEARCH_STRAIGHT_THIRD,
				SEARCH_STRAIGHT_FORTH,
				SEARCH_STRAIGHT_FIFTH,

				SEARCH_RIGHT,
				SEARCH_RIGHT_TWICE,
				SEARCH_RIGHT_THIRD,
				SEARCH_RIGHT_FOURTH,

				SEARCH_WITH_TURN_R,
				SEARCH_WITH_TURN_R_TWICE,

				SEARCH_LEFT,
				SEARCH_LEFT_TWICE,
				SEARCH_LEFT_THIRD,
				SEARCH_LEFT_FOURTH,

				SEARCH_WITH_TURN_L,

				SEARCH_BACK_STRAIGHT,
				SEARCH_BACK_RIGHT,
				SEARCH_BACK_RIGHT_TWICE
			};
		};

		struct GOAL_STATE
		{
			enum{
				AIM_MID,
				AIM_LEFT,
				AIM_RIGHT,
				AIM_AUTO
			};
		};
	};

	// ---- Weightlifting Motion Code Table ---- //
	struct WEIGHT_LIFTING{
		enum
		{
			//Single Motion
			W_PICK_UP = 60,
			HAND_UP = 61,
			STEP_WEIGHT_F = 62,
			STEP_WEIGHT_F2 = 63,
			PICK_UP_TURN_R = 64,  //舉低的右轉
			PICK_UP_TURN_L = 65,  //舉低的左轉
			PUT_DOWN = 66,
			//Conti Motion
			HAND_UP_WALK = 107

// 			PICK_UP_STEP_F = 62,
// 			HAND_UP_STEP_F = 63,
 			
// 			HAND_UP_TURN_R = 23,
// 			HAND_UP_TURN_L = 24,
		};
	};
};

#pragma endregion Motion Code Table

#pragma region State Code Table
// ---- State Code Table ---- //
struct STATE{

	enum{
		INITIAL = 0,
		FINISH = 100
	};
	struct GAZECONTROl{
		enum{
			PREPARE = 1,
			AIM,
			SHOOT,
			FINISH = 100
		};
	};

	struct FOLLOW{   //NEW
		enum{

			LOOK_MARK = 1,
			FORWARD,
			FORWARD_V,
			FORWARD_IMU,
			CHANGE,
			DIP_CONTROL,
			BACKWARD,
			BACK_V,
			BACK_IMU,
			LOOK_BOUNDARY,
			NOFOUND,
			FINISH = 100
		};
	};
};

#pragma endregion State Code Table

#pragma region Strategy Code Table
// ---- Strateg)y Code Table ---- //

struct GAZECONTROL_EVENT{
	enum{
		GAZECONTROl = 5,
		FOLLOW = 6,
	};
	
};

#pragma endregion Strategy Code Table

#pragma region Object Code Table
// ---- Object Code Table ---- //

struct OBJECT 
{
	enum
	{
		NONE = -1,
		COLOR1 = 0,
		COLOR2,
		COLOR3,
		COLOR4,
		COLOR5,
		COLOR6,
		COLOR7,
		COLOR8,
		COLOR9
	};

	struct GAZECONTROL{
		enum{
			G_PUPIL = 0,
			G_WHITE,
			G_SKIN,
		};
	};
	struct AUXILIARY{
		enum{
			COLOR1 = 4,
			COLOR2,
			COLOR3,
			COLOR4
		};
	};

	struct BASKETBALL{
		enum{
			B_BALL = 0,
			B_BOARD,
			B_BASKET,
			B_BALL_2,
		};
	};
	struct WARMUP{
		enum{
			B_BALL = 0,

		};
	};
	struct WEIGHTLIFTING{
		enum{
			LINE = 0
		};
	};
	struct UNITE_SOCCER{
		enum{
			US_BALL = 5,
			US_GOAL,
			US_BALL_2,
			US_GOAL_2, //對手的球門

		};
	};
	struct FALL{
		enum{
			FA_CLOTHES = 0,
			FA_FACE,
		};
	};
	struct COLORLUMP{
		enum{
			C_RED = 0,
			C_BLUE,
			C_GREEN,
			C_BLACK,
			C_WHITE,
		};
	};
};

#pragma endregion Object Code Table

#pragma region Robot Code Table
// ---- Robot Code Table ---- //

struct ROBOT {

	enum{
		ADULT = 1,
		KID
	};

};

#pragma endregion Robot Code Table

#pragma region Other Code Table
// ---- Other Code Table ---- //

struct DIRECTION {

	enum{
		LEFT = 1,
		RIGHT,
		FORWARD,
		BACKWARD
	};

};

struct MAP_AREA {

	enum{
		FRONT_LEFT = 1,
		FRONT_CENTER,
		FRONT_RIGHT,
		HALF_LEFT,
		HALF_CENTER,
		HALF_RIGHT,
		BACK_LEFT,
		BACK_CENTER,
		BACK_RIGHT
	};

};

struct MOTION_SET{
	enum{
		NONE = 0,
		WALK,
		STEP_F,
		STEP_B, 
		TURN_L,
		TURN_R,
		WAIST
	};

};

struct COLORWHEEL_DOT {
	enum{
		H1S1 = 0,
		H1S2,
		H2S1,
		H2S2
	};
};


struct ALGORITHM {
	enum{
		PSO = 0,
		MAGIC,
		GA
	};

};

#pragma endregion Other Code Table

#endif 


