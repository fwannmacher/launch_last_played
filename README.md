# Launch Last Played Game
taiHEN plugin and app which launch the last game you have played


Usage
--------------------------------------------------------------------------------

Before launching the app, at least one game has to be played while the plugin is installed. That is needed because the plugin will store the title id in a file located at the root of ux0 and the app will use that title id.

The plugin store only title ids which begin with PCS to avoid storing apps like VitaShell.

Installation
--------------------------------------------------------------------------------

Put "launch_last_played.skprx" in 'tai' folder in the root of your Vita.

Change config.txt in that directory to load the kernel plugin by adding new lines like below:

```text
# titleid for your game
*KERNEL
ux0:tai/launch_last_played.skprx
```

Install the launch_last_played.vpk file with VitaShell
