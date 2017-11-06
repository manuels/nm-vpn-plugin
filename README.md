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
