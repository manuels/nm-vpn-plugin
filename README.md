The Anatomy of a NM VPN Plugin
==============================

Files
-----

    /usr/lib/x86_64-linux-gnu/NetworkManager/libnm-vpn-plugin-openvpn.so
    /usr/lib/NetworkManager/nm-openvpn-auth-dialog
    /usr/lib/NetworkManager/nm-openvpn-service: A (DBus?) service that calls the openvpn binary implementing a NMVpnServicePlugin class
    /usr/lib/NetworkManager/nm-openvpn-service-vpnc-helper: Sends data via DBus to nm-openvpn-service once connection is established

    /usr/lib/NetworkManager/VPN/nm-openvpn-service.name: The plugin description that is read by NetworkManager


Source Code Files
-----------------

    appdata/: Graphics
    auth-dialog/main.c: GUI password prompt shown when VPN is connecting
    m4/: Automake scripts
    po/: i18n
    properties/: The GUI for the plugin
    properties/nm-openvpn-editor.c: The Gnome GUI for editing VPN network connections
    properties/nm-openvpn-editor-plugin.c: Some boilerplate for the Gnome GUI
    properties/auth-helpers.c: #include'd by nm-openvpn-editor.c
    shared/: Files copied from the nm repository
    src/nm-openvpn-service.c: The (DBus?) service (see binaries)
    src/nm-openvpn-service-openvpn-helper.c: Up-Script (see binaries)

NMVpnServicePlugin
------------------

This is a DBus interface that must be implemented by your VPN service the required methods to implement are:

        connect(conn)
        disconnect()
        connect_interactive(conn, details)
        need_secrets(conn, setting) -> bool: do we need secrets for a connection?
        new_secrets(conn): sets new secrets to pending connection



[18:42] == manuels [58980832@gateway/web/freenode/ip.88.152.8.50] has joined #nm
[18:42] <manuels> hi guys, can anybody tell me what file to include to get the declaration of nm_vpn_plugin_utils_load_editor()?
[18:43] <manuels> I did not find any file containing this function in /usr/include. Maybe I need to install another package (debian)?
[18:45] <manuels> I am building up some documentation on how to write vpn plugins here: https://github.com/manuels/nm-vpn-plugin/
[18:47] == antoinef [~antoine@myfox-157-50.fib.nerim.net] has quit [Quit: Leaving]
[18:48] == ikhan_ [~ikhan@cpe-107-15-183-36.nc.res.rr.com] has joined #nm
[18:54] == morphis [~morphis@pD9ED67C0.dip0.t-ipconnect.de] has quit [Remote host closed the connection]
[19:07] == jgrulich [~jgrulich@2a00:1028:9198:74a6:d24e:b437:7278:823c] has joined #nm
[19:08] == fgiudici [~fg@5.170.18.184] has quit [Quit: Leaving]
[19:36] == ikhan_ [~ikhan@cpe-107-15-183-36.nc.res.rr.com] has quit [Remote host closed the connection]
[19:36] == ikhan_ [~ikhan@cpe-107-15-183-36.nc.res.rr.com] has joined #nm
[19:40] == ikhan_ [~ikhan@cpe-107-15-183-36.nc.res.rr.com] has quit [Remote host closed the connection]
[19:41] == ikhan_ [~ikhan@cpe-107-15-183-36.nc.res.rr.com] has joined #nm
[20:02] == timothy [~tredaelli@redhat/timothy] has quit [Quit: Konversation terminated!]
[20:04] == jgrulich [~jgrulich@2a00:1028:9198:74a6:d24e:b437:7278:823c] has quit [Ping timeout: 250 seconds]
[20:27] <thaller> most (all?) VPN plugins implement a shared library, that can be used client-side together with libnm/glib.   libnm has nm_vpn_plugin_utils_load_editor(), which is a helper function to load the shared library (dlopen) and create the client plugin instance.
[20:28] <thaller> manuels, ^
[20:29] <thaller> the shared library does stuff like: import/export of native VPN configuration files, and create a GTK dialog to configure the VPN (GUI)
[20:30] <thaller> manuels, almost more important for a functioning VPN plugin, is the service program. That is the program spawned by NetworkManager, and which establishes the VPN connection.
[20:31] <thaller> and very important are the .name files, like /usr/lib/NetworkManager/VPN/nm-openvpn-service.name . That file, describes where to find the libnm-shared-library (libnm.plugin) and the service program (VPN Connection.program)
[20:49] == dazo_ [~dazo@2001:470:de40:1021::14] has joined #nm
[20:52] == dazo [~dazo@openvpn/corp/developer/dazo] has quit [Ping timeout: 255 seconds]
[20:52] == dazo_ has changed nick to dazo
[20:52] == dazo [~dazo@2001:470:de40:1021::14] has quit [Changing host]
[20:52] == dazo [~dazo@openvpn/corp/developer/dazo] has joined #nm
[21:02] == wltjr [~wltjr@unaffiliated/wltjr] has quit [Read error: Connection reset by peer]
[21:12] <manuels> sorry, I was AFK, thanks, thaller!
[21:13] <thaller> manuels, via g-object-inspection, you can nicely call the libnm-library. https://cgit.freedesktop.org/NetworkManager/NetworkManager/tree/examples/python/gi/vpn-import.py?id=b227198e92689310e9c72cf4ab58dbcca2b4c0ae is an ugly example, to give you an idea
