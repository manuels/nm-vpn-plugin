#ifndef __MY_VPN_EDITOR_H__
#define __MY_VPN_EDITOR_H__

#define MY_VPN_TYPE_EDITOR            (my_vpn_editor_plugin_widget_get_type ())
#define MY_VPN_EDITOR(obj)                      (G_TYPE_CHECK_INSTANCE_CAST ((obj), MY_VPN_TYPE_EDITOR, MyVpnEditor))
#define MY_VPN_EDITOR_CLASS(klass)              (G_TYPE_CHECK_CLASS_CAST ((klass), MY_VPN_TYPE_EDITOR, MyVpnEditorClass))
#define MY_VPN_IS_EDITOR(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MY_VPN_TYPE_EDITOR))
#define MY_VPN_IS_EDITOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MY_VPN_TYPE_EDITOR))
#define MY_VPN_EDITOR_GET_CLASS(obj)            (G_TYPE_INSTANCE_GET_CLASS ((obj), MY_VPN_TYPE_EDITOR, MyVpnEditorClass))

typedef struct _MyVpnEditor MyVpnEditor;
typedef struct _MyVpnEditorClass MyVpnEditorClass;

struct _MyVpnEditor {
	GObject parent;
};

struct _MyVpnEditorClass {
	GObjectClass parent;
};

GType my_vpn_editor_plugin_widget_get_type (void);

NMVpnEditor *my_vpn_editor_new (NMConnection *connection, GError **error);

#endif
