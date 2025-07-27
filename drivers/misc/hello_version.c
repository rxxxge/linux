// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/utsname.h>
#include <linux/timekeeping.h>

static char *who = "Topia";
module_param(who, charp, 0644);
MODULE_PARM_DESC(who, "Recipient of hello message");

time64_t start_clock;

static int __init hello_version_init(void)
{
	start_clock = ktime_get_seconds();
	pr_info("Hello %s. You are currently using Linux %s.\n", who, init_uts_ns.name.release);
	return 0;
}

static void __exit hello_version_exit(void)
{
	time64_t time_elapsed = ktime_get_seconds() - start_clock;

	pr_info("Goodbye %s. Time elapsed: %lld seconds\n", who, time_elapsed);
}

MODULE_LICENSE("GPL");
module_init(hello_version_init);
module_exit(hello_version_exit);
