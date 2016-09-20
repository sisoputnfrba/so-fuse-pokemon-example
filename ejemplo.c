/*
 * ejemplo.c
 *
 *  Created on: 26/08/2016
 *      Author: utnso
 */

#include <stdio.h>
#include <fuse.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int* pmap_pikachu;
int* pmap_squirtle;
int* pmap_bulbasaur;
struct stat pikachuStat;
struct stat squirtleStat;
struct stat bulbasaurStat;

static int ejemplo_getattr(const char *path, struct stat *stbuf) {
	int res = 0;
	memset(stbuf, 0, sizeof(struct stat));

	if (strcmp(path, "/") == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	} else if (strcmp(path, "/pikachu") == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	} else if (strcmp(path, "/squirtle") == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	} else if (strcmp(path, "/bulbasaur") == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	} else if (strcmp(path, "/pokemon.txt") == 0) {
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = 144;
	} else if (strcmp(path, "/pikachu/pika-chu.mp4") == 0) {
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = pikachuStat.st_size;
	} else if (strcmp(path, "/squirtle/vamo a calmarno.jpg") == 0) {
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = squirtleStat.st_size;
	} else if (strcmp(path, "/bulbasaur/bulbasaur.mp3") == 0) {
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = bulbasaurStat.st_size;
	}  else if (strcmp(path, "/pepito.txt") == 0) {
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = 5;
	} else {
		res = -ENOENT;
	}

	return res;
}

static int ejemplo_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		off_t offset, struct fuse_file_info *fi) {

	int res = 0;

	if (strcmp(path, "/") == 0) {
		filler(buf, "pikachu", NULL, 0);
		filler(buf, "squirtle", NULL, 0);
		filler(buf, "bulbasaur", NULL, 0);
		filler(buf, "pokemon.txt", NULL, 0);
		filler(buf, "pepito.txt", NULL, 0);
	} else if (strcmp(path, "/pikachu") == 0) {
		filler(buf, "pika-chu.mp4", NULL, 0);
	} else if (strcmp(path, "/squirtle") == 0) {
		filler(buf, "vamo a calmarno.jpg", NULL, 0);
	} else if (strcmp(path, "/bulbasaur") == 0) {
		filler(buf, "bulbasaur.mp3", NULL, 0);
	} else {
		res = -ENOENT;
	}

	return res;
}


static int ejemplo_read(const char *path, char *buf, size_t size, off_t offset,
		struct fuse_file_info *fi) {

	if (strcmp(path, "/pikachu/pika-chu.mp4") == 0) {
		memcpy(buf,((char*)pmap_pikachu + offset),size);
	} else if (strcmp(path, "/squirtle/vamo a calmarno.jpg") == 0) {
		memcpy(buf,((char*)pmap_squirtle + offset),size);
	} else if (strcmp(path, "/bulbasaur/bulbasaur.mp3") == 0) {
		memcpy(buf,((char*)pmap_bulbasaur + offset),size);
	} else if (strcmp(path, "/pokemon.txt") == 0) {
		memcpy(buf,"Los pokemon son una clase de criaturas (monstruos) basadas en muchos casos en animales reales o criaturas míticas y mitológicas orientales.\n",size);
	} else if (strcmp(path, "/pepito.txt") == 0) {
		memcpy(buf,"Hola\n",size);
	}
	return size;
}

static struct fuse_operations ejemplo_oper = {
		.getattr = ejemplo_getattr,
		.readdir = ejemplo_readdir,
		.read = ejemplo_read,
};


int main(int argc, char *argv[]) {

	//pikachu
	int fd_pikachu;
	fd_pikachu= open("/home/utnso/fuse_pokemon/pika-chu.mp4",O_RDWR);
	fstat(fd_pikachu,&pikachuStat);
	pmap_pikachu= mmap(0, pikachuStat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_pikachu, 0);

	//squirtle
	int fd_squirtle;
	fd_squirtle= open("/home/utnso/fuse_pokemon/vamo a calmarno.jpg",O_RDWR);
	fstat(fd_squirtle,&squirtleStat);
	pmap_squirtle= mmap(0, squirtleStat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_squirtle, 0);

	//bulbasaur
	int fd_bulbasaur;
	fd_bulbasaur= open("/home/utnso/fuse_pokemon/bulbasaur.mp3",O_RDWR);
	fstat(fd_bulbasaur,&bulbasaurStat);
	pmap_bulbasaur= mmap(0, bulbasaurStat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_bulbasaur, 0);

	return fuse_main(argc, argv, &ejemplo_oper, NULL );

}

