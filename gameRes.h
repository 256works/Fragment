#pragma once

// 스프라이트 리소스 인덱스 관리.
// 이 곳에서 참조하기 원하는 스프라이트 이름 입력 후
// 게임 컨트롤러 init에서 스프라이트 로드에서 불러와주세요.

enum class spr : unsigned int
{
	none, // 삭제 금지. 제일 처음에 위치 시킬 것
	cursor,
	titlebg,
	titlelogo,
	title_start,
	title_cloud,
	title_ring,
	title_copyright,
	title_backlight,
	title_start_backlight,
	title_small_light,
	works256,
	game_backlight,
	player,
	game_ring,
	game_spin_light,
	game_spin_light2,
	bullet,
	score,
	score_num,
	score_num2,
	hexa_bg,
	bullet_effect,
	life,
	enemy,
	explosion,
	ready,
	enemy_warning,
	enemy_warning_ring,
	explosion2,
	explosion2_ring,
	wave_warn,
	highscored,
	retry,
	gameover,
	__max_count // 삭제 금지. 제일 마지막에 위치 시킬 것
};

// 충돌 검사용

enum class obj : unsigned int
{
	none, // 삭제 금지. 제일 처음에 위치 시킬 것
	logo,
	title_manager,
	player,
	bullet,
	game_background,
	bullet_effect,
	explosion,
	enemy,
	enemy_gene,
	huge_explosion,
	player_wave,
	wave_manager,
	game_manager
};

enum class snd : unsigned int
{
	bgm,
	buttonhover,
	game_start,
	player_shot,
	explosion,
	explosion2,
	enemy_hit,
	enemy_warning,
	wave_warning,
	get_ready,
	re_gen,
	__max_count // 삭제 금지. 제일 마지막에 위치 시킬 것
};