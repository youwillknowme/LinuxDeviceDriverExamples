#include <linux/init.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/jiffies.h>
#include <linux/delay.h>
#include <linux/slab.h> 
struct demo_type {
    char *name;
    struct workqueue_struct *wq;
    struct delayed_work dwk;
};

static void demo_work(struct work_struct *work) {
    struct demo_type *dm = container_of(work, struct demo_type, dwk.work);
    pr_info("demo work begin!\n");
    msleep(1000);
    pr_info("demo name:%s\n", dm->name);
    kzfree(dm);
}
int demo_init(void) {
    struct demo_type *dm = NULL;
    dm = kzalloc(sizeof(struct demo_type), GFP_KERNEL);
    pr_info("size = %ld,addr = %llx, size = %ld\n",sizeof(struct demo_type), (uint64_t)dm, sizeof(*dm));
    if (!dm) {
        goto err;
    }
    dm->wq = create_singlethread_workqueue("demo_workqueue");

    dm->name = "Demo";
    INIT_DELAYED_WORK(&dm->dwk,demo_work);

    queue_delayed_work(dm->wq, &dm->dwk, msecs_to_jiffies(1000));
    pr_info("demo work wake\n");
    return 0;
err:
    pr_info("no mem\n");
    return 1;
}
static int hello_init(void) {
    pr_info("%s,%d\n",__func__,__LINE__);
    demo_init();
    return 0;
}

static void hello_exit(void) {
    pr_info("%s,%d\n",__func__,__LINE__);
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("Dual BSD/GPL");
