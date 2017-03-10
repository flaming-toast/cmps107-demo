/*
 * Sample module for CMPS107
 */
#include <linux/module.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>

/*
 * This module creates a directory in sysfs called /sys/kernel/cmps107/
 * In that directory, the file "foo" is created. The value of foo is exported to
 * sysfs and if an integer is written to the file /sys/kernel/cmps107/foo, the
 * variable foo will be set to this value and can be later read from
 * /sys/kernel/cmps107/foo
 */

static struct kobject *cmps107_kobj;

static int foo;

/*
 * The "foo" file where the variable foo is read from and written to.
 */
static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr,
			char *buf)
{
	return sprintf(buf, "%d\n", foo);
}

static ssize_t foo_store(struct kobject *kobj, struct kobj_attribute *attr,
			 const char *buf, size_t count)
{
	int ret;

	ret = kstrtoint(buf, 10, &foo);
	if (ret < 0)
		return ret;

	return count;
}

/* Sysfs setup */

/* name of file, permissions, "show" method, "store" method */
static struct kobj_attribute foo_attribute =
	__ATTR(foo, 0664, foo_show, foo_store);

static struct attribute *attrs[] = {
	&foo_attribute.attr,
	NULL,	/* need to NULL terminate the list of attributes */
};

static struct attribute_group attr_group = {
	.attrs = attrs,
};

static int __init cmps107_init(void)
{
	int ret;

	/* This creates a subdir named "cmps107" under /sys/kernel/ */
	cmps107_kobj = kobject_create_and_add("cmps107", kernel_kobj);
	if (!cmps107_kobj)
		return -ENOMEM;

	/* Create the files associated with this kobject */
	ret = sysfs_create_group(cmps107_kobj, &attr_group);
	if (ret)
		kobject_put(cmps107_kobj);
	return 0;
}

static void __exit cmps107_exit(void)
{
	kobject_put(cmps107_kobj);
}

module_init(cmps107_init);
module_exit(cmps107_exit);
MODULE_LICENSE("GPL");
