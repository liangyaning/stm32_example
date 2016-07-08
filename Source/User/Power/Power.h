
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
