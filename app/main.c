#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/io/fcntl.h>
#include <psp2/appmgr.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char* argv[])
{
    char title_id[9];
    char uri[32];
    SceUID file_id = sceIoOpen(
        "ux0:launch_last_played.tid",
        SCE_O_RDONLY,
        0777);

    if(file_id < 0)
        return 1;

    sceIoRead(file_id, title_id, 9);
    sceIoClose(file_id);
    sprintf(uri, "psgm:play?titleid=%s", title_id);

    while(sceAppMgrLaunchAppByUri(0xFFFFF, uri) != 0)
        sceKernelDelayThread(10000);

    sceKernelExitProcess(0);

    return 0;
}
