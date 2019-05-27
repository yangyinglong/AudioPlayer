#ifndef MEDIALIB_H_
#define MEDIALIB_H_
#define MAX_TITLE_LENGTH 512
#define MAX_ATRIST_LENGTH 512
#define MAX_ALBUM_LENGTH 256
#define MAX_GENRE_LENGTH 256
#define MAX_PATH_LENGTH 4096

typedef struct _medialib Medialib;
struct _medialib							// Media Library Project Struct
{
	char title[MAX_TITLE_LENGTH];			// title
	char artist[MAX_ATRIST_LENGTH];			// atrist
	char album[MAX_ALBUM_LENGTH];			// album name 专辑
	char genre[MAX_GENRE_LENGTH];			// genres 流派
	double record_time;						// time
	char filepath[MAX_PATH_LENGTH];
};

int read_tag_from_file(const char *file, struct _medialib *media);

#endif /* MEDIALIB_H_ */