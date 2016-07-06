/*******************************************************************************
        (c) COPYRIGHT 2010-2018 by Efficient Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to Efficient 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between Efficient Systems and its licensee.
 FileName    : Power.h
 Author      : ranwei
 Version     : 
 Date        : 2016/3/2 16:57:9:982
 Description : 
 Others      : 

 History      :
  1.Date         -- 2016/3/2 16:57:9:982
    Author       -- ranwei
    Modification -- Created file

*******************************************************************************/
#ifndef __POWER_H__
#define __POWER_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#ifdef  POWER_GLOBAL
#define POWER_EXT
#else
#define POWER_EXT extern
#endif /* POWER_GLOBAL */

void Power_Init(void);
void Power_On(void);
void Power_Off(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __POWER_H__ */
/**************** (C) COPYRIGHT 2010-2018 Efficient *****END OF FILE***********/
