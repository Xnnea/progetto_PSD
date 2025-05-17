#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "activity.h"

// Activity data structure definition
struct activity {
	int id;	// Unique identifier of the activity
	char* name;
	char* descr;
	char* course;
	time_t insertDate;
	time_t expiryDate;
	time_t completionDate;
	unsigned int totalTime;
	unsigned int usedTime;
	short unsigned int priority;
};

int compareWithId(Activity * a, int activityId) {
	if (!a) return -2;
	
	if (a->id == activityId) return 0;
	
	return (a->id < activityId) ? -1 : 1;
}

//Based on "id". Like strcmp (<0 if a < b, 0 is a == b, >0 if a > b)
int compare(Activity * a, Activity * b) {
	if (!a && !b) return 0;
	if (a && !b) return 1;
	if (b && !a) return -1;
	
	return compareWithId(a, b->id);
}


Activity * newEmptyActivity() {
	Activity* activity = (Activity*)malloc(sizeof(Activity));
	if (activity == NULL) {
   		return NULL;
	}
	 
	activity->id = 0; 
	activity->name = NULL;
	activity->descr = NULL;
	activity->course = NULL;
	activity->insertDate = 0;
	activity->expiryDate = 0;
	activity->completionDate = 0;
	activity->totalTime = 0;
	activity->usedTime = 0;
	activity->priority = 0;
}


Activity * newActivity( int id,
								char* name, 
								char* descr, 
								char* course, 
								time_t insertDate, 
								time_t expiryDate, 
								time_t completionDate, 
								unsigned int totalTime, 
								unsigned int usedTime, 
								short unsigned int priority ) {
	Activity* activity = newEmptyActivity();
	if (activity == NULL) {
   		return NULL;
	}
	 
	activity->id = id; 
	
	activity->name = copyString(name);
	activity->descr = copyString(descr);
	activity->course = copyString(course);
	
	activity->insertDate = insertDate;
	activity->expiryDate = expiryDate;
	activity->completionDate = completionDate;
	activity->totalTime = totalTime;
	activity->usedTime = usedTime;
	activity->priority = priority;
}


void deleteActivity(Activity * a) {
	if(!a) return;
	
	free(a->name);
	free(a->descr);
	free(a->course);
}


Activity * copyActivity(Activity * old) {
	if(!old) return NULL;
	
	Activity* activity = (Activity*)malloc(sizeof(Activity));
	if (activity == NULL) {
   		return NULL;
	}
	 
	activity->id = old->id; 

	activity->name = copyString(old->name);
	activity->descr = copyString(old->descr);
	activity->course = copyString(old->course);
	
	activity->insertDate = old->insertDate;
	activity->expiryDate = old->expiryDate;
	activity->completionDate = old->completionDate;
	activity->totalTime = old->totalTime;
	activity->usedTime = old->usedTime;
	activity->priority = old->priority;
	
	return activity;
}


int getActivityId(Activity * a) {
	if(!a) return 0;
	return a->id;
}

void setActivityId(Activity * a, int newId) {
	if(a) a->id = newId;
}


void print(Activity* activity) {
    if (activity == NULL) return;
    
    printf("Id: %d \n", activity->id);
    printf("Nome: %s\n", activity->name ? activity->name : "NULL");
    printf("Descrizione: %s\n", activity->descr ? activity->descr : "NULL");
    printf("Corso: %s\n", activity->course ? activity->course : "NULL");
    
    // Format dates in a human-readable way
    char timeBuffer[100];
    struct tm* tm_info;
    
    if (activity->insertDate != 0) {
        tm_info = localtime(&activity->insertDate);
        strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tm_info);
        printf("Data inserimento: %s\n", timeBuffer);
    } else {
        printf("Data inserimento: Non impostata\n");
    }
    
    if (activity->expiryDate != 0) {
        tm_info = localtime(&activity->expiryDate);
        strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tm_info);
        printf("Data scadenza: %s\n", timeBuffer);
    } else {
        printf("Data scadenza: Non impostata\n");
    }
    
    if (activity->completionDate != 0) {
        tm_info = localtime(&activity->completionDate);
        strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tm_info);
        printf("Data completamento: %s\n", timeBuffer);
    } else {
        printf("Data completamento: Non impostata\n");
    }
    
    printf("Tempo totale (min): %u\n", activity->totalTime);
    printf("Tempo usato (min): %u\n", activity->usedTime);
    printf("Priorità: %hu\n", activity->priority);
}



// Read an activity from file (file is supposed to be in read mode), line by line
Activity * readActivityFromFile(FILE* file) {
	int id = 0;
	char* name = NULL; 
	char* descr = NULL; 
	char* course = NULL; 
	time_t insertDate = 0; 
	time_t expiryDate = 0; 
	time_t completionDate = 0; 
	unsigned int totalTime = 0; 
	unsigned int usedTime = 0; 
	short unsigned int priority = 2;  
	
	//try to read 10 lines (an activity) from file
	char* lines[10];
	for(int i=0; i<10; i++) {
		lines[i] = readLine(file);
	}
	
	int someNull = 0;
	for(int i=0; i<10; i++) {
		if(lines[i] == NULL) {
			someNull = 1;
		}
	}
	
	//Less than 10 lines have been read
	if(someNull == 1) {
		for(int i=0; i<10; i++) {
			free(lines[i]);
		}
		
		return NULL;
	}
	
	//Ok, exactly 10 lines have been read

	//line for: id
	if (strlen(lines[0]) > 0) {
		sscanf(lines[0], "%d", &id);
	}
   free(lines[0]);

   //line for: name
	if (strlen(lines[1]) == 0) {
		free(lines[1]);
	} else {
		name = lines[1];
	}

	//line for: descr
	if (strlen(lines[2]) == 0) {
		free(lines[2]);
	} else {
		descr = lines[2];
	}
	
	//line for: course
	if (strlen(lines[3]) == 0) {
		free(lines[3]);
	} else {
		course = lines[3];
	}

	//line for: insertDate
	if (strlen(lines[4]) > 0) {
		sscanf(lines[4], "%ld", &insertDate);
	}
	free(lines[4]);

	//line for: expiryDate
	if (strlen(lines[5]) > 0) {
		sscanf(lines[5], "%ld", &expiryDate);
	}
	free(lines[5]);

	//line for: completionDate
	if (strlen(lines[6]) > 0) {
		sscanf(lines[6], "%ld", &completionDate);
	}
	free(lines[6]);

	//line for: totalTime
	if (strlen(lines[7]) > 0) {
		sscanf(lines[7], "%u", &totalTime);
	}
	free(lines[7]);

	//line for: usedTime
	if (strlen(lines[8]) > 0) {
		sscanf(lines[8], "%u", &usedTime);
	}
	free(lines[8]);

	//line for: priority
	if (strlen(lines[9]) > 0) {
		sscanf(lines[9], "%hu", &priority);
	}
	free(lines[9]);


	Activity* activity = newEmptyActivity();
	if (activity == NULL) {
   		return NULL;
	}
	 
	activity->id = id; 
	activity->name = name;
	activity->descr = descr;
	activity->course = course;
	activity->insertDate = insertDate;
	activity->expiryDate = expiryDate;
	activity->completionDate = completionDate;
	activity->totalTime = totalTime;
	activity->usedTime = usedTime;
	activity->priority = priority;
	
	return activity;
}


// Function to save activities to a file that is supposed to be already correctly opened for writing
// Returns 0 if everything is ok 1 if something went wrong
void saveActivityToFile(FILE* file, Activity * activity) {
	fprintf(file, "%d\n", activity->id);
	fprintf(file, "%s\n", activity->name ? activity->name : "");
	fprintf(file, "%s\n", activity->descr ? activity->descr : "");
	fprintf(file, "%s\n", activity->course ? activity->course : "");
	fprintf(file, "%ld\n", activity->insertDate);
	fprintf(file, "%ld\n", activity->expiryDate);
	fprintf(file, "%ld\n", activity->completionDate);
	fprintf(file, "%u\n", activity->totalTime);
	fprintf(file, "%u\n", activity->usedTime);
	fprintf(file, "%hu\n", activity->priority);
}
