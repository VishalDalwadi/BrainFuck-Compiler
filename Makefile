OUT = bfc
CC = gcc
CFLAGS = -Wall -g
ODIR = bin
SDIR = src
IDIR = include

$(OUT): $(ODIR)/main.o $(ODIR)/stack.o $(ODIR)/vector.o
	$(CC) $(CFLAGS) $(ODIR)/main.o $(ODIR)/vector.o $(ODIR)/stack.o -o $(ODIR)/$(OUT)

$(ODIR)/main.o: $(SDIR)/main.c $(IDIR)/stack.h $(IDIR)/vector.h
	$(CC) $(CFLAGS) -c $(SDIR)/main.c -I$(IDIR) -o $(ODIR)/main.o

$(ODIR)/stack.o: $(SDIR)/stack.c $(IDIR)/stack.h $(IDIR)/vector.h
	$(CC) $(CFLAGS) -c $(SDIR)/stack.c -I$(IDIR) -o $(ODIR)/stack.o

$(ODIR)/vector.o: $(SDIR)/vector.c $(IDIR)/vector.h
	$(CC) $(CFLAGS) -c $(SDIR)/vector.c -I$(IDIR) -o $(ODIR)/vector.o

install:
	mv $(ODIR)/$(OUT) /usr/bin

clean:
	rm -f $(ODIR)/*.o

clean_all:
	rm -f $(ODIR)/*
