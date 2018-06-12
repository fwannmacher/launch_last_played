#include <psp2kern/kernel/modulemgr.h>
#include <psp2kern/io/fcntl.h>
#include <string.h>
#include <taihen.h>


static tai_hook_ref_t hook_ref;
static SceUID hook_id;
static SceUID launch_app_patched(char* title_id, uint32_t flags, char* path, void* unknown)
{
    if((hook_ref < 0) || !(title_id))
        return 1;

    if((strlen(title_id)) >= 3 && (strncmp("PCS", title_id, 3) == 0))
    {
        SceUID file_id = ksceIoOpen(
            "ux0:launch_last_played.tid",
            SCE_O_WRONLY | SCE_O_CREAT | SCE_O_TRUNC,
            0777);

        if(file_id < 0)
            return 1;

        ksceIoWrite(file_id, title_id, 9);
        ksceIoClose(file_id);
    }

    return TAI_CONTINUE(int, hook_ref, title_id, flags, path, unknown);
}

void _start() __attribute__ ((weak, alias("module_start")));

int module_start(SceSize argc, const void *args)
{
    hook_id = taiHookFunctionExportForKernel(
        KERNEL_PID,
        &hook_ref,
        "SceProcessmgr",
        0x7A69DE86,
        0x71CF71FD,
        launch_app_patched);

    if(hook_id < 0)
        hook_id = taiHookFunctionExportForKernel(
            KERNEL_PID,
            &hook_ref,
            "SceProcessmgr",
            0xEB1F8EF7,
            0x68068618,
            launch_app_patched);

    return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args)
{
    if(hook_id >= 0)
        taiHookReleaseForKernel(hook_id, hook_ref);

    return SCE_KERNEL_STOP_SUCCESS;
}
