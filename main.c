/*********************************************************************************************************
* Author: Dimitrios Tsamis
* This Console Application is used for duplicates detection in a file containing licence plates
* It is specifically designed for plates that have the format : AAA000.
* In this program, speed is achieved by the fact that every licence plate is checked for duplication during insertion.
* First, 1000 binary search trees are created for each of the different plates ending numbers. 000-999.
* Then each letter triplet is inserted in the corresponding binary search tree.
* If during insertion, a duplicate is found, the program shows the plate that was found to be duplicate.
* Due to the layout of the program, it can further be improved to store all the duplicate plates in another file
* and therefore getting the maximum information available from the data.**********************************/




#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>


struct bin_tree {
char data[4];
struct bin_tree * right, * left;
};

typedef struct bin_tree node;


char* insert(node ** tree, char *val) {
node *temp=NULL;
if(!(*tree))
{
   temp = (node *)malloc(sizeof(node));
   temp->left = temp->right = NULL;
   strcpy(temp->data,val);
   *tree = temp;
   return val;
 }

if(strcmp(val,(*tree)->data)<0)
    {
      insert(&(*tree)->left, val);
      return val;
    }
else if(strcmp(val,(*tree)->data)>0)
    {
     insert(&(*tree)->right, val);
     return val;
    }
     else return "dupl";


 }

int main()
{
    char firstpart[4];   //Keeping each plate alphabetical part separate
    int secondpart;      //Keeping the number ending
    FILE *fp;
    node **tree;         //The plates will be inserted in binary search trees.
    char filename[100];
    clock_t begin;
    clock_t end;
    int i;



    tree=(node**)malloc(1000*sizeof(node*));
    for(i=0;i<1000;i++)
        tree[i]=NULL;

    printf("Please enter the file to be searched for duplicates:"); //Getting the filename from the user
    scanf("%s",filename);

    begin=clock();


    fp=fopen(filename,"r");

    if(fp==NULL)
    {
        printf("File Error");
        return 0;

    }

     while(!feof(fp))
    {

        fgets(firstpart,4,fp);
        fscanf(fp,"%d\n",&secondpart);

        if(strcmp(insert((&tree[secondpart]),firstpart),"dupl")==0)   //If a plate's alphabetical triplet is found in the same tree, it is a duplicate.
        {
        //Here, if instead of printf we use fprintf and don't stop the program execution by returning,we can store all the duplicates in a separate file.

        //printf("Found duplicate plate %s%03d\n",firstpart,secondpart); //If this line is uncommented, we can also see the duplicate plate.
        printf("Dubbletter");
        end = clock();
        printf("Execution time:%f",((double)(end - begin) / CLOCKS_PER_SEC));
        return 0;
        }


    }

//If the end of file is reached without any duplicate found, the program shows the user that no duplicate has been found.

        printf("Ej dubblett\n");
        end = clock();
        printf("Execution time:%f",((double)(end - begin) / CLOCKS_PER_SEC));
        return 0;

}
