#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "activities_container.h"
//#include "activities_container_avl.h"




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
	printf("6. Salva su file\n");
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

int getChoice(int limit) {
	int choice = -1;
	char buffer[10];
    
	while (choice < 0 || choice > limit) {
        
		if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
			if (sscanf(buffer, "%d", &choice) != 1) {
				choice = -1;
			}
		}
      
      if (choice < 0 || choice > limit) {
      	printf("Scelta non valida. Riprova.\n");
      }
   }
   
   return choice;
}

char* getInfoFromUser() {
	char* info = NULL;
	char buffer[1024]; // input buffer
	
	if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
		buffer[strcspn(buffer, "\n")] = 0;  // remove newline, overwrite with string terminator
		if (strlen(buffer) > 0) {
			info = copyString(buffer);
		}
	}
	
	return info;
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
			int numActivities = 0;
			container = readActivitiesFromFile(DEFAULT_ACTIVITIES_FILE, &numActivities);
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

int handleMainMenu(ActivitiesContainer container) {
	displayMainMenu();
	int choice = getChoice(6);
	
	switch (choice) {
		case 0: {
			int isConfirmed = getConfirmMenuChoice("I dati non salvati verranno persi.");
			if (isConfirmed == 1) {
				printf("Uscita in corso...\n");
				deleteActivityContainer(container);
				return -1;
			}
			break;
		}

		case 1: {
			printActivities(container);
			break;
		}

		case 2: {
			//TODO
      }

		case 3:
			//TODO
			break;

		case 4:
			//TODO
			break;

		case 5:
			//TODO
			break;

		case 6: {
			int saveResult = saveActivitiesToFile(DEFAULT_ACTIVITIES_FILE, container);
			break;
		}

		default:
			printf("Scelta non gestita. Esco.\n");
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
			activities = NULL;
		}
	}
	
	//ActivitiesContainer activities = buildActivities();
	//printActivities(activities);
	//deleteActivityContainer(activities);
}




