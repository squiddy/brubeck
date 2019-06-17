#include "sput.h"
#include "brubeck.h"
#include "helpers.h"

void test_stats_track_by_namespace(void)
{
	struct brubeck_metric *metric = NULL;
	struct brubeck_server *server = new_server();

	stats_track_by_namespace(server, "core.has.a.counter", 18);
	stats_track_by_namespace(server, "core.has.a.counter", 18);
	stats_track_by_namespace(server, "core.has.a.counter", 18);
	stats_track_by_namespace(server, "web.has.a.gauge", 15);

	metric = brubeck_metric_find(server, "statsd.team.core", 17, BRUBECK_MT_METER);
	sput_fail_unless(metric->as.meter.value == 3.0, "metrics match");

	metric = brubeck_metric_find(server, "statsd.team.web", 16, BRUBECK_MT_METER);
	sput_fail_unless(metric->as.meter.value == 1.0, "metrics match");
}