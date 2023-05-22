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

void search(Instruction* head){//recursive search from node backwards to see linked reg's
  Instruction* ptr = head;
  Instruction* pre = ptr->prev;
  switch(ptr->opcode){

  case STOREAI:
    if(ptr->critical == '1'){
			while(pre!=NULL){
				if(ptr->field1 == pre->field3){
					pre->critical = '1';
					search(pre);
					break;
				}
				else if(ptr->field1 == pre->field2){
					pre->critical = '1';
					break;
				}
				pre= pre->prev;
			}
    }
		return;
  case LOADAI:
	while( pre != NULL){
		if( pre->opcode == STOREAI && pre->field2 == ptr->field1 && pre->field3 == ptr->field2){
			pre->critical = '1';
			search(pre);
			break;
		}
			pre = pre->prev;
	}
	return;
  case LOADI:
		return;
	case LSHIFTI:
	if(ptr->critical == '1'){
		while(pre!=NULL){
			if(ptr->field1 == pre->field3){
				pre->critical = '1';
				search(pre);
				break;
			}
			else if(ptr->field1 == pre->field2){
				pre->critical = '1';
				break;
			}
			pre= pre->prev;
		}
	}
	case RSHIFTI:
	if(ptr->critical == '1'){
		while(pre!=NULL){
			if(ptr->field1 == pre->field3){
				pre->critical = '1';
				search(pre);
				break;
			}
			else if(ptr->field1 == pre->field2){
				pre->critical = '1';
				break;
			}
			pre= pre->prev;
		}
	}
	return;
  case ADD:
	if(ptr->critical=='1'){
		int both = 0;
		while(pre!=NULL){
			if(pre->field2==ptr->field1 || pre->field2 == ptr->field2 || pre->field3==ptr->field1 || pre->field3 == ptr->field2){
				pre->critical='1';
				search(pre);
				both++;
				if(both==2){
					break;
				}
			}
			pre= pre->prev;
		}
	}
	return;
  case SUB:
	if(ptr->critical=='1'){
		int both = 0;
		while(pre!=NULL){
			if(pre->field2==ptr->field1 || pre->field2 == ptr->field2 || pre->field3==ptr->field1 || pre->field3 == ptr->field2){
				pre->critical='1';
				search(pre);
				both++;
				if(both==2){
					break;
				}
			}
			pre= pre->prev;
		}
	}
	return;
  case MUL:
	if(ptr->critical=='1'){
		int both = 0;
		while(pre!=NULL){
			if(pre->field2==ptr->field1 || pre->field2 == ptr->field2 || pre->field3==ptr->field1 || pre->field3 == ptr->field2){
				pre->critical='1';
				search(pre);
				both++;
				if(both==2){
					break;
				}
			}
			pre= pre->prev;
		}
	}
	return;
	case DIV:
	if(ptr->critical=='1'){
		int both = 0;
		while(pre!=NULL){
			if(pre->field2==ptr->field1 || pre->field2 == ptr->field2 || pre->field3==ptr->field1 || pre->field3 == ptr->field2){
				pre->critical='1';
				search(pre);
				both++;
				if(both==2){
					break;
				}
			}
			pre= pre->prev;
		}
	}
	return;
  case OUTPUTAI:
    while( pre != NULL){
      if( pre->opcode == STOREAI && pre->field2 == ptr->field1 && pre->field3 == ptr->field2){
	pre->critical = '1';
	search(pre);
	break;
      }
      pre = pre->prev;
    }
    return;
}
}

Instruction *dead_code_elimination(Instruction* head){
  Instruction* ptr = head;
  while(ptr != NULL){
    if( (ptr->opcode == OUTPUTAI)){
      ptr->critical = '1';
			search(ptr);
    }
    ptr = ptr->next;
  }
  Instruction* fptr = head;
	Instruction* temp = head;
	fptr= fptr->next;
  while(fptr != NULL){
    if(fptr->critical=='1'){
			temp->next = fptr;
			temp= temp->next;
			fptr = fptr->next;
		}
		else{
			Instruction* fre = fptr->next;
			free(fptr);
			fptr = fre;
		}
  }
	return head;
}


int main()
{
  Instruction* head;

  head = ReadInstructionList(stdin);

  if (!head) {
    WARNING("No instructions\n");
    exit(EXIT_FAILURE);
  }

  head = dead_code_elimination(head);

  if (head) {
    PrintInstructionList(stdout, head);
  }
  return EXIT_SUCCESS;
}
