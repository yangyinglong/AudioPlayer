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

typedef struct _node_t node_t;
struct _node_t
{
	Medialib item;
	node_t *p;	
};

typedef struct _link_t link_t;				
struct _link_t								// 链表的结构体							
{
	node_t *np;								// 指向链表中第一个节点首地址的指针
	int length;	
};

enum _find_cond
{
	BY_TITLE,
	BY_ARTIST,
	BY_ABLUM,
	BY_GENRE,
	BY_FILEPATH	
};
typedef enum _find_cond find_cond;

int read_tag_from_file(const char *file, struct _medialib *media);
node_t * link_to_end(node_t *nt);
int link_add(link_t *mlink, const char *file);

#endif /* MEDIALIB_H_ */