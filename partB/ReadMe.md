
To define the IP of the server go to the <others> folder in the <structs.h> file change the IP_ADRESS

The makefiles are in each individual folder and we implemented a <make clean> rule

If needed run commands:

in the space-high-score folder:
	protoc --cpp_out=. high_score.proto

in the game-server folder:
	protoc --c_out=. high_score.proto
