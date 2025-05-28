#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "activity_helper.h"
#include "activities_container.h"
#include "activities_container_helper.h"

#define TESTS_RESULTS_FILENAME "TESTS_RESULT.txt" 


/*
 * compareFiles
 * 
 * Syntactic Specification:
 * int compareFiles(const char* filenameA, const char* filenameB);
 * 
 * Semantic Specification:
 * Compares two text files line by line to determine if they are identical.
 * 
 * Preconditions:
 * - 'filenameA' and 'filenameB' must be valid pointers to non-NULL strings
 * - The specified files must exist and be readable
 * 
 * Postconditions:
 * - Returns 0 if the files are identical line by line
 * - Returns 1 if the files differ or if an error occurs
 * 
 * Effects:
 * - Opens both files in read mode
 * - Reads and compares each line of the two files
 * - Closes the files at the end of the operation
 * 
 * Side Effects:
 * - Prints error messages to stdout in case of file opening problems
 * - Dynamically allocates and deallocates memory for each line read
 * - Modifies file position pointers during reading
 */
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


/*
 * tc_1
 * 
 * Syntactic Specification:
 * int tc_1();
 * 
 * Semantic Specification:
 * Test case 1: verifies the correct execution of file loading, data creation, and saving operations.
 * 
 * Preconditions:
 * - The file "tc_1.txt" must exist and be accessible
 * - The file "tc_1_oracle.txt" must exist for comparison
 * - The activity container functions must be implemented
 * 
 * Postconditions:
 * - Returns 0 if the test passes (output file equals oracle)
 * - Returns 1 if the test fails
 * 
 * Effects:
 * - Loads activities from the test file
 * - Saves activities to an output file
 * - Compares the output with the oracle file
 * 
 * Side Effects:
 * - Creates the file "tc_1_output.txt"
 * - Allocates and deallocates memory for the activity container
 * - Modifies the filesystem by creating temporary files
 */
int tc_1() {
	int numActivities = 0;
	ActivitiesContainer container = readActivitiesFromFile("tc_1.txt", &numActivities);
	int saveResult = saveActivitiesToFile("tc_1_output.txt", container);
	deleteActivityContainer(container);
	if (saveResult != 0) return 1;
	int compareResult = compareFiles("tc_1_output.txt", "tc_1_oracle.txt");
	return (compareResult == 0) ? 0 : 1;
}

/*
 * tc_2
 * 
 * Syntactic Specification:
 * int tc_2();
 * 
 * Semantic Specification:
 * Test case 2: loads activities from file and prints and tests details of a specific activity.
 * 
 * Preconditions:
 * - The file "tc_2.txt" must exist and be accessible
 * - The file "tc_2_oracle.txt" must exist for comparison
 * - An activity with ID 1 must exist in the input file
 * 
 * Postconditions:
 * - Returns 0 if the test passes
 * - Returns 1 if the test fails or the activity is not found
 * 
 * Effects:
 * - Loads the activity container
 * - Retrieves the activity with ID 1
 * - Prints activity details to file
 * 
 * Side Effects:
 * - Creates the file "tc_2_output.txt"
 * - Allocates and deallocates memory for the container
 * - Opens and closes files for writing
 */
int tc_2() {
	int numActivities = 0;
	ActivitiesContainer container = readActivitiesFromFile("tc_2.txt", &numActivities);
	Activity activity = getActivityWithId(container, 1);
	if (activity == NULL) return 1; //KO
	FILE* file = fopen("tc_2_output.txt", "w");
	if (file == NULL) return 1; //KO
	printActivityToFile(activity, file);
	fclose(file);
	deleteActivityContainer(container);
	int compareResult = compareFiles("tc_2_output.txt", "tc_2_oracle.txt");
	return (compareResult == 0) ? 0 : 1;
}


/*
 * tc_3_to_11
 * 
 * Syntactic Specification:
 * int tc_3_to_11(int numTest, char* fileIn, char* fileOut, char* fileOracle);
 * 
 * Semantic Specification:
 * Generic function for test cases 3 to 11: loads an activity, modifies a specific field, and verifies output.
 * 
 * TC 3 modifies and tests: activity name.
 * TC 4 modifies and tests: activity description. 
 * TC 5 modifies and tests: activity course. 
 * TC 6 modifies and tests:  activity insertion date. 
 * TC 7 modifies and tests: activity expiry date. 
 * TC 8 modifies and tests: activity completion date. 
 * TC 9 modifies and tests: activity total time. 
 * TC 10 modifies and tests: activity used time. 
 * TC 11 modifies and tests: activity priority. 
 *
 * Preconditions:
 * - 'numTest' must be a value between 3 and 11
 * - 'fileIn', 'fileOut', and 'fileOracle' must be pointers to valid strings
 * - The input file must exist and contain an activity with ID 1
 * - The oracle file must exist for comparison
 * 
 * Postconditions:
 * - Returns 0 if the test passes
 * - Returns 1 if the test fails or errors occur
 * 
 * Effects:
 * - Loads the activity from the input file
 * - Modifies the specific field of the activity based on the test number
 * - Saves the modified activity to the output file
 * - Compares the output with the oracle file
 * 
 * Side Effects:
 * - Creates temporary output files
 * - Modifies the internal state of the Activity object
 * - Prints error messages for unsupported tests
 * - Allocates and deallocates memory for the container
 */
int tc_3_to_11(int numTest, char* fileIn, char* fileOut, char* fileOracle) {
	int numActivities = 0;
	ActivitiesContainer container = readActivitiesFromFile(fileIn, &numActivities);
	Activity activity = getActivityWithId(container, 1);
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


/*
 * tc_12
 * 
 * Syntactic Specification:
 * int tc_12();
 * 
 * Semantic Specification:
 * Test case 12: loads activities from file and prints and tests the list of all activities.
 * 
 * Preconditions:
 * - The file "tc_12.txt" must exist and be accessible
 * - The file "tc_12_oracle.txt" must exist for comparison
 * 
 * Postconditions:
 * - Returns 0 if the test passes
 * - Returns 1 if the test fails
 * 
 * Effects:
 * - Loads all activities from the file
 * - Prints the complete list of activities to file
 * 
 * Side Effects:
 * - Creates the file "tc_12_output.txt"
 * - Allocates and deallocates memory for the container
 * - Opens and closes files for writing
 */
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

/*
 * tc_13
 * 
 * Syntactic Specification:
 * int tc_13();
 * 
 * Semantic Specification:
 * Test case 13: loads activities from file and prints and test the progress list.
 * 
 * Preconditions:
 * - The file "tc_13.txt" must exist and be accessible
 * - The file "tc_13_oracle.txt" must exist for comparison
 * 
 * Postconditions:
 * - Returns 0 if the test passes
 * - Returns 1 if the test fails
 * 
 * Effects:
 * - Loads activities from the file
 * - Generates and prints the progress report
 * 
 * Side Effects:
 * - Creates the file "tc_13_output.txt"
 * - Allocates and deallocates memory for the container
 * - Opens and closes files for writing
 */
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

/*
 * tc_14
 * 
 * Syntactic Specification:
 * int tc_14();
 * 
 * Semantic Specification:
 * Test case 14: loads activities from file and prints and tests the weekly report.
 *               This also includes: categorization of activities into sections (completed, ongoing, etc.) and sorting activities.
 * 
 * Preconditions:
 * - The file "tc_14.txt" must exist and be accessible
 * - The file "tc_14_oracle.txt" must exist for comparison
 * 
 * Postconditions:
 * - Returns 0 if the test passes
 * - Returns 1 if the test fails
 * 
 * Effects:
 * - Loads activities from the file
 * - Generates the weekly report for the specified timestamp (1746613562)
 * 
 * Side Effects:
 * - Creates the file "tc_14_output.txt"
 * - Allocates and deallocates memory for the container
 * - Opens and closes files for writing
 */
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

/*
 * tc_15
 * 
 * Syntactic Specification:
 * int tc_15();
 * 
 * Semantic Specification:
 * Test case 15: verifies the correct execution of file loading, data creation, and saving operations of multiple activities.
 * 
 * Preconditions:
 * - The file "tc_15.txt" must exist and be accessible
 * - The file "tc_15_oracle.txt" must exist for comparison
 * - The activity container functions must be implemented
 * 
 * Postconditions:
 * - Returns 0 if the test passes (output file equals oracle)
 * - Returns 1 if the test fails
 * 
 * Effects:
 * - Loads activities from the test file
 * - Saves activities to an output file
 * - Compares the output with the oracle file
 * 
 * Side Effects:
 * - Creates the file "tc_15_output.txt"
 * - Allocates and deallocates memory for the activity container
 * - Modifies the filesystem by creating temporary files
 */
int tc_15() {
	int numActivities = 0;
	ActivitiesContainer container = readActivitiesFromFile("tc_15.txt", &numActivities);
	int saveResult = saveActivitiesToFile("tc_15_output.txt", container);
	deleteActivityContainer(container);
	if (saveResult != 0) return 1;
	int compareResult = compareFiles("tc_15_output.txt", "tc_15_oracle.txt");
	return (compareResult == 0) ? 0 : 1;
}

/*
 * tc_16
 * 
 * Syntactic Specification:
 * int tc_16();
 * 
 * Semantic Specification:
 * Test case 16: loads activities from file, change activities data and prints and tests the weekly report.
 *               This also includes: categorization of activities into sections (completed, ongoing, etc.) and sorting activities.
 * 
 * Preconditions:
 * - The file "tc_16.txt" must exist and be accessible
 * - The file "tc_16_oracle.txt" must exist for comparison
 * 
 * Postconditions:
 * - Returns 0 if the test passes
 * - Returns 1 if the test fails
 * 
 * Effects:
 * - Loads activities from the file
 * - Generates the weekly report for the specified timestamp (1746613562)
 * 
 * Side Effects:
 * - Creates the file "tc_16_output.txt"
 * - Allocates and deallocates memory for the container
 * - Opens and closes files for writing
 */
int tc_16() {
	int numActivities = 0;
	ActivitiesContainer container = readActivitiesFromFile("tc_16.txt", &numActivities);
	Activity activity = getActivityWithId(container, 9);
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


/*
 * execTest
 * 
 * Syntactic Specification:
 * void execTest(int numTest, FILE* fileWithTestsResult);
 * 
 * Semantic Specification:
 * Executes a specific test and records the results both to console and file.
 * 
 * Preconditions:
 * - 'numTest' must be a value between 1 and 16
 * - 'fileWithTestsResult' can be NULL or a valid file pointer opened for writing
 * 
 * Postconditions:
 * - The specified test is executed
 * - Results are printed to console
 * - If the file is valid, results are also written to file
 * 
 * Effects:
 * - Executes the test case corresponding to the specified number
 * - Prints the test result
 * 
 * Side Effects:
 * - Prints messages to stdout
 * - Writes to file if the pointer is valid
 * - May print error messages for unsupported tests
 */
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


/*
 * main
 * 
 * Syntactic Specification:
 * int main();
 * 
 * Semantic Specification:
 * Main function that coordinates the execution of all test cases.
 * 
 * Preconditions:
 * - All test and oracle files must be present in the current directory
 * - The system must have write permissions to create output files
 * 
 * Postconditions:
 * - Returns 0 (implicit) at the end of execution
 * - All tests are executed in sequence
 * 
 * Effects:
 * - Opens a file to save test results
 * - Executes all test cases from 1 to 14
 * - Provides user feedback on results
 * 
 * Side Effects:
 * - Creates the file "TESTS_RESULT.txt" if possible
 * - Prints informational and error messages to stdout
 * - Opens and closes files for writing results
 * - Executes a loop that modifies system state through various tests
 */
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




