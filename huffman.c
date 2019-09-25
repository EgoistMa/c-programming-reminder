
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//define huffmanNode struct
typedef struct huffmanNode
{
	int weight;
	char data;
	struct huffmanNode *leftNode;
	struct huffmanNode *rightNode;
	char * huffmancode;
} huffmanNode_t;

typedef struct feq_table
{
	char c;
	int f;
} feq_table_t;

typedef struct huffman_code_table
{
	char c;
	char code;
} huffman_code_table_t;

typedef struct record
{
	int year;
	int month;
	int date;
	struct record *next;
} record_t;
int readFile(FILE *fp,feq_table_t *feq_table)
{
	if(fp == NULL)
	{
		return 1;
	}
	char line[1024] = "";
	FILE *debug = fopen("debug.txt","w+");
	int feq_table_size = 0;
	int i;
	while (fgets(line, 1024, fp))
	{
		fprintf(debug,"%s\n",line);
		char *p = line;
		while(*p != '\0' && *p !='\n')
		{
			for(i = 0;i<=feq_table_size;i++)
			{
				if(feq_table[i].c == *p)//current char in the feq_table
				{
					feq_table[i].f++;
					break;
				}
				if(i == feq_table_size && feq_table[i].c != *p)//current char not in the feq_table
				{
					feq_table[feq_table_size].c = *p;
					feq_table[feq_table_size].f = 1;
					feq_table_size++;
					break;
				}
			}
			p++; //get next char of the p
		}

	}
	//feq_table = (feq_table_t *)realloc(feq_table,(feq_table_size-1)*sizeof(feq_table_t));
	/* need to fix this */ //feq_table[feq_table_size] = '\0';
	return feq_table_size;
}
int sort(huffmanNode_t *node,int len)
{
	int i,j;
	huffmanNode_t temp;
	for(i=0;i<len-1;i++)
	{
		for(j=0; j <len-i-1;j++)
		{
			if(node[j].weight < node[j+1].weight)
			{
				temp = node[j];
				node[j] = node[j+1];
				node[j+1] = temp;
			}
		}
	}
	return 0;
}

huffmanNode_t create_Huffman_Tree(int element_in_feq_table, feq_table_t feq_table[])
{
	//allocate nodes memo address
	huffmanNode_t *root = NULL;
	huffmanNode_t *huffmanNodes = calloc(element_in_feq_table, sizeof(huffmanNode_t));
	huffmanNode_t *huffmanNodes_DATA = calloc(element_in_feq_table, sizeof(huffmanNode_t));
	int current=0;\
	int element_in_huffmanNodes=0;
	int i;
	for(i=0;i<element_in_feq_table;i++)
	{
		huffmanNode_t *node = (huffmanNode_t *)malloc(sizeof(huffmanNode_t));
		(*node).data = feq_table[i].c;
		(*node).weight = feq_table[i].f;
		(*node).leftNode = NULL;
		(*node).rightNode = NULL;
		huffmanNodes[element_in_huffmanNodes++] = *node;
		
	}
	
	
	while(element_in_huffmanNodes>0)
	{
		sort(huffmanNodes,element_in_huffmanNodes);  //weight high -> low
		printf("--------debug mode--------\n");
		for(int i =0;i<element_in_huffmanNodes;i++)
		{
			printf("<%c\t%d>",huffmanNodes[i].data,huffmanNodes[i].weight);
		}
		printf("\n");
		printf("--------end debug mode--------\n");
		
		if(element_in_huffmanNodes == 1)
		{
			root = &huffmanNodes[0];
			element_in_huffmanNodes--;
		}else
		{
			//get last two nodes
			huffmanNodes_DATA[current++] = huffmanNodes[element_in_huffmanNodes-1];
			huffmanNodes_DATA[current++] = huffmanNodes[element_in_huffmanNodes-2];
			//remove last two nodes
			element_in_huffmanNodes = element_in_huffmanNodes - 2;
			//make the new node
			huffmanNode_t *temp_node = (huffmanNode_t *) calloc(1, sizeof(huffmanNode_t));
			(*temp_node).weight = huffmanNodes_DATA[current-2].weight + huffmanNodes_DATA[current-1].weight;
			if(huffmanNodes_DATA[current-2].weight<huffmanNodes_DATA[current-1].weight)
			{
				(*temp_node).leftNode = &huffmanNodes_DATA[current-2];
				(*temp_node).rightNode = &huffmanNodes_DATA[current-1];
			}else
			{
				(*temp_node).leftNode = &huffmanNodes_DATA[current-1];
				(*temp_node).rightNode = &huffmanNodes_DATA[current-2];
			}
			element_in_huffmanNodes++;
			huffmanNodes[element_in_huffmanNodes-1] = *temp_node;
		}
	}
	return *root;
}
int print_huffman_pre(huffmanNode_t *root){
	if (root != NULL){
		fprintf(stderr, "%c\t%d\n", (*root).data, (*root).weight);
		print_huffman_pre((*root).leftNode);
		print_huffman_pre((*root).rightNode);
	}
	return 0;
}

int print_leaf(huffmanNode_t *root){
	if (root != NULL){
		print_leaf((*root).leftNode);
		if ((*root).leftNode == NULL && (*root).rightNode == NULL)
		{
			printf("%c\t%s\n", (*root).data, (*root).huffmancode);
			
		}
		print_leaf((*root).rightNode);
	}
	return 0;
}

int set_huffman_code(huffmanNode_t *root,char* s,int len)
{
	huffmanNode_t current = *root;
	if(current.leftNode != NULL)
	{
		strcat(s,"0");
		set_huffman_code(*&(current.leftNode),s,len+1);
	}
	if (current.rightNode != NULL)
	{
		strcat(s,"1");
		set_huffman_code(*&(current.rightNode),s,len+1);
	}
	if(current.leftNode == NULL && current.rightNode == NULL)
	{
		s[len] = '\0';
		(*root).huffmancode = (char *)malloc(sizeof(char)*20);
		strcpy((*root).huffmancode,s);
		s[len-1] = '\0';
	}else
	{
		s[len-1] = '\0';
	}
	return 0;
}



int set_huffman_table(huffmanNode_t *root,int n,huffman_code_table_t *table[n])
{
	
	return 0;
}

int zip(int debugmode)
{
	//reading a file and find the frequency of chars
	FILE *fp = fopen("a.txt", "r+");
	feq_table_t feq_table[129];
	int n = readFile(fp,feq_table);
	feq_table_t feq_table_fianl[n];
	int temp;
	for(temp =0;temp<=n;temp++)
	{
		feq_table_fianl[temp] = feq_table[temp];
	}
	if(debugmode)
	{
		 printf("--------debug mode--------\n");
		int test_i,test_sum = 0;
		for(test_i = 0; test_i < n;test_i++)
		{
			printf("%c%d\n",feq_table_fianl[test_i].c,feq_table_fianl[test_i].f);
			test_sum += feq_table_fianl[test_i].f;
		}
		 printf("--------end debug mode--------\n");
	}
	
	int element_in_feq_table = (int)(sizeof(feq_table_fianl)/sizeof(feq_table_t));

	//create huffman tree
	huffmanNode_t root = create_Huffman_Tree(element_in_feq_table, feq_table_fianl);
	if(debugmode)
	{
		printf("--------debug mode--------\n");
		printf("pre-order\n");
		print_huffman_pre(&root);
		 printf("--------end debug mode--------\n");
	}
	//create huffman code
	char *s = (char *)malloc(sizeof(char)*128);
	s[0] = '\0';
	set_huffman_code(&root,s,0);
	if(debugmode)
	{
		printf("--------debug mode--------\n");
		printf("print leafs\n");
		print_leaf(&root);
		printf("--------end debug mode--------\n");
	}
	huffman_code_table_t *table[element_in_feq_table];
	set_huffman_table(&root,element_in_feq_table,table);
	return 0;
}
int main()
{
	int mode = 1;
	zip(mode);
}

record_t* search_by_date(record_t *root,int year,int month,int date)
{
	//find length of records
	record_t *current;
	record_t *results = NULL;
	record_t *head = results;
	//searching
	for (current = root; current !=NULL; current = (*current).next) {
		if((*current).year == year && (*current).month == month && (*current).date == date)
		{
			results = current;
			results = results->next;
		}
	}
	return head;
}
