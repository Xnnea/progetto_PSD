#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "activities_container.h"

#define TESTS_RESULTS_FILENAME "TESTS_RESULT.txt" 

// Function to compare 2 text files.
// Returns 0 if file are equal (line by line), 1 otherwise
int compareFiles(const char* filenameA, const char* filenameB) {
	FILE* fileA = fopen(filenameA, "r");
	if (fileA == NULL) {
		printf("Errore apertura file %s.\n", filenameA);
		return 1;
	}

	FILE* fileB = fopen(filenameB, "r");
	if (fileB == NULL) {
		printf("Errore apertura file %s.\n", filenameB);
		fclose(fileA);
		return 1;
	}
	
	int result = 0; 
	
	while (!feof(fileA) && !feof(fileB)) {  
		char* lineA = readLine(fileA);
		char* lineB = readLine(fileB);
		
		if (lineA == NULL && lineB == NULL) break;
		
		if (lineA == NULL && lineB != NULL) {
			result = 1;
			free(lineB);
			break;
		} else if (lineA != NULL && lineB == NULL) {
			result = 1;
			free(lineA);
			break;
		}
		
		if ( strcmp(lineA, lineB) != 0 ) {
			result = 1;
			free(lineA);
			free(lineB);
			break;
		}
		
		free(lineA);
		free(lineB);
	}
	
	if (result == 0 && (!feof(fileA) || !feof(fileB)) ) {
		result = 1;
	}
	
	fclose(fileA);
	fclose(fileB);
	return result;
}


// TC_1: tests the correct execution of load from file, data creation and save operations. 
// 0 = OK, 1 = KO
int tc_1() {
	int numActivities = 0;
	ActivitiesContainer container = readActivitiesFromFile("tc_1.txt", &numActivities);
	int saveResult = saveActivitiesToFile("tc_1_output.txt", container);
	deleteActivityContainer(container);
	if (saveResult != 0) return 1;
	int compareResult = compareFiles("tc_1_output.txt", "tc_1_oracle.txt");
	return (compareResult == 0) ? 0 : 1;
}

// TC_2: load activities froma file and print an activity detail. 
// 0 = OK, 1 = KO
int tc_2() {
	int numActivities = 0;
	ActivitiesContainer container = readActivitiesFromFile("tc_2.txt", &numActivities);
	Activity activity = getActivityWithIdForTest(container, 1);
	if (activity == NULL) return 1; //KO
	FILE* file = fopen("tc_2_output.txt", "w");
	if (file == NULL) return 1; //KO
	printActivityToFile(activity, file);
	fclose(file);
	deleteActivityContainer(container);
	int compareResult = compareFiles("tc_2_output.txt", "tc_2_oracle.txt");
	return (compareResult == 0) ? 0 : 1;
}

// TC 3: load an activity, change activity name, print the new activity detail.
// TC 4: load an activity, change activity description, print the new activity detail. 
// TC 5: load an activity, change activity course, print the new activity detail. 
// TC 6: load an activity, change activity insertion date, print the new activity detail. 
// TC 7: load an activity, change activity expiry date, print the new activity detail. 
// TC 8: load an activity, change activity completion date, print the new activity detail. 
// TC 9: load an activity, change activity total time, print the new activity detail. 
// TC 10: load an activity, change activity used time, print the new activity detail. 
// TC 11: load an activity, change activity priority, print the new activity detail. 
// 0 = OK, 1 = KO
int tc_3_to_11(int numTest, char* fileIn, char* fileOut, char* fileOracle) {
	int numActivities = 0;
	ActivitiesContainer container = readActivitiesFromFile(fileIn, &numActivities);
	Activity activity = getActivityWithIdForTest(container, 1);
	if (activity == NULL) return 1; //KO

	switch (numTest) {

		case 3:	setActivityName(activity, "NOME CAMBIATO");
					break;
		case 4:	setActivityDescr(activity, "DESCRIZIONE CAMBIATA");
					break;
		case 5:	setActivityCourse(activity, "CORSO CAMBIATO");
					break;
		case 6:	setActivityInsertDate(activity, 1742613000);
					break;
		case 7:	setActivityExpiryDate(activity, 1749613000);
					break;
		case 8:	setActivityCompletionDate(activity, 1752613000);
					break;
		case 9:	setActivityTotalTime(activity, 12345);
					break;
		case 10:	setActivityUsedTime(activity, 333);
					break;
		case 11:	setActivityPriority(activity, 2);
					break;
		default:	printf("TC_%d non può essere eseguito.\n", numTest);
					return 1;
	}
	
	FILE* file = fopen(fileOut, "w");
	if (file == NULL) return 1; //KO
	printActivityToFile(activity, file);
	fclose(file);
	deleteActivityContainer(container);
	int compareResult = compareFiles(fileOut, fileOracle);
	return (compareResult == 0) ? 0 : 1;
}

// TC_12: load activities from file and print a list of all activities. 
// 0 = OK, 1 = KO
int tc_12() {
	int numActivities = 0;
	ActivitiesContainer container = readActivitiesFromFile("tc_12.txt", &numActivities);
	FILE* file = fopen("tc_12_output.txt", "w");
	if (file == NULL) return 1; //KO
	printActivitiesToFile(container, file);
	fclose(file);
	deleteActivityContainer(container);
	int compareResult = compareFiles("tc_12_output.txt", "tc_12_oracle.txt");
	return (compareResult == 0) ? 0 : 1;
}

// TC_13: load activities from file and print the progress list. 
// 0 = OK, 1 = KO
int tc_13() {
	int numActivities = 0;
	ActivitiesContainer container = readActivitiesFromFile("tc_13.txt", &numActivities);
	FILE* file = fopen("tc_13_output.txt", "w");
	if (file == NULL) return 1; //KO
	printActivitiesProgressToFile(container, file);
	fclose(file);
	deleteActivityContainer(container);
	int compareResult = compareFiles("tc_13_output.txt", "tc_13_oracle.txt");
	return (compareResult == 0) ? 0 : 1;
}

// TC_14: load activities from file and print the weekly report list. 
// 0 = OK, 1 = KO
int tc_14() {
	int numActivities = 0;
	ActivitiesContainer container = readActivitiesFromFile("tc_14.txt", &numActivities);
	FILE* file = fopen("tc_14_output.txt", "w");
	if (file == NULL) return 1; //KO
	printActivitiesReportToFile(container, 1746613562, file);
	fclose(file);
	deleteActivityContainer(container);
	int compareResult = compareFiles("tc_14_output.txt", "tc_14_oracle.txt");
	return (compareResult == 0) ? 0 : 1;
}

// TC_15: same as TC_1 but with multiple activities.
// 0 = OK, 1 = KO
int tc_15() {
	int numActivities = 0;
	ActivitiesContainer container = readActivitiesFromFile("tc_15.txt", &numActivities);
	int saveResult = saveActivitiesToFile("tc_15_output.txt", container);
	deleteActivityContainer(container);
	if (saveResult != 0) return 1;
	int compareResult = compareFiles("tc_15_output.txt", "tc_15_oracle.txt");
	return (compareResult == 0) ? 0 : 1;
}

// TC_16: same as 14 but with activity change after loading. 
// 0 = OK, 1 = KO
int tc_16() {
	int numActivities = 0;
	ActivitiesContainer container = readActivitiesFromFile("tc_16.txt", &numActivities);
	Activity activity = getActivityWithIdForTest(container, 9);
	if (activity == NULL) return 1; //KO
	setActivityUsedTime(activity, 100);
	FILE* file = fopen("tc_16_output.txt", "w");
	if (file == NULL) return 1; //KO
	printActivitiesReportToFile(container, 1746613562, file);
	fclose(file);
	deleteActivityContainer(container);
	int compareResult = compareFiles("tc_16_output.txt", "tc_16_oracle.txt");
	return (compareResult == 0) ? 0 : 1;
}

void execTest(int numTest, FILE* fileWithTestsResult) {
	printf("Eseguo TC_%d...\n", numTest);
	int tc_result = 1;

	char* okText = "SUPERATO";
	char* errorText = "FALLITO";
	
	switch (numTest) {
		case 1:	tc_result = tc_1();
					break;
		case 2:	tc_result = tc_2();
					break;
		case 3:	tc_result = tc_3_to_11(3, "tc_3.txt", "tc_3_output.txt","tc_3_oracle.txt");
					break;
		case 4:	tc_result = tc_3_to_11(4, "tc_4.txt", "tc_4_output.txt","tc_4_oracle.txt");
					break;
		case 5:	tc_result = tc_3_to_11(5, "tc_5.txt", "tc_5_output.txt","tc_5_oracle.txt");
					break;
		case 6:	tc_result = tc_3_to_11(6, "tc_6.txt", "tc_6_output.txt","tc_6_oracle.txt");
					break;
		case 7:	tc_result = tc_3_to_11(7, "tc_7.txt", "tc_7_output.txt","tc_7_oracle.txt");
					break;
		case 8:	tc_result = tc_3_to_11(8, "tc_8.txt", "tc_8_output.txt","tc_8_oracle.txt");
					break;
		case 9:	tc_result = tc_3_to_11(9, "tc_9.txt", "tc_9_output.txt","tc_9_oracle.txt");
					break;
		case 10:	tc_result = tc_3_to_11(10, "tc_10.txt", "tc_10_output.txt","tc_10_oracle.txt");
					break;
		case 11:	tc_result = tc_3_to_11(11, "tc_11.txt", "tc_11_output.txt","tc_11_oracle.txt");
					break;
		case 12:	tc_result = tc_12();
					break;
		case 13:	tc_result = tc_13();
					break;
		case 14:	tc_result = tc_14();
					break;
		case 15:	tc_result = tc_15();
					break;
		case 16:	tc_result = tc_16();
					break;
		default:	printf("TC_%d non può essere eseguito.\n", numTest);
					return;
	}
	
	printf("TC_%d: %s\n", numTest,  (tc_result == 0) ? okText : errorText);
	if (fileWithTestsResult != NULL) {
		fprintf(fileWithTestsResult, "TC_%d: %s\n", numTest, (tc_result == 0) ? okText : errorText);
	}
}

int main() {
	int fileError = 0;
	FILE* fileWithTestsResult = fopen(TESTS_RESULTS_FILENAME, "w");
	if (fileWithTestsResult == NULL) {
		printf("Errore nell'apertura del file %s per la scrittura.\n I risultati dei test verranno mostrati solo a video.\n", TESTS_RESULTS_FILENAME);
		fileError = 1;
	}
	
	printf("\n");
	
	for (int i=1; i<=16; i++) {
		execTest(i, fileWithTestsResult);
		printf("\n");
	}
	
	if (fileError == 0) {
		printf("Puoi trovare i risultati di questi test anche nel file %s\n", TESTS_RESULTS_FILENAME);
		fclose(fileWithTestsResult);
	}
}




