/*===============================================================
*   Copyright (C) 2014 All rights reserved.
*   
*   文件名称：example_receiver_pktchan.c
*   创 建 者：张 笑
*   创建日期：2014年12月09日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdlib.h>
#include <mcapi.h>
#include <stdio.h>

#define TIMEOUT 5000
#define BUFSIZE 1024

#define NAME "RECV: "

int main()
{
	mcapi_status_t status;
	mcapi_info_t info;

	char status_msg[MCAPI_MAX_STATUS_MSG_LEN];
	size_t size;
	size_t bufsize;

	mcapi_request_t request;

	char *recvbuf=NULL;
	recvbuf=(char*)malloc(sizeof(char)*BUFSIZE);

	mcapi_endpoint_t recv_point;
	mcapi_endpoint_t send_point;
	mcapi_pktchan_recv_hndl_t handy;
	printf(NAME "Receiver here!\n");

	mcapi_initialize(THE_DOMAIN,GREEN_NODE,0,0,&info,&status);
	mcapi_display_status(status,status_msg,MCAPI_MAX_STATUS_MSG_LEN);

	printf(NAME "Result of initialization: %s\n\r",status_msg);

	printf(NAME "creating receiving endpoing.\n\r");
	recv_point=mcapi_endpoint_create(GREEN_PKT,&status);

	printf(NAME "obaitaing endpoint.\n\r");
	send_point=mcapi_endpoint_get(THE_DOMAIN,YELLOW_NODE,YELLOW_PKT,TIMEOUT,&status);
	mcapi_pktchan_connect_i(send_point,recv_point,&request,&status);
	mcapi_wait(&request,&size,TIMEOUT,&status);
	printf(NAME "opening the receving end of the channel.\n\r");
	mcapi_pktchan_recv_open_i(&handy,recv_point,&request,&status);
	//mcapi_wait(&request,&size,TIMEOUT,&status);
	printf(NAME "receving.\n\r");

	mcapi_pktchan_recv(handy,(void *)&recvbuf,&bufsize,&status);
	printf(NAME "received %s\n\r",(char*)recvbuf);
	printf(NAME "closing!\n\r");
	free(recvbuf);
	mcapi_pktchan_recv_close_i(handy,&request,&status);
	mcapi_wait(&request,&size,TIMEOUT,&status);
	printf(NAME "closed!\n");
	mcapi_finalize(&status);
	return EXIT_SUCCESS;
}
