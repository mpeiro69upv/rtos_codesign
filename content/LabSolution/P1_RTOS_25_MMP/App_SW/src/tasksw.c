
#include "..\inc\tasksw.h"

/*
 * SW1:SW0 -> indicate the action: 00:none, 01:suspends, 10:resumes,11:none
 * SW5:SW2 -> indicate the PRIO of the task for the previous action
 * Note: the PRIO TASK7_PRIORITY has no effect (the task do not self suspends or self resumes)
 */
void TaskSW(void* pdata)
{
	INT8U action, action_old;
	INT8U item;
	INT8U err;
	for(;;){
		action_old=action;
		action=*SW_switch_ptr&0x0003;
		item=(*SW_switch_ptr>>2)&0x000F;
		if(action!=action_old){
			OSSemPend(Semaphore,0,&err);
			alt_ucosii_check_return_code(err);
			printf("Action is %d - ",action);
			printf("Item is %d\n",item);
			OSSemPost(Semaphore);
		}
		if ((INT8U)item!=TASK_SWITCH_PRIORITY){
			OSSemPend(Semaphore,0,&err);
			alt_ucosii_check_return_code(err);
			printf("Hello from TaskSW\n");
			OSSemPost(Semaphore);

			switch (action)
			{
				case 2:
				{
					err=OSTaskResume((INT8U)item);
					if (err!=OS_ERR_NONE){
						OSSemPost(Semaphore);
						alt_ucosii_check_return_code(err);
						printf("Task%0d resumed\n",item);
						OSSemPost(Semaphore);
						
					}
					break;
				}
				case 1:
				{
					err=OSTaskSuspend((INT8U)item);
					if (err!=OS_ERR_NONE){
						OSSemPend(Semaphore,0,&err);
						alt_ucosii_check_return_code(err);
						printf("Task%0d suspended\n",item);
						OSSemPost(Semaphore);
					}
					break;
				}

				default:
					break;
			}
		}

		// when SW8 is ON activates Flags
		/*
		if(*SW_switch_ptr&0x80){
			OSFlagPost(EventFlag,0x04,OS_FLAG_SET, &err);
			alt_ucosii_check_return_code(err);
		} else {
			OSFlagPost(EventFlag,0x04,OS_FLAG_CLR, &err);
			alt_ucosii_check_return_code(err);
		}
		*/
		OSTimeDlyHMSM(0,0,1,500);
	}
}
