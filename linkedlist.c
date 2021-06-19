/*Author: Henry Zhang*/
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "linkedlist.h"


/*Iterates through a linked list and has a call-back function that does something*/ 
void iterate(void *head, ActionFunction doThis)
{

	Node *temp = head;

    while (temp != NULL)
    {
       	doThis(temp->data);
        temp = temp->next;
   	}

}

/*Returns the least value in a linked list, returns NAN if list is empty*/
double least(void *head, NumericFunction compute_this)
{

	Node *temp = head;
    double least, secondLeast;

    if (temp == NULL)return 0./0.;

    else least = *(double*)temp->data;

    while(temp != NULL)
    {
        if (temp->next != NULL)secondLeast = *(double*)temp->next->data;
        if (least > secondLeast)least = secondLeast;
        temp = temp->next;
    }

    return least;

}

/*If an element in the linked list pass someTest, returns true*/
int some(void *head, CriteriaFunction someTest)
{
    int rval = 0;
    Node *nodePtr = head;
    while (head != NULL)
    {
        if (!someTest(nodePtr->data))
        {
            head = (Node*)nodePtr->next;
            if(nodePtr->next != NULL)nodePtr = (Node*)nodePtr->next;
        }

        if (someTest(nodePtr->data))
        {
            rval = 1;
            break;
        }

    }
    return rval;
}



