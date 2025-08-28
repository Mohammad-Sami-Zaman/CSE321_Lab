#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 5
#define MAX_RESOURCES 5
#define MAX_NAME_LEN 20
#define MAX_ACL_ENTRIES 20
#define MAX_CAP_ENTRIES 20

typedef enum {
    READ     = 1, 
    WRITE    = 2,
    EXECUTE  = 4
} Permission;

typedef struct {
    char name[MAX_NAME_LEN];
} User;

typedef struct {
    char name[MAX_NAME_LEN];
} Resource;

typedef struct {
    char user[MAX_NAME_LEN];
    char resource[MAX_NAME_LEN];
    int permissions;
} ACLEntry;

typedef struct {
    ACLEntry entries[MAX_ACL_ENTRIES];
    int count;
} ACLControlledResource;

typedef struct {
    char resource[MAX_NAME_LEN];
    int permissions;
} Capability;

typedef struct {
    char user[MAX_NAME_LEN];
    Capability caps[MAX_CAP_ENTRIES];
    int count;
} CapabilityUser;

void printPermissions(int perm) {
    if (perm & READ) printf("READ ");
    if (perm & WRITE) printf("WRITE ");
    if (perm & EXECUTE) printf("EXECUTE ");
}

int hasPermission(int userPerm, int requiredPerm) {
    return (userPerm & requiredPerm) == requiredPerm;
}

void addACLEntry(ACLControlledResource *acl, const char *user, const char *resource, int perm) {
    if (acl->count < MAX_ACL_ENTRIES)
        acl->entries[acl->count++] = (ACLEntry){ .user = "", .resource = "", .permissions = perm },
        strncpy(acl->entries[acl->count - 1].user, user, MAX_NAME_LEN - 1),
        strncpy(acl->entries[acl->count - 1].resource, resource, MAX_NAME_LEN - 1);
}

void addCapability(CapabilityUser *user, const char *resource, int perm) {
    if (user->count < MAX_CAP_ENTRIES) {
        strcpy(user->caps[user->count].resource, resource);
        user->caps[user->count].permissions = perm;
        user->count = user->count + 1; 
    }
}

void checkACLAccess(ACLControlledResource *acl, const char *userName, const char *resourceName, int perm) {
    int i = 0;
    while (i < acl->count) {
        if (strcmp(acl->entries[i].user, userName) == 0){
            if(strcmp(acl->entries[i].resource, resourceName) == 0) {
            
            printf("ACL Check: User %s requests ", userName);
            printPermissions(perm);
            printf("on %s: ", resourceName);

            if (hasPermission(acl->entries[i].permissions, perm)) {
                printf("Access GRANTED\n");
            	} 
            else {
                printf("Access DENIED\n");
            	}
            return;
        	}
        }
        i = i + 1;
    }
    printf("ACL Check: User %s has NO entry for resource %s: Access DENIED\n", userName, resourceName);
}

void checkCapabilityAccess(CapabilityUser *user, const char *resourceName, int perm) {
    int i = 0; 
    while (i < user->count) {
        if (strcmp(user->caps[i].resource, resourceName) == 0) {
            printf("Capability Check: User %s requests ", user->user);
            printPermissions(perm);
            printf("on %s: ", resourceName);

            if (hasPermission(user->caps[i].permissions, perm)) {
                printf("Access GRANTED\n");
            } 
            else {
                printf("Access DENIED\n");
            }
            return;
        }
        i = i + 1;
    }
    printf("Capability Check: User %s has NO capability for %s: Access DENIED\n", user->user, resourceName);
}

int main() {

    User users[MAX_USERS] = {{"Alice"}, {"Bob"}, {"Charlie"}, {"Sami"}, {"Sanowar"}};
    Resource resources[MAX_RESOURCES] = {{"File1"}, {"File2"}, {"File3"}, {"File4"}, {"File5"}};

    ACLControlledResource acl = {.count = 0};
    addACLEntry(&acl, "Alice", "File1", READ);
    addACLEntry(&acl, "Bob", "File1", READ);
    addACLEntry(&acl, "Sami", "File4", READ | WRITE);
    addACLEntry(&acl, "Sanowar", "File5", EXECUTE);

    CapabilityUser capUsers[MAX_USERS];
    int i = 0;
    while (i < MAX_USERS) {
        strcpy(capUsers[i].user, users[i].name);
        capUsers[i].count = 0;
        i = i + 1;
    }
    addCapability(&capUsers[0], "File1", WRITE);            
    addCapability(&capUsers[1], "File1", READ); 
    addCapability(&capUsers[3], "File4", READ | WRITE); 
    addCapability(&capUsers[4], "File5", EXECUTE);

    checkACLAccess(&acl, "Alice", "File1", READ);
    checkACLAccess(&acl, "Bob", "File1", WRITE);
    checkACLAccess(&acl, "Charlie", "File1", READ);
    checkACLAccess(&acl, "Sami", "File4", WRITE);
    checkACLAccess(&acl, "sanowar", "File5", EXECUTE);
    
    printf("\n");

    checkCapabilityAccess(&capUsers[0], "File1", WRITE);
    checkCapabilityAccess(&capUsers[1], "File1", WRITE);
    checkCapabilityAccess(&capUsers[2], "File2", READ);
    checkCapabilityAccess(&capUsers[3], "File4", READ);
    checkCapabilityAccess(&capUsers[4], "File5", EXECUTE);

    return 0;
}











