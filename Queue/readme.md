This folder has queue tried example on my own 

1.send_receive file 

passing structure data of student from TASK A to TASK B
queue creation with the help of struct student pointer which can reduce heap memory 
suppose if u create with struct student then it will be more byte occupied.

tried with generic apporach below with out typedef 

here we have two points to note 
1.creating with struct student * occupies less bytes of heap (or)  struct student only occupies more bytes of heap
2.usig typedef apporach for struct student.

Below tried with generic apporach below with out typedef. 
struct student{

char name[7];
uint8_t roll_no;

};   

//main loop 
myQueue = xQueueCreate(5, sizeof( struct student* ));   //
configASSERT(myQueue != NULL);

void Task_1(void *pvparameters)
{

	 struct student *ps1;
	 struct student xstudent;
	 strcpy(xstudent.name ,"karthik");
	 xstudent.roll_no = 3;

     ps1 = &xstudent;
    xQueueSend(myQueue,(void*)&ps1,0);

	while(1)
	{

	}

}


void Task_2(void *pvparameters)
{
	struct student xrStudent,*pxrStudent;
	while(1){

		if(myQueue!=NULL){

			if(xQueueReceive(myQueue, (void*)&pxrStudent ,5)){

			//	UART_Transmit(&UART_0,(uint8_t*) receive, sizeof(receive)-1);

				//try from udemy notes once for heap size optimisation
				 strcpy(xrStudent.name , pxrStudent->name);
			   //	xrStudent.name = pxrStudent->name;   you got error here
				xrStudent.roll_no =  pxrStudent->roll_no;

				printf("hello\r\n");  //dummy kept for break point

			}
		}
	}

}


2.send_receive file  

In this file Task A send global data to another Task B 
data is not corrupted between them.

Task A goes to block state after sending 10 values to queue 



3.queue 

TAsk1 send 2 times data to the queue receive will take that data receive side array is implemented.

4.queue and 5.queue will are almost same vishal bro sensor project equivalent done here.
