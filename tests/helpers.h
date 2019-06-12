#ifndef __HELPERS_H__
#define __HELPERS_H__

#include "sput.h"
#include "brubeck.h"

static struct brubeck_server *
new_server()
{
	struct brubeck_server *server = malloc(sizeof(struct brubeck_server));
	memset(server, 0x0, sizeof(struct brubeck_server));
	brubeck_slab_init(&server->slab);

	server->metrics = brubeck_hashtable_new(1 << 20);
	server->backends[0] = malloc(sizeof(struct brubeck_backend));

	return server;
}

#endif
