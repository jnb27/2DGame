#include <stdlib.h>

#include "simple_json.h"
#include "simple_logger.h"

#include "level.h"


Level *level_new()
{
	Level *level;
	level = (Level *)malloc(sizeof(Level));
	if (!level)
	{
		slog("failed to allocate memory for the game level");
		return NULL;
	}
	memset(level, 0, sizeof(Level));
	return level;
}

Level *level_load(const char *filename)
{
	const char *string;
	Level *level;
	SJson *json, *levelJS, *levelMap, *row;
	int rows, columns;
	int count, tileindex;
	int i, j;

	if (!filename)
	{
		slog("filename is NULL, cannot load the level");
		return NULL;
	}
	json = sj_load(filename);
	if (!json)return NULL;

	level = level_new();
	if (!level)
	{
		sj_free(json);
		return NULL;
	}

	levelJS = sj_object_get_value(json, "level");
	if (!levelJS)
	{
		slog("level json missing level object");
		level_free(level);
		sj_free(json);
		return NULL;
	}

	string = sj_get_string_value(sj_object_get_value(levelJS, "bgImage"));
	if (string)
	{
		level->bgImage = gf2d_sprite_load_image((char *)string);
	}
	string = sj_get_string_value(sj_object_get_value(levelJS, "tileSet"));
	if (string)
	{
		sj_get_integer_value(sj_object_get_value(levelJS, "tileWidth"), &level->tileWidth);
		sj_get_integer_value(sj_object_get_value(levelJS, "tileHeight"), &level->tileHeight);
		sj_get_integer_value(sj_object_get_value(levelJS, "tileFPL"), &level->tileFPL);
		level->tileSet = gf2d_sprite_load_all(
			(char *)string,
			level->tileWidth,
			level->tileHeight,
			level->tileFPL);
	}

	sj_get_integer_value(sj_object_get_value(levelJS, "biome"), &level->Biome);

	levelMap = sj_object_get_value(levelJS, "tileMap");
	if (!levelMap)
	{
		slog("missing tileMap data");
		level_free(level);
		sj_free(json);
		return NULL;
	}
	rows = sj_array_get_count(levelMap);
	row = sj_array_get_nth(levelMap, 0);
	columns = sj_array_get_count(row);
	count = rows * columns;
	level->levelWidth = columns;
	level->levelHeight = rows;
	level->tileMap = (TileTypes*)gfc_allocate_array(sizeof(TileTypes), count);
	if (!level->tileMap)
	{
		level_free(level);
		sj_free(json);
		return NULL;
	}
	level->tileCount = count;

	tileindex = 0;
	slog("tilemap data:");
	for (j = 0; j < rows; j++)
	{
		row = sj_array_get_nth(levelMap, j);
		if (!row)continue;// skip it, its bad
		if (columns != sj_array_get_count(row))
		{
			slog("row %i, column count mismatch", j);
			continue;
		}
		for (i = 0; i < columns; i++)
		{
			sj_get_integer_value(sj_array_get_nth(row, i), &level->tileMap[tileindex]);
			printf("%i,", level->tileMap[tileindex++]);
		}
		printf("\n");
	}
	slog("map width: %i", level->levelWidth);
	slog("map height: %i", level->levelHeight);

	sj_free(json);
	return level;
}

void level_free(Level *level)
{
	if (!level)return;// nothing to do

	if (level->tileMap != NULL)
	{
		free(level->tileSet);
		level->tileMap = NULL;
	}
	gf2d_sprite_free(level->bgImage);
	gf2d_sprite_free(level->tileSet);

	free(level);
}

void level_draw(Level *level)
{
	int i;
	if (!level)
	{
		slog("cannot draw level, NULL pointer provided");
		return;
	}
	// draw the background first
	gf2d_sprite_draw_image(level->bgImage, vector2d(0, 0));
	//then draw the tiles

	if (!level->tileMap)
	{
		slog("not tiles loaded for the level, cannot draw it");
		return;
	}

	for (i = 0; i < level->tileCount; i++)
	{
		if (level->tileMap[i] == 0)continue;
		gf2d_sprite_draw(
			level->tileSet,
			vector2d((i % level->levelWidth)*level->tileSet->frame_w, (i / level->levelWidth)*level->tileSet->frame_h),
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			level->tileMap[i] - 1);
	}
}



/*file footer*/