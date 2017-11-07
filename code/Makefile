CFLAGS=$(shell pkg-config glib-2.0 libnm-util libnm libnm-glib libnm-glib-vpn libnm-gtk NetworkManager --cflags --libs)

all:
	gcc ${CFLAGS} -fPIC -c -I. -Ishared properties/my-vpn-editor-plugin.c -o my-vpn-editor-plugin.o
	gcc ${CFLAGS} -fPIC -c -I. -Ishared properties/my-vpn-editor.c -o my-vpn-editor.o
	gcc my-vpn-editor-plugin.o my-vpn-editor.o -shared -o libmy-vpn-editor-plugin.so
