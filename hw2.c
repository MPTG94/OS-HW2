#include <linux/module.h>
#include <linux/sched.h>
#include <linux/kernel.h>

long search_children(struct task_struct* task) {
	struct task_struct *child;
	struct list_head *list;
	long sum = task->weight;
	list_for_each(list, &task->children) {
        	child = list_entry(list, struct task_struct, sibling);
        	sum += search_children(child);
    	}
	return sum;
}

asmlinkage long sys_hello(void) {
	printk("Hello, World!\n");
	return 0;
}

asmlinkage long sys_get_total_weight(void) {
	long sum = search_children(current);
	return sum;
}

asmlinkage long sys_set_weight(int weight) {
	if (weight < 0) {
		return -EINVAL;
	}
	current->weight = weight;
	return 0;
}

asmlinkage long sys_get_heaviest_child(void) {
	struct task_struct *child;
        struct list_head *list;
	long max_weight = 0;
	long max_pid = 0;
	long curr_weight = -1;

	if (&(current->children) == current->children.next) {
		// current has no children 
		return -ECHILD;
	}

        list_for_each(list, &current->children) {
                child = list_entry(list, struct task_struct, sibling);
		curr_weight = search_children(child);
		if (curr_weight >= max_weight) {
			max_weight = curr_weight;
			max_pid = child->pid;
		}
		curr_weight = -1;
        }

	return max_pid;
}
