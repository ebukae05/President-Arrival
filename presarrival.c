//creating a linked list that ask for capacity size of date
//ask user for date digit per node, and collects and contains the data in a list
//encodes, scrambles and decodes the list.
//then displays the list

//include <stdio.h> lib for basic user input, include <stdlib.h> to collect data for node
#include <stdio.h>
#include <stdlib.h>
//define the node (typedef)
struct Node {
    int data;
    struct Node* next;
};
//create the Node 
struct Node* createNode(int data) {
    struct Node* newNode = (struct  Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    //link newNode with data to collect input into list
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

//create a void to be able to see the list as ur updating
void* displayList(struct Node* head){
    struct Node* temp = head;
    while(temp != NULL){
        printf("%d", temp->data);
        temp = temp->next;
    }
}

//ask user for size of node, and collect data for each digit of list
struct Node* enterDate(){
    struct Node* head = NULL;
    struct Node* tail = NULL;
    int n=0, data, addedNumber;
    //put 6 as date format mmddyy
    printf("Enter size of date(6): ");
    scanf("%d", &n);
    printf("\nEnter %d numbers: ", n);
    for (int i = 0; i < n; i++){
        printf("\nEnter date for node %d: ", i + 1);
        scanf("%d", &data);
        struct Node* newNode = createNode(data);
        if (head == NULL){
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}
//encode the list with + 7 % 10
struct Node* encodeDate(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        temp->data = ((temp->data) + 7) % 10;
        temp = temp->next;
    }
    return head;
}
//scramble digits to required format YYMMDD
struct Node* scrambleDate(struct Node* head) {
    //initialize list variables
    struct Node* M1 = head;
    struct Node* M2 = head->next;
    struct Node* D1 = M2->next;
    struct Node* D2 = D1->next;
    struct Node* Y1 = D2->next;
    struct Node* Y2 = Y1->next;
    
    //scrambled to required format
    head = Y1;
    Y1->next = Y2;
    Y2->next = M1;
    M1->next = M2;
    M2->next = D1;
    D1->next = D2;
    D2->next = NULL;
    return head;
}
//unscramble back to original format MMDDYY
struct Node* unscrambleList(struct Node* head) {
    struct Node* Y1 = head;
    struct Node* Y2 = head->next;
    struct Node* M1 = Y2->next;
    struct Node* M2 = M1->next;
    struct Node* D1 = M2->next;
    struct Node* D2 = D1->next;

    head = M1;
    M1->next = M2;
    M2->next = D1;
    D1->next = D2;
    D2->next = Y1;
    Y1->next = Y2;
    Y2->next = NULL;
    return head;
}

//Decode the unscrambled code, separate into variables and display arrival date
struct Node* displayArrival(struct Node* head){
    struct Node* temp = head;
    int months = 0, divisor = 10, days = 0, years = 0, i;
    while(temp != NULL) {
        if ((temp->data) - 7 < 0) {
            temp->data = ((temp->data) - 7) + 10;
        } 
        else temp->data = (temp->data) - 7;
        temp = temp->next;
    }

    //use an array to extract the digits
    int digits[6];
    i = 0;
    temp = head;
    while (temp!=NULL && i < 6) {
        digits[i] = temp->data;
        temp = temp->next;
        i++;
    }
    //once extracted contain digits within the necessary variable
    //months
    divisor = 10;
    for (i = 0; i < 2; i++) {
        months += (digits[i] * divisor);
        divisor /= 10;
    }
    //days
    divisor = 10;
    for (i = 2; i < 4; i++) {
        days += (digits[i] * divisor);
        divisor /= 10;
    }
    //years, and account for before 2000 dates
    divisor = 10;
    for (i = 4; i < 6; i++) {
        years += (digits[i] * divisor);
        divisor /= 10;
    }
    if (years <= 25) {
        years += 2000;
    }
    else {
        years += 1900;
    }
    //display arrival
    printf("\nThe President will arrive on ");
    switch(months) {
    case 1: printf("January");
        break;
    case 2: printf("Febuary");
        break;
    case 3: printf("March");
        break;
    case 4: printf("April");
        break;
    case 5: printf("May");
        break;
    case 6: printf("June");
        break;
    case 7: printf("July");
        break;
    case 8: printf("August");
        break;
    case 9: printf("September");
        break;
    case 10: printf("October");
        break;
    case 11: printf("November");
        break;
    case 12: printf("December");
        break;
    }
    printf(" %d, %d", days, years);
    return 0;
}

//update the linked list
int main() {
    struct Node* head = NULL;
    

    head = enterDate();
    head = encodeDate(head);
    head = scrambleDate(head);
    head = unscrambleList(head);
    head = displayArrival(head);

}   