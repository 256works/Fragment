#pragma once

// ��������Ʈ ���ҽ� �ε��� ����.
// �� ������ �����ϱ� ���ϴ� ��������Ʈ �̸� �Է� ��
// ���� ��Ʈ�ѷ� init���� ��������Ʈ �ε忡�� �ҷ����ּ���.

enum class spr : unsigned int
{
	none, // ���� ����. ���� ó���� ��ġ ��ų ��
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
	__max_count // ���� ����. ���� �������� ��ġ ��ų ��
};

// �浹 �˻��

enum class obj : unsigned int
{
	none, // ���� ����. ���� ó���� ��ġ ��ų ��
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
	__max_count // ���� ����. ���� �������� ��ġ ��ų ��
};