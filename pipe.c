/*管道通信实验程序残缺版 */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
    int pid1,
    pid2; // 定义两个进程变量
main() {
	int fd[2];
	char InPipe[1000]; // 定义读缓冲区
	char c1 ='1', c2 ='2';
	pipe(fd); // 创建管道
	while ((pid1 = fork()) == -1)
		;            // 如果进程1创建不成功,则空循环
	if (pid1 == 0) { // 如果子进程1创建成功,pid1为进程号
		// 补充；       // 锁定管道
		    // 补充;    //  分200次每次向管道写入字符’1’
		 sleep(5);  // 等待读进程读出数据
		// 补充;        // 解除管道的锁定
		exit(0);     // 结束进程1
	}

	/*管道通信实验程序残缺版 （续） */ else {
		while ((pid2 = fork()) == -1)
			; // 若进程2创建不成功,则空循环
		if (pid2 == 0) {
			lockf(fd[1], 1, 0);
			// 补充; //  分200次每次向管道写入字符’2’
			sleep(5);
			lockf(fd[1], 0, 0);
			exit(0);
		} else {
			// 补充;                   // 等待子进程1 结束
			wait(0);                // 等待子进程2 结束
			// 补充;                   // 从管道中读出400个字符
			// 补充;                   //  加字符串结束符
			printf("%s\n", InPipe); // 显示读出的数据
			exit(0);                // 父进程结束
		}
	}
}
