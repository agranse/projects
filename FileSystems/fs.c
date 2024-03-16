#include "fs.h"
#include "disk.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FS_MAGIC 0xf0f03410
#define INODES_PER_BLOCK 128
#define POINTERS_PER_INODE 5
#define POINTERS_PER_BLOCK 1024

// Returns the number of dedicated inode blocks given the disk size in blocks
#define NUM_INODE_BLOCKS(disk_size_in_blocks) (1 + (disk_size_in_blocks / 10))

int *takenBlocks;
int mounted = -1;   // -1 if false, 0 if true
int unmounted = -1;   // -1 if false, 0 if true

struct fs_superblock {
  int magic;        // Magic bytes
  int nblocks;      // Size of the disk in number of blocks
  int ninodeblocks; // Number of blocks dedicated to inodes
  int ninodes;      // Number of dedicated inodes
};

struct fs_inode {
  int isvalid;                    // 1 if valid (in use), 0 otherwise
  int size;                       // Size of file in bytes
  int direct[POINTERS_PER_INODE]; // Direct data block numbers (0 if invalid)
  int indirect;                   // Indirect data block number (0 if invalid)
};

union fs_block {
  struct fs_superblock super;              // Superblock
  struct fs_inode inode[INODES_PER_BLOCK]; // Block of inodes
  int pointers[POINTERS_PER_BLOCK]; // Indirect block of direct data block
                                    // numbers
  char data[DISK_BLOCK_SIZE];       // Data block
};

void fs_debug() {
  union fs_block superBlock;

  disk_read(0, superBlock.data);

  // Prints the entire superblock
  printf("superblock:\n");
  printf("    %d blocks\n", superBlock.super.nblocks);
  printf("    %d inode blocks\n", superBlock.super.ninodeblocks);
  printf("    %d inodes\n", superBlock.super.ninodes);

  union fs_block inodeBlock;
  struct fs_inode currInode;
  for (int i = 1; i < (superBlock.super.ninodeblocks + 1); i++) {
    disk_read(i, inodeBlock.data);
    for (int j = 0; j < INODES_PER_BLOCK; j++) {
      currInode = inodeBlock.inode[j];

      // Prints each direct poitner
      if (currInode.isvalid) {
        printf("inode %d:\n", (j * i));
        printf("    size %d bytes\n", currInode.size);
        printf("    direct blocks:");
        for (int k = 0; k < POINTERS_PER_INODE; k++) {
          if (currInode.direct[k]) {
            printf(" %d", currInode.direct[k]);
          }
        }

        // Prints each indirect block location
        printf("\n");
        if (currInode.indirect) {
          union fs_block indirectBlock;
          disk_read(currInode.indirect, indirectBlock.data);
          printf("    indirect block: %d\n", currInode.indirect);
          printf("    indirect data blocks:");
          for (int k = 0; k < POINTERS_PER_BLOCK; k++) {
            if (indirectBlock.pointers[k]) {
              printf(" %d", indirectBlock.pointers[k]);
            }
          }
          printf("\n");
        }
      }
    }
  }
}

int fs_format() {
  union fs_block block;

  // set up superblock
  block.super.nblocks = disk_size();
  block.super.ninodeblocks = NUM_INODE_BLOCKS(block.super.nblocks);
  block.super.ninodes = block.super.ninodeblocks * INODES_PER_BLOCK;
  block.super.magic = FS_MAGIC;

  // sets inodes and pointers to 0
  struct fs_inode inode;
  for (int i = 0; i < POINTERS_PER_INODE; i++) {
    inode.direct[i] = 0;
  }
  inode.isvalid = 0;
  inode.size = 0;
  inode.indirect = 0;

  union fs_block inodeBlock;
  for (int i = 0; i < INODES_PER_BLOCK; i++) {
    inodeBlock.inode[i] = inode;
  }

  // write changes to blocks to disk
  for (int i = 1; i < (block.super.ninodeblocks + 1); i++) {
    disk_write(i, inodeBlock.data);
  }
  disk_write(0, block.data);

  return 1;
}

int fs_mount() {
  union fs_block block;
  disk_read(0, block.data);

  if (block.super.magic != FS_MAGIC) {
    fprintf(stderr, "Failed to find File System");
    return 0;
  }

  // Creates "bitmap" for blocks
  int numDataBlocks = block.super.nblocks - block.super.ninodeblocks;
  takenBlocks = malloc(sizeof(int) * numDataBlocks);
  if (takenBlocks == NULL){
    fprintf(stderr, "Failed to malloc free block bitmap");
    return 0;
  }
  for (int i = 0; i < (numDataBlocks); i++) {
    takenBlocks[i] = 0;
  }

  mounted = 0;    // changes global to acknowldege disk now mounted
  return 1;
}

int fs_unmount() {
  if (mounted == -1) {
    fprintf(stderr, "Please mount the file system before deleting.\n");
    return 0;
  }
  // disk has been unmounted. Return 1 to avoid double free error
  if (unmounted == 0) {
    return 1;
  }

  free(takenBlocks);
  unmounted = 0;    // changes global to acknowldege disk now mounted
  return 1;
}

int fs_create() {
  if (mounted == -1) {
    fprintf(stderr, "Please mount the file system before creating.\n");
    return -1;
  }

  union fs_block superBlock;
  union fs_block inodeBlock;
  disk_read(0, superBlock.data);

  int inumber = -1;

  // loop through superblock inode blocks looking for valid inodes, once found break
  for(int i = 0; (i < superBlock.super.ninodeblocks) && (inumber == -1); i++){
    disk_read(i + 1, inodeBlock.data);
    for (int j = 0; j < INODES_PER_BLOCK; j++){
      if (!inodeBlock.inode[j].isvalid){
        inumber = (j + (INODES_PER_BLOCK * i));
        break;
      }
    }
  }
  if (inumber == -1) {
    fprintf(stderr, "Out of Valid Inodes");
    return -1;
  }

  // updates inode size and validity
  inodeBlock.inode[(inumber % INODES_PER_BLOCK)].size = 0;
  inodeBlock.inode[(inumber % INODES_PER_BLOCK)].isvalid = 1;

  // write inodeBlock.data changes to disk
  disk_write((1 + (inumber / INODES_PER_BLOCK)), inodeBlock.data);
  return inumber;
}

int fs_delete(int inumber) {
  if (mounted == -1) {
    fprintf(stderr, "Please mount the file system before deleting.\n");
    return 0;
  }

  // Take in inode block for inumber
  union fs_block inodeBlock;
  disk_read((1 + (inumber / INODES_PER_BLOCK)), inodeBlock.data);

  // Inode to replace current Inode with
  struct fs_inode inode;
  for (int i = 0; i < POINTERS_PER_INODE; i++) {
    inode.direct[i] = 0;
  }
  inode.isvalid = 0;
  inode.size = 0;
  inode.indirect = 0;

  // Gets indirect block pointer
  int indirectBlock = inodeBlock.inode[(inumber % INODES_PER_BLOCK)].indirect;
  if (indirectBlock) {
    takenBlocks[indirectBlock] = 0;

    // Clears all Indirect Pointers
    union fs_block indirectBlockUnion;
    disk_read(indirectBlock, indirectBlockUnion.data);
    for (int i = 0; i < POINTERS_PER_BLOCK; i++) {
      takenBlocks[indirectBlockUnion.pointers[i]] = 0;
    }
  }

  // Clears all direct pointers
  for (int i = 0; i < POINTERS_PER_INODE; i++) {
    if (inodeBlock.inode[(inumber % INODES_PER_BLOCK)].direct[i]) {
      takenBlocks[inodeBlock.inode[(inumber % INODES_PER_BLOCK)].direct[i]] = 0;
    }
  }

  // Clears out entire inode
  inodeBlock.inode[(inumber % INODES_PER_BLOCK)] = inode;

  disk_write((1 + (inumber / INODES_PER_BLOCK)), inodeBlock.data);

  return 1;
}

int fs_getsize(int inumber) {
  if (mounted == -1) {
    fprintf(stderr, "Please mount the file system before getting inode size.\n");
    return -1;
  }

  union fs_block inodeBlock;

  disk_read((1 + (inumber / INODES_PER_BLOCK)), inodeBlock.data);

  // if inode is valid, return size of inode
  if (inodeBlock.inode[inumber % INODES_PER_BLOCK].isvalid) {
    return inodeBlock.inode[inumber % INODES_PER_BLOCK].size;
  }
  return -1;
}

int fs_read(int inumber, char *data, int length, int offset) {
  if (mounted == -1) {
    fprintf(stderr, "Please mount the file system before reading.\n");
    return 0;
  }
  
  //Get inode
  union fs_block inodeBlock;
  disk_read((1 + (inumber / INODES_PER_BLOCK)), inodeBlock.data);
  struct fs_inode inode = inodeBlock.inode[inumber % INODES_PER_BLOCK];    
  if (offset >= inode.size){
    return 0;
  }
  if (!inode.isvalid){
    fprintf(stderr, "Attemping to read from invalid node\n");
    return 0;
  }
  int currOffset = offset;

  // direct block code
  while ((currOffset < inode.size) && (currOffset < (DISK_BLOCK_SIZE * POINTERS_PER_INODE)) && currOffset < (length + offset)) {
    disk_read(inode.direct[currOffset / DISK_BLOCK_SIZE], data + (currOffset - offset));
    currOffset += DISK_BLOCK_SIZE;
  }

  union fs_block pointerBlock;
  disk_read(inode.indirect, pointerBlock.data);

  // Indirect pointer code
  while (currOffset < inode.size && currOffset < (length + offset)) {
    disk_read(pointerBlock.pointers[((currOffset - (POINTERS_PER_INODE * DISK_BLOCK_SIZE))  / DISK_BLOCK_SIZE)], data + (currOffset - offset));
    currOffset += DISK_BLOCK_SIZE;
  }
  if ((inode.size - offset) > length){
    return length;
  }
  return (inode.size - offset);
}

// helper for fs_write()
// find free block to write to
int findFreeBlock() {
  union fs_block superBlock;
  disk_read(0, superBlock.data);

  for (int i = superBlock.super.ninodeblocks + 1; i < superBlock.super.nblocks;
       i++) {
    if (!takenBlocks[i]) {
      takenBlocks[i] = 1;
      return i;
    }
  }
  return -1;
}


int fs_write(int inumber, const char *data, int length, int offset) {
  if (mounted == -1) {
    fprintf(stderr, "Please mount the file system before creating.\n");
    return 0;
  }
  // printf("offset %d\n",offset);
  union fs_block inodeBlock;
  disk_read((1 + (inumber / INODES_PER_BLOCK)), inodeBlock.data);
  struct fs_inode inode = inodeBlock.inode[inumber % INODES_PER_BLOCK];

  if (!inode.isvalid){
    fprintf(stderr, "Attempting to write to invalid node\n");
    return 0;
  } 
    int currOffset = offset;
    int bytesWritten = 0;
    while ((currOffset < (offset + length)) &&
           (currOffset < (DISK_BLOCK_SIZE * (POINTERS_PER_INODE)))) {
      // Find a new block
      int freeBlock = findFreeBlock();
      if (freeBlock == -1) {
        return 0;
      }
      // Set direct blocks
      for (int i = 0; i < POINTERS_PER_INODE; i++) {
        if (!inode.direct[i]) {
          inode.direct[i] = freeBlock;
          break;
        }
      }
      disk_write(freeBlock, data + (currOffset - offset));
      if (((length + offset) - currOffset) < DISK_BLOCK_SIZE) {
        bytesWritten += (length + offset) - currOffset;
      } 
      else {
        bytesWritten += DISK_BLOCK_SIZE;
      }
      currOffset = bytesWritten + offset;
    }

    // INDIRECT BLOCKS
    union fs_block pointerBlock;

    // Create indirect block if needed
    if (!inode.indirect && currOffset <= (offset + length) && (inode.direct[POINTERS_PER_INODE - 1]) != 0) {
      int freeIndirectBlock = findFreeBlock();
      if (freeIndirectBlock == -1) {
        return 0;
      }
      inode.indirect = freeIndirectBlock;
      inodeBlock.inode[inumber % INODES_PER_BLOCK] = inode;
      disk_write((1 + (inumber / INODES_PER_BLOCK)), inodeBlock.data);
      for (int i = 0; i < POINTERS_PER_BLOCK; i++) {
        pointerBlock.pointers[i] = 0;
      }
      disk_write(inode.indirect, pointerBlock.data);
    }

    disk_read(inode.indirect, pointerBlock.data);

    //write to the indirect Blocks
    while (currOffset < (offset + length)) {
      int freeBlock = findFreeBlock();
      if (freeBlock == -1) {
        return 0;
      }
      for (int i = 0; i < POINTERS_PER_BLOCK; i++) {
        if (!pointerBlock.pointers[i]) {
          pointerBlock.pointers[i] = freeBlock;
          break;
        }
      }

      disk_write(freeBlock, data + (currOffset - offset));

      if (((length + offset) - currOffset) < DISK_BLOCK_SIZE) {
        bytesWritten += (length + offset) - currOffset;
      } else {
        bytesWritten += DISK_BLOCK_SIZE;
      }
      currOffset = bytesWritten + offset;
    }

    inode.size += bytesWritten;
    disk_write(inode.indirect, pointerBlock.data);
    inodeBlock.inode[inumber % INODES_PER_BLOCK] = inode;
    disk_write((1 + (inumber / INODES_PER_BLOCK)), inodeBlock.data);
    return bytesWritten;
}
