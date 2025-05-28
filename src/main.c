#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "activities_container.h"
#include "activities_container_helper.h"


/*
 * displayStartMenu
 * 
 * Syntactic Specification:
 * void displayStartMenu();
 * 
 * Semantic Specification:
 * Displays the initial menu of the application with available options for program startup.
 * 
 * Preconditions:
 * - No particular preconditions
 * 
 * Postconditions:
 * - The initial menu has been printed to standard output
 * - The cursor is positioned after the choice request
 * 
 * Effects:
 * - Prints the formatted initial menu with options:
 *   - Load activities from file
 *   - Create new empty container
 *   - Exit program
 * 
 * Side Effects:
 * - Output to stdout
 */
void displayStartMenu() {
	printf("\n=========================\n");
	printf("====[ MENU INIZIALE ]====\n");
	printf("=========================\n");
	printf("1. Carica le attività da file\n");
	printf("2. Crea un nuovo contenitore (vuoto) di attività\n");
	printf("0. Esci\n");
	printf("Scelta: ");
}

/*
 * displayMainMenu
 * 
 * Syntactic Specification:
 * void displayMainMenu();
 * 
 * Semantic Specification:
 * Displays the main menu of the application with all available operations for activity management.
 * 
 * Preconditions:
 * - No particular preconditions
 * 
 * Postconditions:
 * - The main menu has been printed to standard output
 * - The cursor is positioned after the choice request
 * 
 * Effects:
 * - Prints the formatted main menu with options:
 *   - View activities
 *   - Add/Delete activities
 *   - View reports and details
 *   - Save to file
 *   - Exit
 * 
 * Side Effects:
 * - Output to stdout
 */
void displayMainMenu() {
	printf("\n===========================\n");
	printf("====[ MENU PRINCIPALE ]====\n");
	printf("===========================\n");
	printf("1. Visualizza tutte le attività\n");
	printf("2. Aggiungi nuova attività\n");
	printf("3. Elimina attività\n");
	printf("4. Visualizza avanzamento attività\n");
	printf("5. Visualizza report settimanale\n");
	printf("6. Visualizza dettaglio attività\n");
	printf("7. Salva su file\n");
	printf("0. Esci\n");
	printf("Scelta: ");
}


/*
 * handleStartMenu
 * 
 * Syntactic Specification:
 * ActivitiesContainer handleStartMenu();
 * 
 * Semantic Specification:
 * Handles interaction with the initial menu, acquires user choice and initializes
 * the activities container accordingly.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - Returns a valid ActivitiesContainer if user chooses option 1 or 2
 * - Returns NULL if user chooses to exit (option 0)
 * - Memory allocated for userFile is freed if necessary
 * 
 * Effects:
 * - Option 0: Terminates execution
 * - Option 1: Loads activities from file (default or user-specified)
 * - Option 2: Creates a new empty container
 * - Default: Confirmation message and exit
 * 
 * Side Effects:
 * - Input from stdin
 * - Output to stdout
 * - Dynamic memory allocation/deallocation
 * - Possible file reading
 */
ActivitiesContainer handleStartMenu() {
	displayStartMenu();
	int choice = getChoice(2);

	ActivitiesContainer container = NULL;

	switch (choice) {
		case 0:
			printf("Uscita in corso...\n");
			break;

		case 1: {
			char* userFile = getInfoFromUser("Nome file da caricare (lascia vuoto per default): ");
			int numActivities = 0;
			if (userFile == NULL) {
				container = readActivitiesFromFile(DEFAULT_ACTIVITIES_FILE, &numActivities);
			} else {
				container = readActivitiesFromFile(userFile, &numActivities);
				free(userFile);
			}
			break;
		}

		case 2: {
			container = newActivityContainer();
			break;
      }

		default:
			printf("Scelta non gestita. Esco.\n");
			break;
	}
	
	return container;
}


/*
 * handleMainMenu
 * 
 * Syntactic Specification:
 * int handleMainMenu(ActivitiesContainer container);
 * 
 * Semantic Specification:
 * Handles interaction with the main menu, executes the operation chosen by the user
 * on the activities container.
 * 
 * Preconditions:
 * - container != NULL
 * - container must be a valid activities container
 * 
 * Postconditions:
 * - Returns -1 if user chooses to exit (option 0)
 * - Returns the chosen option number in other cases
 * - Container may be modified by operations 2 and 3
 * - If option 0 is confirmed, container is deallocated and program terminates
 * 
 * Effects:
 * - Option 0: Requests confirmation and exits deallocating memory
 * - Option 1: Displays all activities
 * - Option 2: Adds new activity (may modify container)
 * - Option 3: Deletes specified activity (may modify container)
 * - Option 4: Displays activity progress
 * - Option 5: Displays weekly report
 * - Option 6: Displays details of a specific activity
 * - Option 7: Saves activities to file
 * 
 * Side Effects:
 * - Input from stdin
 * - Output to stdout
 * - Possible modification of activities container
 * - Possible dynamic memory allocation/deallocation
 * - Possible file writing (option 7)
 * - Possible complete memory deallocation (option 0)
 */
int handleMainMenu(ActivitiesContainer container) {
	displayMainMenu();
	int choice = getChoice(7);
	
	switch (choice) {
		case 0: { // Menu: '0. Esci'
			int isConfirmed = getConfirmMenuChoice("i dati non salvati verranno persi.\nVuoi uscire dal programma?");
			if (isConfirmed == 1) {
				printf("Uscita in corso...\n");
				deleteActivityContainer(container);
				return -1;
			}
			break;
		}

		case 1: { // Menu: '1. Visualizza tutte le attività'
			printActivities(container);
			break;
		}

		case 2: { // Menu: '2. Aggiungi nuova attività'
			//This action can modify the tree...
			addNewActivityToContainer(container);
			break;
      }

		case 3: {// Menu: '3. Elimina attività'
			int maxId = getNextId(container);
			if (maxId > 0) {
				printf("\nInserisci l'id dell'attività da ELIMINARE (numero < %d): ", maxId);
				int id = getChoice(maxId);
				int isConfirmed = getConfirmMenuChoice("Sei sicuro di voler eliminare questa attività?");
				if (isConfirmed == 1) {
					removeActivity(container, id);
					printf("\nAttività eliminata.\n");
				}
			} else {
				printf("\nAl momento non puoi eliminare attività.");
			}
			break;
		}

		case 4: { // Menu: '4. Visualizza avanzamento attività'
			printActivitiesProgress(container);
			break;
		}

		case 5: { // Menu: '5. Visualizza report settimanale'
			printActivitiesReport(container);
			break;
		}

		case 6: { // Menu: '6. Visualizza dettaglio attività'
			int maxId = getNextId(container);
			if (maxId > 0) {
				printf("\nInserisci l'id dell'attività (numero < %d): ", maxId);
				int id = getChoice(maxId);
				printActivityWithId(container, id);
			} else {
				printf("\nAl momento non puoi cercare attività.");
			}
			break;
		}

		case 7: { // Menu: '7. Salva su file'
			char* userFile = getInfoFromUser("Nome file per salvataggio (se esiste sarà sovrascritto - lascia vuoto per default): ");
			int saveResult = 0;
			if (userFile == NULL) {
				saveResult = saveActivitiesToFile(DEFAULT_ACTIVITIES_FILE, container);
			} else {
				saveResult = saveActivitiesToFile(userFile, container);
				free(userFile);
			}
			
			break;
		}

		default:
			printf("Scelta non gestita.\n");
			break;
	}
	
	return choice;
}
	
int main() {
	ActivitiesContainer activities =  handleStartMenu();
	
	if (activities != NULL) {
		int userChoice = 0;
		while( userChoice >= 0) {
			userChoice = handleMainMenu(activities);
		}
		
		//ActivitiesContainer was deleted on exit choice...
		activities = NULL;
	}
}




