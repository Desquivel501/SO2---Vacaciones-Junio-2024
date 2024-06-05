#include <linux/module.h> 
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Sistemas Operativos 2 -  Clase 3");
MODULE_AUTHOR("Derek Esquivel");

static int __init _insert(void){
    printk(KERN_INFO "Hola mundo\n");
    return 0;
}

static void __exit _remove(void){
    printk(KERN_INFO "Goodbye\n");
}

module_init(_insert)
module_exit(_remove)