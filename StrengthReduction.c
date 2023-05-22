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
#include <math.h>
#include "InstrUtils.h"
#include "Utils.h"

int isLog2(int n) {

	int s = 1, i = 0;

	while (s < n) {
		s = s << 1;
		i++;
	}

	if (s == n)
		return i;
	else
		return -1;

}

/*
* Will traverse instructions in groups of two, searching for a patten of LOADI and MUL | DIV instructions
* where LOADI is a power of 2, and collapse these instructions into on shift operation of LSHIFTI | RSHIFTI
*/
Instruction *strength_reduction(Instruction *head) {
	/* STUDENTS - BEGIN */
	Instruction *ptr = head;
	while (ptr) {
		if(ptr->next != NULL && ptr->next->next != NULL){
			if(ptr->opcode == LOADI && ptr->next->opcode == LOADI
				&& (ptr->next->next->opcode == MUL || ptr->next->next->opcode == DIV)){
				Instruction *operator = ptr->next->next;
				Instruction *loadTwo = ptr->next;
				int lognum;
				if(operator->field2 == loadTwo->field2) {
					lognum = isLog2(loadTwo->field1);
					if (lognum == -1) {
						ptr = ptr->next;
						continue;
					}
				} else if(operator->field2 == ptr->field2) {
					lognum = isLog2(ptr->field1);
					if (lognum == -1) {
						ptr = ptr->next;
						continue;
					}
				}
				if (operator->opcode == DIV) {
					operator->opcode = RSHIFTI;
				}else if (operator->opcode == MUL) {
					operator->opcode = LSHIFTI;
				}
				operator->field2 = lognum;
			} else if (ptr->opcode == LOADI && (ptr->next->opcode == MUL || ptr->next->opcode == DIV)) {
				int lognum = isLog2(ptr->field1);
				if (lognum == -1) {
					ptr = ptr->next;
					continue;
				}
				Instruction *temp = ptr->next;
				if (temp->opcode == DIV) {
					temp->opcode = RSHIFTI;
				}else if (temp->opcode == MUL) {
					temp->opcode = LSHIFTI;
				}
				temp->field2 = lognum;
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

	head = strength_reduction(head);

	if (head)
		PrintInstructionList(stdout, head);

	return EXIT_SUCCESS;
}
