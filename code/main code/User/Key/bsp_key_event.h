#ifndef __KEY_EVNET_H
#define __KEY_EVNET_H


#include "stm32f10x.h"



extern void key_event_init();                              //初始化按键消息
extern void deal_key_event(void);                          //处理按键消息（自动切换选中的数字，自动对数字进行加减）



#endif /* __KEY_EVNET_H */