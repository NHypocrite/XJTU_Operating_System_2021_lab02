/*软中断通信实验程序残缺版 */
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
    int wait_flag;
void stop(int signum);

main() {
	int pid1, pid2;  // 定义两个进程号变量
	signal(3, stop); // 或者 signal(14,stop);
	while ((pid1 = fork()) == -1)
		;           // 若创建子进程1不成功,则空循环
	if (pid1 > 0) { // 子进程创建成功,pid1为进程号
		while ((pid2 = fork()) == -1)
			; // 创建子进程2
		if (pid2 > 0) {
			wait_flag = 1;
			//   补充；				// 父进程等待5秒
			//   补充);      		       // 杀死进程1发中断号16
			kill(pid2, 17); // 杀死进程2
			wait(0);        // 等待第1个子进程1结束的信号
			wait(0);        // 等待第2个子进程2结束的信号
			printf("\n Parent process is killed !!\n");
			exit(0); // 父进程结束
		}
		else {
			wait_flag = 1;
			// 补充; // 等待进程2被杀死的中断号17
			printf("\n Child process 2 is killed by parent !!\n");
			exit(0);
		}
	} else {
		wait_flag = 1;
		signal(16, stop); // 等待进程1被杀死的中断号16
		printf("\n Child process 1 is killed by parent !!\n");
		exit(0);
	}
}
void stop(int signum) {
	// 补充;
	Printf("\n % d stop test \n", signum);
}
