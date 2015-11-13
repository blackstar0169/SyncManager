#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <err.h>
#include <blkid/blkid.h>
#include <fcntl.h>
#include <unistd.h>
#include <regex>

using namespace std;

#define ERROR_FOPEN_MOUNTS 1
#define TYPE_NUMBER 2
string accepted_type[TYPE_NUMBER] = {string("ntfs"),string("vfat")};


int main() { 
    struct dirent *lecture;
    FILE *mount_file=NULL;    
    DIR *rep;
    char str[100];
    int res, same;

    std::regex integer("sd[a-z]+");

    blkid_probe pr;

    rep = opendir("/dev/");
    if(rep==NULL)
    	return 1;

    while ((lecture = readdir(rep))) {   	
    	if(strcmp(lecture->d_name, "..")!=0 && strcmp(lecture->d_name, ".")!=0 && regex_match(lecture->d_name,integer)){
    		pr = blkid_new_probe();
    		strcpy(str, "/dev/");
    		strcat(str, lecture->d_name);
    		
	        pr = blkid_new_probe_from_filename(str);
	        if(pr){

		        printf("%s | ", str);

		        blkid_partlist ls;
				int nparts, i;

				ls = blkid_probe_get_partitions(pr);
				nparts = blkid_partlist_numof_partitions(ls);
				

				//if (nparts > 0){
					printf("Number of partitions:%d\n", nparts);

					// Get UUID, label and type
					const char *uuid;
					const char *label;
					const char *type;
					char *mountPath;
					char *devPath;
					char *trash;

					for (i = 0; i < nparts; i++) {
						char in_array=0;
						char dev_name[20];
						sprintf(dev_name, "%s%d", str, (i+1));

						pr = blkid_new_probe_from_filename(dev_name);
						blkid_do_probe(pr);

						blkid_probe_lookup_value(pr, "UUID", &uuid, NULL);

						blkid_probe_lookup_value(pr, "LABEL", &label, NULL);

						blkid_probe_lookup_value(pr, "TYPE", &type, NULL);

						for(int j=0; j<TYPE_NUMBER; j++){
							if(strcmp(type, (char*)accepted_type[j].c_str())==0 && strlen(label)>0)
								in_array=1;
						}

						if(in_array){
							mount_file = fopen("/proc/mounts", "r");
							if(mount_file==NULL)
								exit(ERROR_FOPEN_MOUNTS);

							do{
								res = fscanf(mount_file, "%s %s ", devPath, mountPath);
								same = strcmp(devPath, dev_name);
							}while(res!=EOF && same!=0);
							printf("UUID=%s, LABEL=%s, MOUNT=%s\n", uuid, label, mountPath);
							fclose(mount_file);
						}
					}
				//}
			}
			
			blkid_free_probe(pr);
			
	    }
    }
    closedir(rep);
	return 0;
}




