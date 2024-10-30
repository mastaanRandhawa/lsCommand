#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_permissions(mode_t mode)
{
    // Check if it's a directory or a regular file
    if (S_ISDIR(mode))
    {
        printf("d");
    }
    else
    {
        printf("-");
    }

    // Owner permissions
    if (mode & S_IRUSR)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if (mode & S_IWUSR)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if (mode & S_IXUSR)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }

    // Group permissions
    if (mode & S_IRGRP)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if (mode & S_IWGRP)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if (mode & S_IXGRP)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }

    // Other (world) permissions
    if (mode & S_IROTH)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if (mode & S_IWOTH)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if (mode & S_IXOTH)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }
}



void print_file_info(const char *file, int show_inode, struct stat *info)
{
    if (show_inode)
    {
        printf("%lu ", (unsigned long)info->st_ino);
    }

    //what premissions are allowed on the files
    print_permissions(info->st_mode);
    printf("%2lu ", (unsigned long)info->st_nlink);

    struct passwd *pw = getpwuid(info->st_uid);
    struct group *gr = getgrgid(info->st_gid);
    printf("%-8s%-8s", pw->pw_name, gr->gr_name); // names to the directory

    printf("%5ld ", (long)info->st_size); // size of the files

    char timeString[20];
    strftime(timeString, sizeof(timeString), "%b %e %Y %H:%M", localtime(&info->st_mtime));
    printf("%s ", timeString);

    printf("%s\n", file);
}



// Func for proccessing directoires
void process_directory(const char *directoryName, int show_inode, int long_list)
{

    printf("%s\n", directoryName);
    DIR *directory = opendir(directoryName);
    if (!directory)
    {
        printf("Could not open directory!\n");
        return;
    }

    struct dirent *statistics;
    while ((statistics = readdir(directory)) != NULL)
    {

        //Skip "." and ".."
        if (strcmp(statistics->d_name, ".") == 0 || strcmp(statistics->d_name, "..") == 0)
        {
            continue;
        }

        //name of the directory
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", directoryName, statistics->d_name);

        struct stat info;
        if (stat(path, &info) == -1)
        {
            fprintf(stderr, "Failed to get file status for %s\n", path);
            continue;
        }

        if (long_list)
        {
            print_file_info(path, show_inode, &info);
        }
        else if (show_inode)
        {
            printf("%lu %s  ", (unsigned long)info.st_ino, statistics->d_name);
        }
        else
        {
            printf("%s  ", statistics->d_name);
        }
    }

    closedir(directory);
}



int main(int argc, char *argv[])
{
    int show_inode = 0, long_list = 0;

    // Parse command line options
    int first_dir_index = argc; // Track the first directory index
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            for (int j = 1; argv[i][j] != '\0'; j++)
            {
                if (argv[i][j] == 'i')
                {
                    show_inode = 1;
                }
                else if (argv[i][j] == 'l')
                {
                    long_list = 1;
                }
            }
        }
        else
        {
            first_dir_index = i;
            break;
        }
    }

    if (first_dir_index == argc)
    {
        // No directory arguments provided, default to current directory
        process_directory(".", show_inode, long_list);
    }
    else
    {
        // Process each directory provided on the command line
        for (int i = first_dir_index; i < argc; i++)
        {
            process_directory(argv[i], show_inode, long_list);
        }
    }

    return 0;
}
