#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "STD.h"

/**
 * @brief Structure to store patient information.
 */
struct patient{
	u8 name[50];
	u32 age;
	u8 gender[20];
	u32 ID;
	struct patient * next;
};

/** @brief Pointer to the first patient in the linked list. */
struct patient * head1 = NULL;

/** @brief Global pointer used to access a searched patient. */
struct patient * global_pointer=NULL;

/** @brief Array storing the patient ID assigned to each reservation slot. */
u32 slot_patient_id[5]={0,0,0,0,0};

/** @brief Array containing the available reservation time slots. */
u8 slot[5][30]={"1- 2:00 - 2:30","2- 2:30 - 3:00","3- 3:00 - 3:30","4- 4:00 - 4:30","5- 4:30 - 5:00"};

/**
 * @brief Searches for a patient using their ID.
 * @param head1 Pointer to the first patient in the linked list.
 * @param id ID of the patient to search for.
 * @return -1 if the patient exists, 1 otherwise.
 */
u32 search_ID(struct patient * head1,u32 id){
	while( head1 != NULL){
		if(head1->ID==id){ 
			global_pointer=head1;
			return -1; //موجود
		}
		head1=head1->next;
	}
	return 1;
}

/**
 * @brief Adds a new patient to the linked list.
 * @param head2 Double pointer to the head of the patient list.
 */
void add_patient(struct patient **head2){
	u32 id;
	struct patient * last =(struct patient *)malloc(sizeof(struct patient ));

	printf("enter id of patient : ");
	scanf("%d",&id);

	if (search_ID(*head2,id)==1){
		last->ID=id;
		printf("enter name of patient : ");
		scanf("%s",last->name);
		printf("enter age of patient : ");
		scanf("%d",&last->age);
		printf("enter gender of patient : ");
		scanf("%s",last->gender);
	}
	else {
		printf("ERRORRRR .. ID already exists \n"); 
		return;
	}
	last->next = NULL;
	if(*head2==NULL){
		*head2=last;
	}
	else
	{	
		struct patient *temp=*head2;
		while(temp->next != NULL){
			temp=temp->next;
		}
		temp->next=last;
	}
}

/**
 * @brief Edits the information of an existing patient.
 * @param head2 Double pointer to the head of the patient list.
 */
void Edit_patient(struct patient **head2){
	u32 id;
	struct patient *Edit=*head2;

	printf("please enter ID ");
	scanf("%d",&id);

	if (search_ID(*head2,id)==-1){
		Edit->ID=id;
		printf("Enter new name ");
		scanf("%s",Edit->name);
		printf("Enter new age ");
		scanf("%d",&Edit->age);
		printf("Enter new gender ");
		scanf("%s",Edit->gender);
		printf("Information updated successfully \n");
		return ;
	}
	else {
		printf("ERRORRRR .. ID not exists \n"); 
		return;
	}
}

/**
 * @brief Displays the information of a patient.
 * @param head Pointer to the first patient in the linked list.
 * @param id ID of the patient whose information will be displayed.
 */
void print(struct patient * head,u32 id){	
	if (search_ID(head,id)==-1){
			printf("patient Name : %s \n",global_pointer->name);
			printf("patient Age : %d \n",global_pointer->age);
			printf("patient Gender : %s \n",global_pointer->gender);
		return ;
	}
	else {
		printf("ERRORRRR .. ID not exists \n"); 
	}
}

/**
 * @brief Reserves an available time slot for an existing patient.
 * @param head1 Pointer to the first patient in the linked list.
 * @return Reservation status.
 */
u32 Reserve(struct patient * head1){
	u32 id,num;

	for(u32 i=0;i<5;i++){ //print slots avaliable
		if(slot_patient_id[i]==0){
			printf("%s  avaliable \n",slot[i]);
		}
	}
	printf("enter num of slot ");
	scanf("%d",&num);
	u32 index=num-1;
	printf("enter id ");
	scanf("%d",&id);

	if (search_ID(head1,id)==-1){
		if(slot_patient_id[index]==0 && index<5 && index>=0){  
			slot_patient_id[index]=id;


		}
	}
	else printf("ID not exist\n");
}

/**
 * @brief Cancels a patient's reservation.
 * @param head1 Pointer to the first patient in the linked list.
 */
void cancel_reservation(struct patient * head1){
	u32 num,cancle_ID;
	printf("enter ID :");
	scanf("%d",&cancle_ID);

	if (search_ID(head1,cancle_ID)==-1){ 
		for(u32 i =0;i<5;i++)
		{
			if(slot_patient_id[i]==cancle_ID){ 
				slot_patient_id[i]=0;
				printf("Reservation cancelled successfully\n");
			}
		}	
	}
	else 
		printf("ID not exist\n");
}	

/**
 * @brief Displays the admin menu and handles admin operations.
 * @return 0 when the admin exits the menu.
 */
u32 Right_pass(){
	u32 answer;

	while(1)
	{
	printf("1-Add new patient\n");
	printf("2-Edit patient\n");
	printf("3-Reserve a slot\n");
	printf("4-Cancel reservation\n");
	printf("5-EXIT\n");
	printf("Enter your answer ");
	scanf("%d",&answer);
	switch(answer){
		case 1:
		{
			add_patient(&head1); 
			break;
		}
		case 2:
			Edit_patient(&head1);
			break;
		case 3:
			Reserve(head1);
			break;
		case 4:
			cancel_reservation(head1);
			break;
		case 5:
			return 0;
		default :
			printf("Invalid number! .. please try again\n");
			Right_pass();
			break;
	}
	}
}

/**
 * @brief Authenticates the administrator using a password.
 * @return -1 if the maximum number of attempts is exceeded.
 */
u32 Admin_mode(){
	u32 pass,attempts=0;
	printf("You have 3 attempts \n");
	printf("enter password ");
	for(u32 i=0;i<3;i++){
		scanf("%d",&pass);
		if(pass==1234){
			Right_pass();
			break;
		}
		else{
			printf("password wrong \n");
			attempts++;
			if(attempts==3){
				printf("No more attempts\n");
				return -1;
			}
			else { 
				printf("enter password ");
			}
		}
	}
}

/**
 * @brief Requests a patient ID and displays the patient's record.
 * @param head1 Pointer to the first patient in the linked list.
 */
void View_Patient_Record(struct patient * head1){
	u32 id;
	printf("Enter patient ID : ");
	scanf("%d",&id);

	if(search_ID(head1,id)==-1){
			print(head1,id);
		}
	else
		printf("ID not exist\n");
}

/**
 * @brief Displays all reservation slots and their current status.
 */
void View_Today_Reservations(){
	for(u32 i=0;i<5;i++){ //print slots avaliable
			if(slot_patient_id[i]==0)
			{
				printf("%s  avaliable \n",slot[i]);
			}
			else printf("%s patient ID : %d\n",slot[i],slot_patient_id[i]);
	}
}

/**
 * @brief Displays the user menu and handles user operations.
 * @return 0 when the user exits the menu.
 */
u32 User_mode(){
	u32 choice;
	while(1){
		printf("1-View Patient Record\n");
		printf("2-View Today's Reservations\n");
		printf("3-EXIT\n");
		printf("Enter your choice ");
		scanf("%d",&choice);
		switch (choice){
			case 1:
				View_Patient_Record(head1);
				break;

			case 2:
				View_Today_Reservations();
				break;
			case 3:
				return 0;
			default :
				printf(" ERROR .. TRY AGAIN\n");
				break;
		}
	}	
}

/**
 * @brief Main entry point of the Clinic Management System.
 * @details Allows the user to select admin mode, user mode, or exit.
 * @author Mai Essam
 */
void main(void){
	u32 mode;
	while(1){
	printf("1-Admin mode \n");
	printf("2-user mode\n");
	printf("3-EXIT\n");
	printf("Choose the mood : ");
	scanf("%d",&mode);

	switch (mode){
	case 1:
		if(Admin_mode()==-1) return;
		else continue;
	case 2:
		User_mode();
		break;
	case 3:
		return;
	default:
		printf("ERRORRR");
		return;
	}	
	}
}
