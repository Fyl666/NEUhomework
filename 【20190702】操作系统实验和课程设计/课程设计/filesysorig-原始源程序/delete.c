/*删除文件函数delete( )(文件名delete.c)*/
#include <stdio.h>
#include "filesys.h"

delete (char *filename)
{
	unsigned int dinodeid;
	struct inode *inode;
	dinodeid=namei(filename);
	if (dinodeid!= NULL)
		inode =iget(dinodeid);
	inode ->di_number--;
	iput(inode);
}
