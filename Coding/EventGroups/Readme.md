1.eventgrouptask.c file has temp and pressure task  run indivudually 
the calibration task runs only when it receives signal from temp and pressure tasks completion send as event finished to calibration task.

#define configUSE_EVENTS_GROUPS  1 
if above macro is there or not no problem in XMC 4400 it worked.
