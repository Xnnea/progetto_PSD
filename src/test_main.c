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
	//deleteActivityContainer(container);
	if (saveResult != 0) return 1;
	int compareResult = compareFiles("tc_1_output.txt", "tc_1_oracle.txt");
	return (compareResult == 0) ? 0 : 1;
}

int main() {
	int fileError = 0;
	FILE* fileWithTestsResult = fopen(TESTS_RESULTS_FILENAME, "w");
	if (fileWithTestsResult == NULL) {
		printf("Errore nell'apertura del file %s per la scrittura.\n I risultati dei test verranno mostrati solo a video.\n", TESTS_RESULTS_FILENAME);
		fileError = 1;
	}
	
	char* okText = "PASSED";
	char* errorText = "ERROR";
	
	printf("Eseguo TC_1...\n");
	int tc_1_result = tc_1();
	printf("TC_1: %s\n",  (tc_1_result == 0) ? okText : errorText);
	if (fileError == 0) {
		fprintf(fileWithTestsResult, "TC_1: %s\n", (tc_1_result == 0) ? okText : errorText);
	}
	
	if (fileError == 0) {
		printf("Puoi trovare i risultati di questi test anche nel file %s\n", TESTS_RESULTS_FILENAME);
		fclose(fileWithTestsResult);
	}
}




