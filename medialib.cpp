#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <id3tag.h>
#include "medialib.h"

int read_tag_from_file(const char *file, struct _medialib *media)
{
	struct id3_file * id3file;				// 用于保存libid3tag库文件对象
	struct id3_tag * tag;					// 用于保存文件信息
	struct id3_frame * frame_title;			// 用于保存标题信息
	struct id3_frame * frame_artist;
	struct id3_frame * frame_album;
	struct id3_frame * frame_genre;
	struct id3_frame * frame_time;



	id3file = id3_file_open(file, ID3_FILE_MODE_READONLY);
	if (id3file == NULL)
	{
		printf("file open fail!\n");
		return -1;
	}
	tag = id3_file_tag(id3file);			// 创建id3_tag结构体

	if (frame_title = id3_tag_findframe(tag, ID3_FRAME_TITLE, 0))
	{
		// strcpy(media->title, (char*) frame_title->fields);
        union id3_field const *field = id3_frame_field(frame_title, 1);
        unsigned int nstrings = id3_field_getnstrings(field);
        id3_ucs4_t const *ucs4;
        for(int j = 0; j < nstrings; j++)
        {
            ucs4 = id3_field_getstrings(field, j);
            // printf("%s\n", (char *)id3_ucs4_latin1duplicate(ucs4));
            strcpy(media->title, (char *)id3_ucs4_latin1duplicate(ucs4));
        }
	}

	if (frame_artist = id3_tag_findframe(tag, ID3_FRAME_ARTIST, 0))
	{
		union id3_field const *field = id3_frame_field(frame_artist, 1);
        unsigned int nstrings = id3_field_getnstrings(field);
        id3_ucs4_t const *ucs4;
        for(int j = 0; j < nstrings; j++)
        {
            ucs4 = id3_field_getstrings(field, j);
            strcpy(media->artist, (char *)id3_ucs4_latin1duplicate(ucs4));
        }
	}

	// 专辑
	if (frame_album = id3_tag_findframe(tag, ID3_FRAME_ALBUM, 0))
	{
		union id3_field const *field = id3_frame_field(frame_album, 1);
        unsigned int nstrings = id3_field_getnstrings(field);
        id3_ucs4_t const *ucs4;
        for(int j = 0; j < nstrings; j++)
        {
            ucs4 = id3_field_getstrings(field, j);
            strcpy(media->album, (char *)id3_ucs4_latin1duplicate(ucs4));
        }
	}

	if (frame_genre = id3_tag_findframe(tag, ID3_FRAME_GENRE, 0))
	{
		union id3_field const *field = id3_frame_field(frame_genre, 1);
        unsigned int nstrings = id3_field_getnstrings(field);
        id3_ucs4_t const *ucs4;
        for(int j = 0; j < nstrings; j++)
        {
            ucs4 = id3_field_getstrings(field, j);
            ucs4 = id3_genre_name(ucs4);
            strcpy(media->genre, (char *)id3_ucs4_latin1duplicate(ucs4));
        }
	}

	if (frame_time = id3_tag_findframe(tag, "TDRC", 0))
	{
		media->record_time = id3_field_getint(frame_time->fields);
	}
	strcpy(media->filepath, file);
	// printf("%s\n", media->title);
	// printf("%s\n", media->artist);
	// printf("%s\n", media->album);
	// printf("%s\n", media->genre);
	// printf("%f\n", media->record_time);
	id3_file_close(id3file);
	return 0;
}

// int main(int argc, char const *argv[])
// {
// 	struct _medialib *media;
// 	media = (struct _medialib *)malloc(sizeof(struct _medialib));
// 	read_tag_from_file("Korb-Cuchulainn.mp3", media);
// 	return 0;
// }