/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Spring 2023                              *
 *  Student Version                          *
 *  Author: Andy Cheung                      *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

/*
* Will traverse instructions in groups of 3, searching for a patten of LOADI, LOADI, and ADD | SUB | MUL instructions
*/

Instruction *constant_folding(Instruction *head) {
    /* STUDENTS - BEGIN */
    Instruction *ptr = head;
    while (ptr) {
        if (ptr->opcode == LOADI && ptr->next->opcode == LOADI) {
            int first = ptr->field1;
            int second = ptr->next->field1;
            int result = 0;
            if(ptr->next->next == NULL) {
                ptr = ptr->next;
                continue;
            }
            Instruction *operator = ptr->next->next;
            if(operator->field1 == ptr->field2 && operator->field2 == ptr->next->field2) {
                if (ptr->next->next->opcode == ADD) {
                    result = first + second;
                }
                else if (ptr->next->next->opcode == SUB) {
                    result = first - second;
                }
                else if (ptr->next->next->opcode == MUL) {
                    result = first * second;
                } else {
                    ptr = ptr->next;
                    continue;
                }
                Instruction *temp = ptr->next->next;
                temp->field1 = result;
                temp->opcode = LOADI;
                temp->field2 = temp->field3;

            }
        }
        ptr = ptr->next;
    }

    return head;
    /* STUDENTS - END */
}

int main()
{
    Instruction *head;
    head = ReadInstructionList(stdin);
    if (!head) {
        WARNING("No instructions\n");
        exit(EXIT_FAILURE);
    }

    head = constant_folding(head);

    if (head)
        PrintInstructionList(stdout, head);

    return EXIT_SUCCESS;
}
