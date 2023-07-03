#pragma once

enum class SceneId
{
	None = -1,
	Title,
	Game,
	Count,
};

enum class ResourceTypes
{
	Texture,
	Font,
	SoundBuffer,
};

enum class Origins	// �ǹ�
{
	TL,
	TC,
	TR,
	ML,
	MC,
	MR,
	BL,
	BC,
	BR,
	CUSTOM
};

enum class Collide
{
	None,
	Top,
	Other
};