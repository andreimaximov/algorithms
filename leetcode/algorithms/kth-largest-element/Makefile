JAVA := java
JAVAC := javac
JAVACFLAGS := -Xlint:all

default: clean build run

build:
	$(JAVAC) $(JAVACFLAGS) Solution.java

clean:
	$(RM) Solution.class

run:
	$(JAVA) Solution 2
