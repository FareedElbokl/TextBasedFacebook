/********* definitions.c ********
    Student Name 	= Fareed El Bokl
    Student Number	= 101256495
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "a2_nodes.h"
#include "a2_functions.h"
#include <assert.h>
#include <stdbool.h>

// Your solution goes here

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{
   user_t *new_node_user = malloc(sizeof(user_t));
   assert(new_node_user != NULL);

   strcpy(new_node_user->username, username);
   strcpy(new_node_user->password, password);
   new_node_user->next = NULL;

   //if users linked list is empty
   if(users == NULL) {
      users = new_node_user;
      return users;
   }

   //otherwise, must loop through users linked list to find position of where to add new user (ascending)
   user_t *temp = malloc(sizeof(user_t));
   assert(temp != NULL);
   temp = users;

   //if new user needs to be first in the linked list according to acending order
   if (strcmp(users->username, username) > 0) {
      new_node_user->next = users;
      users = new_node_user;
      return users;

   } else { //if new user should be somewhere in middle of linked list (or at end)

      while (temp->next != NULL) {
         if (strcmp(temp->next->username, username) > 0) {
            new_node_user->next = temp->next;
            temp->next = new_node_user;
            return users;
         }

         temp = temp->next;
      }
      
      temp->next = new_node_user;
      
   }

   
  return users;

}
/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username)
{  

   user_t *current = malloc(sizeof(user_t));
   assert(current != NULL);
   current = users;
   
   bool found = false;

   while (current != NULL) {
      if(strcmp(current->username, username) == 0) {
         found = true;
         return current;
      }
      current = current->next;
   }

   return NULL; //could also have said 'return current'
}
/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username)
{
    friend_t *new_node_friend = malloc(sizeof(friend_t));
    assert(new_node_friend != NULL);
    strcpy(new_node_friend->username, username);
    new_node_friend->next = NULL;
    
    return new_node_friend;
}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend)
{
    friend_t *new_node_friend = create_friend(friend);//this node->next points to NULL

    if (user->friends == NULL) {//user has no friends
         user->friends = new_node_friend;
         return;
    }

    friend_t *temp = malloc(sizeof(friend_t));
    assert(temp != NULL);
    temp = user->friends;

   //if new friend needs to be first in the linked list according to acending order
    if (strcmp(user->friends->username, friend) > 0) {

      new_node_friend->next = user->friends;
      user->friends = new_node_friend;

    } else {//new friend need to be added smwhere else in linked list

      while(temp->next != NULL) {
         if (strcmp(temp->next->username, friend) > 0) {
            new_node_friend->next = temp->next;
            temp->next = new_node_friend;
            return;
         }

         temp = temp->next;
      }

      temp->next = new_node_friend;

    }

    


}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
    //first must get hold of friend node
    friend_t *current = malloc(sizeof(friend_t));
    assert(current != NULL);
    current = user->friends;

    friend_t *prev = malloc(sizeof(friend_t));
    assert(prev != NULL);
    prev = NULL;

    //if first friend in linked list needs to be removed
    if (strcmp(user->friends->username, friend_name) == 0) {
      user->friends = user->friends->next;
      free(current);
      return true;
    } 
      
   while(current != NULL && strcmp(current->username, friend_name) != 0) {
         prev = current;
         current = current->next;
   }

   if (current != NULL) {
      prev->next = current->next;
      free(current);
      return true;
   }

   return false;

}



/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{
   post_t *new_post_node = malloc(sizeof(post_t));//create a new post node
   assert(new_post_node != NULL);
   strcpy(new_post_node->content, text); //set the new posts content to be what the user inputted
   new_post_node->next = NULL;
    
   return new_post_node;
}

/*
   Function that adds a post to a user's timeline. New posts should be added following
   the stack convention (LIFO) (i.e., to the beginning of the Posts linked list).
*/
void add_post(user_t *user, const char *text)
{
   
   post_t *new_post_node = create_post(text);
   //add the new post node to the beggining of the posts linked list
   new_post_node->next = user->posts;
   user->posts = new_post_node;

   


}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user, int number)
{
    
    post_t *current_post = malloc(sizeof(post_t));
    assert(current_post != NULL);
    post_t *prev_post = malloc(sizeof(post_t));
    assert(prev_post != NULL);

    current_post = user->posts;
    prev_post = NULL;
    int count = 1;

    while (current_post != NULL) {
      if (count == number) {
         if (prev_post == NULL) {//the post to be removed is post 1 (first in linked list)
            user->posts = current_post->next;
         } else {
            prev_post->next = current_post->next;
         }
         free(current_post);//free memory of post we want to delete
         return true;
      }

      prev_post = current_post;
      current_post = current_post->next;
      count++;

    }
    
    return false;
}

/*
   Function that  displays a specific user's posts
*/
void display_user_posts(user_t *user)
{
    printf("-------------------------------------------------\n\t\t%s posts\n", user->username);

    if (user->posts == NULL) {//this means the user has no posts

      printf("No posts available for %s.\n-------------------------------------------------\n", user->username);

    } else {//the user does have posts

      post_t *current = malloc(sizeof(post_t));
      assert(current != NULL);
      current = user->posts;
      int post_count = 1;
      while (current != NULL) {
         printf("%d- %s\n", post_count, current->content);//print the post
         current = current->next; //then increment the 'current' pointer to point to the next post
         post_count++;
      }
      printf("------------------------------------------");

    }


}

/*
   Function that displays a specific user's friends
*/
void display_user_friends(user_t *user)
{
    printf("\nList of %s's friends: \n", user->username);
    
    if (user->friends == NULL) { //user has no friends
      printf("\nNo friends available for %s.", user->username);
    } else {
         friend_t *current = malloc(sizeof(friend_t));
         assert(current != NULL);
         current = user->friends;
         int friend_count = 1;
         while (current != NULL) {
            printf("%d- %s\n", friend_count, current->username);//print the friends username
            current = current->next; //then increment the 'current' pointer to point to the next friend node
            friend_count++;
         }
    }

}
/*
   Function that displays all the posts of 2 users at a time from the database.
   After displaying 2 users' posts, it prompts if you want to display
   posts of the next 2 users.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_all_posts(user_t *users)
{
    
   user_t *current_user = malloc(sizeof(user_t));
   assert(current_user != NULL);
   current_user = users;
   int count = 0;

   while (current_user != NULL && current_user->next != NULL) {

         //1st user of the 2     
         post_t *current_post = malloc(sizeof(post_t));
         assert(current_post != NULL);
         current_post = current_user->posts;
         int post_count1 = 1;
         while (current_post != NULL) {
            printf("%d- %s: %s\n", post_count1, current_user->username, current_post->content);//print the post
            current_post = current_post->next; //then increment the 'current_post' pointer to point to the next post
            post_count1++;
         }

         //2nd user of the 2
         current_post = current_user->next->posts;
         int post_count2 = 1;
         while (current_post != NULL) {
            printf("%d- %s: %s\n", post_count2, current_user->next->username, current_post->content);//print the post
            current_post = current_post->next; //then increment the 'current_post' pointer to point to the next post
            post_count2++;
         }

         count += 2;

         char choice;
         if (current_user->next->next == NULL) {
            printf("\nAll posts have been displayed.\n");
            return;
         } else {
            printf("\n\nDo you want to display next 2 users posts? (Y/N): ");
            scanf(" %c", &choice);
            printf("\n\n");

            if(choice == 'n' || choice == 'N') {
               return;
            }
         }

         //move to next two users
         current_user = current_user->next->next;

   }

   
}

/*
   Fucntion that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{     
   //if users linked list is empty
    if (users == NULL) {
      return;
    }
   //free the user's posts and friiends from the database, then free the user
    user_t *current_user = malloc(sizeof(user_t));
    assert(current_user != NULL);
    current_user = users;

    user_t *next_user = malloc(sizeof(user_t));
    assert(next_user != NULL);
    next_user = NULL;

    while (current_user != NULL) {

      //free the user's posts
      post_t *current_post = malloc(sizeof(post_t));
      assert(current_post != NULL);
      current_post = current_user->posts;

      post_t *next_post = malloc(sizeof(post_t));
      assert(next_post != NULL);
      next_post = NULL;

      while (current_post != NULL) {
         next_post = current_post->next;
         free(current_post); 
         current_post = next_post;
      }

      //free the users friends
      friend_t *current_friend = malloc(sizeof(friend_t));
      assert(current_friend != NULL);
      current_friend = current_user->friends;

      friend_t *next_friend = malloc(sizeof(friend_t));
      assert(next_friend != NULL);
      next_friend = NULL;

      while(current_friend != NULL) {
         next_friend = current_friend->next;
         free(current_friend);
         current_friend = next_friend;
      }

      next_user = current_user->next;
      free(current_user);
      current_user = next_user;

    }

    
    


}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu()
{

   printf("\n************************************************\n");
   printf("                   MAIN MENU\n************************************************\n");
   printf("1. Register a new User\n2. Manage a user's profile (change password)\n3. Manage a user's posts (display/add/remove)\n4. Manage a user's friends (display/add/remove)\n5. Display All Posts\n6. Exit\n\nEnter your choice: ");
}

/*
   Get unsigned short integer user input. 
*/
unsigned short int get_input_usi(void) {
   unsigned short int input;
   scanf("%hu", &input);

   

   return input;
}

/* Parameter head points to the first node in the list.
   Return the length of a linked list (0 if the linked list is empty). 
 */
int num_of_posts(post_t *head)
{
    int count = 0;
    for (post_t * current = head; current != NULL; current = current->next) {
        count += 1;
    }
    return count;
}

/*
   check if friend exists in users linked list of friends, return true if so, false otherwise
*/
_Bool check_friend_exist(user_t *user, char *friend_name) {
   friend_t *current = malloc(sizeof(friend_t));
   assert(current != NULL);
   current = user->friends;

   while(current != NULL) {
      if (strcmp(current->username, friend_name) == 0) {
         return true;
      }

      current = current->next;
   }

   return false;

}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}
