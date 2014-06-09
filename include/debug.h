//***********************************************************************/
//    Author                    : Erwin
//    Email                     : erwin.wang@qq.com
//    Original Date             : 29th May, 2014
//    Module Name               : debug.h
//    Module Funciton           : 

//                                This module countains the definations,
//                                data types,and procedures of debug subsystem.
//								  Only the log function has been implemented.
//
//    Last modified Author      :
//    Last modified Date        :
//    Last modified Content     :
//                                1.
//                                2.
//    Lines number              :
//***********************************************************************/
#ifndef __DEBUG_H__
#define __DEBUG_H__

typedef struct LOG_MESSAGE{
	int code;
	int len;
	int time;
	int pid;
	int tid;

	int format;

	char *name;
	char *tag;
	char *msg;
}__LOG_MESSAGE;

//typedef struct LOGK_MESSAGE{
//	int code;
//	int len;
//	int time;
//	int pid;
//	int tid;
//
//	int format;
//
//	char *tag;
//
//	char *msg;
//}__LOGK_MESSAGE;

typedef struct BUFFER_QUEUE
{
	__LOG_MESSAGE BufferQueue[256];
	int head;
	int tail;
	int len;

	void (*Enqueue)(struct BUFFER_QUEUE *pThis, __LOG_MESSAGE *pMsg);
	__LOG_MESSAGE *(*Dequeue)(struct BUFFER_QUEUE *pThis);

}__BUFFER_QUEUE;

//typedef struct LOGK_POOL
//{
//	__LOGK_MESSAGE LogPool[128];
//	int head;
//	int tail;
//	int len;
//
//	void (*Enqueue)(struct LOGK_POOL *pThis, __LOG_MESSAGE *pMsg);
//	__LOG_MESSAGE *(*Dequeue)(struct LOGK_POOL *pThis);
//
//}__LOGK_POOL;

typedef struct DEBUG_MANAGER{
	//一个同步对象 用啥呢？
	__MUTEX *pMutexForBufferQueue;
	// User logpool..
	__BUFFER_QUEUE *pBufferQueue;

	// For kernel bufferqueue and sync
	__MUTEX *pMutexForKRNLBufferQueue;
	__BUFFER_QUEUE *pKRNLBufferQueue;

	void (*Log)(struct DEBUG_MANAGER *pThis, char *tag, char *msg);
	void (*Logk)(struct DEBUG_MANAGER *pThis, char *tag, char *msg);
	void (*Logcat)(struct DEBUG_MANAGER *pThis, char *buf, int len);
	void (*Initialize)(struct DEBUG_MANAGER *pThis);
	void (*Unintialize)(struct DEBUG_MANAGER *pThis);
}__DEBUG_MANAGER;

extern __DEBUG_MANAGER DebugManager;

#endif //end __DEBUG_H__