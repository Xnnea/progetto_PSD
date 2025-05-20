#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "activities_container.h"




void displayStartMenu() {
	printf("\n=========================\n");
	printf("====[ MENU INIZIALE ]====\n");
	printf("=========================\n");
	printf("1. Carica le attività da file\n");
	printf("2. Crea un nuovo contenitore (vuoto) di attività\n");
	printf("0. Esci\n");
	printf("Scelta: ");
}

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

void displayConfirmMenu(const char* confirmInfo) {
	printf("\n=========================\n");
	if (confirmInfo != NULL) printf("Attenzione: %s\n", confirmInfo);
	printf("1. Continua\n");
	printf("0. Annulla\n");
	printf("Scelta: ");
}


int getConfirmMenuChoice(const char* confirmInfo) {
	displayConfirmMenu(confirmInfo);
	return getChoice(1);
}

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
			container = newActivityContainer();;
			break;
      }

		default:
			printf("Scelta non gestita. Esco.\n");
			break;
	}
	
	return container;
}

int handleMainMenu(ActivitiesContainer * container) {
	displayMainMenu();
	int choice = getChoice(7);
	
	switch (choice) {
		case 0: { // 0. Esci
			int isConfirmed = getConfirmMenuChoice("i dati non salvati verranno persi.\nVuoi uscire dal programma?");
			if (isConfirmed == 1) {
				printf("Uscita in corso...\n");
				deleteActivityContainer(*container);
				return -1;
			}
			break;
		}

		case 1: { // 1. Visualizza tutte le attività
			printActivities(*container);
			break;
		}

		case 2: { // 2. Aggiungi nuova attività
			//This action can modify the tree...
			*container = addNewActivityToContainer(*container);
			break;
      }

		case 3: {// 3. Elimina attività
			int maxId = getNextId(*container);
			if (maxId > 0) {
				printf("\nInserisci l'id dell'attività da ELIMINARE (numero < %d): ", maxId);
				int id = getChoice(maxId);
				int isConfirmed = getConfirmMenuChoice("Sei sicuro di voler eliminare questa attività?");
				if (isConfirmed == 1) {
					*container = removeActivity(*container, id);
					printf("\nAttività eliminata.\n");
				}
			} else {
				printf("\nAl momento non puoi eliminare attività.");
			}
			break;
		}

		case 4: { // 4. Visualizza avanzamento attività
			printActivitiesProgress(*container);
			break;
		}

		case 5: { //5. Visualizza report settimanale
			//TODO
			break;
		}

		case 6: { //6. Visualizza dettaglio attività
			int maxId = getNextId(*container);
			if (maxId > 0) {
				printf("\nInserisci l'id dell'attività (numero < %d): ", maxId);
				int id = getChoice(maxId);
				printActivityWithId(*container, id);
			} else {
				printf("\nAl momento non puoi cercare attività.");
			}
			break;
		}

		case 7: { //7. Salva su file
			char* userFile = getInfoFromUser("Nome file per salvataggio (se esiste sarà sovrascritto - lascia vuoto per default): ");
			int saveResult = 0;
			if (userFile == NULL) {
				saveResult = saveActivitiesToFile(DEFAULT_ACTIVITIES_FILE, *container);
			} else {
				saveResult = saveActivitiesToFile(userFile, *container);
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
			userChoice = handleMainMenu(&activities);
		}
		
		//ActivitiesContainer was deleted on exit choice...
		activities = NULL;
	}
	
	//ActivitiesContainer activities = buildActivities();
	//printActivities(activities);
	//deleteActivityContainer(activities);
}




