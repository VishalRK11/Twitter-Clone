#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

typedef struct User{
	char *username;
	char *email;
	int userID;
	int followersCount;
	int followingCount;
	int tweetCount;
	User *next;
}User;

#include "ServerUtilities.h"

User *userHead = NULL;

void establishConnections(){
	readDataFromFiles();
}

int signUp(char *username, char *password, char *emailID){
	
	int ack = createUser(username, password, emailID);
	
	writeToUsers();

	return ack;
}

int login(char *username, char *password){
	
	int ack = selectUser(username, password);
	
	return ack;
}

User *createUserNode(){
	User *newNode = (User *)malloc(sizeof(User));
	newNode->email = (char *)malloc(sizeof(char)* STRING_SIZE);
	newNode->username = (char *)malloc(sizeof(char)* STRING_SIZE);
	newNode->next = NULL;

	return newNode;
}

User *getDisplayData(int userID){
	UserInfo *userDetails = getUserDetails(userID);
	TweetInfo *tweetDetails = getTweetDetails(userID);
	FollowersInfo *followersDetails = getFollowersDetails(userID);
	FollowersInfo *followingDetails = getFollowingDetails(userID);

	if (userDetails == NULL)
		return NULL;
	User *newNode = createUserNode();
	newNode->userID = userDetails->userID;
	strcpy(newNode->email, userDetails->emailID);
	strcpy(newNode->username, userDetails->username);

	newNode->followersCount = findCount(followersDetails);
	newNode->followingCount = findCount(followingDetails);
	newNode->tweetCount = findTweetCount(tweetDetails);

	if (userHead == NULL){
		userHead = newNode;
	}
	else{
		User *tempNode = userHead;
		while (tempNode->next != NULL){
			tempNode = tempNode->next;
		}
		tempNode->next = newNode;
	}
	return newNode;
}

TweetInfo *getMyTweets(int userID){
	return getTweetDetails(userID);
}

int favorites(TweetInfo *tweet, int tweetID, int userID){
	int ack = addFavorite(tweet, tweetID, userID);
	writeToFavorites();
	return ack;
}

int reTweet(TweetInfo *tweet, int tweetID, int userID, char *comment){
	int ack = addReTweet(tweet, tweetID, userID, comment);
	writeToComments();
	return ack;
}

User *getFavoriteUsers(int tweetID){
	FavoritesInfo *favorites = getFavoritesData();
	User *favoriteUsers = NULL;
	while (favorites != NULL){
		if (favorites->tweetID == tweetID){
			UserInfo *userDetails = getUserDetails(favorites->userID);
			User *newNode = createUserNode();
			newNode->userID = userDetails->userID;
			strcpy(newNode->email, userDetails->emailID);
			strcpy(newNode->username, userDetails->username);

			if (favoriteUsers == NULL){
				favoriteUsers = newNode;
			}
			else{
				User *tempNode = favoriteUsers;
				while (tempNode->next != NULL){
					tempNode = tempNode->next;
				}
				tempNode->next = newNode;
			}
		}
		favorites = favorites->next;
	}		
	return favoriteUsers;
}

User *getCommentUsers(int tweetID){
	CommentsInfo *comments = getCommentsData();
	User *commentUsers = NULL;
	while (comments != NULL){
		if (comments->tweetID == tweetID){
			UserInfo *userDetails = getUserDetails(comments->userID);
			User *newNode = createUserNode();
			newNode->userID = userDetails->userID;
			strcpy(newNode->email, userDetails->emailID);
			strcpy(newNode->username, userDetails->username);

			if (commentUsers == NULL){
				commentUsers = newNode;
			}
			else{
				User *tempNode = commentUsers;
				while (tempNode->next != NULL){
					tempNode = tempNode->next;
				}
				tempNode->next = newNode;
			}
		}
		comments = comments->next;
	}
	return commentUsers;
}

int editTweet(int tweetId, char *tweet){
	int ack = updateTweet(tweetId, tweet);
	writeToTweets();
	return ack;
}

int removeTweet(int tweetId){
	int ack = deleteTweet(tweetId);
	writeToTweets();
	return ack;
}

User *getMyFollowers(int userID){
	FollowersInfo *followers = getFollowersDetails(userID);
	UserInfo *followersData = getFollowersData(followers);

	User *head = NULL;

	while (followersData != NULL){

		User *newNode = createUserNode();
		newNode->userID = followersData->userID;
		strcpy(newNode->email, followersData->emailID);
		strcpy(newNode->username, followersData->username);

		if (head == NULL){
			head = newNode;
		}
		else{
			User *tempNode = head;
			while (tempNode->next != NULL){
				tempNode = tempNode->next;
			}
			tempNode->next = newNode;
		}

		followersData = followersData->next;
	}
	return head;
}

User *getMyFollowing(int userID){
	FollowersInfo *following = getFollowingDetails(userID);
	UserInfo *followingData = getFollowingData(following);
	
	User *head = NULL;
	
	while (followingData != NULL){
		User *newNode = createUserNode();
		newNode->userID = followingData->userID;
		strcpy(newNode->email, followingData->emailID);
		strcpy(newNode->username, followingData->username);

		if (head == NULL){
			head = newNode;
		}
		else{
			User *tempNode = head;
			while (tempNode->next != NULL){
				tempNode = tempNode->next;
			}
			tempNode->next = newNode;
		}

		followingData = followingData->next;
	}
	return head;
}

int postTweet(char *tweet, int userID){
	int ack = createTweet(tweet, userID);
	writeToTweets();
	return ack;
}

User *viewProfile(char *username){
	int userID = getUserID(username);
	return getDisplayData(userID);
}

int checkFollow(int userID, int followID){
	FollowersInfo *tempNode = followersInfoHead;
	while (tempNode != NULL){
		if (tempNode->userID == userID && tempNode->followersID == followID)
			return -1;
		tempNode = tempNode->next;
	}
	return 1;
}

int follow(int userID, int followID){
	int ack = createFollow(userID, followID);
	writeToFollowers();
	return ack;
}

TweetInfo *getTrendingTweets(){
	TweetInfo *allTweets = getAllTweets();
	return sort(clone(allTweets));
}

TweetInfo *getFeedTweets(int userID){
	FollowersInfo *following = getFollowingDetails(userID);
	TweetInfo *tempNode = tweetInfoHead, *feedTweets = NULL;
	while (tempNode != NULL && following != NULL){
		if (tempNode->userID == following->followersID || tempNode->userID == userID){
			TweetInfo *newNode = createTweetInfoNode();
			newNode->count = tempNode->count;
			newNode->tweetID = tempNode->tweetID;
			newNode->userID = tempNode->userID;
			strcpy(newNode->tweet, tempNode->tweet);

			newNode->next = feedTweets;
			feedTweets = newNode;
		}
		tempNode = tempNode->next;
	}
	if (following == NULL)
		return getTweetDetails(userID);

	return feedTweets;
}

int changeUsername(int userID, char *username){
	int ack = updateUsername(userID, username);
	writeToUsers();
	return ack;
}

int changePassword(int userID, char *password){
	int ack = updatePassword(userID, password);
	writeToUsers();
	return ack;
}

int logUserOut(int userID){
	return disableConnections(userID);
}

void updateData(){
	writeToUsers();
	writeToTweets();
	writeToComments();
	writeToFollowers();
	writeToFavorites();
}
