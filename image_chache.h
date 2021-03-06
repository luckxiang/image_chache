/*************************************************************************
	> File Name: image_chache.h
	> Author: LuckXiang
	> GitHub: https://github.com/luckxiang
	> Created Time: 日  6/19 11:33:31 2016
 ************************************************************************/

#ifndef _IMAGE_CHACHE_H
#define _IMAGE_CHACHE_H

#include"list.h"

#define MAX_IMAGE_NUM 100
#define IMAGE_DEL_NUM 10
#define MAX_PRIORITY 2

/* Define your own struct */
struct UserData{
    char url[100];

};

struct ImageNode{
    int image_priority; /* 0 is the highest priority */
    int image_id;
    struct UserData image_data;
    struct list_head image_list;
};

void Image_list_head_init(struct ImageNode *head);
void Image_node_add(struct ImageNode *new_node, struct ImageNode *head);
struct UserData *Image_node_find(int id, struct ImageNode *head);
int Image_list_empty_test(struct ImageNode *head);
void Image_list_all_del(struct ImageNode *head);
void Image_list_splice(struct ImageNode *list, struct ImageNode *head);

#endif
