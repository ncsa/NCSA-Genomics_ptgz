#include <iostream>
#include <unistd.h>
#include <dirent.h>

void helpCheck(char *argv[]) {
	if (argv[1] == std::string("-h") || argv[1] == std::string("--help")) {
		std::cout << "\nptxv - Parallel Tar XZ by Ryan Chui (2017)\n" << std::endl;
		exit(0);
	}
}

void findAll(int *numFiles, const char *cwd) {
	DIR *dir;
	struct dirent *ent;

	// Check if cwd is a directory
	if ((dir = opendir(cwd)) != NULL) {
		// Get all file paths within directory.
		while ((ent = readdir (dir)) != NULL) {
			std::string fileBuff = std::string(ent -> d_name);
			if (fileBuff != "." && fileBuff != "..") {
				DIR *dir2;
				std::string filePath = std::string(cwd) + "/" + fileBuff;
				// Check if file path is a directory.
				if ((dir2 = opendir(filePath.c_str())) != NULL) {
					closedir(dir2);
					findAll(numFiles, filePath.c_str());
				} else {
					*numFiles += 1;
				}
			}
		}
	}
}

char cwd [PATH_MAX];

int main(int argc, char *argv[]) {
	int *numFiles = new int(0);
	
	if (argc > 1) {
		helpCheck(argv);
	}
	getcwd(cwd, PATH_MAX);
	std::cout << cwd << std::endl;
	findAll(numFiles, cwd);
	
	delete(numFiles);
	return 0;
}
