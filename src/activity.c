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
	unsigned int totalTime; //minutes
	unsigned int usedTime;  //minutes
	short unsigned int priority;
};

int compareWithId(Activity a, int activityId) {
	if (!a) return -2;
	
	if (a->id == activityId) return 0;
	
	return (a->id < activityId) ? -1 : 1;
}

// Used "int" consciously
int activityCompletionPercentage(Activity activity) {
	if (activity == NULL) return 0;
	
	int completionPercentage = (activity->usedTime * 100) / activity->totalTime;
	return completionPercentage;
}


int compareNullActivity(const Activity a, const Activity b) {
	if (!a && !b) return 0;
	if (a && !b) return 1;
	if (b && !a) return -1;
	
	return 0;
}

int compareNullString(const char* a, const char*  b) {
	if (!a && !b) return 0;
	if (a && !b) return 1;
	if (b && !a) return -1;
	
	return 0;
}

int compareAcivityById(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	return compareWithId(a, b->id);
}

int compareAcivityByName(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	if (a->name == NULL || b->name == NULL) {
		return compareNullString(a->name, b->name);
	}
	
	return strcmp(a->name, b->name);
}

int compareAcivityByDescr(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	if (a->descr == NULL || b->descr == NULL) {
		return compareNullString(a->descr, b->descr);
	}
	
	return strcmp(a->descr, b->descr);
}

int compareAcivityByCourse(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	if (a->course == NULL || b->course == NULL) {
		return compareNullString(a->course, b->course);
	}
	
	return strcmp(a->course, b->course);
}

int compareAcivityByInsertDate(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	if (a->insertDate == b->insertDate) return 0;
	
	return (a->insertDate < b->insertDate) ? -1 : 1;
}

int compareAcivityByExpiryDate(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	if (a->expiryDate == b->expiryDate) return 0;
	
	return (a->expiryDate < b->expiryDate) ? -1 : 1;
}

int compareAcivityByCompletionDate(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	if (a->completionDate == b->completionDate) return 0;
	
	return (a->completionDate < b->completionDate) ? -1 : 1;
}

int compareAcivityByTotalTime(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	if (a->totalTime == b->totalTime) return 0;
	
	return (a->totalTime < b->totalTime) ? -1 : 1;
}

int compareAcivityByUsedTime(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	if (a->usedTime == b->usedTime) return 0;
	
	return (a->usedTime < b->usedTime) ? -1 : 1;
}

int compareAcivityByPriority(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	if (a->priority == b->priority) return 0;
	
	return (a->priority < b->priority) ? -1 : 1;
}

int compareAcivityByPercentCompletion(Activity a, Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	int aPercent = activityCompletionPercentage(a);
	int bPercent = activityCompletionPercentage(b);
	
	if (aPercent == bPercent) return 0;
	
	return (aPercent < bPercent) ? -1 : 1;
}

int compareAcivityByTimeToCompletion(Activity a, Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	unsigned int aTimeToCompletion = 0;
	unsigned int bTimeToCompletion = 0;
	
	if (a->totalTime >= a->usedTime) {
		aTimeToCompletion = a->totalTime - a->usedTime;
	}
	
	if (b->totalTime >= b->usedTime) {
		bTimeToCompletion = b->totalTime - b->usedTime;
	}
	
	if (aTimeToCompletion == bTimeToCompletion) return 0;
	
	return (aTimeToCompletion < bTimeToCompletion) ? -1 : 1;
}









// 1 = activity is yet to begin, 0 = is completed or ongoing
int isActivityYetToBegin(Activity a) {
	if (a == NULL) return 0;
	
	return (a->usedTime == 0) ? 1 : 0;
}

// 1 = activity is completed, 0 = is NOT completed
int isActivityCompleted(Activity a) {
	if (a == NULL) return 0;
	
	return (a->completionDate != 0) ? 1 : 0;
}

// 1 = activity was completed after the threshold date, 0 = otherwise
int wasActivityCompletedAfterDate(Activity a, time_t thresholdDate) {
	if (a == NULL) return 0;
	
	return (a->completionDate > thresholdDate) ? 1 : 0;
}

// 0 = activity was expired before the threshold date, 1 = otherwise
int wasActivityExpiredBeforeDate(Activity a, time_t thresholdDate) {
	if (a == NULL) return 0;
	
	//expiryDate = 0 mean no expiry date
	return (a->expiryDate > 0 && a->expiryDate < thresholdDate) ? 1 : 0;
}



Activity newEmptyActivity() {
	Activity activity = (Activity)malloc(sizeof(struct activity));
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


Activity newActivity( int id,
								char* name, 
								char* descr, 
								char* course, 
								time_t insertDate, 
								time_t expiryDate, 
								time_t completionDate, 
								unsigned int totalTime, 
								unsigned int usedTime, 
								short unsigned int priority ) {
	Activity activity = newEmptyActivity();
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


void deleteActivity(Activity a) {
	if(!a) return;
	
	free(a->name);
	free(a->descr);
	free(a->course);
}


Activity copyActivity(Activity old) {
	if(!old) return NULL;
	
	Activity activity = (Activity)malloc(sizeof(struct activity));
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


char * textForActivityPriority(int priority) {
	switch(priority) {
		case 1: return "ALTA";
		case 2: return "MEDIA";
		case 3: return "BASSA";
		default: break;
	}
	
	return "?";
}


int getActivityId(Activity a) {
	if(!a) return 0;
	return a->id;
}

void setActivityId(Activity a, int newId) {
	if(a) a->id = newId;
}









char* getActivityName(Activity a) {
	if (a == NULL) return NULL;
	
	return a->name;
}

char* getActivityDescr(Activity a) {
	if (a == NULL) return NULL;
	
	return a->descr;
}

char* getActivityCourse(Activity a) {
	if (a == NULL) return NULL;
	
	return a->course;
}

time_t getActivityInsertDate(Activity a) {
	if (a == NULL) return 0;
	
	return a->insertDate;
}

time_t getActivityExpiryDate(Activity a) {
	if (a == NULL) return 0;
	
	return a->expiryDate;
}

time_t getActivityCompletionDate(Activity a) {
	if (a == NULL) return 0;
	
	return a->completionDate;
}

unsigned int getActivityTotalTime(Activity a) {
	if (a == NULL) return 0;
	
	return a->totalTime;
}

unsigned int getActivityUsedTime(Activity a) {
	if (a == NULL) return 0;
	
	return a->usedTime;
}

short unsigned int getActivityPriority(Activity a) {
	if (a == NULL) return 0;
	
	return a->priority;
}

char*  getActivityPriorityFormatted(Activity a) {
	if (a == NULL) return NULL;
	
	return textForActivityPriority(a->priority);
}





void setActivityName(Activity a, char* name) {
	if (a == NULL) return;
	
	if (a->name != NULL) {
		free(a->name);
	}
	
	a->name = copyString(name);
}

void setActivityDescr(Activity a, char* descr) {
	if (a == NULL) return;
	
	if (a->descr != NULL) {
		free(a->descr);
	}
	
	a->descr = copyString(descr);
}

void setActivityCourse(Activity a, char* course) {
	if (a == NULL) return;
	
	if (a->course != NULL) {
		free(a->course);
	}
	
	a->course = copyString(course);
}

void setActivityInsertDate(Activity a, time_t insertDate) {
	if (a == NULL) return;
	
	a->insertDate = insertDate;
}

void setActivityExpiryDate(Activity a, time_t expiryDate) {
	if (a == NULL) return;
	
	a->expiryDate = expiryDate;
}

void setActivityCompletionDate(Activity a, time_t completionDate) {
	if (a == NULL) return;
	
	a->completionDate = completionDate;
}




void setActivityTotalTime(Activity a, unsigned int totalTime) {
	if (a == NULL) return;
	
	a->totalTime = totalTime;
}

void setActivityUsedTime(Activity a, unsigned int usedTime) {
	if (a == NULL) return;
	
	a->usedTime = usedTime;
}

void setActivityPriority(Activity a, short unsigned int priority) {
	if (a == NULL) return;
	
	a->priority = priority;
}












void displayAcivityDetailMenu() {
	printf("===================================\n");
	printf("====[ Menu dettaglio attività ]====\n");
	printf("===================================\n");
	printf("1. Aggiorna nome\n");
	printf("2. Aggiorna descrizione\n");
	printf("3. Aggiorna corso\n");
	printf("4. Cambia data di scadenza\n");
	printf("5. Cambia la durata totale\n");
	printf("6. Aggiorna il tempo impiegato sull'attività\n");
	printf("7. Cambia la priorità\n");
	printf("8. Imposta come COMPLETATA\n");
	printf("0. Torna al menu precedente\n");
	printf("Scelta: ");
}

Activity handleAcivityDetailMenu(Activity activity) {
	displayAcivityDetailMenu();
	int choice = getChoice(8);
	
	Activity returnActivity = activity;
	
	char* tmpString = NULL;
	printf("\n");
	
	switch (choice) {
		case 0: { //0. Torna al menu precedente
			printf("Torno al menu precedente...\n");
			returnActivity = NULL;
			break;
		}

		case 1: { //1. Aggiorna nome
			printf("[Aggiorna nome]\n");
			tmpString = getActivityName(activity);
			printf("Nome (valore attuale): %s\n", tmpString ? tmpString : "NULL" );
			tmpString = getInfoFromUser("Inserisci in nuovo valore (lascia vuoto per non cambiarlo): ");
			if (tmpString != NULL) {
				setActivityName(activity, tmpString);
				free(tmpString);
			}
			break;
		}		
		
		case 2: { //2. Aggiorna descrizione
			printf("[Aggiorna descrizione]\n");
			tmpString = getActivityDescr(activity);
			printf("Descrizione (valore attuale): %s\n", tmpString ? tmpString : "NULL" );
			tmpString = getInfoFromUser("Inserisci in nuovo valore (lascia vuoto per non cambiarlo): ");
			if (tmpString != NULL) {
				setActivityDescr(activity, tmpString);
				free(tmpString);
			}
			break;
		}
		
		case 3: { //3. Aggiorna corso
			printf("[Aggiorna corso]\n");
			tmpString = getActivityCourse(activity);
			printf("Corso (valore attuale): %s\n", tmpString ? tmpString : "NULL" );
			tmpString = getInfoFromUser("Inserisci in nuovo valore (lascia vuoto per non cambiarlo): ");
			if (tmpString != NULL) {
				setActivityCourse(activity, tmpString);
				free(tmpString);
			}
			break;
		}
		
		case 4: { //4. Cambia data di scadenza
			printf("[Cambia data di scadenza]\n");
			time_t expDate = getActivityExpiryDate(activity);
			if ( expDate > 0) {
				char timeBuffer[100];
				struct tm* tmInfo;
				tmInfo = localtime(&expDate);
				strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
				printf("Data di scadenza (valore attuale): %s\n", timeBuffer);
			} else {
				printf("Data di scadenza (valore attuale): Non impostata\n");
			}
			
			int userConfirmation = getConfirmMenuChoice("Vuoi davvero modificare la data di scadenza? ");
			if (userConfirmation == 1) {
				time_t dateFromUser = getDateFromUser();
				setActivityExpiryDate(activity, dateFromUser);
			}
			break;
		}
		
		case 5: { //5. Cambia la durata totale
			printf("[Cambia la durata totale]\n");
			unsigned int totalTime = getActivityTotalTime(activity);
			printf("Durata totale (valore attuale in min): %u\n", totalTime );
			printf("Inserisci il nuovo valore (espresso in MINUTI, compreso 1 e un anno): ");
			totalTime = getChoiceWithLimits(1, 525600);
			setActivityTotalTime(activity, totalTime);
			break;
		}
		
		case 6: { //6. Aggiorna il tempo impiegato sull'attività
			printf("[Aggiorna il tempo impiegato sull'attività]\n");
			unsigned int totalTime = getActivityTotalTime(activity);
			unsigned int usedTime = getActivityUsedTime(activity);
			printf("Tempo impiegato (valore attuale in min): %u\n", usedTime );
			printf("Inserisci il nuovo valore (espresso in MINUTI, compreso 0 e %u): ", totalTime);
			usedTime = getChoiceWithLimits(0, totalTime);
			setActivityUsedTime(activity, usedTime);
			break;
		}
		
		case 7: { //7. Cambia la priorità
			printf("[Cambia la priorità]\n");
			printf("Priorità (valore attuale): %s\n", getActivityPriorityFormatted(activity) );
			printf("\nInserisci la nuova priorità.\n");
			printf("1. ALTA\n");
			printf("2. MEDIA\n");
			printf("3. BASSA\n");
			printf("Scelta: ");
			short unsigned int priority = (short unsigned int) getChoiceWithLimits(1, 3);
			setActivityPriority(activity, priority);
			break;
		}
		
		case 8: { //8. Imposta come COMPLETATA
			printf("[Imposta come COMPLETATA]\n");
			int userConfirmation = getConfirmMenuChoice("Vuoi davvero segnare questa attività come completata? ");
			if (userConfirmation == 1) {
				setActivityCompletionDate(activity, time(NULL) );
			}
			break;
		}
		
		default: {
			printf("Scelta non gestita...\n");
			returnActivity = NULL;
			break;
		}
	}
	
	tmpString = NULL;
	return returnActivity;
}

void printActivity(Activity activity) {
	if (activity == NULL) return;
	printf("\n===========================================\n");
	printf("==== Dettaglio attività con id %d \n", activity->id);
	printf("===========================================\n\n");
    
	printf("Id: %d \n", activity->id);
	printf("Nome: %s\n", activity->name ? activity->name : "NULL");
	printf("Descrizione: %s\n", activity->descr ? activity->descr : "NULL");
	printf("Corso: %s\n", activity->course ? activity->course : "NULL");

	char timeBuffer[100];
	struct tm* tmInfo;
	
	if (activity->insertDate != 0) {
		tmInfo = localtime(&activity->insertDate);
		strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
		printf("Data inserimento: %s\n", timeBuffer);
	} else {
		printf("Data inserimento: Non impostata\n");
	}

	if (activity->expiryDate != 0) {
		tmInfo = localtime(&activity->expiryDate);
		strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
		printf("Data scadenza: %s\n", timeBuffer);
	} else {
		printf("Data scadenza: Non impostata\n");
	}

 	if (activity->completionDate != 0) {
		tmInfo = localtime(&activity->completionDate);
		strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
		printf("Data completamento: %s\n", timeBuffer);
	} else {
		printf("Data completamento: ancora da completare\n");
	}
	
	printf("Tempo speso/usato (min): %u\n", activity->usedTime);
	unsigned int hours = 0;
	unsigned int minutes = 0;
	minToHoursAnMinutes(activity->usedTime, &hours, &minutes);
	printf("Tempo speso/usato (ore e min): %u ore e %u minuti\n", hours, minutes);
	
	printf("Durata totale attività (min): %u\n", activity->totalTime);
	minToHoursAnMinutes(activity->totalTime, &hours, &minutes);
	printf("Durata totale attività (ore e min): %u ore e %u minuti\n", hours, minutes);
	
	if (activity->totalTime >= activity->usedTime) {
		unsigned int diff = activity->totalTime - activity->usedTime;
		printf("Tempo stimato per il completamento (min): %u\n", diff);
		minToHoursAnMinutes(diff, &hours, &minutes);
		printf("Tempo stimato per il completamento (ore e min): %u ore e %u minuti\n", hours, minutes);
	}
	
	int completionPercentage = activityCompletionPercentage(activity);
	printf("Percentuale di completamento: %d%%\n", completionPercentage);
	
	printf("Priorità: %s\n", textForActivityPriority(activity->priority) );

	printf("========= Fine dettaglio attività =========\n\n");
}

void printActivityDetailWithMenu(Activity activity) {
	Activity current = activity;
	while(current != NULL) {
		printActivity(current); 
		current = handleAcivityDetailMenu(current);
	}
}




void printActivityToFile(Activity activity, FILE* file) {
	if (activity == NULL || file == NULL) return;
	  
	fprintf(file, "Id: %d \n", activity->id);
	fprintf(file, "Nome: %s\n", activity->name ? activity->name : "NULL");
	fprintf(file, "Descrizione: %s\n", activity->descr ? activity->descr : "NULL");
	fprintf(file, "Corso: %s\n", activity->course ? activity->course : "NULL");

	char timeBuffer[100];
	struct tm* tmInfo;
	
	if (activity->insertDate != 0) {
		tmInfo = localtime(&activity->insertDate);
		strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
		fprintf(file, "Data inserimento: %s\n", timeBuffer);
	} else {
		fprintf(file, "Data inserimento: Non impostata\n");
	}

	if (activity->expiryDate != 0) {
		tmInfo = localtime(&activity->expiryDate);
		strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
		fprintf(file, "Data scadenza: %s\n", timeBuffer);
	} else {
		fprintf(file, "Data scadenza: Non impostata\n");
	}

 	if (activity->completionDate != 0) {
		tmInfo = localtime(&activity->completionDate);
		strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
		fprintf(file, "Data completamento: %s\n", timeBuffer);
	} else {
		fprintf(file, "Data completamento: ancora da completare\n");
	}
	
	fprintf(file, "Tempo speso/usato (min): %u\n", activity->usedTime);
	unsigned int hours = 0;
	unsigned int minutes = 0;
	minToHoursAnMinutes(activity->usedTime, &hours, &minutes);
	fprintf(file, "Tempo speso/usato (ore e min): %u ore e %u minuti\n", hours, minutes);
	
	fprintf(file, "Durata totale attività (min): %u\n", activity->totalTime);
	minToHoursAnMinutes(activity->totalTime, &hours, &minutes);
	fprintf(file, "Durata totale attività (ore e min): %u ore e %u minuti\n", hours, minutes);
	
	if (activity->totalTime >= activity->usedTime) {
		unsigned int diff = activity->totalTime - activity->usedTime;
		fprintf(file, "Tempo stimato per il completamento (min): %u\n", diff);
		minToHoursAnMinutes(diff, &hours, &minutes);
		fprintf(file, "Tempo stimato per il completamento (ore e min): %u ore e %u minuti\n", hours, minutes);
	}
	
	int completionPercentage = activityCompletionPercentage(activity);
	fprintf(file, "Percentuale di completamento: %d%%\n", completionPercentage);
	
	fprintf(file, "Priorità: %s\n", textForActivityPriority(activity->priority) );
}








void printActivityForListToScreenOrFile(Activity activity, FILE* file) {
	if (activity == NULL) return;
	    
	// Format dates in a human-readable way
	char expiryDateBuffer[100];
	char completionDateBuffer[100];
	int isCompleted = 0;
	char priorityBuffer[10];
	struct tm* tm_info;

	if (activity->expiryDate != 0) {
		tm_info = localtime(&activity->expiryDate);
		strftime(expiryDateBuffer, sizeof(expiryDateBuffer), "%d/%m/%Y %H:%M", tm_info);
	} else {
		strcpy(expiryDateBuffer, "Non impostata");
	}
    
	if (activity->completionDate != 0) {
		isCompleted = 1;
		tm_info = localtime(&activity->completionDate);
		strftime(completionDateBuffer, sizeof(completionDateBuffer), "%d/%m/%Y %H:%M", tm_info);
	}
	
	strcpy(priorityBuffer, textForActivityPriority(activity->priority));
	
	if (file == NULL) {
		if (isCompleted == 0) {
			printf("[%d] %.20s | %.20s | %.20s | %s | SCADENZA: %s\n", activity->id, activity->name ? activity->name : "NULL", activity->descr ? activity->descr : "NULL", activity->course ? activity->course : "NULL", priorityBuffer, expiryDateBuffer);
		} else {
			printf("[%d] %.20s | %.20s | %.20s | %s | COMPLETATA: %s\n", activity->id, activity->name ? activity->name : "NULL", activity->descr ? activity->descr : "NULL", activity->course ? activity->course : "NULL", priorityBuffer, completionDateBuffer);
		}
	} else {
		if (isCompleted == 0) {
			fprintf(file, "[%d] %.20s | %.20s | %.20s | %s | SCADENZA: %s\n", activity->id, activity->name ? activity->name : "NULL", activity->descr ? activity->descr : "NULL", activity->course ? activity->course : "NULL", priorityBuffer, expiryDateBuffer);
		} else {
			fprintf(file, "[%d] %.20s | %.20s | %.20s | %s | COMPLETATA: %s\n", activity->id, activity->name ? activity->name : "NULL", activity->descr ? activity->descr : "NULL", activity->course ? activity->course : "NULL", priorityBuffer, completionDateBuffer);
		}	
	}
}

void printActivityForList(Activity activity) {
	printActivityForListToScreenOrFile(activity, NULL);
}

void printActivityForListToFile(Activity activity, FILE* file) {
	if (file == NULL) return;
	printActivityForListToScreenOrFile(activity, file);
}


//Don't show completed activities
void printActivityProgressForListToScreenOrFile(Activity activity, FILE* file) {
	if (activity == NULL || activity->completionDate != 0) return;
	    
	// Format dates in a human-readable way
	char expiryDateBuffer[100];
	char priorityBuffer[10];
	struct tm* tmInfo;

	if (activity->expiryDate != 0) {
		tmInfo = localtime(&activity->expiryDate);
		strftime(expiryDateBuffer, sizeof(expiryDateBuffer), "%d/%m/%Y %H:%M", tmInfo);
	} else {
		strcpy(expiryDateBuffer, "Non impostata");
	}
   
	strcpy(priorityBuffer, textForActivityPriority(activity->priority));
	int completionPercentage = activityCompletionPercentage(activity);
	
	if (file == NULL) {
		// [id] title | descr | course | priority | PROGRESS | usedTime | TIME REMAINING | totalTime | expiryDate
		printf("[%d] %.20s | %.10s | %.10s | %s | %d%% | %d min | %d min | %d min | SCADENZA: %s\n", activity->id, activity->name ? activity->name : "NULL", activity->descr ? activity->descr : "NULL", activity->course ? activity->course : "NULL", priorityBuffer, completionPercentage, activity->usedTime, activity->totalTime - activity->usedTime,  activity->totalTime, expiryDateBuffer);
	} else {
		// [id] title | descr | course | priority | PROGRESS | usedTime | TIME REMAINING | totalTime | expiryDate
		fprintf(file, "[%d] %.20s | %.10s | %.10s | %s | %d%% | %d min | %d min | %d min | SCADENZA: %s\n", activity->id, activity->name ? activity->name : "NULL", activity->descr ? activity->descr : "NULL", activity->course ? activity->course : "NULL", priorityBuffer, completionPercentage, activity->usedTime, activity->totalTime - activity->usedTime,  activity->totalTime, expiryDateBuffer);	
	}
}

void printActivityProgressForList(Activity activity) {
	printActivityProgressForListToScreenOrFile(activity, NULL);
}

void printActivityProgressForListToFile(Activity activity, FILE* file) {
	if (file == NULL) return;
	printActivityProgressForListToScreenOrFile(activity, file);
}


// Read an activity from file (file is supposed to be in read mode), line by line
Activity readActivityFromFile(FILE* file) {
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


	Activity activity = newEmptyActivity();
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
void saveActivityToFile(FILE* file, Activity activity) {
	if (activity == NULL) return;
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
