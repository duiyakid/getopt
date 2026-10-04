#ifndef GETOPT_H
#define GETOPT_H

/* ---- 导出宏 ---- */
#ifdef GETOPT_EXPORTS
#define GETOPT_API __declspec(dllexport)
#else
#define GETOPT_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	GETOPT_API extern char* optarg;   /* 当前选项的参数 */
	GETOPT_API extern int   optind;   /* 下一个待处理参数的索引 */
	GETOPT_API extern int   opterr;   /* 是否打印错误信息，默认 1 */
	GETOPT_API extern int   optopt;   /* 出错的选项字符 */

	/* 与标准 getopt 行为一致：返回选项字符，无更多选项时返回 -1，出错返回 '?' */
	GETOPT_API int getopt(int argc, char* const argv[], const char* optstring);

#ifdef __cplusplus
}
#endif

#endif /* GETOPT_H */