#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include "valcapt.h"

#define LENEVAL    15
#define LENNOMB    20
#define LENAPEL    10
#define LENCODGRP  20
#define LENID       9
#define LENHOR     30
#define MAXGRP     10
#define MAXEVAL    10
#define DEFSTRLEN  100
typedef struct {
	 char eval[LENEVAL];
	 float valor;
} EVAL;

typedef struct {
	 char id[LENID], nombre[LENNOMB], apellido[LENAPEL];
} ALUMNO;

typedef struct {
	 char codgrupo[LENCODGRP];
	 EVAL evals[MAXEVAL];
	 int canteval;
} EVALGRP;


typedef struct {
	 ALUMNO alumno;
	 char codgrupo[LENCODGRP];
	 EVAL evalalumno[MAXEVAL];
} GRPALUMNO;

void printEvalGrp(EVALGRP grupo, int size) {
	printf("\nCodigo del grupo: %s\n", grupo.codgrupo);
	for (int x = 0; x < size; x++) {
		printf("\n| %s: %.2f |\n", grupo.evals[x].eval, grupo.evals[x].valor);
	}
}

char loopExitVerification(char *question) {
	char resp;
	while (1) {
		system("cls");
		printf("%s", question);
		resp = getch();
		if (resp == 'y')
			return 'p';
		if (resp == 'n')
			return 'c';
	}
}

EVALGRP assignEval() {
	EVALGRP customEvalGrp;
	char resp;
	int size = 11;
	while (1) {
		fflush(0);
		size = getNum("cuantas evaluaciones desea?\n", 0, 2);
		while (1) {
			fflush(0);
			size = getNum("Solo se permite 10 evaluaciones! Introduzca otro numero.\n", 0, 2);
			if (size <= 10) {
				break;
			}
		}

		while (1) {
			system("cls");
			printf("Esta seguro que desea %d evaluaciones? y/n", size);
			resp = getch();
			if (resp == 'y') {
				resp = 'p';
				break;
			}
			if (resp == 'n') {
				break;
			}
		}
		if (resp == 'p') {
			break;
		}
	}
	float totalGrade = 100;
	char eval[LENEVAL];
	system("cls");
	printf("\nse esta evaluando en base a 100, tener esto en cuenta cuando inserte evaluaciones.\n");
	customEvalGrp.canteval = size;
	for (int x = 0; x < size; x++) {
		getString("Dame el nombre de la evaluacion: ", customEvalGrp.evals[x].eval, LENEVAL);
		customEvalGrp.evals[x].valor = getNum("Dame el valor de la evaluacion: ", 2, 5);
		while (customEvalGrp.evals[x].valor > 100) {
			customEvalGrp.evals[x].valor = getNum("El valor no puede ser mayor que 100, dame este valor otra vez: ", 2,
															  5);
		}
		system("cls");
		printf("el formato de evaluacion actual es: \n");
		printEvalGrp(customEvalGrp, x + 1);
		while (1) {
			printf("desea conservar esta ultima evaluacion? y/n\n");
			resp = getch();
			if (resp == 'y') {
				break;
			}
			if (resp == 'n') {
				resp = 'c';
				break;
			}
		}
		if (resp == 'c') {
			x--;
			continue;
		}
		system("cls");
		totalGrade -= customEvalGrp.evals[x].valor;
		printf("Quedan %.2f puntos para usar, presione cualquier tecla para continuar\n", totalGrade);
		getch();
		fflush(0);
	}
	system("cls");
	return customEvalGrp;

}


GRPALUMNO insertAlumn(EVALGRP grpEval) {
	GRPALUMNO alumno;
	char resp, question[DEFSTRLEN];
	float calif;
	strcpy(alumno.codgrupo, grpEval.codgrupo);
	system("cls");
	while (1) {
		system("cls");
		getString("Dame el nombre de el estudiante: ", alumno.alumno.nombre, LENNOMB);
		sprintf(question, "Nombre selecionado: %s\n", alumno.alumno.nombre);
		resp = loopExitVerification(question);

		if (resp == 'p')
			break;
	}
	while (1) {
		system("cls");
		getString("Dame el apellido de el estudiante: ", alumno.alumno.apellido, LENNOMB);
		sprintf(question, "Apellido selecionado: %s\nPara el estudiante: %s\n", alumno.alumno.apellido,
				  alumno.alumno.nombre);
		resp = loopExitVerification(question);

		if (resp == 'p')
			break;
	}
	while (1) {
		system("cls");
		getString("Dame el ID de el estudiante: ", alumno.alumno.id, LENID);
		sprintf(question, "ID selecionado: %s\nPara el alumno: %s %s\n", alumno.alumno.id, alumno.alumno.nombre,
				  alumno.alumno.apellido);
		resp = loopExitVerification(question);
		if (resp == 'p')
			break;
	}
	for (int x = 0; x < grpEval.canteval; x++) {
		while (1) {
			system("cls");
			sprintf(question, "Cuanto saco el estudiante en la evaluacion: %s? (en base a 100)\n", grpEval.evals[x].eval);
			calif = getNum(question, 2, 5);
			while (calif > 100) {
				sprintf(question, "El estudiante no puede sacar mas de 100! dame la calification de %s otravez",
						  grpEval.evals[x].eval);

			}
			sprintf(question, "Estas seguro que %s saco %d en %s? y/n\n", alumno.alumno.nombre, calif,
					  grpEval.evals[x].eval);
			resp = loopExitVerification(question);
			strcpy(alumno.evalalumno[x].eval, grpEval.evals[x].eval);

			if (resp == 'p')
				break;
		}
	}
	return alumno;
}

int selectOpt() {
	int coords = 0;
	char resp;
	char options[DEFSTRLEN][DEFSTRLEN] =
			{
					{"Ingresar Clave"},
					{"Ingresar Est."},
					{"Listar Est."},
					{"Listar evals"},
					{"Eliminar Est."},
					{"Nota Min. y Max."},
					{"Sobre promedio"},
					{"listar probabilidad"},
					{"Salvar"},
					{"Salir"}
			};
	while (1) {

		for (int x = 0; x < 10; x++) {
			if (x == coords) {
				printf("\n>>>  %s\n", options[x]);
				continue;
			}
			printf("\n%s\n", options[x]);

		}

		resp = getch();
		system("cls");
		if ((resp == 119 | resp == 72) && coords > 0) {
			coords--;
			continue;
		}
		if ((resp == 115 | resp == 80) && coords < 10) {
			coords++;
			continue;
		}
		if (resp == 13) {
			return coords;
		}
	}
	//up 119 72
	//down 115 80
}
void nuevaClave(EVALGRP *grupoEval);
void saveEval(FILE evalFile, EVALGRP evalgrp);
int main() {
	int ind, exit = 0;
	char cwd[DEFSTRLEN];
	getcwd(cwd, sizeof(cwd));
	char *evalDir = malloc(sizeof(cwd) + sizeof("\\evalDir.bin"));
	char *alumnDir = malloc(sizeof (cwd) + sizeof ("\\alumnDir.bin"));
	strcpy(evalDir, cwd);
	strcat(evalDir, "\\evalDir.bin");
	strcpy(alumnDir, cwd);
	strcat(alumnDir, "\\alumnDir.bin");

	EVALGRP currEval;

	FILE *groupEvalFile;
	FILE *groupAlumnFile;
	if ((groupEvalFile = fopen(evalDir, "rb+")) == NULL) {
		strcpy(currEval.codgrupo,"undefined");
		currEval.evals[0].valor=20;
		strcpy(currEval.evals[0].eval,"parcial_1");
		currEval.evals[1].valor=30;
		strcpy(currEval.evals[1].eval,"parcial_2");
		currEval.evals[2].valor=25;
		strcpy(currEval.evals[0].eval,"examen_final");
		currEval.evals[3].valor=25;
		strcpy(currEval.evals[3].eval,"tareas");
		currEval.canteval=4;
		groupEvalFile = fopen(evalDir,"wb");
		fwrite(&currEval, sizeof(EVALGRP), 1, groupEvalFile);
		printf("too busy\n");
	}
	else
	{
		fread(&currEval,sizeof(EVALGRP),1,groupEvalFile);
	}
	if((groupAlumnFile = fopen(alumnDir,"rb")) == NULL){

	}

	while (!exit) {
		ind = selectOpt();

		switch (ind) {

			case 0:
				nuevaClave(&currEval);
				break;
			case 1:
				insertAlumn(currEval);
				break;
			case 3:
				printEvalGrp(currEval,currEval.canteval);
				break;
			case 8:
				printf("what");
				groupEvalFile = fopen(evalDir,"wb");
				fwrite(&currEval, sizeof (EVALGRP), 2,  groupEvalFile);

				break;
			case 9:
				exit = 1;
				break;

		}


	}

	return 0;
}
void saveEval(FILE evalFile, EVALGRP evalgrp)
{
}
void nuevaClave(EVALGRP *grupoEval)
{
	char resp,question[DEFSTRLEN];

	while(1)
	{
		fflush(0);
		strcpy(grupoEval->codgrupo," ");
		getString("Cual es el nuevo codigo de el grupo?",grupoEval->codgrupo,LENCODGRP);
		sprintf(question,"Estas seguro que el codigo es: %s? y/n",grupoEval->codgrupo);
		resp = loopExitVerification(question);
		if(resp == 'p')
			break;
	}
}