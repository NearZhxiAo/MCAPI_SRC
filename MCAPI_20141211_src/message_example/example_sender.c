/*===============================================================
*   Copyright (C) 2014 All rights reserved.
*   
*   文件名称：example_sender_message.c
*   创 建 者：张 笑
*   创建日期：2014年12月10日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#define __USE_GNU
#include <sched.h>
#include <pthread.h>
#include <ctype.h>
#include <mcapi.h>
#include <math.h>

#define BUFLEN 30

#define TIMEOUT 5000
#define NAME "SEND: "

int main(int argc,char*argv[])
{
	int process_num=sysconf(_SC_NPROCESSORS_CONF);
	printf("%i processors() in KeyStoneII system.\n\r",process_num);
	cpu_set_t mask;
	int myid= atoi(argv[1]);
	CPU_ZERO(&mask);
	CPU_SET(myid,&mask);
	if(sched_setaffinity(getpid(),sizeof(mask),&mask)==-1)
	{
		printf("Error: set CPU affinity failed.\n\r");
		return 0;
	}
	printf("Set CPU affinity success!\n\r");
	usleep(3000000);
	if(CPU_ISSET(myid, &mask)) 
	{
		printf("SEND is running on Processor %i\n\r",myid);
	}
	usleep(3000000);
	mcapi_status_t status;
	mcapi_info_t info;
	char status_msg[MCAPI_MAX_STATUS_MSG_LEN];

	mcapi_request_t request;
	size_t size=1;
	
	mcapi_endpoint_t send_msg_point;
	mcapi_endpoint_t recv_msg_point;

	char send_buf[BUFLEN]="HelloWorld";

	mcapi_initialize(THE_DOMAIN,RED_NODE,0,0,&info,&status);

	send_msg_point=mcapi_endpoint_create(RED_MSG,&status);
	recv_msg_point=mcapi_endpoint_get(THE_DOMAIN,YELLOW_NODE,YELLOW_MSG,TIMEOUT,&status);

	mcapi_msg_send(send_msg_point,recv_msg_point,send_buf,BUFLEN,0,&status);
	usleep(3000000);
	mcapi_finalize(&status);
	return EXIT_SUCCESS;
}
