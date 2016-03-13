CC ?= gcc

CFLAGS += -g -I./src
          
LDFLAGS += -lm -lGLU -lGL -lglut

OBJS = src/matrix.o \
       test/objrotate.o
       
HEADERS = 
       
TARGETS = objrotate

all: $(TARGETS)

clean:
	-$(RM) $(OBJS) $(TARGETS)

objrotate: $(OBJS) $(HEADERS)
	$(CC) -o objrotate $(OBJS) $(LDFLAGS)

$(OBJS): %.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<
