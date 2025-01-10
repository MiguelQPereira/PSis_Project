# Makefile for space-high-score

CC = g++
CFLAGS = -std=c++17
LDFLAGS = -lzmq -lncurses -lprotobuf

all: space-high-score


space-high-score: space-high-score.cpp high_score.pb.cc high_score.pb.h
	$(CC) $(CFLAGS) -o space-high-score space-high-score.cpp high_score.pb.cc $(LDFLAGS)

clean:
	rm -f *.o core space-high-score *~
