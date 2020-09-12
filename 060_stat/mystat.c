#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

//This function is for printing line 1
void line1(struct stat statName, char * fileName) {
  char linktarget[256];
  ssize_t len = readlink(fileName, linktarget, 256);
  linktarget[len] = '\0';
  if (S_ISLNK(statName.st_mode) != 0) {
    printf("  File: %s -> %s\n", fileName, linktarget);
  }
  else {
    printf("  File: %s\n", fileName);
  }
}

//This function is for printing line 2
void line2(struct stat statName) {
  char * filetype;
  switch (statName.st_mode & S_IFMT) {
    case S_IFBLK:
      filetype = "block special file";
      break;
    case S_IFCHR:
      filetype = "character special file";
      break;
    case S_IFDIR:
      filetype = "directory";
      break;
    case S_IFIFO:
      filetype = "fifo";
      break;
    case S_IFLNK:
      filetype = "symbolic link";
      break;
    case S_IFREG:
      filetype = "regular file";
      break;
    case S_IFSOCK:
      filetype = "socket";
      break;
  }

  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         statName.st_size,
         statName.st_blocks,
         statName.st_blksize,
         filetype);
}

//This function is for printing line 3
void line3(struct stat statName) {
  if ((S_ISCHR(statName.st_mode) == 0) && (S_ISBLK(statName.st_mode) == 0)) {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
           (long)statName.st_dev,
           (long)statName.st_dev,
           statName.st_ino,
           statName.st_nlink);
  }
  else {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
           (long)statName.st_dev,
           (long)statName.st_dev,
           statName.st_ino,
           statName.st_nlink,
           major(statName.st_rdev),
           minor(statName.st_rdev));
  }
}

//This is a helper function for function line4()
char permitHelper(int S_mode, char * modeChar) {
  char mode_t;
  if ((S_mode) == 0) {
    mode_t = '-';
  }
  else {
    mode_t = *modeChar;
  }
  return mode_t;
}

//This function is for printing line 4
void line4(struct stat statName) {
  char permit[11];
  switch (statName.st_mode & S_IFMT) {
    case S_IFBLK:
      permit[0] = 'b';
      break;
    case S_IFCHR:
      permit[0] = 'c';
      break;
    case S_IFDIR:
      permit[0] = 'd';
      break;
    case S_IFIFO:
      permit[0] = 'p';
      break;
    case S_IFLNK:
      permit[0] = 'l';
      break;
    case S_IFREG:
      permit[0] = '-';
      break;
    case S_IFSOCK:
      permit[0] = 's';
      break;
  }
  permit[1] = permitHelper(statName.st_mode & S_IRUSR, "r");
  permit[2] = permitHelper(statName.st_mode & S_IWUSR, "w");
  permit[3] = permitHelper(statName.st_mode & S_IXUSR, "x");
  permit[4] = permitHelper(statName.st_mode & S_IRGRP, "r");
  permit[5] = permitHelper(statName.st_mode & S_IWGRP, "w");
  permit[6] = permitHelper(statName.st_mode & S_IXGRP, "x");
  permit[7] = permitHelper(statName.st_mode & S_IROTH, "r");
  permit[8] = permitHelper(statName.st_mode & S_IWOTH, "w");
  permit[9] = permitHelper(statName.st_mode & S_IXOTH, "x");
  permit[10] = '\0';

  char * userName = getpwuid(statName.st_uid)->pw_name;
  char * groupName = getgrgid(statName.st_gid)->gr_name;

  printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
         statName.st_mode & ~S_IFMT,
         permit,
         statName.st_uid,
         userName,
         statName.st_gid,
         groupName);
}

//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

//This function is for printing last 4 line
void last4Line(struct stat statName) {
  char * timeAcc = time2str(&statName.st_atime, statName.st_atim.tv_nsec);
  char * timeMod = time2str(&statName.st_mtime, statName.st_mtim.tv_nsec);
  char * timeCha = time2str(&statName.st_ctime, statName.st_ctim.tv_nsec);
  printf("Access: %s\n", timeAcc);
  printf("Modify: %s\n", timeMod);
  printf("Change: %s\n", timeCha);
  printf(" Birth: -\n");
  //free memory
  free(timeAcc);
  free(timeMod);
  free(timeCha);
}

//Main Function
int main(int argc, char * argv[]) {
  struct stat mystat;
  //error for wrong format
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    return EXIT_FAILURE;
  }
  //get multiple arguments
  for (int i = 1; i < argc; i++) {
    if (lstat(argv[i], &mystat) == -1) {
      perror("lstat");
      return EXIT_FAILURE;
    }
    //function invoke
    line1(mystat, argv[i]);
    line2(mystat);
    line3(mystat);
    line4(mystat);
    last4Line(mystat);
  }
}
