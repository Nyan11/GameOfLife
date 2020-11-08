TARGET_EXEC ?= prog

SRCS := $(shell find -name *.c)
OBJS := $(SRCS:./%.c=%.o)

DEPS = conway.h

CC ?= gcc
CFLAGS ?= -w -Wall -Werror

$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

# c source
%.o: %.c $(DEPS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o $(TARGET_EXEC)
