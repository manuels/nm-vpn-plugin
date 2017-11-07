#ifndef __MY_VPN_EDITOR_PLUGIN_H__
#define __MY_VPN_EDITOR_PLUGIN_H__

#include <glib-object.h>

#define MY_VPN_TYPE_EDITOR_PLUGIN                (my_vpn_editor_plugin_get_type ())
#define MY_VPN_EDITOR_PLUGIN(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), MY_VPN_TYPE_EDITOR_PLUGIN, MyVpnEditorPlugin))
#define MY_VPN_EDITOR_PLUGIN_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), MY_VPN_TYPE_EDITOR_PLUGIN, MyVpnEditorPluginClass))
#define MY_VPN_IS_EDITOR_PLUGIN(obj)             (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MY_VPN_TYPE_EDITOR_PLUGIN))
#define MY_VPN_IS_EDITOR_PLUGIN_CLASS(klass)     (G_TYPE_CHECK_CLASS_TYPE ((klass), MY_VPN_TYPE_EDITOR_PLUGIN))
#define MY_VPN_EDITOR_PLUGIN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), MY_VPN_TYPE_EDITOR_PLUGIN, MyVpnEditorPluginClass))

typedef struct _MyVpnEditorPlugin MyVpnEditorPlugin;
typedef struct _MyVpnEditorPluginClass MyVpnEditorPluginClass;

struct _MyVpnEditorPlugin {
	GObject parent;
};

struct _MyVpnEditorPluginClass {
	GObjectClass parent;
};

typedef NMVpnEditor *(*NMVpnEditorFactory) (NMVpnEditorPlugin *editor_plugin,
                                            NMConnection *connection,
                                            GError **error);

NMVpnEditor *
nm_vpn_editor_factory_myvpn (NMVpnEditorPlugin *editor_plugin,
                             NMConnection *connection,
                             GError **error);

#endif /* __VIEWER_FILE_H__ */
