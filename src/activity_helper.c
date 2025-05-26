#include "activity_helper.h"


// 1 = activity is yet to begin, 0 = is completed or ongoing
int isActivityYetToBegin(Activity a) {
	if (a == NULL) return 0;
	
	unsigned int usedTime = getActivityUsedTime(a);
	
	return (usedTime == 0) ? 1 : 0;
}

// 1 = activity is completed, 0 = is NOT completed
int isActivityCompleted(Activity a) {
	if (a == NULL) return 0;
	
	time_t completionDate = getActivityCompletionDate(a);
	
	return (completionDate != 0) ? 1 : 0;
}

// 1 = activity was completed after the threshold date, 0 = otherwise
int wasActivityCompletedAfterDate(Activity a, time_t thresholdDate) {
	if (a == NULL) return 0;
	
	time_t completionDate = getActivityCompletionDate(a);
	
	return (completionDate > thresholdDate) ? 1 : 0;
}

// 0 = activity was expired before the threshold date, 1 = otherwise
int wasActivityExpiredBeforeDate(Activity a, time_t thresholdDate) {
	if (a == NULL) return 0;
	
	time_t expiryDate = getActivityExpiryDate(a);
	
	//expiryDate = 0 mean no expiry date
	return (expiryDate > 0 && expiryDate < thresholdDate) ? 1 : 0;
}


int compareWithId(Activity a, int activityId) {
	if (!a) return -2;
	
	int a_id = getActivityId(a);
	
	if (a_id == activityId) return 0;
	
	return (a_id < activityId) ? -1 : 1;
}

// Used "int" consciously
int activityCompletionPercentage(Activity activity) {
	if (activity == NULL) return 0;
	
	unsigned int totalTime = getActivityTotalTime(activity);
	unsigned int usedTime = getActivityUsedTime(activity);
	
	if (usedTime == 0 || totalTime == 0 ) return 0;
	
	int completionPercentage = (usedTime * 100) / totalTime;
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



int compareActivityById(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	int b_id = getActivityId(b);
	
	return compareWithId(a, b_id);
}

int compareActivityByName(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	char* a_name = getActivityName(a);
	char* b_name = getActivityName(b);
	
	if (a_name == NULL || b_name == NULL) {
		return compareNullString(a_name, b_name);
	}
	
	return strcmp(a_name, b_name);
}

int compareActivityByDescr(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	char* a_descr = getActivityDescr(a);
	char* b_descr = getActivityDescr(b);
	
	if (a_descr == NULL || b_descr == NULL) {
		return compareNullString(a_descr, b_descr);
	}
	
	return strcmp(a_descr, b_descr);
}

int compareActivityByCourse(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	char* a_course = getActivityCourse(a);
	char* b_course = getActivityCourse(b);
	
	if (a_course == NULL || b_course == NULL) {
		return compareNullString(a_course, b_course);
	}
	
	return strcmp(a_course, b_course);
}

int compareActivityByInsertDate(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	time_t a_insertDate = getActivityInsertDate(a);
	time_t b_insertDate = getActivityInsertDate(a);
	
	if (a_insertDate == b_insertDate) return 0;
	
	return (a_insertDate < b_insertDate) ? -1 : 1;
}

int compareActivityByExpiryDate(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	time_t a_expiryDate = getActivityExpiryDate(a);
	time_t b_expiryDate = getActivityExpiryDate(a);
	
	if (a_expiryDate == b_expiryDate) return 0;
	
	return (a_expiryDate < b_expiryDate) ? -1 : 1;
}

int compareActivityByCompletionDate(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	time_t a_completionDate = getActivityCompletionDate(a);
	time_t b_completionDate = getActivityCompletionDate(a);
	
	if (a_completionDate == b_completionDate) return 0;
	
	return (a_completionDate < b_completionDate) ? -1 : 1;
}

int compareActivityByTotalTime(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	unsigned int a_totalTime = getActivityTotalTime(a);
	unsigned int b_totalTime = getActivityTotalTime(b);
	
	if (a_totalTime == b_totalTime) return 0;
	
	return (a_totalTime < b_totalTime) ? -1 : 1;
}

int compareActivityByUsedTime(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	unsigned int a_usedTime = getActivityUsedTime(a);
	unsigned int b_usedTime = getActivityUsedTime(b);
	
	if (a_usedTime == b_usedTime) return 0;
	
	return (a_usedTime < b_usedTime) ? -1 : 1;
}

int compareActivityByPriority(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	short unsigned int a_priority = getActivityPriority(a);
	short unsigned int b_priority = getActivityPriority(b);
	
	if (a_priority == b_priority) return 0;
	
	return (a_priority < b_priority) ? -1 : 1;
}

int compareActivityByPercentCompletion(Activity a, Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	int a_percent = activityCompletionPercentage(a);
	int b_percent = activityCompletionPercentage(b);
	
	if (a_percent == b_percent) return 0;
	
	return (a_percent < b_percent) ? -1 : 1;
}

int compareActivityByTimeToCompletion(Activity a, Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	unsigned int a_timeToCompletion = 0;
	unsigned int b_timeToCompletion = 0;
	
	unsigned int a_totalTime = getActivityTotalTime(a);
	unsigned int a_usedTime = getActivityUsedTime(a);
	
	if (a_totalTime >= a_usedTime) {
		a_timeToCompletion = a_totalTime - a_usedTime;
	}
	
	unsigned int b_totalTime = getActivityTotalTime(b);
	unsigned int b_usedTime = getActivityUsedTime(b);
	
	if (b_totalTime >= b_usedTime) {
		b_timeToCompletion = b_totalTime - b_usedTime;
	}
	
	if (a_timeToCompletion == b_timeToCompletion) return 0;
	
	return (a_timeToCompletion < b_timeToCompletion) ? -1 : 1;
}


int compareActivityBy(Activity a, Activity b, int compareBy) {
	int cmp = 0;
	switch (compareBy) {
		case 0: cmp = compareActivityById(a, b);
				break;
				
		case 1: cmp = compareActivityByName(a, b);
				break;
				
		case 2: cmp = compareActivityByDescr(a, b);
				break;
				
		case 3: cmp = compareActivityByCourse(a, b);
				break;
				
		case 4: cmp = compareActivityByInsertDate(a, b);
				break;
				
		case 5: cmp = compareActivityByExpiryDate(a, b);
				break;
				
		case 6: cmp = compareActivityByCompletionDate(a, b);
				break;
				
		case 7: cmp = compareActivityByTotalTime(a, b);
				break;
				
		case 8: cmp = compareActivityByUsedTime(a, b);
				break;
				
		case 9: cmp = compareActivityByPriority(a, b);
				break;
				
		case 10: cmp = compareActivityByPercentCompletion(a, b);
				break;
				
		case 11: cmp = compareActivityByTimeToCompletion(a, b);
				break;
				
		default: cmp = compareActivityById(a, b);
				break;
	}
	
	return cmp;
}



char * priorityToText(int priority) {
	switch(priority) {
		case 1: return "ALTA";
		case 2: return "MEDIA";
		case 3: return "BASSA";
		default: break;
	}
	
	return "?";
}

char*  getActivityPriorityText(Activity a) {
	if (a == NULL) return NULL;
	
	return priorityToText( getActivityPriority(a) );
}




void displayActivityDetailMenu() {
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

Activity handleActivityDetailMenu(Activity activity) {
	displayActivityDetailMenu();
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
			printf("Priorità (valore attuale): %s\n", getActivityPriorityText(activity) );
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
	
	int id =  getActivityId(activity);
	char* name = getActivityName(activity);
	char* descr = getActivityDescr(activity);
	char* course = getActivityCourse(activity);
	time_t insertDate = getActivityInsertDate(activity);
	time_t expiryDate = getActivityExpiryDate(activity);
	time_t completionDate = getActivityCompletionDate(activity);
	unsigned int totalTime = getActivityTotalTime(activity);
	unsigned int usedTime = getActivityUsedTime(activity);
	short unsigned int priority = getActivityPriority(activity);
	
	printf("\n===========================================\n");
	printf("==== Dettaglio attività con id %d \n", id);
	printf("===========================================\n\n");
    
	printf("Id: %d \n", id);
	printf("Nome: %s\n", name ? name : "NULL");
	printf("Descrizione: %s\n", descr ? descr : "NULL");
	printf("Corso: %s\n", course ? course : "NULL");

	char timeBuffer[100];
	struct tm* tmInfo;
	
	if (insertDate != 0) {
		tmInfo = localtime(&insertDate);
		strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
		printf("Data inserimento: %s\n", timeBuffer);
	} else {
		printf("Data inserimento: Non impostata\n");
	}

	if (expiryDate != 0) {
		tmInfo = localtime(&expiryDate);
		strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
		printf("Data scadenza: %s\n", timeBuffer);
	} else {
		printf("Data scadenza: Non impostata\n");
	}

 	if (completionDate != 0) {
		tmInfo = localtime(&completionDate);
		strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
		printf("Data completamento: %s\n", timeBuffer);
	} else {
		printf("Data completamento: ancora da completare\n");
	}
	
	printf("Tempo speso/usato (min): %u\n", usedTime);
	unsigned int hours = 0;
	unsigned int minutes = 0;
	minToHoursAnMinutes(usedTime, &hours, &minutes);
	printf("Tempo speso/usato (ore e min): %u ore e %u minuti\n", hours, minutes);
	
	printf("Durata totale attività (min): %u\n", totalTime);
	minToHoursAnMinutes(totalTime, &hours, &minutes);
	printf("Durata totale attività (ore e min): %u ore e %u minuti\n", hours, minutes);
	
	if (totalTime >= usedTime) {
		unsigned int diff = totalTime - usedTime;
		printf("Tempo stimato per il completamento (min): %u\n", diff);
		minToHoursAnMinutes(diff, &hours, &minutes);
		printf("Tempo stimato per il completamento (ore e min): %u ore e %u minuti\n", hours, minutes);
	}
	
	int completionPercentage = activityCompletionPercentage(activity);
	printf("Percentuale di completamento: %d%%\n", completionPercentage);
	
	printf("Priorità: %s\n", getActivityPriorityText(activity) );

	printf("========= Fine dettaglio attività =========\n\n");
}

void printActivityDetailWithMenu(Activity activity) {
	Activity current = activity;
	while(current != NULL) {
		printActivity(current); 
		current = handleActivityDetailMenu(current);
	}
}




void printActivityToFile(Activity activity, FILE* file) {
	if (activity == NULL || file == NULL) return;

	int id =  getActivityId(activity);
	char* name = getActivityName(activity);
	char* descr = getActivityDescr(activity);
	char* course = getActivityCourse(activity);
	time_t insertDate = getActivityInsertDate(activity);
	time_t expiryDate = getActivityExpiryDate(activity);
	time_t completionDate = getActivityCompletionDate(activity);
	unsigned int totalTime = getActivityTotalTime(activity);
	unsigned int usedTime = getActivityUsedTime(activity);
	short unsigned int priority = getActivityPriority(activity);

	fprintf(file, "Id: %d \n", id);
	fprintf(file, "Nome: %s\n", name ? name : "NULL");
	fprintf(file, "Descrizione: %s\n", descr ? descr : "NULL");
	fprintf(file, "Corso: %s\n", course ? course : "NULL");

	char timeBuffer[100];
	struct tm* tmInfo;
	
	if (insertDate != 0) {
		tmInfo = localtime(&insertDate);
		strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
		fprintf(file, "Data inserimento: %s\n", timeBuffer);
	} else {
		fprintf(file, "Data inserimento: Non impostata\n");
	}

	if (expiryDate != 0) {
		tmInfo = localtime(&expiryDate);
		strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
		fprintf(file, "Data scadenza: %s\n", timeBuffer);
	} else {
		fprintf(file, "Data scadenza: Non impostata\n");
	}

 	if (completionDate != 0) {
		tmInfo = localtime(&completionDate);
		strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
		fprintf(file, "Data completamento: %s\n", timeBuffer);
	} else {
		fprintf(file, "Data completamento: ancora da completare\n");
	}
	
	fprintf(file, "Tempo speso/usato (min): %u\n", usedTime);
	unsigned int hours = 0;
	unsigned int minutes = 0;
	minToHoursAnMinutes(usedTime, &hours, &minutes);
	fprintf(file, "Tempo speso/usato (ore e min): %u ore e %u minuti\n", hours, minutes);
	
	fprintf(file, "Durata totale attività (min): %u\n", totalTime);
	minToHoursAnMinutes(totalTime, &hours, &minutes);
	fprintf(file, "Durata totale attività (ore e min): %u ore e %u minuti\n", hours, minutes);
	
	if (totalTime >= usedTime) {
		unsigned int diff = totalTime - usedTime;
		fprintf(file, "Tempo stimato per il completamento (min): %u\n", diff);
		minToHoursAnMinutes(diff, &hours, &minutes);
		fprintf(file, "Tempo stimato per il completamento (ore e min): %u ore e %u minuti\n", hours, minutes);
	}
	
	int completionPercentage = activityCompletionPercentage(activity);
	fprintf(file, "Percentuale di completamento: %d%%\n", completionPercentage);
	
	fprintf(file, "Priorità: %s\n", priorityToText(priority) );
}








void printActivityForListToScreenOrFile(Activity activity, FILE* file) {
	if (activity == NULL) return;

	int id =  getActivityId(activity);
	char* name = getActivityName(activity);
	char* descr = getActivityDescr(activity);
	char* course = getActivityCourse(activity);
	time_t expiryDate = getActivityExpiryDate(activity);
	time_t completionDate = getActivityCompletionDate(activity);
	short unsigned int priority = getActivityPriority(activity);
 
	// Format dates in a human-readable way
	char expiryDateBuffer[100];
	char completionDateBuffer[100];
	int isCompleted = 0;
	char priorityBuffer[10];
	struct tm* tm_info;

	if (expiryDate != 0) {
		tm_info = localtime(&expiryDate);
		strftime(expiryDateBuffer, sizeof(expiryDateBuffer), "%d/%m/%Y %H:%M", tm_info);
	} else {
		strcpy(expiryDateBuffer, "Non impostata");
	}
    
	if (completionDate != 0) {
		isCompleted = 1;
		tm_info = localtime(&completionDate);
		strftime(completionDateBuffer, sizeof(completionDateBuffer), "%d/%m/%Y %H:%M", tm_info);
	}
	
	strcpy(priorityBuffer, priorityToText(priority));
	
	if (file == NULL) {
		if (isCompleted == 0) {
			printf("[%d] %.20s | %.20s | %.20s | %s | SCADENZA: %s\n", id, name ? name : "NULL", descr ? descr : "NULL", course ? course : "NULL", priorityBuffer, expiryDateBuffer);
		} else {
			printf("[%d] %.20s | %.20s | %.20s | %s | COMPLETATA: %s\n", id, name ? name : "NULL", descr ? descr : "NULL", course ? course : "NULL", priorityBuffer, completionDateBuffer);
		}
	} else {
		if (isCompleted == 0) {
			fprintf(file, "[%d] %.20s | %.20s | %.20s | %s | SCADENZA: %s\n", id, name ? name : "NULL", descr ? descr : "NULL", course ? course : "NULL", priorityBuffer, expiryDateBuffer);
		} else {
			fprintf(file, "[%d] %.20s | %.20s | %.20s | %s | COMPLETATA: %s\n", id, name ? name : "NULL", descr ? descr : "NULL", course ? course : "NULL", priorityBuffer, completionDateBuffer);
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
	if (activity == NULL || isActivityCompleted(activity) == 1) return;
	
	int id =  getActivityId(activity);
	char* name = getActivityName(activity);
	char* descr = getActivityDescr(activity);
	char* course = getActivityCourse(activity);
	time_t insertDate = getActivityInsertDate(activity);
	time_t expiryDate = getActivityExpiryDate(activity);
	unsigned int totalTime = getActivityTotalTime(activity);
	unsigned int usedTime = getActivityUsedTime(activity);
	short unsigned int priority = getActivityPriority(activity);

	// Format dates in a human-readable way
	char expiryDateBuffer[100];
	char priorityBuffer[10];
	struct tm* tmInfo;

	if (expiryDate != 0) {
		tmInfo = localtime(&expiryDate);
		strftime(expiryDateBuffer, sizeof(expiryDateBuffer), "%d/%m/%Y %H:%M", tmInfo);
	} else {
		strcpy(expiryDateBuffer, "Non impostata");
	}
   
	strcpy(priorityBuffer, priorityToText(priority));
	int completionPercentage = activityCompletionPercentage(activity);
	
	if (file == NULL) {
		// [id] title | descr | course | priority | PROGRESS | usedTime | TIME REMAINING | totalTime | expiryDate
		printf("[%d] %.20s | %.10s | %.10s | %s | %d%% | %d min | %d min | %d min | SCADENZA: %s\n", id, name ? name : "NULL", descr ? descr : "NULL", course ? course : "NULL", priorityBuffer, completionPercentage, usedTime, totalTime - usedTime,  totalTime, expiryDateBuffer);
	} else {
		// [id] title | descr | course | priority | PROGRESS | usedTime | TIME REMAINING | totalTime | expiryDate
		fprintf(file, "[%d] %.20s | %.10s | %.10s | %s | %d%% | %d min | %d min | %d min | SCADENZA: %s\n", id, name ? name : "NULL", descr ? descr : "NULL", course ? course : "NULL", priorityBuffer, completionPercentage, usedTime, totalTime - usedTime,  totalTime, expiryDateBuffer);	
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
	
	return newActivity(id,name, descr, course, insertDate, expiryDate, completionDate, totalTime, usedTime, priority);
}


// Function to save activities to a file that is supposed to be already correctly opened for writing
// Returns 0 if everything is ok 1 if something went wrong
void saveActivityToFile(FILE* file, Activity activity) {
	if (activity == NULL) return;
	
	int id =  getActivityId(activity);
	char* name = getActivityName(activity);
	char* descr = getActivityDescr(activity);
	char* course = getActivityCourse(activity);
	time_t insertDate = getActivityInsertDate(activity);
	time_t expiryDate = getActivityExpiryDate(activity);
	time_t completionDate = getActivityCompletionDate(activity);
	unsigned int totalTime = getActivityTotalTime(activity);
	unsigned int usedTime = getActivityUsedTime(activity);
	short unsigned int priority = getActivityPriority(activity);
	
	fprintf(file, "%d\n", id);
	fprintf(file, "%s\n", name ? name : "");
	fprintf(file, "%s\n", descr ? descr : "");
	fprintf(file, "%s\n", course ? course : "");
	fprintf(file, "%ld\n", insertDate);
	fprintf(file, "%ld\n", expiryDate);
	fprintf(file, "%ld\n", completionDate);
	fprintf(file, "%u\n", totalTime);
	fprintf(file, "%u\n", usedTime);
	fprintf(file, "%hu\n", priority);
}



