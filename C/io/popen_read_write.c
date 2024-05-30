#include <stdio.h>
int main()
{
    FILE *fpr = NULL, *fpw = NULL;
    char buf[256];
    int ret;

    fpr = popen("cat /etc/group", "r");  //执行完这行代码，标准输出就装满，这里这个标准输出标记为out1，管道指向out1，fpr指向管道的读端
    fpw = popen("grep root", "w");       //执行这句代码，会一直去读取标准输出，若标准输出为空，则会阻塞，直到标准输出不为空，执行命令后又
                                         //会去指读取标准输出继续执行。这里这个标准输入标记为in2。
                                         //管道指向int2，fpw指向管道的写端

    while ((ret = fread(buf, 1, sizeof(buf), fpr)) > 0)  //从out1中读取256个字节数据，存放在buf
    {
        fwrite(buf, 1, ret, fpw);                        //将buf的数据写到int2(此时gerp命令一直在获取int2，直到进行退出)
    }

    pclose(fpr);
    pclose(fpw);
}