// coheny405@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
using namespace doctest;

const int MIN_TESTS = 5;

int return_code = -1;

struct ReporterCounter : public ConsoleReporter
{
    ReporterCounter(const ContextOptions &input_options)
        : ConsoleReporter(input_options) {}

    void test_run_end(const TestRunStats &run_stats) override
    {
        if (run_stats.numAsserts >= MIN_TESTS)
        {
            return_code = 0;
        }
        else
        {
            std::cout << "Please write at least " << MIN_TESTS << " tests! " << std::endl;
            return_code = 1;
        }
        // Print summary of tests
        std::cout << "Number of tests: " << run_stats.numTestCases << std::endl;
        std::cout << "Number of assertions: " << run_stats.numAsserts << std::endl;
        std::cout << "Number of failures: " << run_stats.numAssertsFailed << std::endl;
    }
};

REGISTER_REPORTER("counter", 1, ReporterCounter);

int main(int argc, char **argv)
{
    (void)argc; // Silence unused parameter warning
    (void)argv; // Silence unused parameter warning
    Context context;
    context.addFilter("reporters", "counter");
    context.run();
    return return_code;
}