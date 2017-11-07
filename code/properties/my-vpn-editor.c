	#include "nm-default.h"
#include "nm-connection.h"
#include "nm-vpn-editor.h"
#include "nm-vpn-editor-plugin.h"

#include "my-vpn-editor.h"

#include <gtk/gtk.h>

static void my_vpn_editor_plugin_widget_interface_init (NMVpnEditorInterface *iface_class);

G_DEFINE_TYPE_EXTENDED (MyVpnEditor, my_vpn_editor_plugin_widget, G_TYPE_OBJECT, 0,
                        G_IMPLEMENT_INTERFACE (NM_TYPE_VPN_EDITOR,
                                               my_vpn_editor_plugin_widget_interface_init))

#define MY_VPN_EDITOR_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), MY_VPN_TYPE_EDITOR, MyVpnEditorPrivate))

typedef struct {
	GtkBuilder *builder;
	GtkWidget *widget;
	GtkWindowGroup *window_group;
	gboolean window_added;
	GHashTable *advanced;
	gboolean new_connection;
	GtkWidget *tls_user_cert_chooser;
} MyVpnEditorPrivate;

static void
my_vpn_editor_plugin_widget_init (MyVpnEditor *plugin)
{
	g_message("my_vpn_editor_plugin_widget_init");
}

static void
dispose (GObject *object)
{
	g_message("dispose");
	MyVpnEditor *plugin = MY_VPN_EDITOR (object);
	MyVpnEditorPrivate *priv = MY_VPN_EDITOR_GET_PRIVATE (plugin);

	g_clear_object (&priv->window_group);
	g_clear_object (&priv->widget);
	g_clear_object (&priv->builder);
	g_clear_pointer (&priv->advanced, g_hash_table_destroy);
//	G_OBJECT_CLASS (openvpn_editor_plugin_widget_parent_class)->dispose (object);
}

static void
my_vpn_editor_plugin_widget_class_init (MyVpnEditorClass *req_class)
{
	g_message("my_vpn_editor_plugin_widget_class_init");
	GObjectClass *object_class = G_OBJECT_CLASS (req_class);

	g_type_class_add_private (req_class, sizeof (MyVpnEditorPrivate));

	object_class->dispose = dispose;
}

static GObject *
get_widget (NMVpnEditor *iface)
{
	g_message("get_widget");
	MyVpnEditor *self = MY_VPN_EDITOR (iface);
	MyVpnEditorPrivate *priv = MY_VPN_EDITOR_GET_PRIVATE (self);

	return G_OBJECT (priv->widget);
}

static gboolean
update_connection (NMVpnEditor *iface,
                   NMConnection *connection,
                   GError **error)
{
	g_message("update_connection");
	return false;
}

static void
my_vpn_editor_plugin_widget_interface_init (NMVpnEditorInterface *iface_class)
{
	g_message("my_vpn_editor_plugin_widget_interface_init");
	/* interface implementation */
	iface_class->get_widget = get_widget;
	iface_class->update_connection = update_connection;
}

static void
stuff_changed_cb (GtkWidget *widget, gpointer user_data)
{
	g_message("stuff_changed_cb");
	g_signal_emit_by_name (MY_VPN_EDITOR (user_data), "changed");
}

G_MODULE_EXPORT NMVpnEditor *
nm_vpn_editor_factory_my_vpn (NMVpnEditorPlugin *editor_plugin,
                              NMConnection *connection,
                              GError **error)
{
	g_message("nm_vpn_editor_factory_my_vpn");
	g_return_val_if_fail (!error || !*error, NULL);

	return my_vpn_editor_new (connection, error);
}
