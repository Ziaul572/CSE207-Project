#include<stdio.h>
#include<stdlib.h>

struct train
{

    int trainID;
    struct train *nextStation, *prevStation;
    char stationName;
    int seatAvailable;

} *head, *tail;

//Dhaka 1, Cummila 2, Chittagong 3, Barisal 4, Khulna 5(tail),
//Rajshahi 6, Sylhet 7, Dinajpur 8;

struct customer
{

    char name[25];
    int nid;
    int from;
    int destination;
    int price;
    struct customer *nextCustomer;

} *headQueue;

int trainCount = 8;

void trainRoad();

void trainListSetUp()
{
    int i;
    head = (struct train *)malloc(sizeof(struct train));
    tail = (struct train *)malloc(sizeof(struct train));

    if(head == NULL || tail == NULL)
    {
        printf("memory Error.\n");
        return;
    }
    else
    {
        //printf("Hi");
        struct train *newStation, *temp;
        int j = 1;

        head->trainID = j;
        head->nextStation = NULL;
        head->prevStation = NULL;
        head->seatAvailable = 5;
        //head->stationName = "Dhaka";
        j++;
        temp = head;

        for(i = 2; i <= 8; i++)
        {
            //printf("Hi");
            newStation = (struct train *)malloc(sizeof(struct train));
            temp->nextStation = newStation;
            newStation->trainID = j;
            //printf("%d" , j);
            newStation->nextStation = NULL;
            //  printf("Hi");
            newStation->prevStation = temp;

            newStation->seatAvailable = 5;
            temp = newStation;
            j++;
            // printf("Hi");
            if(i == 5)
            {
                //   printf("Hi");
                tail = newStation;
            }
        }//printf("Hi");
        newStation->nextStation = head;
        head->prevStation = newStation;
        //printf("%d %d", newStation->trainID, head->prevStation->trainID);
        // trainRoad();

    }
}

void trainRoad()
{

    struct train *temp;
    temp = head;
    for(int i = 0; i < 8; i++)
    {
        printf("%d", temp->trainID);
        temp = temp->nextStation;
    }

}
int seatBooking(int station)
{
    struct train *temp;
    temp = head;
    int noSeat = 0;
    //printf("%d", station);
    while(noSeat == 0)
    {
        if(station == temp->trainID)
        {

            printf("Seat Reamining from this Station %d \n", temp->seatAvailable);

            if(temp->seatAvailable == 0)
            {
                noSeat = 1;
                printf("%d", temp->seatAvailable);
                return noSeat;
            }
            temp->seatAvailable--;
            return 0;
        }
        else
        {
            temp = temp->nextStation;
        }
    }
}
void seatFreeing(int station)
{
    struct train *temp;
    temp = head;
    while (temp->nextStation == head)
    {
        if(station == temp->trainID)
        {
            temp->seatAvailable++;
            return;
        }
        else
        {
            temp = temp->nextStation;
        }
    }
}

int ticketPrice(int from, int destination)
{

    int price;
    int diff;

    diff = from - destination;

    if (diff < 0)
    {
        diff = diff * (-1);
        price = 500 * diff;
    }
    else
    {
        price = 500 * diff;
    }
    return price;


}

int firstCustomer = 0;
void ticketBooking()
{
    struct customer *newCustomer, *temp;

    if(firstCustomer == 0)
    {
label1:
        //printf("%s", head->stationName);
        headQueue = (struct customer *)malloc(sizeof(struct customer));
        headQueue->nextCustomer = NULL;
        printf("Welcome First Customer!!!\nEnter Your Name, \n");
        scanf("%s", headQueue->name);

        // printf("%s", headQueue->name);

        printf("Enter Your NID.\n");
        scanf("%d", &headQueue->nid);
        printf("From: \n1.Dhaka\n2.Cumilla\n3.Chittagong\n4.Barisal\n5.Khulna\n6.Rajshahi\n7.Sylhet\n8.Dinajpur\n");
        scanf("%d", &headQueue->from);
        seatBooking(headQueue->from);
        printf("To: \n1.Dhaka\n2.Cumilla\n3.Chittagong\n4.Barisal\n5.Khulna\n6.Rajshahi\n7.Sylhet\n8.Dinajpur\n");
        scanf("%d", &headQueue->destination);
        headQueue->price = ticketPrice(headQueue->from, headQueue->destination);
        printf("The Ticket Price is : %d \n", headQueue->price);
        printf("Would you like to confirm the purchase?\n");
        printf("1.Yes\t2.No");
        int choice;
        scanf("%d", &choice);
        if(choice == 1)
        {

        }
        else
        {
            goto label1;
        }
        seatFreeing(headQueue->destination);

        firstCustomer = 1;
        printf("First Booking is Successful.\n\n");
    }
    else
    {
        int seat;
label2:
        newCustomer = (struct customer *)malloc(sizeof(struct customer));
        temp = headQueue;
        if (newCustomer == NULL)
        {
            printf("Error.");
        }
        else
        {

            temp->nextCustomer = newCustomer;
            newCustomer->nextCustomer = NULL;
            printf("Enter your Name\n");
            scanf("%s", newCustomer->name);
            printf("Enter Your NID.\n");
            scanf("%d", &newCustomer->nid);
            printf("From: \n1.Dhaka\n2.Cumilla\n3.Chittagong\n4.Barisal\n5.Khulna\n6.Rajshahi\n7.Sylhet\n8.Dinajpur\n");
            scanf("%d", &newCustomer->from);
            seat = seatBooking(newCustomer->from);
            if(seat == 1)
            {
                free(newCustomer);
                printf("No Seat LEFT.\n");
                return;
            }
            printf("To: \n1.Dhaka\n2.Cumilla\n3.Chittagong\n4.Barisal\n5.Khulna\n6.Rajshahi\n7.Sylhet\n8.Dinajpur\n");
            scanf("%d", &newCustomer->destination);
            seatFreeing(newCustomer->destination);
            newCustomer->price = ticketPrice(newCustomer->from, newCustomer->destination);
            printf("The Ticket Price is : %d \n", headQueue->price);
            printf("Would you like to confirm the purchase?\n");
            printf("1.Yes\t2.No\n");
            int choice;
            scanf("%d", &choice);
            if(choice == 1)
            {

            }
            else
            {
                goto label2;
            }

            temp = newCustomer;

            printf("Booking Successful.\n\n");
        }
    }

}

void trainAvailable()
{

    struct train *temp;
    temp = head;

    printf("The Departing from Dhaka has remaining seats : %d\n", temp->seatAvailable);
    temp = temp->nextStation;
    printf("The Departing from Cumilla has remaining seats : %d\n", temp->seatAvailable);
    temp = temp->nextStation;
    printf("The Departing from Chittagong has remaining seats : %d\n", temp->seatAvailable);
    temp = temp->nextStation;
    printf("The Departing from Barisal has remaining seats : %d\n", temp->seatAvailable);
    temp = temp->nextStation;
    printf("The Departing from Khulna has remaining seats : %d\n", temp->seatAvailable);
    temp = temp->nextStation;
    printf("The Departing from Rajshahi has remaining seats : %d\n", temp->seatAvailable);
    temp = temp->nextStation;
    printf("The Departing from Sylhet has remaining seats : %d\n", temp->seatAvailable);
    temp = temp->nextStation;
    printf("The Departing from Dinajpur has remaining seats : %d\n", temp->seatAvailable);
    temp = temp->nextStation;
    printf("\n");

}

void viewCustomerHistory()
{

    struct customer *temp;
    temp = headQueue;
    // printf("hi");
    while(temp != NULL)
    {
        //printf("yo");
        if(temp == headQueue)
        {
            //printf("hi");
            printf("\nFirst Customer.\n");
        }

        printf("Customer Details: \n\n");
        printf("Customer's Name : %s\n", temp->name);
        printf("Customer's NID : %d \n", temp->nid);
        printf("Customer's Ticket Price: %d\n", temp->price);
        printf("Departure from: ");
        if(temp->from % 2 == 0)
        {
            if(temp->from == 2)
            {
                printf("Cumilla\n");
            }
            else if(temp->from == 4)
            {
                printf("Barisal\n");
            }
            else if(temp->from == 6)
            {
                printf("Rajshahi\n");
            }
            else if(temp->from == 8)
            {
                printf("Dinajpur\n");
            }

        }
        else
        {
            if(temp->from == 1)
            {
                printf("Dhaka\n");
            }
            else if(temp->from == 3)
            {
                printf("Chittagong\n");
            }
            else if(temp->from == 5)
            {
                printf("Khulna\n");
            }
            else if(temp->from == 7)
            {
                printf("Sylhet\n");
            }
        }
        printf("To: ");

        if(temp->destination % 2 == 0)
        {
            if(temp->destination == 2)
            {
                printf("Cumilla\n");
            }
            else if(temp->destination == 4)
            {
                printf("Barisal\n");
            }
            else if(temp->destination == 6)
            {
                printf("Rajshahi\n");
            }
            else
            {
                printf("Dinajpur\n");
            }

        }
        else
        {
            if(temp->destination == 1)
            {
                printf("Dhaka\n");
            }
            else if(temp->destination == 3)
            {
                printf("Chittagong\n");
            }
            else if(temp->destination == 5)
            {
                printf("Khulna\n");
            }
            else
            {
                printf("Sylhet\n");
            }
        }

        temp = temp->nextCustomer;

    }

}


int main()
{
    trainListSetUp();
    //trainRoad();
    int option;
    int exit = 0;
//
    printf("Welcome to the Train Reservation Online Platform.\n");
    // printf("%s", head->stationName);
    while(exit == 0)
    {

        printf("1. Reserve a Train Ticket.\n");
        printf("2. View Available Train Details.\n");
        printf("3. View Customer History.\n");
        printf("4. Exit.\n");

        scanf("%d", &option);

        switch(option)
        {

        case 1:
            ticketBooking();
            break;
        case 2:
            trainAvailable();
            break;
        case 3:
            viewCustomerHistory();
            break;
        case 4:
            exit = 1;
            break;
        }

    }

}
