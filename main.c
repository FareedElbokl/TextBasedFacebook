/********* main.c ********
    Student Name 	= Fareed El Bokl
    Student Number	= 101256495
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"

int main()
{
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    /* THIS CODE WILL LOAD THE DATABASE OF USERS FROM THE FILE 
       AND GENERATE THE STARTING LINKED LIST.
    */
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    
    /* IMPORTANT: You must use the users linked list created in the code above. 
                  Any new users should be added to that linked list.
    */

    // Your solution goes here
    bool workingState = true;
    
    while (workingState == true) {
        print_menu();
        unsigned short int user_choice_main = get_input_usi();
        while (user_choice_main < 0 || user_choice_main > 6) {
            printf("Invalid choice. Please try again.\n");
            print_menu();
            user_choice_main = get_input_usi();
        }
        
        if (user_choice_main == 1) {//choice 1
            char username[30];
            char password[15];
            printf("\nEnter a username: ");
            scanf("%s", username );
            printf("Enter an upto 15 characters password: ");
            scanf("%s", password );

            users = add_user(users, username, password);


        } else if (user_choice_main == 2) { //choice 2
            char username_to_update_account[30];
            char new_password[15];
            printf("\nEnter username to update their password: ");
            scanf("%s", username_to_update_account);
            
            //this function call will return NULL if the user is not found (doesnt exist) or a pointer to the user's node if it does exist
            user_t *userToUpdate_node = find_user(users, username_to_update_account);

            if(userToUpdate_node == NULL) {//user not found in linked list
                printf("\n\n------------------------------------------\nUser not found.\n------------------------------------------\n");
            } else {//user is found in linked list
                printf("\nEnter a new password that is upto 15 characters: ");
                scanf("%s", new_password);
                strcpy(userToUpdate_node->password, new_password);
            }


        } else if (user_choice_main == 3) { //choice 3 in main menu
             char username_to_update_posts[30];
             printf("\nEnter username to manage their posts: ");
             scanf("%s", username_to_update_posts);

             user_t *userToUpdate_node = find_user(users, username_to_update_posts);

             if (userToUpdate_node == NULL) { //user not found in linked list
                 printf("\n\n------------------------------------------\nUser not found.\n------------------------------------------\n");

             } else { //user is found in linked list, must display their posts. 
                    display_user_posts(userToUpdate_node);
                    unsigned short int user_choice_post_menu = 50;

                    while (user_choice_post_menu != 3) {

                        printf("\n\n1. Add a new user post\n2. Remove a users post\n3. Return to main menu\n\nYour choice: ");
                        user_choice_post_menu = get_input_usi();

                        while (user_choice_post_menu < 1 || user_choice_post_menu > 3) {
                            printf("\nInvalid Choice, select again.\n\n1. Add a new user post\n2. Remove a users post\n3. Return to main menu\n\nYour choice: ");
                            user_choice_post_menu = get_input_usi();
                        }

                        if (user_choice_post_menu == 1) { //user decides to add a post

                            char post_content[250];
                            printf("\nEnter your post content: ");
                            scanf(" %[^\n]s", post_content);
                            add_post(userToUpdate_node, post_content);//add the post to the user's 'posts' linked list
                            printf("\nPost added to your profile.\n");
                            display_user_posts(userToUpdate_node);
                            

                        } else if (user_choice_post_menu == 2) {

                            int post_to_delete_num;
                            printf("Which post do you want to delete? ");
                            scanf("%d", &post_to_delete_num);
                            //before proceeding, must check that post number inputted by user is valid (ie that post exists)

                            if (post_to_delete_num < 1 || post_to_delete_num > num_of_posts(userToUpdate_node->posts)){
                                printf("\nInvalid post's number");
                                break;
                            }
                            
                            bool delete_status = delete_post(userToUpdate_node, post_to_delete_num);
                            if (delete_status == true) {
                                printf("\nPost %d was deleted successfully!\n", post_to_delete_num);
                            } else {
                                printf("Post %d failed to delete\n", post_to_delete_num);
                            }
                            display_user_posts(userToUpdate_node);
                            
                        } 

                        
                    }
                    



             }

        } else if (user_choice_main == 4) {//choice 4 in main menu
            char username_to_manage_friends[30];
            printf("\nEnter username to manage their friends: ");
            scanf("%s", username_to_manage_friends);

            user_t *userToUpdate_node = find_user(users, username_to_manage_friends);

             if (userToUpdate_node == NULL) { //user not found in linked list
                printf("\n\n------------------------------------------\nUser not found.\n------------------------------------------\n");

             } else {
                unsigned short int user_choice_friends_menu = 50;

                while (user_choice_friends_menu != 4) {
                    printf("\n\n1. Display all user's friends \n2. Add a new friend\n3. Delete a friend\n4. Return to main menu\n\nYour choice: ");
                    user_choice_friends_menu = get_input_usi();

                    while (user_choice_friends_menu < 1 || user_choice_friends_menu > 4) {
                        printf("\nInvalid Choice, select again.\n\n1. Display all user's friends\n2. Add a new friend\n3. Delete a friend\n4. Return to main menu\n\nYour choice: ");
                        user_choice_friends_menu = get_input_usi();
                    }

                    if (user_choice_friends_menu == 1) {//display users friends
                        display_user_friends(userToUpdate_node);

                    } else if (user_choice_friends_menu == 2) {//user wants to add friends
                        char new_friend_name[30];
                        printf("\nEnter a new friend's name: ");
                        scanf("%s", new_friend_name);
                        add_friend(userToUpdate_node, new_friend_name);
                        printf("Friend added to the list.");

                    } else if(user_choice_friends_menu == 3) {//user wants to delete friends

                        display_user_friends(userToUpdate_node);//display current list of friends
                        
                        //get hold of username of friend they want to delete
                        char friend_to_delete[30];
                        printf("\nEnter a friend's name to delete: ");
                        scanf("%s", friend_to_delete);

                        //check if friend name valid
                        if(check_friend_exist(userToUpdate_node, friend_to_delete)){

                            bool delete_status = delete_friend(userToUpdate_node, friend_to_delete);
                            if(delete_status == true) {
                                display_user_friends(userToUpdate_node);//display new list of friends
                            } else {
                                printf("\nFailed to remove friend.");
                            }

                        } else {//if friend name invalid,  friends menu displayed again 
                            printf("\nInvalid friend's name.");
                        }

                    
                }
             }

            

        }



    } else if (user_choice_main == 5) {
        display_all_posts(users);


    } else if (user_choice_main == 6) {
        printf("\n************************************************\n");
        printf("\tThank you for using Text-Based Facebook\n\t\tGoodbye!");
        printf("\n************************************************\n");
        teardown(users);
        exit(0);
    }
    

}
}