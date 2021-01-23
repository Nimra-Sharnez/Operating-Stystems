#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/slab.h>

MODULE_AUTHOR("Nimra Sharnez");
MODULE_LICENSE("GPL");

char* device_buffer; //pointer to a spot
#define BUFFER_SIZE 1024
int open_counter = 0;
int close_counter = 0;

ssize_t cd_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset){
	int ret;
	// check to see if we can even do a read
	if (*offset+length > BUFFER_SIZE){
		printk(KERN_ALERT "Out of bounds read!\n");
		return -1;
	}
	else{
		ret = copy_to_user(buffer, device_buffer+*offset, length);
		printk(KERN_ALERT "Offset before: %ld\n", *offset);
		
	}
	if (ret == 0){
		*offset = *offset+length;
		printk(KERN_ALERT "Offset after: %ld\n", *offset);
		printk(KERN_ALERT "Bytes read %ld\n",length);
		printk(KERN_ALERT "The users buffer %s\n", buffer);
		printk(KERN_ALERT "Here is the device buffer now: %s\n", device_buffer);
		return length;
	}
	else{
		printk(KERN_ALERT "copy to user unsuccessful\n");
		return -1;
	}
}

ssize_t cd_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset){
	int ret;
	printk(KERN_ALERT "Here is the device buffer before: %s\n", device_buffer);
	// check to see if we can even do a write
	printk(KERN_ALERT "offset+length %d\n", *offset+length);
	printk(KERN_ALERT "Buffer Size %d\n", BUFFER_SIZE);
	if (*offset+length > BUFFER_SIZE){
		printk(KERN_ALERT "Out of bounds write!\n");
		return -1;
	}
	else{
		ret = copy_from_user(device_buffer+*offset, buffer, length);
		
	}
	if (ret == 0){
		*offset = *offset+length;
		printk(KERN_ALERT "Offset after: %ld\n", *offset);
		printk(KERN_ALERT "Bytes written %ld\n", length);
		printk(KERN_ALERT "The Device Buffer is now: %s\n", device_buffer);
		return length;
	}
	else{
		printk(KERN_ALERT "copy from user unsuccessful");
		return -1;
	}
}

int cd_open(struct inode *pinode, struct file *pfile){
	open_counter = open_counter+1;
	printk(KERN_ALERT "File opend %d times\n", open_counter);
	return 0;
}

int cd_close(struct inode *pinode, struct file *pfile){
	close_counter = close_counter+1;
	printk(KERN_ALERT "File closed %d times\n", close_counter);
	return 0;
}

loff_t cd_seek(struct file *pfile, loff_t offset, int whence){
	
	if (whence == 0){
		// offset is >=BUFF_SIZE
		if (offset > BUFFER_SIZE || offset < 0){
			printk(KERN_ALERT "Out of bounds\n");
			return -1;	
		}
		else{
			//position is set to the value of offset
			pfile->f_pos = offset;
			printk(KERN_ALERT "Offset set to %d\n", pfile->f_pos);
		}
	}
	else if (whence == 1){
		// offset+position > BUFFER_SIZE 
		if (pfile->f_pos+offset > BUFFER_SIZE || pfile->f_pos+offset < 0){
			printk(KERN_ALERT "Out of bounds\n");
			return -1;
		}	
		else{
			//increment file pointer by offset to new location
			pfile->f_pos = pfile->f_pos+offset;
			printk(KERN_ALERT "Offset set to %d\n", pfile->f_pos);
		}
	}
	else if (whence == 2){
		//if Buffer_size+offset < 0, also if offset is > 0 indicated movement FORWARDS (piazza @158)
		if (BUFFER_SIZE+offset < 0 || offset > 0){
			printk(KERN_ALERT "Out of bounds\n");
			return -1;
		}
		else{
			//move file pointer to end of file
			pfile->f_pos = BUFFER_SIZE+offset;
			printk(KERN_ALERT "Offset set to %d\n", pfile->f_pos);
		}
	}
	return pfile->f_pos;
}

struct file_operations fops = { 
	.owner = THIS_MODULE,
	.open = cd_open,
	.release = cd_close,
	.read = cd_read,
	.write = cd_write,
	.llseek = cd_seek
};

int part2_init(void) {
	device_buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
	register_chrdev(240, "simple_character_device", &fops);
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	return 0;
}

void part2_exit(void) {
	kfree(device_buffer);
	unregister_chrdev(240, "simple_character_device");
	printk(KERN_ALERT "inside %s function\n", __FUNCTION__);
}

module_init(part2_init);
module_exit(part2_exit);
