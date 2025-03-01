#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/types.h>

MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");

static int __init tzram_test_init(void)
{
        int value = 0;

	phys_addr_t phys_addr = 0x10100000;  // your physical address
	void __iomem *mapped_addr = (void __iomem *)phys_to_virt(phys_addr);

	value = *(int*)mapped_addr;
	pr_info("tzram_test: Value read from: tzram_phys_addr:0x%08x, virt_addr:%p, value:0x%08x", (unsigned int)phys_addr, mapped_addr, value);

	return 0;

}

static void __exit tzram_test_exit(void)
{
	pr_info("tzram_test: Module unloaded\n");
}

module_init(tzram_test_init);
module_exit(tzram_test_exit);
