#include "brubeck.h"
#include "sput.h"

struct sput __sput;

void test_histogram__sampling(void);
void test_histogram__single_element(void);
void test_histogram__large_range(void);
void test_histogram__multisamples(void);
void test_histogram__with_sample_rate(void);
void test_histogram__capacity(void);

void test_mstore__save(void);
void test_atomic_spinlocks(void);
void test_ftoa(void);
void test_statsd_msg__parse_strings(void);

void test_get_metric_suffix(void);

int main(int argc, char *argv[])
{
	sput_start_testing();

	sput_enter_suite("histogram: time/data series aggregation");
	sput_run_test(test_histogram__sampling);
	sput_run_test(test_histogram__single_element);
	sput_run_test(test_histogram__large_range);
	sput_run_test(test_histogram__multisamples);
	sput_run_test(test_histogram__with_sample_rate);
	sput_run_test(test_histogram__capacity);

	sput_enter_suite("mstore: concurrency test for metrics hash table");
	sput_run_test(test_mstore__save);

	sput_enter_suite("atomic: atomic primitives");
	sput_run_test(test_atomic_spinlocks);

	sput_enter_suite("ftoa: double-to-string conversion");
	sput_run_test(test_ftoa);

	sput_enter_suite("statsd: packet parsing");
	sput_run_test(test_statsd_msg__parse_strings);

	sput_enter_suite("metric: creating / sampling metrics");
	sput_run_test(test_get_metric_suffix);

	sput_finish_testing();
	return sput_get_return_value();
}
