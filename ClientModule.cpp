#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 255
#define TWEET_SIZE 144

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#include "ServerModule.h"

int getAuthentication(){
	int userID, choice, flag = 1;
	
	while (flag){
		printf("\n1. Sign Up");
		printf("\n2. Login");
		printf("\n3. Exit");

		printf("\n\nEnter your choice: ");
		scanf("%d", &choice);

		char *username = (char *)malloc(sizeof(char)* STRING_SIZE);
		char *password = (char *)malloc(sizeof(char)* STRING_SIZE);
		char *emailID = (char *)malloc(sizeof(char)* STRING_SIZE);

		switch (choice)
		{
		case 1: while (flag){
					printf("\nEnter your username: ");
					fflush(stdin);
					gets(username);
					printf("\nEnter your password: ");
					fflush(stdin);
					gets(password);
					printf("\nEnter your emailID: ");
					fflush(stdin);
					gets(emailID);
					userID = signUp(username, password, emailID);
					if (userID != -1)
						flag = 0;
					else
						printf("\n\nUsername already taken! Please, Try again!");
		}
				break;

		case 2: while (flag){
					printf("\nEnter your username: ");
					fflush(stdin);
					gets(username);
					printf("\nEnter your password: ");
					fflush(stdin);
					gets(password);
					userID = login(username, password);
					if (userID != -1)
						flag = 0;
					else
						printf("\n\nInvalid Credentials entered! Please Try again!");
				}
				break;

		case 3: system("pause");
			exit(1);
		default: printf("\nInvalid option entered!");
		}
	}
	return userID;
}

void displayData(User *user){
	printf("\nUsername:  %-15s", user->username);
	printf("\nEmail id:  %-15s", user->email);
	printf("\nTweets:    %d", user->tweetCount);
	printf("\nFollowers: %d", user->followersCount);
	printf("\nFollowing: %d\n\n", user->followingCount);
}

void printFavorites(int tweetID){
	User *user = getFavoriteUsers(tweetID);
	int flag = 1;
	printf("\n\n");
	while (user != NULL){
		flag = 0;
		printf("%s favorited this tweet.\n\n", user->username);
		user = user->next;
	}
	if (flag)
		printf("\n\nNo Favorites\n\n");
}

void printCommentOptions(int tweetID){
	User *user = getCommentUsers(tweetID);
	int flag = 1;
	while (user != NULL){
		flag = 0;
		printf("\n\n%s retweeted on this tweet.\n\n", user->username);
		user = user->next;
	}
	if (flag)
		printf("\n\nNo retweets\n\n");
}

void printTweets(TweetInfo *tweets, int userID){
	char *tweet = (char *)malloc(sizeof(char)* TWEET_SIZE);
	int innerChoice;

	while (tweets != NULL){
		puts(tweets->tweet);
		printf("\nSeen by %d people.\n", tweets->count);
		printf("\n1. Favorite");
		printf("\n2. Re-Tweet");
		printf("\n3. Show Next Tweet");
		printf("\n4. Show Favorites");
		printf("\n5. Show Retweets");
		if (tweets->userID == userID){
			printf("\n6. Edit");
			printf("\n7. Delete");
		}
		printf("\nGo Back");
		printf("\n\nEnter your choice: ");
		scanf("%d", &innerChoice);

		switch (innerChoice){
		case 1: favorites(tweets, tweets->tweetID, userID);
			break;
		case 2: printf("\nTweet your ReTweet: ");
			fflush(stdin);
			gets(tweet);
			reTweet(tweets, tweets->tweetID, userID, tweet);
			break;
		case 3:	tweets = tweets->next;
			break;
		case 4: printFavorites(tweets->tweetID);
			break;
		case 5: printCommentOptions(tweets->tweetID);
			break;
		case 6:	if (tweets->userID == userID){
					printf("\nTweet your ReTweet: ");
					fflush(stdin);
					gets(tweet);
					editTweet(tweets->tweetID, tweet);
				}
				else
					return;
		case 7:	if (tweets->userID == userID){
						removeTweet(tweets->tweetID);
				}
				else
					return;
		default: return;
		}
	}
	printf("\nAll tweets shown");
}

void askFollow(int userID, User *user){
	char ch;
	int isFollowing = checkFollow(userID, user->userID);
	if (isFollowing == 1){
		printf("\nDo you want to follow?[Y/N]");
		fflush(stdin);
		scanf("%c", &ch);
		if (ch == 'y' || ch == 'Y'){
			follow(userID, user->userID);
		}
	}
}

void printMyFollowers(int userID){
	User *user = getMyFollowers(userID);
	int flag = 1;
	printf("-------------\n");
	printf("Followers\n");
	printf("-------------\n");
	while (user != NULL){
		printf("%-15s", user->username);
		flag = 0;
		askFollow(userID, user);
		user = user->next;
	}
	printf("\n\nYou don't have any followers.\n\n");
}

void printMyFollowing(int userID){
	User *user = getMyFollowing(userID);
	int flag = 1;
	printf("------------\n");
	printf("Following\n");
	printf("------------\n");
	while (user != NULL){
		flag = 0;
		printf("%-15s", user->username);
		user = user->next;
	}
	if (flag)
		printf("\n\nYou are not following anyone.\n\n");
}

void postATweet(int userID){
	char *tweet = (char *)malloc(sizeof(char)* TWEET_SIZE);

	printf("\nEnter tweet: ");
	fflush(stdin);
	gets(tweet);
	postTweet(tweet, userID);
}

void displayProfile(int userID){
	char *userName = (char *)malloc(sizeof(char)* STRING_SIZE);
	printf("\nEnter username: ");
	fflush(stdin);
	gets(userName);
	User *user = viewProfile(userName);
	displayData(user);
	askFollow(userID, user);
}

void printTrendingTweets(int userID){
	TweetInfo *allTweets = getTrendingTweets();
	printTweets(allTweets, userID);
}

void printFeed(int userID){
	TweetInfo *feedTweets = getFeedTweets(userID);
	printTweets(feedTweets, userID);
}

void showSettings(int userID){
	char *username = (char *)malloc(sizeof(char)* STRING_SIZE);
	char *password = (char *)malloc(sizeof(char)* STRING_SIZE);

	int choice, flag = 1;
	while (flag){
		printf("\n1. Change Username");
		printf("\n2. Change Password");
		printf("\nGo Back");
		printf("\n\nEnter your choice: ");
		scanf("%d", &choice);
		int ack;
		switch (choice){
		case 1: printf("\nEnter new username: ");
				fflush(stdin);
				gets(username);
				ack = changeUsername(userID, username);
				if (ack != -1)
					flag = 0;
				else if (ack = INT_MIN)
					printf("\n\nUsername already taken! Please, Try again!");
				else
					printf("\nUnable to change Username. Please try again later!");
				break;
		case 2: printf("\nEnter new username: ");
				fflush(stdin);
				gets(password);
				ack = changePassword(userID, password);
				if (ack != -1)
					flag = 0;
				else
					printf("\nUnable to change Username. Please try again later!");
				break;
		default: return;
		}
	}
}

void logout(int userID){
	userID = logUserOut(userID);
	updateData();
}

void displayOptions(int userID){
	int choice, flag = 1;
	while (flag){
		printf("\n1. View My Profile");
		printf("\n2. View My Tweets");
		printf("\n3. View My Followers");
		printf("\n4. View My Following");
		printf("\n5. Post Tweet");
		printf("\n6. View Profile");
		printf("\n7. Trending Tweets");
		printf("\n8. Show feed");
		printf("\n9. Settings");
		printf("\n10. Logout");

		printf("\n\nEnter your choice: ");
		scanf("%d", &choice);

		User *user;
		TweetInfo *tweets;

		switch (choice){
		case 1: user = getDisplayData(userID);
				displayData(user);
				break;
		case 2:	tweets = getMyTweets(userID);
				printTweets(tweets, userID);
				break;
		case 3: printMyFollowers(userID);
				break;
		case 4: printMyFollowing(userID);
				break;
		case 5: postATweet(userID);
				break;
		case 6: displayProfile(userID);
				break;
		case 7: printTrendingTweets(userID);
				break;
		case 8: printFeed(userID);
				break;
		case 9: showSettings(userID);
				break;
		case 10: logout(userID);
				flag = 0;
				break;
		default: printf("\nInvalid option entered!");
		}
	}
}

int main(){
	
	establishConnections();
	
	while (1){
		int userID = getAuthentication();
		displayOptions(userID);
	}

	system("pause");
	return 0;
}