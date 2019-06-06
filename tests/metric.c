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

	server->metrics = brubeck_hashtable_new(1 << 20);
	server->backends[0] = malloc(sizeof(struct brubeck_backend));

	return server;
}

void test_brubeck_metric_find(void)
{
	struct brubeck_server *server = new_server();

	// Existing metrics for keys should be reused
	struct brubeck_metric *metric = brubeck_metric_find(server, "this.is.a.test", 14, BRUBECK_MT_COUNTER);
	struct brubeck_metric *metric2 = brubeck_metric_find(server, "this.is.a.test", 14, BRUBECK_MT_COUNTER);
	sput_fail_unless(metric == metric2, "metrics match");

	// New keys should give us new metrics
	struct brubeck_metric *metric3 = brubeck_metric_find(server, "this.is.not.a.test", 18, BRUBECK_MT_COUNTER);
	sput_fail_if(metric2 == metric3, "metrics dont't match");
}