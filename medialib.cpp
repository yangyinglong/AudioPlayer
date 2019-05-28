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


node_t * link_to_end(node_t *nt)
{
	if (nt->p)
	{
		return link_to_end(nt->p);
	}
	else
	{
		return nt;
	}
}


int link_add(link_t *mlink, const char *file)
{
	node_t *endnode;
	node_t *mnode = (node_t *)malloc(sizeof(node_t));
	if (!mnode)
	{
		printf("malloc fail!\n");
		return 1;
	}
	if (read_tag_from_file(file, &mnode->item))
	{
		printf("read file fail\n");
		free(mnode);
		return 1;
	}
	mnode->p = NULL;
	if (mlink->np)
	{
		endnode = link_to_end(mlink->np);
		endnode->p = mnode;
	}
	else
	{
		mlink->np = mnode;
	}
	mlink->length++;
	return 0;
}


int link_find(link_t *mlink, find_cond t, const char *str2, node_t **res)
{
	if (*res)
	{	
		free(*res);
		*res = NULL;
	}
	int i, l;
	int count = 0;
	const char *str1;
	node_t * tmp, **jump, **jump2;
	if (!mlink->length)
	{
		printf("medialib is empty, can not find!\n");
		return 0;
	}
	if (str2)
	{
		l = strlen(str2);
	}
	else
	{
		printf("string address is error!\n");
		return 0;
	}
	if (!l)
	{
		printf("string length is 0, error\n");
		return 0;
	}
	tmp = mlink->np;
	node_t * tmp_link = (node_t *)malloc(sizeof(node_t *) * mlink->length);
	jump = &tmp_link;
	while(tmp)
	{
		switch(t) {
			case BY_TITLE:
				str1 = tmp->item.title;
				break;
			case BY_ARTIST:
				str1 = tmp->item.artist;
				break;
			case BY_ABLUM:
				str1 = tmp->item.album;
				break;
			case BY_GENRE:
				str1 = tmp->item.genre;
			case BY_FILEPATH:
				str1 = tmp->item.filepath;
				break;
			default:
				printf("error\n");
				free(tmp_link);
				return 0;
		}
		if (str1 && strlen(str1))
		{
			if (strcmp(str1, str2) == 0)
			{
				*(jump + count) = tmp;
				count ++;
			}
		}
		tmp = tmp->p;
	}
	*res = (node_t *)malloc(sizeof(node_t *) * count);

	jump2 = res;
	for (int i = 0; i < count; ++i)
	{
		*(jump2 + i) = *(jump + i);
	}
	free(tmp_link);
	return count;
}


int main(int argc, char const *argv[])
{
	// struct _medialib *media;
	// media = (struct _medialib *)malloc(sizeof(struct _medialib));
	// read_tag_from_file("SunnyChoi-IWillStandByYou.mp3", media);

	link_t mlink = {NULL, 0};
	link_add(&mlink, "Korb-Cuchulainn.mp3");
	link_add(&mlink, "SunnyChoi-IWillStandByYou.mp3");
	node_t *res = (node_t *)malloc(sizeof(node_t));
	int i = link_find(&mlink, BY_TITLE, "Cuchulainn", &res);
	printf("%d\n", i);
	return 0;
}