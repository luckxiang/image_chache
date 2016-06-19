/*************************************************************************
	> File Name: image_chache.c
	> Author: LuckXiang
	> GitHub: https://github.com/luckxiang
	> Created Time: 六  6/18 13:47:41 2016
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"image_chache.h"

static void _image_node_batch_del(struct ImageNode *head, const int del_num);

void Image_list_head_init(struct ImageNode *head)
{
    head->image_priority = MAX_PRIORITY;/* 用头节点的priority记录优先级最大值 */
    head->image_id = 0;/* 用头节点的id记录node节点数 */
    GX_INIT_LIST_HEAD(&(head->image_list));
}

void Image_node_add(struct ImageNode *new_node, struct ImageNode *head)
{
    if(head->image_id >= MAX_IMAGE_NUM)
        _image_node_batch_del(head, IMAGE_DEL_NUM);
    gxlist_add_tail(&(new_node->image_list), &(head->image_list));
    head->image_id++;
}

int Image_list_empty_test(struct ImageNode *head)
{
    return gxlist_empty(&(head->image_list));
}

static void _image_node_del(struct ImageNode *node)
{
    gxlist_del(&(node->image_list));
    /* do release resources ... */
    free(node);
}

static void _image_node_batch_del(struct ImageNode *head, const int del_num)
{ 
    struct ImageNode *pos;
    struct ImageNode *pos_back;
    int i, num = 0;
    int priority = head->image_priority;

    for(i = 0; i < head->image_priority; i++)
    {
        gxlist_for_each_entry_safe(pos, pos_back, &(head->image_list), image_list)
        {
            if(pos->image_priority == priority)
            {
                _image_node_del(pos);
                num++;
                head->image_id--;
            }
            if(num == IMAGE_DEL_NUM)
                return ;
        }
        priority--;
    }
}

void Image_list_all_del(struct ImageNode *head)
{
    struct ImageNode *pos;
    struct ImageNode *pos_back;
    head->image_id = 0;
    gxlist_for_each_entry_safe(pos, pos_back, &(head->image_list), image_list)
    {
        _image_node_del(pos);
    }
}

void Image_list_splice(struct ImageNode *list, struct ImageNode *head)
{
    gxlist_splice(&(list->image_list), &(head->image_list));
}

void Image_node_print(struct ImageNode *head)
{
    struct ImageNode *pos;

    gxlist_for_each_entry(pos, &(head->image_list), image_list)
    {
        printf("priority: %d, id: %d,url: %s\n", pos->image_priority, pos->image_id,pos->image_data.url);
    }
}

/*main for test*/
int main(int argc, char *argv[])
{
    struct ImageNode list_head;
    struct ImageNode *image;
    int i;
    Image_list_head_init(&list_head);   
    for(i = 0; i < 30; i++)
    {
        image = (struct ImageNode *)malloc(sizeof(struct ImageNode));
        if(image == NULL)
            return -1;
        memset(image, 0, sizeof(struct ImageNode));
        image->image_priority = 0;
        image->image_id = i;
        memcpy(image->image_data.url, "http://hello.com", 99);
        Image_node_add(image, &list_head);
    }
    Image_node_print(&list_head);
    printf("image num:%d \n", list_head.image_id);
    for(i = 0; i < 90; i++)
    {
        image = (struct ImageNode *)malloc(sizeof(struct ImageNode));
        if(image == NULL)
            return -1;
        memset(image, 0, sizeof(struct ImageNode));
        image->image_priority = 1;
        image->image_id = i;
        memcpy(image->image_data.url, "http://bigxiangbaobao.com", 99);
        Image_node_add(image, &list_head);
    }
    Image_node_print(&list_head);
    printf("image num:%d \n", list_head.image_id);
    for(i = 0; i < 70; i++)
    {
        image = (struct ImageNode *)malloc(sizeof(struct ImageNode));
        if(image == NULL)
            return -1;
        memset(image, 0, sizeof(struct ImageNode));
        image->image_priority = 0;
        image->image_id = i;
        memcpy(image->image_data.url, "http://xxxx.com", 99);
        Image_node_add(image, &list_head);
    }
    Image_node_print(&list_head);
    printf("image num:%d \n", list_head.image_id);
    Image_list_all_del(&list_head);
    printf("empty: %s\n", Image_list_empty_test(&list_head)?"yes":"no");

    return 0;
}
