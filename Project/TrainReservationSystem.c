#include<stdio.h>
#include<stdlib.h>

struct train {

        int trainID;
        struct train *nextStation, *prevStation;
        char stationName;
        int seatAvailable;

} *head, *tail;

//Dhaka 1, Cummila 2, Chittagong 3, Barisal 4, Khulna 5(tail),
//Rajshahi 6, Sylhet 7, Dinajpur 8;

struct customer {

    char name[25];
    int nid;
    int from;
    int destination;
    int price;
    struct customer *nextCustomer;

} *headQueue;

    int trainCount = 8;

void trainListSetUp(){
    int i;
    head = (struct train *)malloc(sizeof(struct train));
    tail = (struct train *)malloc(sizeof(struct train));

    if(head == NULL || tail == NULL){
        printf("memory Error.\n");
        return;
    }
    else {
            //printf("Hi");
            struct train *newStation, *temp;
        int j = 1;

        head->trainID = j;
        head->nextStation = NULL;
        head->prevStation = NULL;
        head->seatAvailable = 5;
        j++;
        temp = head;

    for(i = 2; i <= 7; i++){
           // printf("Hi");
            newStation = (struct train *)malloc(sizeof(struct train));
        newStation->trainID = j;
       // printf("Hi");
        newStation->nextStation = NULL;
      //  printf("Hi");
        newStation->prevStation = temp;
        newStation->seatAvailable = 5;
        temp = newStation;
        j++;
   // printf("Hi");
        if(i == 5){
         //   printf("Hi");
            tail = newStation;
        }
    }//printf("Hi");
        newStation->nextStation = head;
        head->prevStation = newStation;

    }
}
int seatBooking(int station){
    struct train *temp;
    temp = head;
    int noSeat = 0;
    if(station == temp->trainID){
        temp->seatAvailable--;
        if(temp->seatAvailable <= -1){
            noSeat = 1;
            printf("%d", temp->seatAvailable);
            return noSeat;
        }
    }
    else{
        temp = temp->nextStation;
    }
}
void seatFreeing(int station){
    struct train *temp;
    temp = head;
    if(station == temp->trainID){
        temp->seatAvailable++;
    }
    else {
        temp = temp->nextStation;
    }
}

    int firstCustomer = 0;
void ticketBooking() {
    struct customer *newCustomer, *temp;

    if(firstCustomer == 0){
        headQueue = (struct customer *)malloc(sizeof(struct customer));
        headQueue->nextCustomer = NULL;
        printf("Welcome First Customer!!!\nEnter Your Name, \n");
        scanf("%s", headQueue->name);
        printf("Enter Your NID.\n");
        scanf("%d", &headQueue->nid);
        printf("From: \n1.Dhaka\n2.Cumilla\n3.Chittagong\n4.Barisal\n5.Khulna\n6.Rajshahi\n7.Sylhet\n8.Dinajpur\n");
        scanf("%d", &headQueue->from);
        seatBooking(headQueue->from);
        printf("To: \n1.Dhaka\n2.Cumilla\n3.Chittagong\n4.Barisal\n5.Khulna\n6.Rajshahi\n7.Sylhet\n8.Dinajpur\n");
        scanf("%d", &headQueue->destination);
        seatFreeing(headQueue->destination);
        temp = headQueue;
        firstCustomer = 1;
    }
    else {
        int seat;
        newCustomer = (struct customer *)malloc(sizeof(struct customer));

        temp->nextCustomer = newCustomer;
        newCustomer->nextCustomer = NULL;
        printf("Enter your Name\n");
        scanf("%s", newCustomer->name);
        printf("Enter Your NID.\n");
        scanf("%d", &newCustomer->nid);
        printf("From: \n1.Dhaka\n2.Cumilla\n3.Chittagong\n4.Barisal\n5.Khulna\n6.Rajshahi\n7.Sylhet\n8.Dinajpur\n");
        scanf("%d", &newCustomer->from);
        seat = seatBooking(newCustomer->from);
            if(seat == 1){
                free(newCustomer);
                printf("No Seat LEFT.\n");
                return;
            }
        printf("To: \n1.Dhaka\n2.Cumilla\n3.Chittagong\n4.Barisal\n5.Khulna\n6.Rajshahi\n7.Sylhet\n8.Dinajpur\n");
        scanf("%d", &newCustomer->destination);
        seatFreeing(newCustomer->destination);
        temp = newCustomer;

    }


}


int main()
{
    trainListSetUp();
    int option;
    int exit = 0;

    printf("Welcome to the Train Reservation Online Platform.\n");

    while(exit == 0){

        printf("1. Reserve a Train Ticket.\n");
        printf("2. View Available Train Details.\n");
        printf("3. View Customer History.\n");
        printf("4. Exit.\n");

        scanf("%d", &option);

        switch(option){

        case 1:
                ticketBooking();
            break;
        case 2:

            break;
        case 3:

            break;
        case 4:
            exit == 1;
            break;
        }

    }






}
