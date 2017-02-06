CC     = gcc
CFLAGS = -Wall -Wextra -g -pedantic-errors

julia_omp: main.o julia_omp.o savebmp.o color.o getparams.o
	$(CC) $(CFLAGS) -o $@ $?
run0: julia_omp
	./julia_omp 0 -0.4 0.6 -0.2 -0.1 1 1.1 1000 1000 1000 image.bmp
clean:
	@rm -rf $(OBJS) julia_acc_d julia_acc_s julia_omp *~ *.bak *.bmp

# CC=pgcc
# CFLAGS=-fast -acc -Minfo -ta=nvidia,cc13 −O2
# LDFLAGS=-acc -ta=nvidia,cc13
# CFLAGSOMP=-O2 -mp
# LDFLAGSOMP=-mp 

# OBJSACCD=main_acc_d.o julia_acc_d.o savebmp.o color.o getparams.o 
# OBJSACCS=main_acc_s.o julia_acc_s.o savebmp.o color.o getparams_acc_s.o
# EXECUTABLE=julia_acc_s
# all: julia_acc_d julia_acc_s julia_omp

# julia_acc_d : $(OBJSACCD)
# 	$(CC) $(LDFLAGS)  -o $@ $?

# julia_acc_s : $(OBJSACCS)
# 	$(CC) $(LDFLAGS)  -o $@ $?

# julia_omp: main_mp.o julia_omp.o savebmp.o color.o getparams.o
# 	$(CC) $(LDFLAGSOMP) -o $@ $?
# run0: julia_omp
# 	./julia_omp 0 -0.4 0.6 -0.2 -0.1 1 1.1 1000 1000 1000 image.bmp
# run1: julia_acc_s
# 	./julia_acc_s 0 -0.4 0.6 -0.2 -0.1 1 1.1 1000 1000 1000 image.bmp
# run2: julia_acc_d
# 	./julia_acc_d 0 -0.4 0.6 -0.2 -0.1 1 1.1 1000 1000 1000 image.bmp image.bmp
# clean:
# 	@rm -rf $(OBJS) julia_acc_d julia_acc_s julia_omp *~ *.bak *.bmp
