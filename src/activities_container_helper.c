#include "activities_container_helper.h"
#include "activities_container_support_list.h"




// Search a node in the AVL tree
TreeNode search(TreeNode root, int activityId) {
	if (root == NULL) return NULL;
	
	int compareResult = compareWithId( getActivityFromNode(root), activityId );
	
	if(compareResult == 0) {
		return root;
	} else if(compareResult < 0) { // root->activity is < of activityId
		return search( getRightNode(root), activityId );
	} else {
		return search( getLeftNode(root), activityId );
	}
}

Activity getActivityWithIdForTest(ActivitiesContainer container, int activityId) {
	TreeNode root = getRootNode(container);
	if(root == NULL) return NULL;

	TreeNode activityNode = search(root, activityId);
	if (activityNode != NULL) {
		return getActivityFromNode(activityNode);
	}
	
	return NULL;
}











// Function to perform preorder traversal of AVL tree and save to file activity by activity
void inOrderSaveActivitiesToFile(FILE* file, TreeNode root) {
	if (root != NULL) {
		inOrderSaveActivitiesToFile(file, getLeftNode(root) );
		saveActivityToFile(file, getActivityFromNode(root) );
		inOrderSaveActivitiesToFile(file, getRightNode(root) );
	}
}

// Function to save activities (tree) to a file
// 0 = OK, 1 = ERROR
int saveActivitiesToFile(const char* filename, ActivitiesContainer container) {
	if (container == NULL) return 1;
	
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("Errore nell'apertura del file %s per la scrittura.\n", filename);
		return 1;
	}

	TreeNode root = getRootNode(container);
	inOrderSaveActivitiesToFile(file, root);

	fclose(file);
	printf("Attività salvate con successo nel file %s\n", filename);
	return 0;
}








// Function to read all activities from a file
ActivitiesContainer readActivitiesFromFile(const char* filename, int* count) {
	ActivitiesContainer newContainer = newActivityContainer();
	if(newContainer == NULL) return NULL;
	
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("Il file %s non esiste. Verrà creato un contenitore vuoto per le attività.\n", filename);
		*count = 0;
		return newContainer;
	}
	
	*count = 0;
	
	while (!feof(file)) {  
		Activity currentActivity = readActivityFromFile(file);
		if (currentActivity == NULL) {
			fclose(file);
			return newContainer;
		}
		
		newContainer = insertActivity(newContainer, currentActivity);
		*count += 1;
	}
	  
	fclose(file);
	printf("Lette %d attività dal file %s.\n", *count, filename);
	return newContainer;
}









ActivitiesContainer addNewActivityToContainer(ActivitiesContainer container) {
	
	if (container == NULL) return 0;
	
	
	printf("\n====== Inserisci una nuova attività ======\n");
	
	char* activityName = NULL;
	while (activityName == NULL) {
		activityName = getInfoFromUser("Nome dell'attività (non vuoto): ");
		if (activityName == NULL) {
			printf("\nNome non valido. Per favore inserisci un nome valido.\n");
		}
	}

	char* activityDesr = NULL;
	while (activityDesr == NULL) {
		activityDesr = getInfoFromUser("Descrizione dell'attività (non vuota): ");
		if (activityDesr == NULL) {
			printf("\nDescrizione non valida. Per favore inserisci una descrizione valida.\n");
		}
	}

	char* activityCourse = NULL;
	while (activityCourse == NULL) {
		activityCourse = getInfoFromUser("Corso dell'attività (non vuoto): ");
		if (activityCourse == NULL) {
			printf("\nCorso non valido. Per favore inserisci un corso valido.\n");
		}
	}
	
	time_t insertDate = time(NULL);
	
	printf("\nVuoi inserire la data di scadenza per questa attività?\n");
	printf("1. Si\n");
	printf("0. No\n");
	printf("Scelta: ");
	int insertExpiryDate = getChoice(1);
	
	time_t expiryDate = 0; 
	if (insertExpiryDate == 1) {
		expiryDate = getDateFromUser();
	}
	
	time_t completionDate = 0;
	
	printf("\nCi siamo quasi! Inserisci il tempo stimato per il completamento dell'attività (espresso in MINUTI, compreso 1 e 525600, circa un anno):");
	unsigned int totalTime = getChoiceWithLimits(1, 525600);
	unsigned int usedTime = 0;
	
	printf("\nUltimo passo. Inserisci la priorità.\n");
	printf("1. ALTA\n");
	printf("2. MEDIA\n");
	printf("3. BASSA\n");
	printf("Scelta: ");
	short unsigned int priority = (short unsigned int) getChoiceWithLimits(1, 3);
	
	//With 0 id is automatically calculated
	Activity activity = newActivity( 0, activityName, activityDesr, activityCourse, insertDate, expiryDate, completionDate, totalTime, usedTime, priority);
	
	return insertActivity(container, activity);
}












void printActivityWithId(ActivitiesContainer container, int activityId) {
	TreeNode root = getRootNode(container);
	if(root == NULL) return;

	TreeNode activityNode = search(root, activityId);
	if (activityNode != NULL) {
		printActivityDetailWithMenu( getActivityFromNode(activityNode) );
	}
}





// Function to perform inorder traversal of AVL tree and print the contained activity
void printInOrder(TreeNode root) {
	if (root != NULL) {
		printInOrder( getLeftNode(root) );
		//printActivity(root->activity);
		printActivityForList( getActivityFromNode(root) );
		printInOrder( getRightNode(root) );
	}
}


// Prints all activities
void printActivities(ActivitiesContainer container) {
	if (container != NULL) {
		printf("\n=============================\n");
		printf("====== Tutte le attività =====\n");
		printf("==============================\n");
		printf("[NOTA: titolo, descrizione e corso potrebbero essere abbreviati. Vai al dettaglio attività per vedere le info complete]\n");
		printf("[Le attività sono ordinate per id]\n");
		printf("\n====================================================================================================\n");
		printf("[id] Titolo | Descrizione | Corso | Priorità | Data scadenza o data completamento\n");
		printf("====================================================================================================\n\n");

		TreeNode root = getRootNode(container);
		printInOrder(root);
	}
}





void printInOrderToFile(TreeNode root, FILE* file) {
	if (root != NULL) {
		printInOrderToFile( getLeftNode(root), file );
		printActivityForListToFile( getActivityFromNode(root), file );
		printInOrderToFile( getRightNode(root), file );
	}
}

// Prints all activities to file
void printActivitiesToFile(ActivitiesContainer container, FILE* file) {
	if (container != NULL && file != NULL) {
		TreeNode root = getRootNode(container);
		printInOrderToFile(root, file);
	}
}





void printInOrderProgress(TreeNode root) {
	if (root != NULL) {
		printInOrderProgress( getLeftNode(root) );
		printActivityProgressForList( getActivityFromNode(root) );
		printInOrderProgress( getRightNode(root) );
	}
}

// Prints activities progress
void printActivitiesProgress(ActivitiesContainer container) {
	if (container != NULL) {
		printf("\n=============================\n");
		printf("=== MONITORAGGIO PROGRESSO ===\n");
		printf("==============================\n");
		printf("[NOTA: titolo, descrizione e corso potrebbero essere abbreviati. Vai al dettaglio attività per vedere le info complete]\n");
		printf("[Le attività sono ordinate per id. Qui NON vengono mostrate le attività completate]\n");
		printf("\n====================================================================================================================================================\n");
		printf("[id] Titolo | Descrizione | Corso | Priorità | Progresso (%%) | Tempo usato (min) | Tempo al completamento (min) | Tempo totale (min) | Data scadenza\n");
		printf("====================================================================================================================================================\n\n");
		
		TreeNode root = getRootNode(container);
		printInOrderProgress(root);
	}
}



void printInOrderProgressToFile(TreeNode root, FILE* file)  {
	if (root != NULL) {
		printInOrderProgressToFile( getLeftNode(root), file );
		printActivityProgressForListToFile( getActivityFromNode(root), file);
		printInOrderProgressToFile( getRightNode(root), file);
	}
}

void printActivitiesProgressToFile(ActivitiesContainer container, FILE* file) {
	if (container != NULL && file != NULL) {
		fprintf(file, "=== MONITORAGGIO PROGRESSO ===\n");
		
		TreeNode root = getRootNode(container);
		printInOrderProgressToFile(root, file);
	}
}













void buildInOrderSupportListsForActivitiesReport(TreeNode root, ActivitiesContainerSupportList completedList, ActivitiesContainerSupportList ongoingList, ActivitiesContainerSupportList expiredList, ActivitiesContainerSupportList yetToBeginList, time_t beginDate, time_t nowDate) {
	if (root != NULL) {
		buildInOrderSupportListsForActivitiesReport( getLeftNode(root), completedList, ongoingList, expiredList, yetToBeginList, beginDate, nowDate); //left
		
		Activity activity = getActivityFromNode(root);
		int isCompleted = isActivityCompleted(activity);
		if (isCompleted == 1) { //all complete activities
			int wasCompletedInLastPeriod = wasActivityCompletedAfterDate(activity, beginDate);
			if (wasCompletedInLastPeriod == 1) { //completed in the last period
				addActivityToSupportList(completedList, activity);
			}
		} else if ( wasActivityExpiredBeforeDate(activity, nowDate) == 1 ) { //expired and not completed
			addActivityToSupportList(expiredList, activity);
		} else if ( isActivityYetToBegin(activity) == 1 ) { //yet to begin
			addActivityToSupportList(yetToBeginList, activity);
		} else { //ongoing
			addActivityToSupportList(ongoingList, activity);
		}
		
		buildInOrderSupportListsForActivitiesReport( getRightNode(root), completedList, ongoingList, expiredList, yetToBeginList, beginDate, nowDate); //right
	}
}



void printActivitiesReport(ActivitiesContainer container) {
	TreeNode root = getRootNode(container);
	if (root == NULL) return;
	
	time_t beginDate = time(NULL); //now
	beginDate = beginDate - 60*60*24*7; //one week ago
	
	char timeBuffer[100];
	struct tm* tmInfo;
	
	tmInfo = localtime(&beginDate);
	strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
	
	printf("\n\nIl report settimanale di default mostra i cambiamenti nell'ultima settimana.\n");
	printf("\nVuoi visualizzare il report a partire da %s (se scegli 'No' dovrai inserire una data)?\n", timeBuffer);
	printf("1. Si\n");
	printf("0. No\n");
	printf("Scelta: ");
	int insertReportDate = getChoice(1);
	
	if (insertReportDate == 0) {		
		time_t userDate = getDateFromUser();
		
		if (userDate >= time(NULL)) {
			printf("\nLa data inserita è nel futuro: verrà usata la data di default.");
		} else {
			tmInfo = localtime(&userDate);
			strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
			printf("\nSarà usata la seguente data per il report: %s\n", timeBuffer);
			beginDate = userDate;
		}
	}
	
	ActivitiesContainerSupportList completedList = newSupportList();
	ActivitiesContainerSupportList ongoingList = newSupportList();
	ActivitiesContainerSupportList expiredList = newSupportList();
	ActivitiesContainerSupportList yetToBeginList = newSupportList();
	buildInOrderSupportListsForActivitiesReport(root, completedList, ongoingList, expiredList, yetToBeginList, beginDate, time(NULL) );

	sortSupportList(completedList, 6); //compareActivityByCompletionDate
	sortSupportList(yetToBeginList, 4); //compareActivityByInsertDate
	sortSupportList(ongoingList, 10); //compareActivityByPercentCompletion
	sortSupportList(expiredList, 5); //compareActivityByExpiryDate

	printf("\n=============================\n");
	printf("=== REPORT ULTIMO PERIODO ====\n");
	printf("==============================\n");
	printf("[NOTA: titolo, descrizione e corso potrebbero essere abbreviati. Vai al dettaglio attività per vedere le info complete]\n");
	printf("[Qui le attività completate vengono mostrate solo se completate nel periodo di riferimento del report (e non prima)]\n");

	printf("\n\n=========================================================================");
	printf("\n=== Attività COMPLETATE nel periodo (ordinate per data di completamento):\n");
	printf("=======================================================================================\n");
	printf("[id] Titolo | Descrizione | Corso | Priorità | Data scadenza o data completamento\n\n");
	printActivitiesInSupportList(completedList, 0, NULL); //printActivityForList
	
	printf("\n\n=========================================================================");
	printf("\n=== Attività ANCORA DA INIZIARE (ordinate per data di inserimento):\n");
	printf("=======================================================================================\n");
	printf("[id] Titolo | Descrizione | Corso | Priorità | Data scadenza\n\n");
	printActivitiesInSupportList(yetToBeginList, 0, NULL); //printActivityForList
	
	printf("\n\n=========================================================================");
	printf("\n=== Attività IN CORSO (ordinate per percentuale di completamento):\n");
	printf("====================================================================================================================================================\n");
	printf("[id] Titolo | Descrizione | Corso | Priorità | Progresso (%%) | Tempo usato (min) | Tempo al completamento (min) | Tempo totale (min) | Data scadenza\n\n");
	printActivitiesInSupportList(ongoingList, 1, NULL); //printActivityProgressForList
	
	printf("\n\n=========================================================================");
	printf("\n=== Attività IN RITARDO (ordinate per data di scadenza):\n");
	printf("====================================================================================================================================================\n");
	printf("[id] Titolo | Descrizione | Corso | Priorità | Progresso (%%) | Tempo usato (min) | Tempo al completamento (min) | Tempo totale (min) | Data scadenza\n\n");
	printActivitiesInSupportList(expiredList, 1, NULL); //printActivityProgressForList
	
	printf("\n");
	
	//delete support lists
	deleteSupportList(&completedList);
	deleteSupportList(&yetToBeginList);
	deleteSupportList(&ongoingList);
	deleteSupportList(&expiredList);
}

void printActivitiesReportToFile(ActivitiesContainer container, time_t beginDate, FILE* file) {
	TreeNode root = getRootNode(container);
	if (root == NULL || file == NULL || beginDate < 0) return;
	
	ActivitiesContainerSupportList completedList = newSupportList();
	ActivitiesContainerSupportList ongoingList = newSupportList();
	ActivitiesContainerSupportList expiredList = newSupportList();
	ActivitiesContainerSupportList yetToBeginList = newSupportList();
	buildInOrderSupportListsForActivitiesReport(root, completedList, ongoingList, expiredList, yetToBeginList, beginDate, time(NULL) );

	sortSupportList(completedList, 6); //compareActivityByCompletionDate
	sortSupportList(yetToBeginList, 4); //compareActivityByInsertDate
	sortSupportList(ongoingList, 10); //compareActivityByPercentCompletion
	sortSupportList(expiredList, 5); //compareActivityByExpiryDate

	fprintf(file, "Data: %ld\n", beginDate);
	fprintf(file, "=== REPORT ULTIMO PERIODO ====\n\n");

	fprintf(file, "\n=== Attività COMPLETATE nel periodo (ordinate per data di completamento):\n");
	printActivitiesInSupportList(completedList, 0, file); //printActivityForListToFile
	
	fprintf(file, "\n\n=== Attività ANCORA DA INIZIARE (ordinate per data di inserimento):\n");
	printActivitiesInSupportList(yetToBeginList, 0, file); //printActivityForListToFile
	
	fprintf(file, "\n\n=== Attività IN CORSO (ordinate per percentuale di completamento):\n");
	printActivitiesInSupportList(ongoingList, 1, file); //printActivityProgressForListToFile
	
	fprintf(file, "\n\n=== Attività IN RITARDO (ordinate per data di scadenza):\n");
	printActivitiesInSupportList(expiredList, 1, file); //printActivityProgressForListToFile
 
	//delete support lists
	deleteSupportList(&completedList);
	deleteSupportList(&yetToBeginList);
	deleteSupportList(&ongoingList);
	deleteSupportList(&expiredList);
}



