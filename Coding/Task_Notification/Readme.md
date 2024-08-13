1.Notification.c

This an example when switch is pressed, button task will send the notification to task-1 where it receives notification and prints.


2.Notification_ISR.c

UART interupt:
After buffer completed receiving the given size of bytes then UART IRQ handle is triggered.
This xTaskNotifyFromISR is called from UART IRQ Handle. this notifies to TASK 1 to wake up.
Then Task 1 is printed in Tera term 

Note:
This is a pointer to a BaseType_t variable. If the notification causes a task to unblock, and if the unblocked task has a priority higher than the currently running task, the variable pointed to by pxHigherPriorityTaskWoken will be set to pdTRUE. This is typically used to request a context switch when the ISR completes.
