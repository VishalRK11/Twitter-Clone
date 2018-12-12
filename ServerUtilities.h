#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#include "DatabaseModule.h"

int findCount(FollowersInfo *tempNode){
	int count = 0;
	while (tempNode != NULL){
		count += 1;
		tempNode = tempNode->next;
	}
	return count;
}

int findTweetCount(TweetInfo *tempNode){
	int count = 0;
	while (tempNode != NULL){
		count += 1;
		tempNode = tempNode->next;
	}
	return count;
}

TweetInfo *clone(TweetInfo *clonedData){
	if (clonedData == NULL)
		return NULL;

	TweetInfo *newList = createTweetInfoNode();
	
	strcpy(newList->tweet, clonedData->tweet);
	newList->userID = clonedData->userID;
	newList->tweetID = clonedData->tweetID;
	newList->count = clonedData->count;
	newList->next = clone(clonedData->next);
	return newList;
}


void frontBackSplit(TweetInfo* source, TweetInfo** frontRef, TweetInfo** backRef){
	TweetInfo* fast = source->next;
	TweetInfo* slow = source;

	while (fast != NULL){
		fast = fast->next;
		if (fast != NULL){
			slow = slow->next;
			fast = fast->next;
		}
	}

	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}

TweetInfo* sortedMerge(TweetInfo* a, TweetInfo* b){
	TweetInfo* result = NULL;

	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;

	if (a->count > b->count){
		result = a;
		result->next = sortedMerge(a->next, b);
	}
	else{
		result = b;
		result->next = sortedMerge(a, b->next);
	}
	return result;
}

void mergeSort(TweetInfo **clonedDataHead){
	TweetInfo* head = *clonedDataHead, *a = NULL, *b = NULL;

	if ((head == NULL) || (head->next == NULL))
		return;

	frontBackSplit(head, &a, &b);

	mergeSort(&a);
	mergeSort(&b);

	*clonedDataHead = sortedMerge(a, b);
}

TweetInfo *sort(TweetInfo *head){
	mergeSort(&head);
	return head;
}

