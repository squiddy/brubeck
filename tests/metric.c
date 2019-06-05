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

void test_new_metric(void)
{
	struct brubeck_server *server = new_server();
	struct brubeck_metric *metric = NULL;

	metric = new_metric(server, "this.is.a.test", 14, BRUBECK_MT_COUNTER);
	sput_fail_unless(strcmp(metric->key, "this.is.a.test.counter") == 0, metric->key);

	metric = new_metric(server, "this.is.a.test", 14, BRUBECK_MT_METER);
	sput_fail_unless(strcmp(metric->key, "this.is.a.test.counter") == 0, metric->key);

	metric = new_metric(server, "this.is.a.test", 14, BRUBECK_MT_GAUGE);
	sput_fail_unless(strcmp(metric->key, "this.is.a.test.gauge") == 0, metric->key);

	metric = new_metric(server, "this.is.a.test", 14, BRUBECK_MT_TIMER);
	sput_fail_unless(strcmp(metric->key, "this.is.a.test.timer") == 0, metric->key);

	metric = new_metric(server, "this.is.a.test", 14, BRUBECK_MT_INTERNAL_STATS);
	sput_fail_unless(strcmp(metric->key, "this.is.a.test") == 0, metric->key);

	metric = new_metric(server, "this.is.a.test", 14, 42);
	sput_fail_unless(strcmp(metric->key, "this.is.a.test.unknown") == 0, metric->key);
}