#define MAX_SIZE 1024
#define STRING_SIZE 255
#define TWEET_SIZE 144

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#include "DataBaseUtilities.h"

typedef struct UserInfo{
	int userID;
	char *username;
	char *emailID;
	char *password;
	UserInfo *next;
}UserInfo;

UserInfo *userInfoHead = NULL;

typedef struct TweetInfo{
	int tweetID;
	int userID;
	int count;
	char *tweet;	
	TweetInfo *next;
}TweetInfo;

TweetInfo *tweetInfoHead = NULL;

typedef struct CommentsInfo{
	int commentID;
	int tweetID;
	int userID;
	char *comment;
	CommentsInfo *next;
}CommentsInfo;

CommentsInfo *commentInfoHead = NULL;

typedef struct FollowersInfo{
	int userID;
	int followersID;
	FollowersInfo *next;
}FollowersInfo;

FollowersInfo *followersInfoHead = NULL;

typedef struct FavoritesInfo{
	int tweetID;
	int userID;
	FavoritesInfo *next;
}FavoritesInfo;

FavoritesInfo *favoritesInfoHead = NULL;

UserInfo *createUserInfoNode(){
	UserInfo *node = (UserInfo *)malloc(sizeof(UserInfo));
	node->username = (char *)malloc(sizeof(char)* STRING_SIZE);
	node->password = (char *)malloc(sizeof(char)* STRING_SIZE);
	node->emailID = (char *)malloc(sizeof(char)* STRING_SIZE);
	node->next = NULL;
	
	return node;
}

TweetInfo *createTweetInfoNode(){
	TweetInfo *node = (TweetInfo *)malloc(sizeof(TweetInfo));
	node->tweet = (char *)malloc(sizeof(char)* TWEET_SIZE);
	node->count = 0;
	node->next = NULL;

	return node;
}

CommentsInfo *createCommentsInfoNode(){
	CommentsInfo *node = (CommentsInfo *)malloc(sizeof(CommentsInfo));
	node->comment = (char *)malloc(sizeof(char)* TWEET_SIZE);
	node->next = NULL;

	return node;
}

FollowersInfo *createFollowersInfoNode(){
	FollowersInfo *node = (FollowersInfo *)malloc(sizeof(FollowersInfo));
	node->next = NULL;

	return node;
}

FavoritesInfo *createFavoritesInfoNode(){
	FavoritesInfo *node = (FavoritesInfo *)malloc(sizeof(FavoritesInfo));
	node->next = NULL;

	return node;
}

UserInfo *readUserData(){
	FILE *fp = fopen("users.txt", "r");
	if (fp == NULL){
		printf("\nCannot Open File!");
		return NULL;
	}
	char *line = (char *)malloc(sizeof(char)* MAX_SIZE);

	while (fgets(line, MAX_SIZE, fp) != '\0'){
		UserInfo *userNode = createUserInfoNode();
		int id = 0, j = 0, i = 0;
		char *data = (char *)malloc(sizeof(char)* STRING_SIZE);
		while (isDigit(line[i])){
			id = (id * 10) + line[i] - '0';
			++i;
		}
		userNode->userID = id;
		if (line[i] == ','){
			++i;
		}
		for (j = 0; line[i] != ',' && line[i] != '\n' && line[i] != '\0'; ++j, ++i){
			data[j] = line[i];
		}
		data[j] = '\0';
		i++;
		strcpy(userNode->username, data);
	
		for (j = 0; line[i] != ',' && line[i] != '\n' && line[i] != '\0'; ++j, ++i){
			data[j] = line[i];
		}
		data[j] = '\0';
		i++;
		strcpy(userNode->password, data);

		for (j = 0; line[i] != ',' && line[i] != '\n' && line[i] != '\0'; ++j, ++i){
			data[j] = line[i];
		}
		data[j] = '\0';
		strcpy(userNode->emailID, data);

		if (userInfoHead == NULL){
			userInfoHead = userNode;
		}
		else{
			UserInfo *tempNode = userInfoHead;
			while (tempNode->next != NULL){
				tempNode = tempNode->next;
			}
			tempNode->next = userNode;
		}
	}
	return userInfoHead;
}

TweetInfo *readTweetsData(){
	FILE *fp = fopen("tweets.txt", "r");
	if (fp == NULL){
		printf("\nCannot Open File!");
		return NULL;
	}
	char *line = (char *)malloc(sizeof(char)* MAX_SIZE);
	
	while (fgets(line, MAX_SIZE, fp) != '\0'){
		TweetInfo *tweetNode = createTweetInfoNode();
		int id = 0, j = 0, i = 0;
		char *data = (char *)malloc(sizeof(char)* TWEET_SIZE);
		
		while (isDigit(line[i])){
			id = (id * 10) + line[i] - '0';
			i++;
		}
		i++;
		tweetNode->tweetID = id;
		
		id = 0;
		while (isDigit(line[i])){
			id = (id * 10) + line[i] - '0';
			i++;
		}
		i++;
		tweetNode->userID = id;
		
		id = 0;
		while (isDigit(line[i])){
			id = (id * 10) + line[i] - '0';
			i++;
		}
		i++;
		tweetNode->count = id;
		
		while (line[i] != '\n' && line[i] != '\0'){
			data[j++] = line[i++];
		}
		data[j] = '\0';
		strcpy(tweetNode->tweet, data);

		tweetNode->next = tweetInfoHead;
		tweetInfoHead = tweetNode;
	}
	return tweetInfoHead;
}

CommentsInfo *readCommentsData(){
	FILE *fp = fopen("comments.txt", "r");
	if (fp == NULL){
		printf("\nCannot Open File!");
		return NULL;
	}
	char *line = (char *)malloc(sizeof(char)* MAX_SIZE);
	
	while (fgets(line, MAX_SIZE, fp) != '\0'){
		CommentsInfo *commentsNode = createCommentsInfoNode();
		int id = 0, j = 0, i = 0;
		char *data = (char *)malloc(sizeof(char)* TWEET_SIZE);

		while (isDigit(line[i])){
			id = (id * 10) + line[i] - '0';
			i++;
		}
		i++;
		commentsNode->commentID = id;

		id = 0;
		while (isDigit(line[i])){
			id = (id * 10) + line[i] - '0';
			i++;
		}
		i++;
		commentsNode->tweetID = id;

		id = 0;
		while (isDigit(line[i])){
			id = (id * 10) + line[i] - '0';
			i++;
		}
		i++;
		commentsNode->userID = id;

		while (line[i] != '\n' && line[i] != '\0'){
			data[j++] = line[i++];
		}
		data[j] = '\0';
		strcpy(commentsNode->comment, data);

		commentsNode->next = commentInfoHead;
		commentInfoHead = commentsNode;
	}
	return commentInfoHead;
}

FollowersInfo *readFollowersData(){
	FILE *fp = fopen("followers.txt", "r");
	if (fp == NULL){
		printf("\nCannot Open File!");
		return NULL;
	}
	char *line = (char *)malloc(sizeof(char)* MAX_SIZE);
	
	while (fgets(line, MAX_SIZE, fp) != '\0'){
		FollowersInfo *followersNode = createFollowersInfoNode();
		int id = 0, j = 0, i = 0;
		char *data = (char *)malloc(sizeof(char)* TWEET_SIZE);

		while (isDigit(line[i])){
			id = (id * 10) + line[i] - '0';
			i++;
		}
		i++;
		followersNode->userID = id;

		id = 0;
		while (isDigit(line[i])){
			id = (id * 10) + line[i] - '0';
			i++;
		}
		i++;
		followersNode->followersID = id;

		followersNode->next = followersInfoHead;
		followersInfoHead = followersNode;
	}
	return followersInfoHead;
}

FavoritesInfo *readFavoritesData(){
	FILE *fp = fopen("favorites.txt", "r");
	if (fp == NULL){
		printf("\nCannot Open File!");
		return NULL;
	}
	char *line = (char *)malloc(sizeof(char)* MAX_SIZE);

	while (fgets(line, MAX_SIZE, fp) != '\0'){
		FavoritesInfo *favoritesNode = createFavoritesInfoNode();
		int id = 0, j = 0, i = 0;
		char *data = (char *)malloc(sizeof(char)* TWEET_SIZE);

		while (isDigit(line[i])){
			id = (id * 10) + line[i] - '0';
			i++;
		}
		i++;
		favoritesNode->tweetID = id;

		id = 0;
		while (isDigit(line[i])){
			id = (id * 10) + line[i] - '0';
			i++;
		}
		i++;
		favoritesNode->userID = id;

		favoritesNode->next = favoritesInfoHead;
		favoritesInfoHead = favoritesNode;
	}
	return favoritesInfoHead;
}

void readDataFromFiles(){
	userInfoHead = readUserData();
	tweetInfoHead = readTweetsData();
	commentInfoHead = readCommentsData();
	followersInfoHead = readFollowersData();
	favoritesInfoHead = readFavoritesData();
}

int createUser(char *username, char *password, char *emailID){
	UserInfo *newNode = createUserInfoNode(), *tempNode = userInfoHead;

	strcpy(newNode->username, username);
	strcpy(newNode->password, password);
	strcpy(newNode->emailID, emailID);

	if (userInfoHead == NULL){
		newNode->userID = 1;
		userInfoHead = newNode;
		return newNode->userID;
	}

	while (tempNode->next != NULL){
		if (strcmp(username, tempNode->username) == 0)
			return -1;
		tempNode = tempNode->next;
	}
	newNode->userID = tempNode->userID + 1;
	tempNode->next = newNode;

	return newNode->userID;
}

int selectUser(char *username, char *password){
	UserInfo *tempNode = userInfoHead;
	while (tempNode != NULL){
		if (strcmp(username, tempNode->username) == 0 && strcmp(password, tempNode->password) == 0)
			return tempNode->userID;
		tempNode = tempNode->next;
	}
	return -1;
}

UserInfo *getUserDetails(int userID){
	UserInfo *tempNode = userInfoHead;
	while (tempNode != NULL){
		if (tempNode->userID == userID){
			UserInfo *returnNode = createUserInfoNode();
			returnNode->userID = tempNode->userID;
			strcpy(returnNode->username, tempNode->username);
			strcpy(returnNode->password, tempNode->password);
			strcpy(returnNode->emailID, tempNode->emailID);
			return returnNode;
		}
		tempNode = tempNode->next;
	}
	return NULL;
}

TweetInfo *getTweetDetails(int userID){
	TweetInfo *tempNode = tweetInfoHead, *returnNodes = NULL;
	while (tempNode != NULL){
		if (tempNode->userID == userID){
			TweetInfo *currentNode = createTweetInfoNode();
			currentNode->count = tempNode->count;
			currentNode->tweetID = tempNode->tweetID;
			currentNode->userID = tempNode->userID;
			strcpy(currentNode->tweet, tempNode->tweet);
			
			currentNode->next = returnNodes;
			returnNodes = currentNode;
		}
		tempNode = tempNode->next;
	}
	return returnNodes;
}

FavoritesInfo *getFavoritesData(){
	return favoritesInfoHead;
}

CommentsInfo *getCommentsData(){
	return commentInfoHead;
}

FollowersInfo *getFollowersDetails(int userID){
	FollowersInfo *tempNode = followersInfoHead, *returnNode = NULL;
	while (tempNode != NULL){
		if (tempNode->followersID == userID){
			FollowersInfo *newNode = createFollowersInfoNode();
			newNode->userID = tempNode->userID;
			newNode->followersID = tempNode->followersID;

			newNode->next = returnNode;
			returnNode = newNode;
		}
		tempNode = tempNode->next;
	}
	return returnNode;
}

FollowersInfo *getFollowingDetails(int userID){
	FollowersInfo *tempNode = followersInfoHead, *returnNode = NULL;
	while (tempNode != NULL){
		if (tempNode->userID == userID){
			FollowersInfo *newNode = createFollowersInfoNode();
			newNode->userID = tempNode->userID;
			newNode->followersID = tempNode->followersID;

			newNode->next = returnNode;
			returnNode = newNode;
		}
		tempNode = tempNode->next;
	}
	return returnNode;
}

int addFavorite(TweetInfo *tweet, int tweetID, int userID){
	FavoritesInfo *newNode = createFavoritesInfoNode();
	newNode->tweetID = tweetID;
	newNode->userID = userID;
	tweet->count += 1;
	newNode->next = favoritesInfoHead;
	favoritesInfoHead = newNode;

	TweetInfo *tempNode = tweetInfoHead;
	while (tempNode != NULL){
		if (tempNode->tweetID == tweetID){
			tempNode->count += 1;
		}
		tempNode = tempNode->next;
	}
	return 1;
}

int addReTweet(TweetInfo *tweet, int tweetID, int userID, char *comment){
	CommentsInfo *newNode = createCommentsInfoNode();
	newNode->userID = userID;
	newNode->tweetID = tweetID;
	tweet->count += 1;

	if (commentInfoHead == NULL)
		newNode->commentID = 1;
	else
		newNode->commentID = commentInfoHead->commentID + 1;
	strcpy(newNode->comment, comment);

	newNode->next = commentInfoHead;
	commentInfoHead = newNode;

	return 1;
}

int updateTweet(int tweetID, char *tweet){
	TweetInfo *tempNode = tweetInfoHead;
	while (tempNode != NULL){
		if (tempNode->tweetID == tweetID){
			strcpy(tempNode->tweet, tweet);
			return 1;
		}
		tempNode = tempNode->next;
	}
	return 1;
}

int deleteTweet(int tweetID){
	
	if (tweetInfoHead->next == NULL)
		tweetInfoHead = NULL;
	
	TweetInfo *tempNode = tweetInfoHead, *prevNode = NULL;
	while (tempNode != NULL){
		if (tempNode->tweetID == tweetID){
			prevNode->next = tempNode->next;
			free(tempNode);
			break;
		}
		prevNode = tempNode;
		tempNode = tempNode->next;
	}

	if (commentInfoHead->next == NULL)
		commentInfoHead = NULL;

	CommentsInfo *tempCommentsNode = commentInfoHead, *prevCommentsNode = NULL;
	while (tempCommentsNode != NULL){
		if (tempCommentsNode->tweetID == tweetID){
			prevCommentsNode->next = tempCommentsNode->next;
			free(tempCommentsNode);
			break;
		}
		prevCommentsNode = tempCommentsNode;
		tempCommentsNode = tempCommentsNode->next;
	}

	if (favoritesInfoHead->next == NULL)
		favoritesInfoHead = NULL;
	
	FavoritesInfo *tempFavoritesNode = favoritesInfoHead, *prevFavoritesNode = NULL;
	while (tempFavoritesNode != NULL){
		if (tempFavoritesNode->tweetID == tweetID){
			prevFavoritesNode->next = tempFavoritesNode->next;
			free(tempFavoritesNode);
			break;
		}
		prevFavoritesNode = tempFavoritesNode;
		tempFavoritesNode = tempFavoritesNode->next;
	}
	return 1;
}

UserInfo *getFollowersData(FollowersInfo *data){
	UserInfo *tempNode = userInfoHead, *returnNode = NULL;
	while (tempNode != NULL && data != NULL){
		if (tempNode->userID == data->userID){
			UserInfo *newNode = createUserInfoNode();
			newNode->userID = tempNode->userID;
			strcpy(newNode->username, tempNode->username);
			strcpy(newNode->password, tempNode->password);
			strcpy(newNode->emailID, tempNode->emailID);
			
			newNode->next = returnNode;
			returnNode = newNode;
		}
		tempNode = tempNode->next;
	}
	return returnNode;
}

UserInfo *getFollowingData(FollowersInfo *data){
	UserInfo *tempNode = userInfoHead, *returnNode = NULL;
	while (tempNode != NULL && data != NULL){
		if (tempNode->userID == data->followersID){
			UserInfo *newNode = createUserInfoNode();
			newNode->userID = tempNode->userID;
			strcpy(newNode->username, tempNode->username);
			strcpy(newNode->password, tempNode->password);
			strcpy(newNode->emailID, tempNode->emailID);

			newNode->next = returnNode;
			returnNode = newNode;
		}
		tempNode = tempNode->next;
	}
	return returnNode;
}

int createTweet(char *tweet, int userID){
	
	TweetInfo *currentNode = createTweetInfoNode();
	if (tweetInfoHead == NULL)
		currentNode->tweetID = 1;
	else
		currentNode->tweetID = tweetInfoHead->tweetID + 1;
	currentNode->userID = userID;
	strcpy(currentNode->tweet, tweet);

	currentNode->next = tweetInfoHead;
	tweetInfoHead = currentNode;

	return 1;
}

int getUserID(char *username){
	UserInfo *tempNode = userInfoHead;
	while (tempNode != NULL){
		if (strcmp(username, tempNode->username) == 0)
			return tempNode->userID;
		tempNode = tempNode->next;
	}
	return -1;
}

int createFollow(int userID, int followerID){
	FollowersInfo *newNode = createFollowersInfoNode();
	newNode->userID = userID;
	newNode->followersID = followerID;

	newNode->next = followersInfoHead;
	followersInfoHead = newNode;

	return 1;
}

TweetInfo *getAllTweets(){
	return tweetInfoHead;
}

int checkUsername(char *username){
	UserInfo *tempNode = userInfoHead;
	while (tempNode != NULL){
		if (strcmp(tempNode->username, username) == 0)
			return -1;
		tempNode = tempNode->next;
	}
	return 1;
}

int updateUsername(int userID, char *username){
	UserInfo *tempNode = userInfoHead;
	while (tempNode != NULL){
		if (tempNode->userID == userID){
			int check = checkUsername(username);
			if (check != -1){
				strcpy(tempNode->username, username);
				return userID;
			}
			else{
				return INT_MIN;
			}
		}
		tempNode = tempNode->next;
	}
	return -1;
}

int updatePassword(int userID, char *password){
	UserInfo *tempNode = userInfoHead;
	while (tempNode != NULL){
		if (tempNode->userID == userID){
			strcpy(tempNode->password, password);
			return tempNode->userID;
		}
		tempNode = tempNode->next;
	}
	return -1;
}

int disableConnections(int userID){
	return -1;
}

void writeToUsers(){
	UserInfo *user = userInfoHead;

	FILE *fp = fopen("users.txt", "w");

	while (user != NULL){
		fprintf(fp, "%d,%s,%s,%s\n", user->userID, user->username, user->password, user->emailID);
		user = user->next;
	}

	fclose(fp);
}

void writeToTweets(){
	TweetInfo *tweets = tweetInfoHead;

	FILE *fp = fopen("tweets.txt", "w");

	while (tweets != NULL){
		fprintf(fp, "%d,%d,%d,%s\n", tweets->tweetID, tweets->userID, tweets->count, tweets->tweet);
		tweets = tweets->next;
	}

	fclose(fp);
}

void writeToComments(){
	CommentsInfo *comments = commentInfoHead;

	FILE *fp = fopen("comments.txt", "w");

	while (comments != NULL){
		fprintf(fp, "%d,%d,%d,%s\n", comments->commentID, comments->tweetID, comments->userID, comments->comment);
		comments = comments->next;
	}

	fclose(fp);
}

void writeToFollowers(){

	FollowersInfo *followers = followersInfoHead;

	FILE *fp = fopen("followers.txt", "w");

	while (followers != NULL){
		fprintf(fp, "%d,%d\n", followers->userID, followers->followersID);
		followers = followers->next;
	}

	fclose(fp);

}

void writeToFavorites(){

	FavoritesInfo *favorites = favoritesInfoHead;

	FILE *fp = fopen("favorites.txt", "w");

	while (favorites != NULL){
		fprintf(fp, "%d,%d\n", favorites->userID, favorites->tweetID);
		favorites = favorites->next;
	}

	fclose(fp);
}

