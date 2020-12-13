#include <linux/module.h>
#include <linux/sched.h>
#include <linux/kernel.h>

int search_children(struct task_struct* task) {
	struct task_struct *child;
	struct list_head *list;
	int sum = task->weight;
	//printk("Now in search children with PID %d\n", task->pid);
	//printk("The weight is: %d\n", task->weight);
	list_for_each(list, &task->children) {
        	child = list_entry(list, struct task_struct, sibling);
		//printk("Found child with PID %d to call recursively on\n", child->pid);
		//printk("Found child with weight %d to call recursively on\n", child->weight);
        	sum += search_children(child);
    	}
	return sum;
}

asmlinkage long sys_hello(void) {
	printk("Hello, World!\n");
	return 0;
}

asmlinkage int sys_get_total_weight(void) {
	//int sum = get_children_weight(current);
	int sum = search_children(current);
	//printk("The current pid is: %d\n", current->pid);
	//printk("The total weight is: %d\n", sum);
	return sum;
}

asmlinkage int sys_set_weight(int weight) {
	if (weight < 0) {
		errno = -EINVAL
		return -1;
		//return -EINVAL;
	}
	//printk("Got weight %d as input\n", weight);
	current->weight = weight;
	//printk("Current weight of process is now %d\n", current->weight);
	return 0;
}

asmlinkage long sys_get_heaviest_child(void) {
	struct task_struct *child;
        struct list_head *list;
	int max_weight = 0;
	pid_t max_pid = 0;

        list_for_each(list, &current->children) {
                child = list_entry(list, struct task_struct, sibling);
		if (child->weight >= max_weight) {
			max_weight = child->weight;
			max_pid = child->pid;
		}
        }

	if ((int)max_pid == 0) {
		errno = -ECHILD;
		return -1;
	}	
	return max_pid;
}
