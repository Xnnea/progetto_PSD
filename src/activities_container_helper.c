#include "activity_helper.h"
#include "activities_container_helper.h"
#include "activities_container_support_list.h"




/*
 * inOrderSaveActivitiesToFile
 * 
 * Syntactic Specification:
 * void inOrderSaveActivitiesToFile(FILE* file, TreeNode root);
 * 
 * Semantic Specification:
 * Recursively saves all tree activities to file in in-order.
 * 
 * Preconditions:
 * - 'file' must be a file opened for writing
 * 
 * Postconditions:
 * - All activities are saved to file in ascending order of ID
 * 
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - Writing to file via 'saveActivityToFile()'
 */
void inOrderSaveActivitiesToFile(FILE* file, TreeNode root) {
	if (root != NULL) {
		inOrderSaveActivitiesToFile(file, getLeftNode(root) );
		saveActivityToFile(file, getActivityFromNode(root) );
		inOrderSaveActivitiesToFile(file, getRightNode(root) );
	}
}

/*
 * saveActivitiesFromTreeToFile
 * 
 * Syntactic Specification:
 * int saveActivitiesFromTreeToFile(const char* filename, TreeNode root);
 * 
 * Semantic Specification:
 * Saves all activities from the tree to a file.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - If 'root == NULL' or 'filename != NULL', returns 1 (error)
 * - If unable to open the file, returns 1 (error)
 * - Otherwise, saves all activities and returns 0 (success)
 * 
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - File opening and writing
 * - Output to stdout (informational messages)
 */
int saveActivitiesFromTreeToFile(const char* filename, TreeNode root) {
	if (root == NULL || filename == NULL) return 1;
	
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("Errore nell'apertura del file %s per la scrittura.\n", filename);
		return 1;
	}

	inOrderSaveActivitiesToFile(file, root);

	fclose(file);
	printf("Attività salvate con successo nel file %s\n", filename);
	return 0;
}



/*
 * createNewActivityFromUserInput
 * 
 * Syntactic Specification:
 * Activity createNewActivityFromUserInput();
 * 
 * Semantic Specification:
 * Interacts with the user to create a new activity.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - Asks user for data and create and return the new activity
 * 
 * Effects:
 * - Return a new activity
 * - Allocates memory for the new activity
 * 
 * Side Effects:
 * - User interaction (input/output)
 * - Calls to user input functions
 * - Calls to 'time()' for timestamp
 */
Activity createNewActivityFromUserInput() {
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
	
	time_t insertDate = time(NULL); //now
	
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
	
	//If id=0 then is automatically calculated on container insertion
	return newActivity( 0, activityName, activityDesr, activityCourse, insertDate, expiryDate, completionDate, totalTime, usedTime, priority);
}







/*
 * printInOrder
 * 
 * Syntactic Specification:
 * void printInOrder(TreeNode root);
 * 
 * Semantic Specification:
 * Performs an in-order traversal of the tree printing the activities (print activity on a single line).
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - All activities in the tree are printed in ascending order of ID
 * 
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - Output to stdout via 'printActivityForList()'
 */
void printInOrder(TreeNode root) {
	if (root != NULL) {
		printInOrder( getLeftNode(root) );
		//printActivity(root->activity);
		printActivityForList( getActivityFromNode(root) );
		printInOrder( getRightNode(root) );
	}
}


/*
 * printAllActivities
 * 
 * Syntactic Specification:
 * void printAllActivities(TreeNode root);
 * 
 * Semantic Specification:
 * Prints all activities (list format, one per line) from the tree in ascending order of ID.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - If 'root != NULL', prints all activities with headers
 * 
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - Output to stdout
 */
void printAllActivities(TreeNode root) {
	if (root != NULL) {
		printf("\n=============================\n");
		printf("====== Tutte le attività =====\n");
		printf("==============================\n");
		printf("[NOTA: titolo, descrizione e corso potrebbero essere abbreviati. Vai al dettaglio attività per vedere le info complete]\n");
		printf("[Le attività sono ordinate per id]\n");
		printf("\n====================================================================================================\n");
		printf("[id] Titolo | Descrizione | Corso | Priorità | Data scadenza o data completamento\n");
		printf("====================================================================================================\n\n");

		printInOrder(root);
	}
}




/*
 * printInOrderToFile
 * 
 * Syntactic Specification:
 * void printInOrderToFile(TreeNode root, FILE* file);
 * 
 * Semantic Specification:
 * Recursively prints tree activities to file (list format, one per line) in in-order.
 * 
 * Preconditions:
 * - 'file' must be opened for writing
 * 
 * Postconditions:
 * - All activities are printed to file in ascending order of ID
 * 
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - Writing to file
 */
void printInOrderToFile(TreeNode root, FILE* file) {
	if (root != NULL) {
		printInOrderToFile( getLeftNode(root), file );
		printActivityForListToFile( getActivityFromNode(root), file );
		printInOrderToFile( getRightNode(root), file );
	}
}

/*
 * printAllActivitiesToFile
 * 
 * Syntactic Specification:
 * void printAllActivitiesToFile(TreeNode root, FILE* file);
 * 
 * Semantic Specification:
 * Prints all container activities to file (list format, one per line).
 * 
 * Preconditions:
 * - 'file' must be opened for writing
 * 
 * Postconditions:
 * - If both parameters are valid, prints all activities to file
 * 
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - Writing to file
 */
void printAllActivitiesToFile(TreeNode root, FILE* file) {
	if (root != NULL && file != NULL) {
		printInOrderToFile(root, file);
	}
}




/*
 * printInOrderProgress
 * 
 * Syntactic Specification:
 * void printInOrderProgress(TreeNode root);
 * 
 * Semantic Specification:
 * Recursively prints activity progress from the tree (progress list format with progress, one per line) in in-order.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - Progress of all activities is printed in ascending order of ID
 * 
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - Output to stdout via 'printActivityProgressForList()'
 */
void printInOrderProgress(TreeNode root) {
	if (root != NULL) {
		printInOrderProgress( getLeftNode(root) );
		printActivityProgressForList( getActivityFromNode(root) );
		printInOrderProgress( getRightNode(root) );
	}
}

/*
 * printTreeActivitiesProgress
 * 
 * Syntactic Specification:
 * void printTreeActivitiesProgress(TreeNode root);
 * 
 * Semantic Specification:
 * Prints the progress of all container activities (progress list format, one per line) with headers.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - If 'root != NULL', prints progress of all activities in tree
 * 
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - Output to stdout
 */
void printTreeActivitiesProgress(TreeNode root) {
	if (root != NULL) {
		printf("\n=============================\n");
		printf("=== MONITORAGGIO PROGRESSO ===\n");
		printf("==============================\n");
		printf("[NOTA: titolo, descrizione e corso potrebbero essere abbreviati. Vai al dettaglio attività per vedere le info complete]\n");
		printf("[Le attività sono ordinate per id. Qui NON vengono mostrate le attività completate]\n");
		printf("\n====================================================================================================================================================\n");
		printf("[id] Titolo | Descrizione | Corso | Priorità | Progresso (%%) | Tempo usato (min) | Tempo al completamento (min) | Tempo totale (min) | Data scadenza\n");
		printf("====================================================================================================================================================\n\n");
		
		printInOrderProgress(root);
	}
}


/*
 * printInOrderProgressToFile
 * 
 * Syntactic Specification:
 * void printInOrderProgressToFile(TreeNode root, FILE* file);
 * 
 * Semantic Specification:
 * Recursively prints activity progress to file (progress list format, one per line) in in-order.
 * 
 * Preconditions:
 * - 'file' must be opened for writing
 * 
 * Postconditions:
 * - Progress of all activities is printed to file
 * 
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - Writing to file
 */
void printInOrderProgressToFile(TreeNode root, FILE* file)  {
	if (root != NULL) {
		printInOrderProgressToFile( getLeftNode(root), file );
		printActivityProgressForListToFile( getActivityFromNode(root), file);
		printInOrderProgressToFile( getRightNode(root), file);
	}
}

/*
 * printTreeActivitiesProgressToFile
 * 
 * Syntactic Specification:
 * void printTreeActivitiesProgressToFile(TreeNode root, FILE* file);
 * 
 * Semantic Specification:
 * Prints the progress of all container activities to file (progress list format, one per line).
 * 
 * Preconditions:
 * - 'file' must be opened for writing
 * 
 * Postconditions:
 * - If both parameters are valid, prints progress with header
 * 
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - Writing to file
 */
void printTreeActivitiesProgressToFile(TreeNode root, FILE* file) {
	if (root != NULL && file != NULL) {
		fprintf(file, "=== MONITORAGGIO PROGRESSO ===\n");
		printInOrderProgressToFile(root, file);
	}
}












/*
 * buildInOrderSupportListsForActivitiesReport
 * 
 * Syntactic Specification:
 * void buildInOrderSupportListsForActivitiesReport(Node* root, 
 *     ActivitiesContainerSupportList completedList,
 *     ActivitiesContainerSupportList ongoingList, 
 *     ActivitiesContainerSupportList expiredList,
 *     ActivitiesContainerSupportList yetToBeginList, 
 *     time_t beginDate, time_t nowDate);
 * 
 * Semantic Specification:
 * Builds support lists by categorizing activities by status in a given period.
 * 
 * Preconditions:
 * - All support lists must be initialized
 * - 'beginDate <= nowDate'
 * 
 * Postconditions:
 * - Activities are categorized based on their status:
 *   - 'completedList': activities completed in the specified period
 *   - 'ongoingList': ongoing activities
 *   - 'expiredList': expired activities (no completed activities here)
 *   - 'yetToBeginList': activities not yet started
 * 
 * Effects:
 * - Modifies support lists by adding references to activities
 * 
 * Side Effects:
 * - Calls to activity status checking functions
 */
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


/*
 * printTreeActivitiesReport
 * 
 * Syntactic Specification:
 * void printTreeActivitiesReport(TreeNode root);
 * 
 * Semantic Specification:
 * Generates and prints a detailed report of activities categorized by status and period.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - If 'root' is valid, prints a complete report with categorized activities
 * - Interacts with user to define the report period
 * 
 * Effects:
 * - Allocates and deallocates temporary support lists
 * 
 * Side Effects:
 * - User interaction (input/output)
 * - Output to stdout
 * - Calls to time management functions
 */
void printTreeActivitiesReport(TreeNode root) {
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

/*
 * printTreeActivitiesReportToFile
 * 
 * Syntactic Specification:
 * void printTreeActivitiesReportToFile(TreeNode root, time_t beginDate, FILE* file);
 * 
 * Semantic Specification:
 * Prints an activity report to file for a specified period.
 * 
 * Preconditions:
 * - 'file' must be opened for writing
 * - 'beginDate >= 0'
 * 
 * Postconditions:
 * - If all parameters are valid, prints the report to file
 * 
 * Effects:
 * - Allocates and deallocates temporary support lists
 * 
 * Side Effects:
 * - Writing to file
 */
void printTreeActivitiesReportToFile(TreeNode root, time_t beginDate, FILE* file) {
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



