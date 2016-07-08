#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#ifdef  MAIN_GLOBAL
#define MAIN_EXT
#else
#define MAIN_EXT extern
#endif /* MAIN_GLOBAL */

#define SERIAL_DEBUG

// 调试信息打印，同时打印文件名和行号
#define __DEBUG__
#ifdef __DEBUG__
#define DEBUG(format,...) printf("File: "__FILE__", Line: %05d: "format"\n", __LINE__, ##__VA_ARGS__)
#else
#define DEBUG(format,...)
#endif

// 调试信息打印，不打印文件名和行号
#define MY_DEBUG
#ifdef MY_DEBUG
#define mprint(format,...) printf(format, ##__VA_ARGS__)
#else
#define mprint(format,...)
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MAIN_H__ */
