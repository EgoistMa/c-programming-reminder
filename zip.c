/*
 //  main.c
 //  zip
 //
 //  Created by YUZURIHA_EGOIST on 8/10/19.
 //  Copyright © 2019 Tianyu Ma. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*database names*/
#define DATABASE "database.txt"
#define ZIPPED "zipped.DB"

/*debug file names*/
#define DEBUGFILE "debug.txt"
#define UNZIPDEBUGFILE "unzipdebug.txt"

typedef struct huffmanNode
{
    char data;
    int weight;
    struct huffmanNode *leftNode;
    struct huffmanNode *rightNode;
} huffmanNode_t;

/*Global variable*/
char huffmantable[256][100];
huffmanNode_t left[100] = {{0,0,NULL,NULL}};
huffmanNode_t right[100] = {{0,0,NULL,NULL}};

/*sort node hight>>>>>>>>>>>>>>>low weight*/
void sort(huffmanNode_t* node,int length)
{
    int i,j;
    huffmanNode_t temp;
    for(i=0;i<length-1;i++)
    {
        for(j=0; j <length-i-1;j++)
        {
            if(node[j].weight < node[j+1].weight)
            {
                temp = node[j];
                node[j] = node[j+1];
                node[j+1] = temp;
            }
        }
    }
}
/*pre order traversing the binary tree*/
void print_huffman_pre(huffmanNode_t *node,FILE *debug){
    if (node != NULL){
        fprintf(debug,"%c\t%d\n", node->data, node->weight); /*save to debug file*/
        print_huffman_pre(node->leftNode,debug);
        print_huffman_pre(node->rightNode,debug);
    }
}
/*build huffman tree*/
void create_huffman_tree(huffmanNode_t *node,int length)
{
    while(length !=1)
    {
        sort(node,length);
        huffmanNode_t parent = {{0,0,NULL,NULL}};
        left[length] = node[length-2];
        right[length] = node[length-1];
        parent.weight = left[length].weight +right[length].weight;
        parent.leftNode = &left[length];
        parent.rightNode = &right[length];
        node[length-2] = parent;
        length--;
    }
    return;
}
/*save huffman code to huffman table*/
void coding(huffmanNode_t *node,char *unfinished_code,int length){
    if(node->leftNode == NULL || node->rightNode == NULL){
        unfinished_code[length] ='\0';
        strcpy(huffmantable[(node->data)-0],unfinished_code);
        return;
    }
    unfinished_code[length] = '0';
    coding(node->leftNode,unfinished_code,length+1);
    unfinished_code[length] = '1';
    coding(node->rightNode,unfinished_code,length+1);
}

int zip(int mode)
{
    int frequency_table[256] ={0};/*table for huffman tree*/
    char read_char_buffer; /*buffer*/
    FILE *fpr = fopen(DATABASE,"r");/*input of originalfile*/
    if(fpr==NULL)
    {
        printf("no file detected!\n");
        return 1;
    }
    FILE *fpw = fopen(ZIPPED,"wb");
    FILE *config = fopen(".config", "w");
    huffmanNode_t node[100] = {{0,0,NULL,NULL}};/*Initialize nodes*/
    /*data for Statistical compression ratio*/
    int origianl_file_length = 0;
    int zipped_file_length = 0;
    /*load file, and statistical the frequence of text*/
    int current_node=0;
    /* temp code save*/
    char unfinished_code[10000];
    /*for compress*/
    unsigned char data_in_char = 0;
    int current=0;
    /*variable for loop*/
    int i;
    
    while((read_char_buffer = fgetc(fpr))!=EOF)
    {
        frequency_table[read_char_buffer-0]++;
        origianl_file_length++;
    }
    /*save the frequece table in nodes*/
    for(i=0;i<128;i++)
    {
        if(frequency_table[i]!=0)
        {
            node[current_node].data = i;/*ascii code*/
            node[current_node].weight = frequency_table[i];
            current_node++;
        }
    }
    /*build huffman tree*/
    create_huffman_tree(node,current_node);
    if(mode)
    {
        FILE *debug = fopen(DEBUGFILE, "w+");
        fprintf(debug, "-----------huffman tree-----------\n");
        print_huffman_pre(node,debug);
        fprintf(debug, ">>>>>>>>huffman tree end<<<<<<<<<<\n");
        fclose(debug);
        printf("proccess dumped\n");
    }
    /*coding in huffman tree*/
    coding(&node[0],unfinished_code,0);
    if(mode)
    {
        FILE *debug = fopen(DEBUGFILE, "a+");
        fprintf(debug, "-----------ascii table with huffman code-----------\n");
        for(i = 0; i<256;i++)
        {
            fprintf(debug,"%c\t%s\n",i,huffmantable[i]);
        }
        fprintf(debug, ">>>>>>>>>>ascii table with huffman code end<<<<<<<<\n");
        printf("proccess dumped\n");
        fclose(debug);
    }
    /*write config file*/
    for(i =0; i<256;i++)
    {
        fprintf(config,"%d %d\n",i,frequency_table[i]);
    }
    fclose(config);
    /*compress the DB*/
    fseek(fpr, 0L, 0);
    while ((read_char_buffer = fgetc(fpr))!=EOF) {
        for(i=0; i<strlen(huffmantable[read_char_buffer-0]); i++)
        {
            data_in_char |= huffmantable[read_char_buffer-0][i]-'0';
            current++;
            if(current == 8){
                fwrite(&data_in_char,sizeof(char),1,fpw);
                zipped_file_length++;
                data_in_char = 0;
                current=0;
            }
            else{
                data_in_char = data_in_char << 1;
            }
        }
    }
    if(current != 8){
        data_in_char = data_in_char << (7-current);
        fwrite(&data_in_char,sizeof(char),1,fpw);
        zipped_file_length++;
    }
    fclose(fpr);
    fclose(fpw);
    
    /*Statistical compression ratio*/
    printf("Compress finished!!!!!\n");
    printf("Original File:%d character\n",origianl_file_length);
    printf("Zipped File:%d character\n",zipped_file_length);
    printf("Compression ratio: %.2f%%\n",(float)(origianl_file_length-zipped_file_length)/origianl_file_length*100);
    return 0;
}
/*Find a node based on the code*/
huffmanNode_t *unzipcode(huffmanNode_t *node,int flag)
{
    if(flag ==0)
    {
        return node->leftNode;
    }else
    {
        return node->rightNode;
    }
}

int unzip(int mode)
{
    /*read config file*/
    FILE *config = fopen(".config", "r");
    int frequency_table[256];
    int ascii_code = 0;
    int frequency = 0;
    
    /*caculate file length, stop at file length reached */
    int file_length=0;
    
    /*unzip*/
    huffmanNode_t node[100] = {{0,0,NULL,NULL}};
    int current_node = 0;
    char read_char_buffer;
    FILE *fpr = fopen(ZIPPED, "rb");
    if(fpr==NULL)
    {
        printf("no zipped file detected!\n");
        return 1;
    }
    char samplechar = (char)128;
    char tempchar =0;
    huffmanNode_t *temp = &node[0];
    int length = 0;
    
    /*buckup database*/
    char newname[60];
    newname[0] =0;
    strcat(newname, DATABASE);
    strcat(newname, ".old");
    printf("Backup Old Database to : %s\n",newname);
    rename(DATABASE, newname);
    
    /*open database for decoding*/
    FILE *fpw = fopen(DATABASE, "w");
    
    /*variable for loop*/
    int i;
    /*read config file*/
    while(1)
    {
        fscanf(config,"%d %d\n",&ascii_code,&frequency);
        if(ascii_code>=128)
        {
            break;
        }
        frequency_table[ascii_code] = frequency;
    }
    if(mode)
    {
        FILE *debug = fopen(UNZIPDEBUGFILE,"w");
        for(i =0;i<128;i++)
        {
            fprintf(debug,"%c %d\n",i,frequency_table[i]);
        }
        printf("proccess dumped\n");
        fclose(debug);
    }
    
    /*get file_length*/
    for(i =0;i<128;i++)
    {
        file_length += frequency_table[i];
    }
    if(mode)
    {
        FILE *debug = fopen(UNZIPDEBUGFILE,"a+");
        fprintf(debug,"excepted file length is: %d\n",file_length);
        printf("proccess dumped\n");
        fclose(debug);
    }
    /*setup huffman tree*/
    for(i=0;i<128;i++)
    {
        if(frequency_table[i]!=0)
        {
            node[current_node].data = (char)i;/*ascii code*/
            node[current_node].weight = frequency_table[i];
            current_node++;
        }
    }
    create_huffman_tree(node,current_node);
    if(mode)
    {
        FILE *debug = fopen(UNZIPDEBUGFILE, "a+");
        fprintf(debug, "-----------huffman tree-----------\n");
        print_huffman_pre(node,debug);
        fprintf(debug, ">>>>>>>>huffman tree end<<<<<<<<<<\n");
        printf("proccess dumped\n");
        fclose(debug);
    }
    /*unzip the file*/
    while(fread(&read_char_buffer,sizeof(char),1,fpr))
    {
        if(file_length == length)
        {
            break;
        }
        for(i=0; i< 8; i++)
        {
            tempchar = read_char_buffer & samplechar;
            read_char_buffer = read_char_buffer << 1;
            tempchar = tempchar >>7;
            temp = unzipcode(temp,tempchar-0);
            if(temp->leftNode == NULL || temp->rightNode == NULL)
            {
                fprintf(fpw,"%c",temp->data);
                length++;
                temp = &node[0];
            }
        }
    }
    fclose(fpr);
    fclose(fpw);
    printf("Database updated!!!!!\n");
    return 0;
}



