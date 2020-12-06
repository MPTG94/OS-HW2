#include <linux/module.h>
#include <linux/sched.h>
#include <linux/kernel.h>

int search_children(struct task_struct* task) {
	struct task_struct *child;
	struct list_head *list;

	int sum = task->weight;
	list_for_each(list, &task->children) {
        	child = list_entry(list, struct task_struct, sibling);
        	sum += search_children(child);
    	}
	return sum;
}

//asmlinkage int get_children_weight(struct task_struct* task) {
//	struct list_head* list;
//	struct task_struct* child;
//	int sum = task->weight;
//	if (task->children == NULL) {
//		return task->weight;
//	}
//	list_for_each(list, &task->children) {
//              child = list_entry(list, struct task_struct, sibling);
//            sum += get_children_weight(child);
//      }
//
//	return sum;
//}

asmlinkage long sys_hello(void) {
	printk("Hello, World!\n");
	return 0;
}

asmlinkage int sys_get_total_weight(void) {
	//int sum = get_children_weight(current);
	int sum = search_children(current);
//	list_for_each(list, &current->children) {
//		task = list_entry(list, struct task_struct, sibling);
//		sum += get_children_weight;
//	}
	printk("The current pid is: %d\n", current->pid);
	printk("The total weight is: %d\n", sum);
	return sum;
}

asmlinkage int sys_set_weight(int weight) {
	if (weight < 0) {
		return -EINVAL;
	}
	printk("Got weight %d as input\n", weight);
	current->weight = weight;
	printk("Current weight of process is now %d\n", current->weight);
	return 0;
}

asmlinkage pid_t sys_get_heaviest_child(void) {
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
		return -ECHILD;
	}	
	return max_pid;
}
