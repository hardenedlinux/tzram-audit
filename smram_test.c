/*
 * Test SMRAM on x86
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/io.h>


static int __init smram_test_init(void)
{
	int value = 0;
	phys_addr_t comp_smram_phys = 0xA0000; 
	
	void __iomem *mapped = ioremap(comp_smram_phys, 0x10); //reading 10 bytes

	pr_info("smram_test: Mapped SMRAM at %p\n", mapped);

	value = ioread32(mapped);
	pr_info("smram_test: Value read from SMRAM: 0x%08x\n", value);

	iounmap(mapped);

	return 0;
}

static void __exit smram_test_exit(void)
{
	pr_info("smram_test: Module exit\n");
}

module_init(smram_test_init);
module_exit(smram_test_exit);

MODULE_LICENSE("GPL");
