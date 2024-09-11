#pragma once

struct variables
{
	struct
	{
		float x = 5;
		float y = 250;
		float width = 350;

		const float* rectColor = vec4_t(0, 0, 0, 255);

		int m_Design;
	}menu;

	struct
	{
		const float* emptyColor = vec4_t(0, 0, 0, 0);
	}global;

	struct
	{
		Font_s* bodyfont = R_RegisterFont("fonts/normalfont", 0);
		Font_s* normalfont = R_RegisterFont("fonts/normalfont", 0);
	}fonts;

	struct
	{
		Material* white = Material_RegisterHandle("white", 0);
	}materials;
};

extern variables* g_vars;