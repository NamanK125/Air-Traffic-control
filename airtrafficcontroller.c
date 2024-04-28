#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAXLEN 512 

struct msg_buffer {
    long msg_type;
    int plane_no;
    int msg_text[MAXLEN];
};

struct details {
    int aair;
    int dair;
    int pid;
    int totalWeight;
    int ptype;
    int seats;
};

int main() {
    int n;
    int c = 1;
    printf("Enter the number of airports to be handled/managed: ");
    scanf("%d", &n);

    key_t key;
    int msgid;
    char buf[MAXLEN];
    char o = 'A';
    key = ftok("m.txt", o);
    if (key == -1) {
        printf("Error in creating unique key\n");
        exit(1);
    }
    struct msg_buffer message;
    struct details pdetails[11];

    msgid = msgget(key, 0644 | IPC_CREAT);
    if (msgid == -1) {
        printf("Error in creating message queue\n");
        exit(1);
    }
    printf("%d", msgid);

    


    while (1) {
        pid_t p = fork();
        if(p < 0){
            perror("Error in fork.");
        }else if(p == 0){
            if (msgrcv(msgid, (void *)&message, sizeof(message) - sizeof(long), 100, 0) == -1) {
            printf("Error in receiving message\n");
            exit(1);
        }

        pdetails[c].aair = message.msg_text[0];
        pdetails[c].dair = message.msg_text[1];
        pdetails[c].pid = message.msg_text[2];
        pdetails[c].totalWeight = message.msg_text[3];
        pdetails[c].ptype = message.msg_text[4];
        pdetails[c].seats = message.msg_text[5];

        message.msg_type = 120 + pdetails[c].dair;

        if (msgsnd(msgid, (void *)&message, sizeof(message) - sizeof(long), 0) == -1) {
            printf("Error in sending message %s", buf);
            exit(1);
        }

        if (msgrcv(msgid, (void *)&message, sizeof(message) - sizeof(long), 160 + pdetails[c].dair, 0) == -1) {
            printf("Error in receiving message\n");
            exit(1);
        }

        message.msg_type = 200 + pdetails[c].pid;

        if (msgsnd(msgid, (void *)&message, sizeof(message) - sizeof(long), 0) == -1) {
            printf("Error in sending message %s", buf);
            exit(1);
        }

        FILE *fptr;
        fptr = fopen("AirTrafficController.txt", "a");
        if (fptr == NULL) {
            printf("Error in opening file\n");
            exit(1);
        }
        fprintf(fptr, "Plane %d has departed from Airport %d and will land at Airport %d.\n", pdetails[c].pid, pdetails[c].dair, pdetails[c].aair);
        fclose(fptr);

        c++;


        if (c == n + 1)
            break;
        

        }else{
            if (msgrcv(msgid, (void *)&message, sizeof(message) - sizeof(long), 400, 0) == -1) {
            printf("Error in receiving message\n");
            exit(1);
        }

        pdetails[c].aair = message.msg_text[0];
        pdetails[c].dair = message.msg_text[1];
        pdetails[c].pid = message.msg_text[2];
        pdetails[c].totalWeight = message.msg_text[3];
        pdetails[c].ptype = message.msg_text[4];
        pdetails[c].seats = message.msg_text[5];

        message.msg_type = 140 + pdetails[c].aair;

        // void reject_departure() {
        //     // Get the next plane message
        //     int plane_id = get_next_plane_message();

        //     // If the plane_id is -1, there are no more messages
        //     if(plane_id == -1) {
        //         printf("No more plane messages.\n");
        //         return;
        //     }

        //     // Send a rejection message to the plane
        //     send_rejection_message(plane_id);

        //     printf("Departure rejected for plane %d.\n", plane_id);
        // }

        if (msgsnd(msgid, (void *)&message, sizeof(message) - sizeof(long), 0) == -1) {
            printf("Error in sending message %s", buf);
            exit(1);
        }

        if (msgrcv(msgid, (void *)&message, sizeof(message) - sizeof(long), 180 + pdetails[c].aair, 0) == -1) {
            printf("Error in receiving message\n");
            exit(1);
        }

        message.msg_type = 300 + pdetails[c].pid;

        if (msgsnd(msgid, (void *)&message, sizeof(message) - sizeof(long), 0) == -1) {
            printf("Error in sending message %s", buf);
            exit(1);
        }

        if(msgrcv(msgid, &message, sizeof(message.msg_text), 900, 0) == -1) {
            perror("Error in receiving message");
            exit(1);
        }

        // If message type is 900, terminate the program
        if(message.msg_type == 900) {
            printf("Termination call received from cleanup.\n");
           return 0;
        }
    }
    }

    return 0;
}
