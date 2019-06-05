#include "sput.h"
#include "brubeck.h"

void test_get_metric_suffix(void)
{
	sput_fail_unless(get_metric_suffix(BRUBECK_MT_COUNTER),
					 ".counter");
	sput_fail_unless(get_metric_suffix(BRUBECK_MT_METER),
					 ".counter");
	sput_fail_unless(get_metric_suffix(BRUBECK_MT_GAUGE),
					 ".gauge");
	sput_fail_unless(get_metric_suffix(BRUBECK_MT_TIMER),
					 ".timer");
	sput_fail_unless(get_metric_suffix(BRUBECK_MT_HISTO),
					 ".histo");

	sput_fail_unless(get_metric_suffix(23),
					 ".unknown");
}

static struct brubeck_server *
new_server()
{
	struct brubeck_server *server = malloc(sizeof(struct brubeck_server));
	memset(server, 0x0, sizeof(struct brubeck_server));
	brubeck_slab_init(&server->slab);
	return server;
}