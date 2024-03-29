#pragma once

enum ID{
	MONSTER,
	OBSTACLE,
	EFFECT,
	PLAYER,
	BULLET,
	MONSTER_BULLET,
	BUTTON,
	ID_END
};

enum STATE {
	APPEARANCE, //플레이어 STATE
	IDLE,
	MOVE,
	JUMPUP, JUMPDOWN,
	ATTACK, MOVE_ATTACK, CHARGE_ATTACK, DASH_ATTACK, JUMP_ATTACKUP, JUMP_ATTACKDOWN, CLIMB_ATTACK, ROPE_ATTACK,
	DASH, CLIMB, ROPE,
	DAMAGED, MORTAL,
	ATTACK_READY, ATTACK_END, //몬스터 STATE
	ROTATE,
	STATE_END
};

enum DIR {
	DIR_LEFT,
	DIR_RIGHT,
	DIR_END
};

enum SCENEID {
	STAGE,
	STAGE_BOSS,
	MENU,
	MENU_BUTTON,
	LOGO,
	LOADING,
	ENDING,
	SCENE_END
};

enum BULLETID {
	NOMAL_BULLET,
	MEDIUM_BULLET,
	CHARGE_BULLET,
};

enum UI {
	PLAYER_HP,
	BOSS_HP,
	ABILLITY,
	UI_END,
};