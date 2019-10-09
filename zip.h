/*
//  zip.h
//  Group Task
//
//  Created by cn2nick on 8/10/19.
//  Copyright © 2019 nick. All rights reserved.
*/

#ifndef zip_h
#define zip_h

typedef struct huffmanNode
{
    char data;
    int weight;
    struct huffmanNode *leftNode;
    struct huffmanNode *rightNode;
} huffmanNode_t;


#include <stdio.h>


void sort(huffmanNode_t* node,int length);
void print_huffman_pre(huffmanNode_t *node,FILE *debug);
void create_huffman_tree(huffmanNode_t *node,int length);
void coding(huffmanNode_t *node,char *unfinished_code,int length);
int zip(int mode);
huffmanNode_t *unzipcode(huffmanNode_t *node,int flag);
int unzip(int mode);
#endif /* zip_h */
