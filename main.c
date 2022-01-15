#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct Data{

	unsigned short int version;
	unsigned short int drxVersion;
	char reservado0[4];
	double initCW;
	float azimuth;
	float elevation;
	unsigned short int idVolumen;
	unsigned short int idBarrido;
	unsigned short int idCnjunto;
	unsigned short int idGrupo;
	unsigned short int idPulso;
	char iniBarrido;
	char finBarrido;
	char finGrupo;
	char inhibido;
	unsigned short int validSamples;
	unsigned short int nroAdquisicion;
	char reservado1[2];
	unsigned int nroSecuencia;
	unsigned long int readTime_high;
	unsigned long int readTime_low;
	char reservado[64];

}Data;

void printData(Data *fileData,int cantStructs);

int main(){

	
	//Calculo el tamanio del archivo con sys/stat
	struct stat st;
	stat("rawdata/datos",&st);
	int size = st.st_size;
	int fd,cantidadStructs;
	

	//calculo la cantidad de estructuras
	cantidadStructs = size/sizeof(Data);

	//abro el archivo
	fd = open("rawdata/datos", O_RDWR, S_IRUSR | S_IWUSR);

	//lo mapeo en la memoria
	Data *fileData = mmap(0, size,  PROT_READ , MAP_SHARED,fd,0);
	
	//cierro el fd ya que no lo necesito porque lo mapie en memoria
	close(fd);

	//checkeo si hay algun error en el mapeo
	if (fileData == MAP_FAILED) {

	    perror("Error mmapping the file");
	    exit(EXIT_FAILURE);
    }

	
    //funcion que me imprime toda la informacion necesaria
	printData(fileData,cantidadStructs);

	//libero la memoria
	munmap (fileData, size);

	return 0;
}


void printData(Data *fileData,int cantStructs){

	int media = 0;

	printf("Punto 1:\nLos datos obtenidos del archivo son:\n\n");

	for(int i = 0 ; i < cantStructs ; i ++){

		media += fileData[i].validSamples;

		printf("version: %d\n", fileData[i].version);
		printf("drxVersion: %d\n", fileData[i].drxVersion);
		printf("reservado0: %s\n", fileData[i].reservado0);
		printf("initCW: %f\n", fileData[i].initCW);
		printf("azimuth: %f\n", fileData[i].azimuth);
		printf("elevation: %f\n", fileData[i].elevation);
		printf("idVolumen: %u\n", fileData[i].idVolumen);
		printf("idBarrido: %u\n", fileData[i].idBarrido);
		printf("idCnjunto: %u\n", fileData[i].idCnjunto);
		printf("idGrupo: %u\n", fileData[i].idGrupo);
		printf("idPulso: %u\n", fileData[i].idPulso);
		printf("iniBarrido: %d\n", fileData[i].iniBarrido);
		printf("finBarrido: %d\n", fileData[i].finBarrido);
		printf("finGrupo: %d\n", fileData[i].finGrupo);
		printf("inhibido: %d\n", fileData[i].inhibido);
		printf("validSamples: %u\n", fileData[i].validSamples);
		printf("nroAdquisicion: %u\n", fileData[i].nroAdquisicion);
		printf("reservado1: %s\n", fileData[i].reservado1);
		printf("nroSecuencia: %u\n", fileData[i].nroSecuencia);
		printf("readTime_high: %lu\n", fileData[i].readTime_high);
		printf("readTime_low: %lu\n", fileData[i].readTime_low);
		printf("reservado: %s\n", fileData[i].reservado);
		printf("----------------\n");

	}


	printf("Punto 2:\nLa cantidad de estructuras dentro del archivo es %d\n--------------------------------------------------\n", cantStructs);

	media = media/cantStructs;

	printf("Punto 3:\nLa media de validSamples es %d\n---------------------------------\n",media);
}